# UndertaleSaveEditor

With Undertale Save Editor you can easily modify your Undertale save files and learn more about what each save entry does.

## Web Edition

The "Web Edition" of the save editor can be found here [https://cofeiini.github.io/UndertaleSaveEditor](https://cofeiini.github.io/UndertaleSaveEditor).  
The source code for the web edition can be found here [https://github.com/Cofeiini/UndertaleSaveEditor/tree/web](https://github.com/Cofeiini/UndertaleSaveEditor/tree/web).

## Download

> ⚠️ The executable is now **deprecated** and is no longer receiving updates, but it remains compatible with original PC release of the game.

> At this time, only the "Web Edition" has the latest features. It's possible the executable receives the same updates in the future when there's enough time and inspiration.

The executables can be found in the [**releases**](https://github.com/Cofeiini/UndertaleSaveEditor/releases/) page.  
There are files for Linux, Windows, and macOS.

## Features

* Simple controls
* Explanations on data
* Organized user interface
* Tools for automating tasks
* Automated update checking
* **file0** and **undertale.ini** support

## Compilation

To compile, you need the following:

* `qt6-base`
* `cmake`
* `ninja`

\> On Linux, installing `qt6-base` and `ninja` (or `ninja-build`) should install everything else as a dependency.  
\> The easiest option for `cmake` on Windows is to install it with [Chocolatey](https://chocolatey.org/).  
\> The easiest option for the requirements on macOS is to install them with [Homebrew](https://brew.sh/).  
\> To get a standalone executable, you need to compile Qt with static linking and assign the appropriate kits before building (basically same for the terminal).

### Compilation - Qt Creator

Opening the "CMakeLists.txt" file, configuring/selecting _Release_ mode, and clicking _Build_ should be enough.

> ℹ️ The project uses Qt features that deprecate any older Qt libraries, so 6.7.0 is the minimum required version.

### Compilation - Terminal

This will generate the executable in the "build" directory inside the source directory.

1. `git clone --depth=1 https://github.com/Cofeiini/UndertaleSaveEditor.git`
2. `cd UndertaleSaveEditor`
3. `qt-cmake -G Ninja -S . -B build`
4. `cmake --build build --parallel`

> ℹ️ You might have to find `qt-cmake` in your system, especially if you compiled Qt from source.

## Tools used

The project is built using **Open Source** [Qt Libraries](https://www.qt.io/download-open-source)  
