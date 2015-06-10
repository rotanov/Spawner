# C++ Coding Style

# General Practices

- UTF-8
- put comments above the code.
- do not put comments in the same line with code.
- use Egyptian curly braces
- use `nullptr` in C++ code.
- don't use include guards, use `#pragma once`.
- split includes into three sections separated by newline:
    1. main header for this cpp file (if present) e.g. foo.h/foo.cpp.
    2. standard library includes.
    3. any other includes.
- unary operators must stick to the operand.
- when `*` or `&` is a part of the type specification it must stick to the type.
- format initialization list in constructor the following way:
```C++
options_class::options_class(const options_class &options)
    : session(options.session)
    , hide_gui(options.hide_gui)
    , hide_report(options.hide_report)
    , hide_output(options.hide_output)
    , debug(options.debug)
    , json(options.json)
    , controller(options.controller)
    , delegated(options.delegated)
    , secure_token(options.secure_token)
    , silent_errors(options.silent_errors)
    , use_cmd(options.use_cmd)
    , string_arguments(options.string_arguments)
    , working_directory(options.working_directory)
    , login(options.login)
    , password(options.password)
    , report_file(options.report_file) ...
```

# Naming Conventions

- only lowercase Latin letters, numbers and underscore symbol must be used in identifiers.
- words must be separated by underscore symbol `_`.
- private and protected methods and fields must end with an underscore symbol `_`
- class (and structures) type names must end with `_c`.
- enumeration type names must end with `_e`.
- any other defined type names must end with `_t`.

# Whitespace

- any comma `,` must be immediately followed by single space.
- tabs must never be used.
- use 4 spaces for a single indentation level.
- no trailing whitespace must be present.
- any source code file must end with newline.
- function and class definitions must be separated by single newline.
- no more than one consequent newline must be present.
- any binary operator must be enframed with spaces.
- semicolons `;` in `for` statement's `init-expression` and `cond-expression` must be immediately followed by a single space; except for the case `for (;;) {...}`
- a single space must be placed after `if` `for` `while` `do` `switch` keywords.
- there must be no space between function name and argument list.

# Statements

- no more than one statement must be present on a single line e.g.
```C++
// WRONG:
v += a * dt; p += v * dt;
// RIGHT:
v += a * dt;
p += v * dt;
```
- don't exploit comma as a binary operator

# Declarations

- always initialize variables.
- declare only one variable per line.
```C++
// RIGHT:
int a = -1;
int b = -1;
int c = -1;
// WRONG:
int a = -1, b = -1, c = -1;
```

