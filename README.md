# obfacros

obfacros - a set of macros written in C++14 with g++5, that can be used to obfuscate your c/c++ code, to make it harder for reverse-engineering.     

I use this to generate the CTF challenge of "Obfuscating Macros I/II" in `DDCTF` / `*ctf` 2019.

## Demo

Please find the `demo.cpp`. To compile, just `g++ demo.cpp -std=c++14 -o demo.out`.

## Features

- easy to use: header-only, just include the provided `obfacros.hpp` and write your code in a way similar to plain c/c++, then compile with g++.
- easy to disable: to disable the obfuscation, you just need to replace the macros by normal code like: `#define FOR(init, cond, end, ...) for(init; cond; end) { __VA_ARGS__; }`. Check `demo_obfacros_disabled.cpp` and the section `A way to disable the obfuscation` in the document.
- much harder for reverse-engineering: by flattening the control flow and using dynamic JUMPs

If necessary, the macros may be modified into another form which do not require any features of C++14 or g++.

## Usage

1. `#include "obfacros.hpp"`
2. write your code using the macros rather than the `for`/`if`/`while` c/c++ keywords
3. compile and enjoy!

## Basic rules and WARNINGS

0. Using all macros(like `FOR`/`IF`/`RETURN`...) ONLY IN the `obfacros scope`(between `FUNCTION_START(var_to_accept_return_value)` and `FUNCTION_END;`)
1. `DO NOT declare variables` inside the scope. Please declare all the variables outside in advance.
2. Avoid using `{}` in the obfacros scope. If you want to use `{}` anyway, please do not use any obfacros inside the `{}`(before the bracket is closed).

## Document

### Basic features

#### `FUNCTION_START(retVal)` and `FUNCTION_END;`

Write this before using any other obfacros to create a `scope of obfacros` (or we call it `obfacros scope` or `the scope`).    

`retVal` specifies the variable to be assigned when `RETURN`. If you do not use `RETURN`, just fill in a random variable.

#### `FOR(init, cond, end, ...);`

just like `for (init; cond; end) { ... }` in c/c++

#### `WHILE(expr, ...);`

just like `while (expr) { ... }` in c/c++

#### `IF(expr, ...);` and `IF_ELSE(expr, ...)`

just like `if (expr) { ... }` in c/c++, but with a difference that:

`if (expr) { code; }` should be written in the form of `IF(expr, code);`    
`if (expr) { code; } else { code2; }` should be written in the form of `IF_ELSE(expr, code) ELSE (code2);`   

In a word, before you use any `ELIF` or `ELSE`, please check the previous macro is with the suffix `_ELSE`. Likewise, we also have `ELIF` and `ELIF_ELSE`.

#### `RETURN(val);`

Jump to next line of `FUNCTION_END`(jump out of the `scope of obfacros`) and assign the `val` to `retVal` that specified in `FUNCTION_START`.

### Advanced features

If you use any of advanced features, you may not easily disable the obfuscation because there is no corresponding features in the language of c/c++.

#### `BLOCK(...);`

Manually create a code block. Just like `{ code };` in c/c++.

#### `MAKE_BLOCK_WITH_NAME(name, ...);`

Create a code block with a name. Just like `if (false) { name: code };` in c/c++.

#### `INCLUDE_BLOCK(name);`

"include" a previously defined named block(by `MAKE_BLOCK_WITH_NAME`). Like a function call in c/c++ with variables shared.

### A way to disable the obfuscation

1. Comment out `#include "obfacros.hpp"`
2. Using the code below to replace the obfacros:

```c++
#define FUNCTION_START(...)
#define FUNCTION_END
#define BLOCK(...) { __VA_ARGS__; }
#define IF(expr, ...) if (expr) { __VA_ARGS__; } else {}
#define FOR(init, cond, end, ...) for(init; cond; end) { __VA_ARGS__; }
#define WHILE(expr, ...) while(expr) { __VA_ARGS__; }
#define IF_ELSE(expr, ...) if (expr) { __VA_ARGS__; }
#define ELSE(...) else { __VA_ARGS__; }
#define ELIF(expr, ...) else { if (expr) { __VA_ARGS__; } }
#define ELIF_ELSE(expr, ...) else if (expr) { __VA_ARGS__; }
#define RETURN(...) return (__VA_ARGS__)
```