/* 
    lib/src/PunctuationSymbols.hh 
    
    This file contains the list of punctuation symbols that are used by the 
    Cleaner class to perform cleaning operations.

    Maintainer: Sohail
 */

#ifndef IMPRINT_SRC_PUNCTUATION_SYMBOLS_HH
#define IMPRINT_SRC_PUNCTUATION_SYMBOLS_HH

namespace EnglishPunctuation
{

// ==================== 1. Basic Latin Punctuation ====================
constexpr char32_t EXCLAMATION_MARK     = U'\u0021'; // !
constexpr char32_t QUOTATION_MARK       = U'\u0022'; // "
constexpr char32_t NUMBER_SIGN          = U'\u0023'; // #
constexpr char32_t DOLLAR_SIGN          = U'\u0024'; // $
constexpr char32_t PERCENT_SIGN         = U'\u0025'; // %
constexpr char32_t AMPERSAND            = U'\u0026'; // &
constexpr char32_t APOSTROPHE           = U'\u0027'; // '
constexpr char32_t LEFT_PARENTHESIS     = U'\u0028'; // (
constexpr char32_t RIGHT_PARENTHESIS    = U'\u0029'; // )
constexpr char32_t ASTERISK             = U'\u002A'; // *
constexpr char32_t PLUS_SIGN            = U'\u002B'; // +
constexpr char32_t COMMA                = U'\u002C'; // ,
constexpr char32_t HYPHEN_MINUS         = U'\u002D'; // -
constexpr char32_t FULL_STOP            = U'\u002E'; // .
//constexpr char32_t RADIX                = U''
constexpr char32_t SOLIDUS              = U'\u002F'; // /
constexpr char32_t COLON                = U'\u003A'; // :
constexpr char32_t SEMICOLON            = U'\u003B'; // ;
constexpr char32_t LESS_THAN_SIGN       = U'\u003C'; // <
constexpr char32_t EQUALS_SIGN          = U'\u003D'; // =
constexpr char32_t GREATER_THAN_SIGN    = U'\u003E'; // >
constexpr char32_t QUESTION_MARK        = U'\u003F'; // ?
constexpr char32_t AT_SIGN              = U'\u0040'; // @

// ==================== 2. Brackets and Braces ====================
constexpr char32_t LEFT_SQUARE_BRACKET  = U'\u005B'; // [
constexpr char32_t BACKSLASH            = U'\u005C'; // '\'
constexpr char32_t RIGHT_SQUARE_BRACKET = U'\u005D'; // ]
constexpr char32_t CARET                = U'\u005E'; // ^
constexpr char32_t UNDERSCORE           = U'\u005F'; // _
constexpr char32_t GRAVE_ACCENT         = U'\u0060'; // `
constexpr char32_t LEFT_CURLY_BRACE     = U'\u007B'; // {
constexpr char32_t VERTICAL_BAR         = U'\u007C'; // |
constexpr char32_t RIGHT_CURLY_BRACE    = U'\u007D'; // }
constexpr char32_t TILDE                = U'\u007E'; // ~

// ==================== 3. Whitespace / Control noise ====================
constexpr char32_t CARRIAGE_RETURN      = U'\u000D'; // \r
constexpr char32_t LINE_FEED            = U'\u000A'; // \n
constexpr char32_t HORIZONTAL_TAB       = U'\u0009'; // \t

// ==================== 4. Curly / Typographic Quotes ====================
constexpr char32_t LEFT_SINGLE_QUOTE    = U'\u2018'; // '
constexpr char32_t RIGHT_SINGLE_QUOTE   = U'\u2019'; // '
constexpr char32_t LEFT_DOUBLE_QUOTE    = U'\u201C'; // "
constexpr char32_t RIGHT_DOUBLE_QUOTE   = U'\u201D'; // "
constexpr char32_t LEFT_ANGLE_QUOTE     = U'\u00AB'; // «
constexpr char32_t RIGHT_ANGLE_QUOTE    = U'\u00BB'; // »

// ==================== 5. Dashes and Ellipsis ====================
constexpr char32_t EN_DASH              = U'\u2013'; // –
constexpr char32_t EM_DASH              = U'\u2014'; // —
constexpr char32_t ELLIPSIS             = U'\u2026'; // …

// ==================== All punctuation to strip ====================
constexpr char32_t ALL_PUNCTUATION[] = {
    EXCLAMATION_MARK,
    QUOTATION_MARK,
    NUMBER_SIGN,
    DOLLAR_SIGN,
    PERCENT_SIGN,
    AMPERSAND,
    APOSTROPHE,
    LEFT_PARENTHESIS,
    RIGHT_PARENTHESIS,
    ASTERISK,
    PLUS_SIGN,
    COMMA,
    HYPHEN_MINUS,
    FULL_STOP,
    SOLIDUS,
    COLON,
    SEMICOLON,
    LESS_THAN_SIGN,
    EQUALS_SIGN,
    GREATER_THAN_SIGN,
    QUESTION_MARK,
    AT_SIGN,
    LEFT_SQUARE_BRACKET,
    BACKSLASH,
    RIGHT_SQUARE_BRACKET,
    CARET,
    UNDERSCORE,
    GRAVE_ACCENT,
    LEFT_CURLY_BRACE,
    VERTICAL_BAR,
    RIGHT_CURLY_BRACE,
    TILDE,
    CARRIAGE_RETURN,
    LINE_FEED,
    HORIZONTAL_TAB,
    LEFT_SINGLE_QUOTE,
    RIGHT_SINGLE_QUOTE,
    LEFT_DOUBLE_QUOTE,
    RIGHT_DOUBLE_QUOTE,
    LEFT_ANGLE_QUOTE,
    RIGHT_ANGLE_QUOTE,
    EN_DASH,
    EM_DASH,
    ELLIPSIS,
};

constexpr size_t NUM_PUNCTUATION_SYMBOLS = sizeof(ALL_PUNCTUATION) / sizeof(ALL_PUNCTUATION[0]);

    // Check if a codepoint is punctuation
    bool isPunctuation(char32_t codepoint)
    {
        for (size_t i = 0; i < NUM_PUNCTUATION_SYMBOLS; ++i)
        {
            if (codepoint == ALL_PUNCTUATION[i])
                return true;
        }
        return false;
    }

} // namespace EnglishPunctuation

namespace NoiseAndCorruption
{
    // =================================================================
    // Characters to REMOVE/STRIP entirely before tokenization.
    // DO NOT add these to your EnglishPunctuation list.
    // =================================================================

    constexpr char32_t CORRUPTION_AND_NOISE[] = {

        // ------------- 1. Box-drawing & Block chars -------------
        // These NEVER appear in clean UTF-8 English text.
        // They are the #1 sign of reading UTF-8 bytes as Windows-1252 / Latin-1.
        U'\u2591', // ░
        U'\u2592', // ▒
        U'\u2593', // ▓
        U'\u2502', // │
        U'\u2562', // ╢
        U'\u2556', // ╖
        U'\u2555', // ╕
        U'\u2563', // ╣
        U'\u2551', // ║
        U'\u2557', // ╗
        U'\u255D', // ╝
        U'\u255C', // ╜
        U'\u2510', // ┐
        U'\u252C', // ┬
        U'\u251C', // ├
        U'\u2500', // ─
        U'\u253C', // ┼
        U'\u2560', // ╠
        U'\u256C', // ╬
        U'\u256A', // ╪
        U'\u2567', // ╧
        U'\u2553', // ╓
        U'\u256B', // ╫
        U'\u2580', // ▀
        U'\u2554', // ╔
        U'\u2559', // ╚
        U'\u2564', // ╦
        U'\u2569', // ╩

        // ------------- 2. Mojibake Latin-1 supplements -------------
        // In pure English NLP, these often appear when UTF-8 2-byte sequences
        // are misinterpreted. If you later support French/Spanish/German,
        // you may KEEP é, ü, ß, ñ, etc. But for your specific corrupted output,
        // they are garbage. I list them here; comment out the ones you wish to keep.
        U'\u00C7', // Ç
        U'\u00FC', // ü
        U'\u00E9', // é
        U'\u00E2', // â
        U'\u00E4', // ä
        U'\u00E7', // ç
        U'\u00EC', // ì
        U'\u00C4', // Ä
        U'\u00C9', // É
        U'\u00FB', // û
        U'\u00FF', // ÿ
        U'\u00D6', // Ö
        U'\u00ED', // í
        U'\u00F3', // ó
        U'\u00FA', // ú
        U'\u00F1', // ñ
        U'\u00D1', // Ñ
        U'\u00DF', // ß (German lowercase sharp S)
        U'\u1E9E', // ẞ (German uppercase sharp S)

        // ------------- 3. Fractions, Ordinals, and Rare Currency -------------
        U'\u00A3', // £ (remove unless you process finance)
        U'\u00A5', // ¥
        U'\u00BD', // ½
        U'\u00BC', // ¼
        U'\u00AA', // ª
        U'\u00BA', // º
        U'\u00A1', // ¡
        
        // ------------- 4. Greek / Mathematical symbols -------------
        U'\u0393', // Γ
        U'\u03A6', // Φ
        U'\u03B1', // α
        U'\u2229', // ∩

        // ------------- 5. Obscure control/symbols -------------
        U'\u2310', // ⌐
        U'\u00AC', // ¬

        // ------------- 6. ASCII control characters (U+0000–U+001F, except maybe \t, \n, \r which should be handle separately).-------------
        U'\u0000', // NUL
        U'\u0001', // SOH
        U'\u0002', // STX
        U'\u0003', // ETX
        U'\u0004', // EOT
        U'\u0005', // ENQ
        U'\u0006', // ACK
        U'\u0007', // BEL
        U'\u0008', // BS
        U'\u000B', // VT
        U'\u000C', // FF
        U'\u000E', // SO
        U'\u000F', // SI
        U'\u0010', // DLE
        U'\u0011', // DC1
        U'\u0012', // DC2
        U'\u0013', // DC3
        U'\u0014', // DC4
        U'\u0015', // NAK
        U'\u0016', // SYN
        U'\u0017', // ETB
        U'\u0018', // CAN
        U'\u0019', // EM
        U'\u001A', // SUB (Substitute character)
        U'\u001B', // ESC
        U'\u001C', // FS
        U'\u001D', // GS
        U'\u001E', // RS
        U'\u001F', // US 
    };

    constexpr size_t NUM_NOISE_SYMBOLS = sizeof(CORRUPTION_AND_NOISE) / sizeof(CORRUPTION_AND_NOISE[0]);

    // Check if a codepoint is noise
    bool isNoise(char32_t codepoint)
    {
        for (size_t i = 0; i < NUM_NOISE_SYMBOLS; ++i)
        {
            if (codepoint == CORRUPTION_AND_NOISE[i])
                return true;
        }
        return false;
    }

} // namespace NoiseAndCorruption

#endif // IMPRINT_SRC_PUNCTUATION_SYMBOLS_HH