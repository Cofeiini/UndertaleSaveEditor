## UndertaleSaveEditor (Web Edition)
The web version can be accessed here using the browser [https://cofeiini.github.io/UndertaleSaveEditor](https://cofeiini.github.io/UndertaleSaveEditor).  
The executable version can be found here [https://github.com/Cofeiini/UndertaleSaveEditor/tree/master](https://github.com/Cofeiini/UndertaleSaveEditor/tree/master).  

Currently the web edition has the same features as the executable, but any future features will be applied only to the web edition.

### Known Issues
* The browser will not allow the editor to open a file selector in the save directory, so the user has to find that location themselves. The output log will show the correct directory as a suggestion when opening files
  * This should be an experimental feature in most browsers, but we'll wait for it to become "stable"
* Saving files can't be done in a simple manner and require the user to download the target file in order to replace the old file, which the user needs to find themselves. The output log helps with this task also
* Certain browsers force the scroll bars to be visible, so the tabs and editor areas are different sizes than they should be
* Some of the theming will apply in strange ways when no file is loaded and the inputs are disabled
