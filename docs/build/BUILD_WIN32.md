Windows - Visual Studio 2013
============================
#### Prerequisites ####
* Microsoft Visual C++ 2013 Update 1 (the free Express edition will work)
* If you have multiple MSVS installation use MSVS Developer console from target version.
* This build is for 64bit binaries.

#### Set up the directory structure ####
* Create a base directory for all projects.  I'm putting everything in
  `D:\whitecoin`, you can use whatever you like.  In several of the batch files
  and makefiles, this directory will be referred to as `GRA_ROOT`:

```
mkdir D:\whitecoin
```

* Clone the whitecoin Core repository

```
D:
cd D:\whitecoin
git clone https://github.com/whitecoin/whitecoin-core.git
cd whitecoin-core
git submodule update --init --recursive
```

* Download CMake

  Download the latest *Win32 Zip* build CMake from
  http://cmake.org/cmake/resources/software.html (version 2.8.12.2 as of this
  writing).  Unzip it to your base directory, which will create a directory that
  looks something like `D:\whitecoin\cmake-2.8.12.2-win32-x86`.  Rename this
  directory to `D:\whitecoin\CMake`.

  If you already have CMake installed elsewhere on your system you can use it,
  but whitecoin Core has a few batch files that expect it to be in the base
  directory's `CMake` subdirectory, so those scripts would need tweaking.

* Boost

   whitecoin Core depends on the Boost libraries version 1.57 ~ 1.60.  You can build them from
   source.
   * download the latest boost source from http://www.boost.org/users/download/
   * unzip it to the base directory `D:\whitecoin`.
   * This will create a directory like `D:\whitecoin\boost_1_57_0`.

* OpenSSL

   whitecoin Core depends on OpenSSL, and you must build this from source.
    * download the latest OpenSSL source from http://www.openssl.org/source/
    * Untar it to the base directory `D:\whitecoin`
    * this will create a directory like `D:\whitecoin\openssl-1.0.1g`.

At the end of this, your base directory should look like this (directory names will
be slightly different for the 64bit versions):
```
D:\whitecoin
+- whitecoin-core
+- boost_1_57_0
+- CMake
+- openssl-1.0.1g
```

#### Build the library dependencies ####

* Set up environment for building:

```
D:
cd D:\whitecoin
notepad setenv_x64.bat
```

Put this into the notepad window, then save and quit.

```
@echo off
set GRA_ROOT=d:\whitecoin\whitecoin-core
set OPENSSL_ROOT=%GRA_ROOT%\openssl-1.0.1g
set OPENSSL_ROOT_DIR=%OPENSSL_ROOT%
set OPENSSL_INCLUDE_DIR=%OPENSSL_ROOT%\include
set BOOST_ROOT=%GRA_ROOT%\boost_1_57_0

set PATH=%GRA_ROOT%\CMake\bin;%BOOST_ROOT%\lib;%PATH%

echo Setting up VS2013 environment...
call "%VS120COMNTOOLS%\..\..\VC\vcvarsall.bat" x86_amd64
```

Then run

```
setenv_x64.bat
```


* Build OpenSSL DLLs
```
D:
cd D:\whitecoin\openssl-1.0.1g
perl Configure --openssldir=D:\whitecoin\OpenSSL VC-WIN64A
ms\do_ms.bat
nmake -f ms\ntdll.mak
nmake -f ms\ntdll.mak install
```

  This will create the directory `D:\whitecoin\OpenSSL` with the libraries, DLLs,
  and header files.

* Build Boost
```
D:
cd D:\whitecoin\boost_1_57_0
bootstrap
.\b2
```

#### Build project files for whitecoin Core ####

* Run CMake:

```
D:
cd D:\whitecoin\whitecoin-core
notepad run_cmake_x64.bat
```
Put this into the notepad window, then save and quit.
```
setlocal
call "d:\whitecoin\setenv_x64.bat"
cd %GRA_ROOT%
cmake-gui -G "Visual Studio 12"
```
Then run
```
run_cmake_x64.bat
```

 This pops up the cmake gui, but if you've used CMake before it will probably be
 showing the wrong data, so fix that:
 * Where is the source code: `D:\whitecoin\whitecoin-core`
 * Where to build the binaries: `D:\whitecoin\x64` 

 Then hit **Configure**.  It may ask you to specify a generator for this
 project; if it does, choose **Visual Studio 12 2013 Win64** for 64 bit builds and select **Use default
 native compilers**.  Look through the output and fix any errors.  Then
 hit **Generate**.


* Launch *Visual Studio* and load `D:\whitecoin\x64\whitecoin.sln` 
* Set Active Configuration to `RelWithDebInfo`, ensure Active Solution platform is `x64` for 64 bit builds

* *Build Solution*

Or you can build the `INSTALL` target in Visual Studio which will
copy all of the necessary files into your `D:\whitecoin\install`
directory, then copy all of those files to the `bin` directory.
