TITLE: Lexical Analyzer
This project is a Lexical Analyzer (also known as a Tokenizer) implemented in C. A lexical analyzer is a fundamental component of a compiler or interpreter, responsible for reading source code and breaking it down 
into meaningful chunks called tokens. These tokens include keywords, identifiers, operators, constants, and special characters. The goal of this project is to demonstrate the process of lexical analysis and provide 
a clear understanding of how compilers and interpreters process source code at the lowest level.

The lexical analyzer reads a source code file, processes it character by character, and classifies tokens based on predefined rules. It supports a wide range of token types, including:

Keywords: Reserved words like int, if, for, etc.
Identifiers: Variable and function names.
Operators: Both single-character (+, -) and multi-character (++, ==) operators.
Constants: Numeric constants (decimal, hexadecimal, octal) and character/string literals.
Special Characters: Symbols like {, }, ;, etc.

The program also handles preprocessor directives (e.g., #include, #define) and comments (both single-line // and multi-line /* ... */).
It demonstrates my understanding of compiler design principles, low-level programming, and efficient text processing. The code is modular, well-documented, and designed for extensibility, making it a great starting point
for further exploration into compiler construction.

Future Enhancements
Support for more token types, such as floating-point numbers and escape sequences.
Improved error recovery to continue processing after encountering errors.
Integration into a full-fledged compiler or interpreter.
