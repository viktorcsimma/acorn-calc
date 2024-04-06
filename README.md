# AcornCalc

A graphical exact-real calculator written in Qt
that works with the [Acorn](https://github.com/viktorcsimma/acorn) library
and is capable of printing results with an arbitrary precision.

## Building from source

You will need:
- Acorn (see the instructions [there](https://github.com/viktorcsimma/acorn))
- Catch2 (for the tests)
- Qt

**Note:** it is essential that everything gets compiled with the same compiler.
On Windows, GHC 9.4.8 uses Clang 14 as its C backend;
so if you want to use a version of Acorn built with it,
you need to download LLVM-MinGW 14 and build Qt from source with it
(see instructions in [this tutorial](https://doc.qt.io/qt-6/windows-building.html)).
(Another option is to try to convince GHC to use your favourite backend;
I haven't tried that yet.)

For now, on Windows, Acorn must be installed to
`C:/Program Files (x86)/Acorn/`,
because I had to hard-code the path to Acorn's Interaction.o.
(It somehow gets corrupted when creating the static library;
so it had to be installed separately.)

On Ubuntu, the defaults worked for me
(I used GCC).
