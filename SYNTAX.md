<div align=center>

# SYNTAX V0.1

This file defines the syntax of the **Kei Object Notation** (kon).

</div>

## 1. Overview

The **Kei Object Notation (kon)** language is designed to be:

- more expressive and type-safe than JSON
- easier to parse consistently than YAML
- readable, predictable, and simple to implement in any language

kon supports strongly typed values, C-style comments, flexible object notation,
and dot-notation for nested keys.

## 2. Value and Data types

kon supports the following primitive values:

- `null`
- integers (`int` / `uint`)
- floating-point numbers
- booleans
- strings
- arrays (typed)
- objects

All values are represented textually and parsed according to the rules below.

### 2.1 `null`

The `null` literal represents the absence of a value.

```kon
value: null
```

`null` may also appear when a value violates the expected type, an example
would be assigning a negative integer to a `uint` in a schema.

### 2.2 Integer (`int` / `uint`)

kon distinguishes two integer interpretations:

#### 2.2.1 **Signed integer (`int`)**
- May contain negative or positive whole numbers.
- Internally expected to fit in a 64-bit signed integer (`int64`).

```kon
count: -10
level: 42
```

#### 2.2.2 **Unsigned integer (`uint`)**
- Must be zero or positive.
- If a negative number is parsed where a `uint` is expected, the value becomes `null`.

```kon
size: 12
```

### 2.3 Float or Double

Floating-point values are decimal numbers containing a dot:

```kon
pi: 3.14159
temperature: -12.5
```

kon does not distinguish float32 vs float64 at the syntax level,
implementations are free to use double precision by default.

### 2.4 Boolean

Booleans support two syntaxes:

- Literal: `true`, `false`
- Integer-compatibility:
  - `0` → `false`
  - any non-zero integer → `true`

Examples:
```kon
flag: true
enabled: false
is-valid: 1 // True
is-empty: 0 // False
```

### 2.5 String

Strings in kon are written using double quotes (`"`). They have the following rules:

#### 1. Strings are **raw** by default
Text inside quotes is taken literally, including backslashes, unless an explicit
escape sequence is used.

```kon
message: "Path C:\User\Docs" // Raw interpretation
```

#### 2. Escape sequences are supported
kon supports common escape sequences:

| Escape | Meaning          |
|--------|------------------|
| `\\`   | backslash        |
| `\"`   | quote            |
| `\n`   | newline          |
| `\r`   | carriage return  |
| `\t`   | tab              |

Example:
```kon
escaped: "Line1\nLine2"
```

Escapes are optional, raw characters are preserved unless escaped.

#### 3. Strings may span multiple lines
A quoted string may break across line boundaries without requiring `\n`:

```kon
multi-line: "Hello,
 World!"
```

This produces the literal value: `"Hello,\n World!"`,
The newline is embedded exactly where written.

#### 4. Adjacent quoted strings concatenate automatically
If a key's value ends with a quoted string and is immediately followed by another
quoted string on the next line (and no new key is defined), the strings are
concatenated in order.

Example:

```kon
non-multi: "Hello,"
" World!"
```
Equivalent to: `"Hello, World!"`,
This allows long strings to be split across lines without introducing newlines.

### 2.6 List or Array

Arrays use square brackets `[ ... ]`.

**Arrays must contain only a single data type.**
All items must be integers, or all strings, or all floats, etc.

```kon
array-int: [ 0, 1, 2, 3 ]
array-str: [ "a", "b", "c" ]
array-bool: [ true, false, true ]
```

Spacing inside arrays is flexible, and commas are **required** to separate values.

### 2.7 Object

Objects define key–value mappings using the form `key: value`, example:
```kon
object:
    string: "Hello, World!"
    uint:    12
    int:    -5
    float:   25.555
    bool:    true
```

#### Indentation Rules
- Indentation defines the start of object content.
- Tabs or spaces are allowed, but **consistent indentation is recommended**.

#### Object Shorthand (Inline)

Objects may also be written inline using `{ ... }`
with semicolon-separated fields:

```kon
single-line: { string: "Hell"; int: 10 }
```

Semicolons are required between fields.

#### Dot-Notation for Nested Keys

Nested objects may be referenced using dot notation:

```kon
object-dot.string: "Awesome!"
```
Equivalent to:
```kon
object-dot:
    string: "Awesome!"
```

### 2.8 Identifiers (Variable / Key Names)

Identifiers are used for object keys and variable-like names in kon.
An identifier's first character must be: `A–Z or a–z`.
Identifiers beginning with anything other than an ASCII letter are a syntax error.

## 3. Comments

kon supports **C-style comments**.

### 3.1 Single-Line Comments

```kon
value: 10 // this is a comment
```
Anything after `//` until the end of the line is ignored.

### 3.2 Multi-Line Comments

```kon
/* A block comment
that spans multiple lines */
```

Block comments may appear anywhere whitespace may appear.

## 4. File Structure

A kon file consists of:

- zero or more comments
- one or more object or key/value definitions at root level

Example kon file:

```kon
/* multi-line comment */
// single-line comment

object:
    string: "Hello, World!"
    uint: 12
    int: 1.5
    float: 25.555
    bool: true
    bool-int: 1 // this is true

    array-int: [ 0, 1, 2, 3, 4, 5 ] // an array can only contain a single data type

object-dot.string: "Awesome!"

single-line: { string: "Hell"; int: 10 }
```

## 5. Reserved Characters

The following characters have special meaning and must not appear unescaped in identifiers:

`.  :  {  }  [  ]  /  *  "  ;`

## 6. Notes

- Type validation is schema-dependent and not part of the core syntax.
- Whitespace outside tokens is insignificant.

<div align=center>

End of SYNTAX v0.1

</div>