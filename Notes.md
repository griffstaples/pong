# Read Me

## How to build your project

1. Create a CMakeLists.txt file (specifies the cmake configuration)
2. Create a `build` folder: `mkdir build`
3. `cd` into `build` folder and run `cmake ..` to make cmake files
4. Run `cmake --build .` inside the `build` folder to compile the cmake files
5. Your executable will be available inside the `build` folder

## What is cmake?

CMake (Cross-Platform make) is a platform independent build tool which specifies how a project should be built regardless of the environment or compiler being used. It is not language specific and can be used for C/C++, C#, Python and more. It accepts your project files and a CMakeLists.txt config file and produces build files which can be compiled into an application usin the `cmake --build .` command.

## SDL2 Library Instructions

Use in CMake projects:
SDL2.framework can be used in CMake projects using the following pattern:
```
find_package(SDL2 REQUIRED COMPONENTS SDL2)
add_executable(my_game ${MY_SOURCES})
target_link_libraries(my_game PRIVATE SDL2::SDL2)
```
If SDL2.framework is installed in a non-standard location,
please refer to the following link for ways to configure CMake:
https://cmake.org/cmake/help/latest/command/find_package.html#config-mode-search-procedure

## C++ Importing Reminders:

Angle brackets `<>` and double quotes `""` are both ways of importing libraries in C++. Angle brackets are used to specify that a standard library such as `<iostream>` or `<vector>` or `<string>` is being imported and therefore to look in the appropriate path for these files. Double quotes specify that the compiler should look in the current directory and directories specified using the `-I` flag during compilation. 

### What libraries are part of the standard library?

It depends on what C++ version you are using and what compiler you are using. To check what compiler you are using, look at the output when you build using cmake `cmake --build . --verbose`. In my case, the compiler script is `/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++`. Doing some googling I find that Xcode usually uses the Clang C/C++ compiler. Therefore, to find what libraries are in the standard library I could look at the C++ version I am using


### Makefile

I chose to abandon the CMake method of build my project because I didn't understand it and it obscured the basic mechanics what was required for my project to build. Instead I am using a Makefile.


### Static vs Dynamic Linking

When you import a library, you need to decide whether to link it to your code statically or dynamically. 

A statically linked library is loaded into your program at compile time so that your compiled code contains all necessary files to run. A dynamically linked library is not loaded into your program at compile time and instead is loaded during runtime. This makes your executable smaller but slower to run since it has to load the library at runtime. Having libraries linked dynamically can make it easier to fix your published code since if the dynamically linked library has a bug or a change, you don't have to recompile your whole program, just the linked library. However, having a dynamically linked library introduces a dependency and if your runtime environment does not have this library, your program won't be able to run. 

### File extensions

`.o` files are object files - file containing machine code - that are a intermediate output of the compilation step. They typically aren't meant to be directly linked to your executable but will be nonetheless used to make your executable.

`.a` files are archive files - often called static libraries. They are collections of one or more object files which are packaged together to make it easy to link and distribute them

`.dll` or `.so` files are dynamically loaded libraries or shared objects (on Windows and MacOS respectively). They are compiled libraries which can be linked to your executable during compilation and loaded during runtime.

### What is SDL?

SDL stands for Simple Direct Media Layer and is essentially a standard API for creating GUI's on Windows, MacOS and Linux. It provides and standard interface to do things like create window objects and render changes to the window. It doesn't handle anything like physics in the case of games built using it.

