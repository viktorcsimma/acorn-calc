# AcornCalc

A graphical exact-real calculator written in Qt
that works with the [Acorn](https://github.com/viktorcsimma/acorn) library
and is capable of printing results with an arbitrary precision.

## Binary distribution

Binaries can be downloaded both
[for Linux](https://csimmaviktor.web.elte.hu/calc_linux.zip) and
[for Windows](https://csimmaviktor.web.elte.hu/calc_windows.zip).
After extracting, AcornCalc can be started
by `calc.sh` or `calc.exe`.

## Building from source

You will need:
- Acorn (see the instructions [there](https://github.com/viktorcsimma/acorn))
- Catch2 (for the tests)
- Qt (preferably built from source, with the `-static` and `-bundled-xcb-input` options – see later)

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

## Deployment

For me, the most sympathetic solution was to link the executable statically
so that it could run anywhere without any additional libraries.

### Ubuntu

On Ubuntu, you have to install the packages listed
in [this article](https://doc.qt.io/qt-6/linux-requirements.html)
of the documentation
(the part after _"we recommend that you install the following packages..."_).
Only _then_ should you proceed with building Qt.

So follow the instructions on building Qt from source,
except that you also provide the `-static` and `-bundled-xcb-xinput` options
for `configure`.
Then build the release executable with this Qt installation.

For a bundle that works on other machines,
you have to include certain Linux shared libraries.
But remember _not_ to include every dependency `ldd` lists
as these would trump system-specific libraries
and this causes bad things to happen.

[This bundle](http://csimmaviktor.web.elte.hu/calc_linux.zip)
seems to work.
Include these libraries and the start script with the executable
and you are ready to go.
Run `calc.sh` to start; this sets the path to the libraries.

### Windows

This is easier.

Build Qt as above and build the release executable with it.
After that, you only need two DLLs from the MinGW directory:
`libc++.dll` and `libunwind.dll`.
But if you use a different MinGW,
you can copy the executable into Windows Sandbox
and see what libraries it misses.

For a working example, see
[this bundle](http://csimmaviktor.web.elte.hu/calc_windows.zip).

