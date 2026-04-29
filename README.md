# imprint

A lightweight, header-only C++ library for cleaning and normalizing English text.  

---

## Overview

**imprint** strips punctuation and noise characters from English text using a Unicode-aware (`char32_t`) approach. It decodes UTF-8 input, checks each codepoint against a predefined punctuation table, and returns a clean `std::string` — all in a single method call.

It is intentionally minimal: one class, one method, one flat array of symbols to filter.

---

## Project Structure

```
Imprint/
├──header.hh          # Umbrella include — include this in your project
└──lib/src/
    ├── PunctuationSymbols.hh   # char32_t constants + ALL_PUNCTUATION array
    └── Cleaner.hh              # Cleaner class with cleanLine() method
```

---

## Usage

Include the umbrella header:

```cpp
#include "lib/imprint/header.hh"
```

Then use the `Cleaner` class:

```cpp
Cleaner cleaner;

std::string raw  = "Hello, World! This is a test... \"quoted\" text.\n";
std::string clean = cleaner.cleanLine(raw);

// clean => "Hello World This is a test quoted text"
```

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
- **Unicode-aware** — uses `char32_t` internally so typographic and multi-byte symbols (e.g. `…`, `"`, `–`) are handled correctly alongside ASCII
- **No dependencies** — only `<string>` and `<cstddef>` from the standard library
- **Single responsibility** — `Cleaner` does one thing; symbol definitions live separately in `PunctuationSymbols.hh`

---

## Extending the Symbol Table

To add or remove a punctuation symbol, edit `PunctuationSymbols.hh`:

1. Add a named `constexpr char32_t` constant
2. Add it to the `ALL_PUNCTUATION[]` array

`NUM_PUNCTUATION_SYMBOLS` updates automatically via `sizeof`.

---

## License

This project is governed by a license, the details of which can be located in the accompanying file named 'LICENSE.'
