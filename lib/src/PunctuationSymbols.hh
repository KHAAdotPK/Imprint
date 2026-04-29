/* 
    lib/src/PunctuationSymbols.hh 
    Q@hackers.pk
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
constexpr char32_t SOLIDUS              = U'\u002F'; // /
constexpr char32_t COLON                = U'\u003A'; // :
constexpr char32_t SEMICOLON            = U'\u003B'; // ;
constexpr char32_t LESS_THAN_SIGN       = U'\u003C'; // 
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

} // namespace EnglishPunctuation

#endif // IMPRINT_SRC_PUNCTUATION_SYMBOLS_HH