# Imprint

A lightweight, header-only C++ library for cleaning and normalizing English text.  
For normalizing the urdu text use [Naqsh](https://github.com/KHAAdotPK/naqsh.git).

---

## Overview

**Imprint** strips punctuation and noise characters from English text using a Unicode-aware (`char32_t`) approach. It decodes UTF-8 input, checks each codepoint against a predefined punctuation table, and returns a clean `std::string` — all in a single method call.

It is designed to be used as an **optional dependency of the [Parser](https://github.com/KHAAdotPK/Parser.git) package**. When included before Parser and paired with the right compile-time macros, it transparently hooks into Parser's `Iterator` to clean each line before tokenization. Parser itself has zero knowledge of Imprint — the integration is entirely macro-driven.

---

## Project Structure

```
lib/ # This is the project root's lib folder
├── Imprint/  
│   ├── header.hh               # Umbrella include — include this in your project
│   └── lib/src
│       ├── PunctuationSymbols.hh   # char32_t constants + ALL_PUNCTUATION array
│       └── Cleaner.hh              # Cleaner class with cleanLine() method
├── Parser/
```

---

## How It Integrates with Parser

Inside Parser's `Iterator.hh`, the cleaning step is guarded by a preprocessor macro:

```cpp
#ifdef ITERATOR_USER_DEFINED_CLEANER_CODE
    Cleaner cleaner;
#endif

if (std::getline(*_stream, line))
{
#ifdef ITERATOR_USER_DEFINED_CLEANER_CODE
    line = cleaner.cleanLine(line);
#endif
    // ... tokenize line ...
}
```

For `Cleaner` to be in scope when `Iterator.hh` compiles, **Imprint must be included before Parser** in your entry point. The macro must also be defined before either header is pulled in.

The correct include order is:

```cpp
// In your main.hh or entry point

#define ITERATOR_USER_DEFINED_CLEANER_CODE   // activates cleaning in Iterator

#include "../lib/Imprint/header.hh"          // brings Cleaner into scope
#include "../lib/Parser/header.hh"           // Iterator now sees Cleaner
```

If `ITERATOR_USER_DEFINED_CLEANER_CODE` is not defined, Parser works as normal and imprint is never referenced — there is no overhead or side effect.

---

## Full Usage Example

The following is a realistic `main.hh` setup showing imprint alongside the other packages in the toolchain:

```cpp
#include <iostream>

// Set token delimiter to space (default is comma)
#ifdef CSV_PARSER_TOKEN_DELIMITER
#undef CSV_PARSER_TOKEN_DELIMITER
#endif
#define CSV_PARSER_TOKEN_DELIMITER ' '

// Skip empty tokens (safe for hash-based indexing)
#ifndef ITERATOR_GUARD_AGAINST_EMPTY_STRING
#define ITERATOR_GUARD_AGAINST_EMPTY_STRING
#endif

// Activate imprint's Cleaner inside Parser's Iterator
#ifndef ITERATOR_USER_DEFINED_CLEANER_CODE
#define ITERATOR_USER_DEFINED_CLEANER_CODE
#endif

// Include order matters — imprint before Parser
#include "../lib/Numcy/header.hh"
#include "../lib/Hash/header.hh"
#include "../lib/Imprint/header.hh"   // Cleaner must be in scope before Parser
#include "../lib/Parser/header.hh"
```

With this setup, every line read by Parser's `Iterator` is passed through `Cleaner::cleanLine()` before being split into tokens.

---

## Compile-Time Macros

| Macro | Package | Effect |
|---|---|---|
| `ITERATOR_USER_DEFINED_CLEANER_CODE` | Parser / imprint | Activates `Cleaner::cleanLine()` inside `Iterator::read_next()` |
| `CSV_PARSER_TOKEN_DELIMITER` | Parser | Sets the token delimiter character (default: `,`) |
| `ITERATOR_GUARD_AGAINST_EMPTY_STRING` | Parser | Skips empty tokens after splitting |

---

## How It Works

### `PunctuationSymbols.hh`

Defines all punctuation constants inside the `EnglishPunctuation` namespace as `char32_t` codepoints, grouped by category:

| Group | Examples |
|---|---|
| Basic Latin punctuation | `! " # $ % & ' ( ) * + , - . / : ; < = > ? @` |
| Brackets and braces | `[ \ ] ^ _ ` { \| } ~` |
| Whitespace / control noise | `\r  \n  \t` |
| Typographic quotes | `' ' " " « »` |
| Dashes and ellipsis | `– — …` |

All constants are collected into a single flat array:

```cpp
constexpr char32_t ALL_PUNCTUATION[] = { ... };
constexpr size_t   NUM_PUNCTUATION_SYMBOLS = sizeof(ALL_PUNCTUATION) / sizeof(ALL_PUNCTUATION[0]);
```

### `Cleaner.hh`

The `Cleaner` class exposes one method:

```cpp
std::string cleanLine(const std::string& line);
```

Internally it:

1. Walks the input string byte by byte
2. Decodes each UTF-8 sequence into a `char32_t` codepoint (1–4 byte sequences)
3. Checks the codepoint against `EnglishPunctuation::ALL_PUNCTUATION`
4. Appends the original bytes to the output only if the codepoint is **not** in the punctuation table
5. Silently skips malformed UTF-8 bytes

The output is a valid UTF-8 `std::string` with all listed punctuation removed.

---

## Design Decisions

- **Header-only** — no build system required, just include and compile
- **Optional by design** — zero coupling with Parser; activation is entirely macro-driven
- **Include-order integration** — imprint just needs to be included before Parser so `Cleaner` is in scope when `Iterator.hh` compiles
- **Unicode-aware** — uses `char32_t` internally so typographic and multi-byte symbols (`…`, `"`, `–`) are handled correctly alongside ASCII
- **No dependencies** — only `<string>` and `<cstddef>` from the standard library
- **Single responsibility** — `Cleaner` does one thing; symbol definitions live separately in `PunctuationSymbols.hh`

---

## Extending the Symbol Table

To add or remove a punctuation symbol, edit `PunctuationSymbols.hh`:

1. Add a named `constexpr char32_t` constant under the appropriate group comment
2. Add it to the `ALL_PUNCTUATION[]` array

`NUM_PUNCTUATION_SYMBOLS` updates automatically via `sizeof`.

---

## Related Packages

| Package | Role |
|---|---|
| [Parser](https://github.com/KHAAdotPK/Parser.git) | CSV / text file iterator that imprint plugs into |
| [naqsh](https://github.com/KHAAdotPK/naqsh.git) | Urdu text normalization — imprint is its English counterpart |

---

## License

This project is governed by a license, the details of which can be located in the accompanying file named 'LICENSE.' Please refer to this file for comprehensive information.
