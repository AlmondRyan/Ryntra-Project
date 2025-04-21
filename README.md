# Ryntra Project

This repository contains the documentation, the compiler, and every tool you need to develop program uses
The Ryntra Programming Language.  

The Ryntra Programming Language is a modern, Object-Oriented, modular programming language.

### Build

#### Build LLVM Project

Ryntra's Compiler uses LLVM as the backend of the compiler. So, of course, you need a built version of LLVM.  

But don't worry, I will tell you how to build LLVM.

> If not specified, the rest of this article will be on a Windows system.

1. First, install `Git`, `CMake`, `Visual Studio` on your computer. How to install? Go search on the Internet, there are
enough tutorials, I won't say again.

2. Clone LLVM Project, I use LLVM 19.1.7, because the newer version has some unexpected errors, LLVM 19.1.7 is the latest
stable version that I found.

```Bash
git clone https://github.com/llvm/llvm-project.git
cd llvm-project
git checkout tags/llvmorg-v19.1.7
```

3. Use any of the generators you like. I use Visual Studio 17 2022 on windows, because Visual Studio is the official
supported generator specified with LLVM.

> If you are on Windows, DON'T BUILD DYNAMIC LIBRARY, BECAUSE IT IS NOT SUPPORTED.

```Bash
cmake -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=<Prefix> -DLLVM_ENABLE_PROJECTS="llvm" -DLLVM_TARGETS_TO_BUILD="X86"
```

4. After the cmake finish processing, run the following command:

```Bash
cmake --build . --config Release
```

5. And if you are all success, LLVM is builted and installed, you can see the libraries that in the path you specified
on step no.4. And continue!