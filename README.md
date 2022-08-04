## UndertaleSaveEditor
With Undertale Save Editor you can easily modify your Undertale save files and learn more about what each save entry does.

### Download
The executables can be found in the [**releases**](https://github.com/Cofeiini/UndertaleSaveEditor/releases/) page.  
There are files for Linux, Windows, and macOS.

### Features
* Simple controls
* Explanations on data
* Organized user interface
* Tools for automating tasks
* Automated update checking
* **file0** and **undertale.ini** support

### Compilation - Requirements
To compile, you need the following:

* `qt6-base`
* `cmake`
* `g++`

\> On Linux, installing `qt6-base` should install everything else as a dependency.  
\> The easiest option for `cmake` on Windows is to install it with [Chocolatey](https://chocolatey.org/).  
\> To get a standalone executable, you need to compile Qt with static linking and assign the appropriate kits before compiling (or use the terminal).

### Compilation - Qt Creator
Opening the "CMakeLists.txt" file, configuring/selecting _Release_ mode, and clicking _Build_ should be enough.  
> **NOTE:** The project uses Qt features that deprecate any older Qt libraries, so 6.0.0 is the minimum required version.

### Compilation - Terminal
Making a "shadow build" is recommended for keeping the source folder clean and organized. This will generate the executable in the root of the build directory.  

1. `git clone https://github.com/Cofeiini/UndertaleSaveEditor.git`
2. `mkdir build-UndertaleSaveEditor`
3. `qt-cmake -S UndertaleSaveEditor -B build-UndertaleSaveEditor`
4. `cmake --build build-UndertaleSaveEditor`

If you don't mind messy source, you can follow these steps. This will generate the executable in the root of the source directory.

1. `git clone https://github.com/Cofeiini/UndertaleSaveEditor.git`
2. `cd UndertaleSaveEditor`
3. `qt-cmake`
4. `cmake --build .`

> **NOTE:** You might have to find `qt-cmake` in your system, especially if you compiled Qt from source.

### Tools used
The project is built using **Open Source** [Qt Libraries](https://www.qt.io/download-open-source)  
Windows version is compiled with the help from [MXE (M cross environment)](https://mxe.cc/).  
The executables are compressed with [UPX](https://upx.sourceforge.net/).

