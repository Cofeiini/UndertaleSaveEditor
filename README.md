# UndertaleSaveEditor (Web Edition)

The web version can be accessed here using the browser [https://cofeiini.github.io/UndertaleSaveEditor](https://cofeiini.github.io/UndertaleSaveEditor).  
The executable version can be found
here [https://github.com/Cofeiini/UndertaleSaveEditor/tree/master](https://github.com/Cofeiini/UndertaleSaveEditor/tree/master).

> The "Web Edition" has the same features as the executable, but any future features will be applied only to the web edition

## Console Exclusive Borders

> The save editor supports unlocking the borders, but they have no effect on PC without mods

Load your `undertale.ini` and enable/edit the values you want (shown in the table below).  
After copying the file to the save folder and launching the game, you should be able to select borders you unlocked in the settings menu.

| ini Value         | Border                                         |
|-------------------|------------------------------------------------|
| General/BW        | Ruins, Snowdin, Waterfall, Hotland, and Castle |
| General/DB        | Super Dog, Hoi                                 |
| General/BP        | True Lab                                       |
| General/BH        | Beauty                                         |
| Alphys/M          | Real / Not Real                                |
| Dogshrine/Donated | Casino                                         |

> There is also `Alphys/R` entry that chooses between "Real" and "Not Real"

## Known Issues

* The browser will not allow the editor to open a file selector in the save directory, so the user has to find that location themselves. The output log will
  show the correct directory as a suggestion when opening files
    * This should be an experimental feature in most browsers, but we'll wait for it to become "stable"
* Saving files can't be done in a simple manner and require the user to download the target file in order to replace the old file, which the user needs to find
  themselves. The output log helps with this task also
* Certain browsers force the scroll bars to be visible, so the tabs and editor areas are different sizes than they should be
* Some of the theming will apply in strange ways when no file is loaded and the inputs are disabled
