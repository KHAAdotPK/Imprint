/*
    lib/src/Cleaner.hh
    Q@hackers.pk
 */

#ifndef IMPRINT_LIB_SRC_CLEANER_HH
#define IMPRINT_LIB_SRC_CLEANER_HH

class Cleaner
{
    public:
        std::string cleanLine(const std::string& line)
        {
            std::string cleaned;
            cleaned.reserve(line.size());

            size_t i = 0;
            while (i < line.size())
            {
                char32_t codepoint = 0;
                size_t   seqLen    = 0;

                // Decode one UTF-8 sequence into a char32_t codepoint
                unsigned char byte = static_cast<unsigned char>(line[i]);

                if (byte < 0x80)                          // 1-byte (ASCII)
                {
                    codepoint = byte;
                    seqLen    = 1;
                }
                else if ((byte & 0xE0) == 0xC0)           // 2-byte sequence
                {
                    codepoint = byte & 0x1F;
                    seqLen    = 2;
                }
                else if ((byte & 0xF0) == 0xE0)           // 3-byte sequence
                {
                    codepoint = byte & 0x0F;
                    seqLen    = 3;
                }
                else if ((byte & 0xF8) == 0xF0)           // 4-byte sequence
                {
                    codepoint = byte & 0x07;
                    seqLen    = 4;
                }
                else                                      // Invalid byte — skip
                {
                    ++i;
                    continue;
                }

                // Accumulate continuation bytes
                for (size_t k = 1; k < seqLen && (i + k) < line.size(); ++k)
                {
                    codepoint = (codepoint << 6) | (static_cast<unsigned char>(line[i + k]) & 0x3F);
                }

                // Check codepoint against ALL_PUNCTUATION
                bool isPunct = false;
                for (size_t p = 0; p < EnglishPunctuation::NUM_PUNCTUATION_SYMBOLS; ++p)
                {
                    if (codepoint == EnglishPunctuation::ALL_PUNCTUATION[p])
                    {
                        isPunct = true;
                        break;
                    }
                }

                // Keep the original bytes only if not punctuation
                if (!isPunct)
                {
                    cleaned.append(line, i, seqLen);
                }

                i += seqLen;
            }

            return cleaned;
        }
};

#endif // IMPRINT_LIB_SRC_CLEANER_HH