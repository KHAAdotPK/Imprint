/*
    lib/src/Cleaner.hh
    
    It decodes UTF‑8 sequences, checks each codepoint against a list of
    punctuation symbols, and keeps only non‑punctuation codepoints.

    Maintainer: Sohail
 */

#ifndef IMPRINT_LIB_SRC_CLEANER_HH
#define IMPRINT_LIB_SRC_CLEANER_HH

/*
    A quick UTF-8 refresher
    -----------------------
    In UTF-8, not all bytes are the same. They fall into two categories:
    1. Leading Bytes: These bytes indicate the start of a new character (codepoint).
       They determine how many bytes are used for that character.
       - 0xxxxxxx : 1-byte character (ASCII)
       - 110xxxxx : 2-byte character
       - 1110xxxx : 3-byte character
       - 11110xxx : 4-byte character
    2. Continuation Bytes: These bytes are part of a multi-byte character.
       They always start with the bits 10xxxxxx.

    For example, the character (Latin small e with acute) 'é' is represented in UTF-8 as two bytes: 0xC3 0xA9.
    . 0xC3 is the leading byte (says "2 bytes total")
    . 0xA9 is the continuation byte (says "this is part of the previous character")

    When decoding UTF-8, you must read the leading byte to know how many continuation bytes to expect. 
 */

class Cleaner
{
    public:
        // Cleans a line of text by removing English punctuation characters.
        // It decodes UTF‑8 sequences, checks each codepoint against a list of
        // punctuation symbols, and keeps only non‑punctuation codepoints.
        // Returns a new string with punctuation removed.
        std::string cleanLine(const std::string& line) const
        {
            std::string cleaned; // Result buffer
            cleaned.reserve(line.size()); // Pre-allocate to avoid reallocations
            
            bool is_preceeded_by_numeric_character = false;    // True if the previous character was a digit.
            bool is_preceeded_by_alphabetic_character = false; // True if the previous character was an alphabet.
        
            size_t i = 0; // Index into the input line
            while (i < line.size())
            {
                char32_t codepoint = 0; // Unicode codepoint (UTF‑32)
                size_t   seqLen    = 0; // Number of bytes in the UTF‑8 sequence

                // Decode one UTF-8 sequence into a char32_t codepoint
                unsigned char byte = static_cast<unsigned char>(line[i]);

                // Read the leading byte to know how many continuation bytes to expect

                if (byte < 0x80)                          // 1-byte (ASCII), no continuation bytes
                {
                    codepoint = byte;                     // ASCII codepoint is the same as the byte value  
                    seqLen    = 1;
                }
                else if ((byte & 0xE0) == 0xC0)           // 2-byte sequence, the number of continuation bytes is 1
                {
                    codepoint = byte & 0x1F;              // Start forming UTF8 codepoint by extracting lower 5 bits 
                    seqLen    = 2;
                }
                else if ((byte & 0xF0) == 0xE0)           // 3-byte sequence, the number of continuation bytes is 2
                {
                    codepoint = byte & 0x0F;              // Start forming UTF8 codepoint by extracting lower 4 bits
                    seqLen    = 3;
                }
                else if ((byte & 0xF8) == 0xF0)           // 4-byte sequence, the number of continuation bytes is 3
                {
                    codepoint = byte & 0x07;              // Start forming UTF8 codepoint by extracting lower 3 bits
                    seqLen    = 4;
                }
                else                                      // Invalid byte — skip
                {
                    ++i;
                    continue;
                }

                // ----- Accumulate continuation bytes with validation -----
                bool valid = true;

                // Check that we have enough bytes left in the string
                if (i + seqLen > line.size())
                {
                    // Not enough bytes: treat as invalid, skip the leading byte. The seqlen will be reassigned                    
                    ++i;
                    continue;
                }
                
                // Accumulate continuation bytes with validation, that is why we start from k = 1 
                // The codepoint already has lower 3 to 5 bits of the leading byte which is at at k = 0
                for (size_t k = 1; k < seqLen; ++k)
                {
                    unsigned char cont = static_cast<unsigned char>(line[i + k]); // Continution byte, extract least significant 6 bits 
                    
                    /*
                        Continuation byte MUST start with bits 10xxxxxx
                        -----------------------------------------------
                        What if input string is corrupted or not perfectly valid UTF-8? For example, imagine this byte sequence:
                        0xC2 0x41
                        . 0xC2 is a leading byte for a 2-byte sequence (expects a continuation byte next).
                        . But 0x41 is the letter 'A' — it's an ASCII byte. In binary, 0x41 is 01000001. It does not start with 10 — it starts with 01.

                        If code does not check this. It blindly treats 0x41 as if it were a continuation byte. It calculates:
                        codepoint = (0xC2 & 0x1F) << 6 | (0x41 & 0x3F)
                                  = (0x02) << 6 | (0x01)
                                  = 0x80 | 0x01
                                  = 0x81
                        So without the check which follow, the 2-byte sequence represents the Unicode codepoint U+0081 (a control character).
                        But the original bytes were total garbage — they didn't represent any real character at all.
                     */                    
                    if ((cont & 0xC0) != 0x80)
                    {
                        valid = false;
                        break;   // invalid sequence – abort processing
                    }

                    // Extract the lower 6 bits and add to the codepoint
                    codepoint = (codepoint << 6) | (cont & 0x3F);

                    // At max we can 24 bits for codepoint, so we can check if the codepoint is valid                    
                }
                                
                if (!valid)
                {
                    // Malformed sequence: skip only the leading byte and retry
                    // (the invalid continuation byte will be handled in the next iteration)
                    ++i;
                    continue;
                }
                
                // Check the decoded codepoint against the list of all punctuation symbols.
                // EnglishPunctuation must be a namespace/class with a static array ALL_PUNCTUATION
                // and a constant NUM_PUNCTUATION_SYMBOLS. This dependency is not shown here.
                bool isPunct = false;
                for (size_t p = 0; p < EnglishPunctuation::NUM_PUNCTUATION_SYMBOLS; ++p)
                {
                    if (codepoint == EnglishPunctuation::ALL_PUNCTUATION[p])
                    {                    
                        isPunct = true;
                        break;
                    }
                    else
                    {
                        // See if it is Numeric character
                        if (codepoint >= U'0' && codepoint <= U'9')
                        {
                            is_preceeded_by_numeric_character = true;
                            is_preceeded_by_alphabetic_character = false;
                        }
                        else if ((codepoint >= U'A' && codepoint <= U'Z') || (codepoint >= U'a' && codepoint <= U'z')) 
                        {                               
                            is_preceeded_by_alphabetic_character = true;
                            is_preceeded_by_numeric_character = false;
                        }
                    }
                }
                
                // Keep the original bytes only if the codepoint is NOT punctuation.
                // This appends the exact sequence of bytes from the input (no re‑encoding).
                if (!isPunct)
                {
                    cleaned.append(line, i, seqLen);                                        
                }
                else // What kind of replacement should we do for punctuation ?
                {
                    // When it is EM_DASH we should replace it with space.
                    // This EM_DASH should be preeceded by a character and followed by a character.
                    // If this condition is met, we should replace EM_DASH with space.
                    // Otherwise, we should replace EM_DASH with empty string.
                    if (codepoint == EnglishPunctuation::EM_DASH)
                    {
                        if (is_preceeded_by_alphabetic_character)
                        {
                            is_preceeded_by_alphabetic_character = false;
                            cleaned.append(" ", 1);                            
                        }                                                
                    }
                    else if (codepoint == EnglishPunctuation::EN_DASH)
                    {
                        if (is_preceeded_by_alphabetic_character)
                        {
                            is_preceeded_by_alphabetic_character = false;
                            cleaned.append(" ", 1);                            
                        }                                  
                    }
                    else if (codepoint == EnglishPunctuation::HYPHEN_MINUS)
                    {
                        if (is_preceeded_by_alphabetic_character)
                        {
                            is_preceeded_by_alphabetic_character = false;
                            cleaned.append(" ", 1);                            
                        }                                  
                    }
                    else if (codepoint == EnglishPunctuation::FULL_STOP)
                    {
                        if (is_preceeded_by_numeric_character)
                        {
                            is_preceeded_by_numeric_character = false;
                            cleaned.append(line, i, seqLen); 
                        }                                  
                    }
                    else if (codepoint == EnglishPunctuation::PERCENT_SIGN)
                    {
                        if (is_preceeded_by_numeric_character)
                        {
                            is_preceeded_by_numeric_character = false;
                            cleaned.append(line, i, seqLen); 
                        }
                    }
                }

                i += seqLen; // Move to the next UTF‑8 sequence
            }

            return cleaned;
        }
};

#endif // IMPRINT_LIB_SRC_CLEANER_HH