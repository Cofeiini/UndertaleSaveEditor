# UndertaleSaveEditor

If you're just looking for the executable (.exe file): You'll find it in the **[releases](https://github.com/Cofeiini/UndertaleSaveEditor/releases/)**.  
***
##### Some thoughts on compiling  
If you, for some reason, want to compile this yourself, just open the ".pro" file with Qt Creator. Or use any method you like, that's just the way I do it.  

For this project I used Qt 5.5.1 with STATIC linking, because I don't like having library files hanging loose from my executables.  
I'm not sure if it works with older versions, since I recall using functions introduced in version 5.5.1  

Also, I used Qmake and MinGW.  
***
Right now it's a mess. I intend to cleanup the code, replace images with some my own artwork and do something else I'm most likely forgetting.  

##### Something I'm forgetting:
- [x] Move settings to a dialog instead of a clumsy menu
- [ ] Place entries in groups
- [ ] Organize content with something (maybe tabs or toolbox)
- [ ] Add support for .ini files
- [ ] Add preset function, like a "Time Machine"
- [ ] Add option to "Reset", "True Reset" and "Undo Genocide"
- [ ] Add "Real-time Monitor" to watch save file for changes while playing
- [ ] Add "Change Highlighter" for "Real-time Monitor"
