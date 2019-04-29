# obfacros

obfacros - a set of macros written in C++14 with g++5, that can be used to obfuscate your c/c++ code, make it harder for reverse-engineering.     

I use this to generate the CTF challenge of "Obfuscating Macros I/II" in DDCTF/*ctf 2019.

## feature

- easy to use: header-only, just include the provided `obfacros.hpp` and write your code in a way similar to plain c/c++, then compile with g++.
- easy to disable: to disable the obfuscation, you just need to replace the macros by normal code like: `#define FOR(init, cond, end, ...) for(init; cond; end) { __VA_ARGS__; }`
- much harder for reverse-engineering: by flattening the control flow and using dynamic JUMPs

If necessary, the macros may be modified into another form which do not require any features of C++14 or g++.

## usage

1. `#include "obfacros.hpp"`
2. write your code using the macros rather than the `for`/`if`/`while` c/c++ keywords
3. compile and enjoy!

## rules and warnings

0. Using all macros(like `FOR`/`IF`/`RETURN`...) ONLY IN the scope between `FUNCTION_START(var_to_accept_return_value)` and `FUNCTION_END;`
1. `DO NOT declare variables` inside the scope. Please declare all the variables outside in advance.
2. If you would like to write a clause(means `else`/`else if` in C) after a `IF`/`ELSE`, please use the form `IF_ELSE`/`ELIF_ELSE` instead of `IF`/`ELIF`. If no clause following, please use the form `IF`/`ELIF`.

## demo

Please find the `demo.cpp`. To compile, just `g++ demo.cpp -std=c++14 -o demo.out`.

## document

Coming soon...