import * as Pages from "./core/pages.js";

/** @type {string | null} */
let openedMenu = null;

const hideMenus = () => {
    const menus = document.querySelectorAll(".menu");
    for (const menu of menus) {
        menu.classList.add("hidden");
    }
    openedMenu = null;
};

const menuBarElements = [
    {
        text: "File",
        name: "fileMenu",
        options: [
            {
                tag: "button",
                text: "Open file",
                hint: {
                    enabled: "Edit the main save data",
                    disabled: "Edit the main save data",
                },
                name: "openFile",
                buddy: {
                    tag: "input",
                    type: "file",
                    classes: [
                        "hidden",
                    ],
                    accept: "",
                    function: (event) => {
                        const file = event.target.files[0];
                        openFile({ name: file.name, path: URL.createObjectURL(file) });
                        hideMenus();
                    },
                },
            },
            {
                tag: "button",
                text: "Open ini",
                hint: {
                    enabled: "Edit the persistent save data",
                    disabled: "Edit the persistent save data",
                },
                name: "openIni",
                buddy: {
                    tag: "input",
                    type: "file",
                    classes: [
                        "hidden",
                    ],
                    accept: ".ini",
                    function: (event) => {
                        const file = event.target.files[0];
                        openIni({ name: file.name, path: URL.createObjectURL(file) });
                        hideMenus();
                    },
                },
            },
            {
                tag: "button",
                text: "Save",
                hint: {
                    enabled: "Save the currently selected file",
                    disabled: "Can't save without an open file",
                },
                name: "save",
                function: (event) => {
                    let output = "";
                    const tab = document.querySelector(".tabs > button.active");
                    switch (tab.id) {
                        case "fileButton": {
                            let saveLastEntry = SAVE_LEN;
                            if (!SAVE_CONSOLE_CONTENT) {
                                saveLastEntry = SAVE_TIME;
                            }
                            for (let i = 1; i < saveLastEntry; i++) {
                                output += `${SaveData[i]}\r\n`;
                            }
                            output += SaveData[saveLastEntry]; // Do the last line separately to avoid writing a newline
                            break;
                        }
                        case "iniButton": {
                            const keys = Object.keys(IniData);
                            for (const key of keys) {
                                let section = `[${key}]\r\n`;

                                const subKeys = Object.keys(IniData[key]);
                                for (const subKey of subKeys) {
                                    section += `${subKey}="${IniData[key][subKey]}"\r\n`;
                                }

                                output += section;
                            }
                            break;
                        }
                    }

                    const link = document.createElement("a");
                    link.download = tab.querySelector("div").innerText;
                    link.href = URL.createObjectURL(new Blob([output], { type: "text/text" }));
                    link.click();

                    const userAgent = navigator.userAgent;
                    // noinspection SpellCheckingInspection
                    let saveLocation = "~/.config/UNDERTALE";
                    if (/Windows/.test(userAgent)) {
                        // noinspection SpellCheckingInspection
                        saveLocation = "%LOCALAPPDATA%/UNDERTALE";
                    } else if (/Mac/.test(userAgent)) {
                        // noinspection SpellCheckingInspection
                        saveLocation = "~/Library/Application Support/com.tobyfox.undertale";
                    }
                    updateStatus({
                        message: `New "${link.download}" downloaded. Replace the old file in <div style='color: white;'>${saveLocation}</div> with it to use it.`,
                        color: "green",
                    });

                    setTimeout(() => {
                        URL.revokeObjectURL(link.href);
                        hideMenus();
                    }, 1);
                    event.stopPropagation();
                },
            },
        ],
    },
    {
        text: "Options",
        name: "optionsMenu",
        options: [
            {
                tag: "input",
                hint: {
                    enabled: "Enables some debugging related features",
                    disabled: "Enables some debugging related features",
                },
                type: "checkbox",
                name: "showDebug",
                buddy: {
                    tag: "label",
                    text: "Show Debug",
                    function: (event) => {
                        event.stopPropagation();
                    },
                },
                function: (event) => {
                    document.querySelector("#mainListDebug").classList.toggle("hidden");
                    event.stopPropagation();
                },
            },
            {
                tag: "input",
                hint: {
                    enabled: "Enables the console exclusive Dog Shrine",
                    disabled: "Enables the console exclusive Dog Shrine",
                },
                type: "checkbox",
                name: "showDogShrine",
                buddy: {
                    tag: "label",
                    text: "Show Dog Shrine",
                    function: (event) => {
                        event.stopPropagation();
                    },
                },
                function: (event) => {
                    document.querySelector("#mainListDogShrine").classList.toggle("hidden");
                    event.stopPropagation();
                },
            },
            {
                tag: "input",
                hint: {
                    enabled: "Toggles this editor between light and dark themes",
                    disabled: "Toggles this editor between light and dark themes",
                },
                type: "checkbox",
                name: "useDarkTheme",
                buddy: {
                    tag: "label",
                    text: "Use Dark Theme",
                    function: (event) => {
                        event.stopPropagation();
                    },
                },
                function: (event) => {
                    document.querySelector("body").classList.toggle("dark");
                    document.querySelector(":root").classList.toggle("dark");
                    event.stopPropagation();
                },
            },
            {
                tag: "input",
                hint: {
                    enabled: "Enables compatibility with console exclusive content",
                    disabled: "Enables compatibility with console exclusive content",
                },
                type: "checkbox",
                name: "useConsoleContent",
                buddy: {
                    tag: "label",
                    text: "Use Console Content",
                    function: (event) => {
                        event.stopPropagation();
                    },
                },
                function: (event) => {
                    const wasConsoleContent = SAVE_CONSOLE_CONTENT;
                    SAVE_CONSOLE_CONTENT = event.target.checked;

                    /** @type {RoomEditor} */
                    const widget = Widgets[548][0];

                    widget.indexes = widget.originalIndexes;
                    if (SAVE_CONSOLE_CONTENT) {
                        widget.indexes = widget.consoleIndexes;
                    }

                    const offset = Number(SAVE_CONSOLE_CONTENT) - Number(wasConsoleContent);
                    widget.editor.selectedIndex = widget.indexes[parseInt(SaveData[widget.saveID]) + offset];

                    if (offset !== 0) {
                        widget.updateSave();
                    }

                    event.stopPropagation();
                },
            },
        ],
    },
    {
        text: "Tools",
        name: "toolsMenu",
        options: [
            {
                tag: "button",
                text: "Set monster names yellow",
                hint: {
                    enabled: "Unified controls to toggle the conditions of monster sparing for the credits",
                    disabled: "Requires a main file to be open",
                },
                name: "yellowName",
                function: () => {
                    for (const yellowWidget of YellowWidgets) {
                        yellowWidget.updateData();
                        yellowWidget.updateStyle();
                    }
                    const tool = document.querySelector("#yellowNameTool");
                    tool.setAttribute("isQuit", "1");
                    tool.classList.remove("hidden");
                    hideMenus();
                },
            },
            {
                tag: "button",
                text: "Manage borders",
                hint: {
                    enabled: "Unified controls to toggle various cosmetic borders",
                    disabled: "Requires an ini file to be open",
                },
                name: "borders",
                function: () => {
                    for (const borderWidget of BorderWidgets) {
                        borderWidget.updateData();
                        borderWidget.updateStyle();
                    }
                    const tool = document.querySelector("#borderTool");
                    tool.setAttribute("isQuit", "1");
                    tool.classList.remove("hidden");
                    hideMenus();
                },
            },
        ],
    },
    {
        text: "Help",
        name: "helpMenu",
        options: [
            {
                tag: "button",
                text: "About",
                hint: {
                    enabled: "Shows more information about this editor",
                    disabled: "Shows more information about this editor",
                },
                name: "about",
                function: () => {
                    document.querySelector("#aboutDialog").classList.remove("hidden");
                    hideMenus();
                },
            },
        ],
    },
];
const menuBar = document.querySelector("#menuBar");
for (const element of menuBarElements) {
    const menu = document.createElement("div");
    menu.className = "menu hidden";

    for (const option of element.options) {
        const layout = document.createElement("div");
        layout.title = option.hint.disabled;

        const item = document.createElement(option.tag);
        item.id = option.name;
        if (option.type) {
            item.type = option.type;
        }
        if (option.text) {
            item.innerText = option.text;
        }
        if (option.function) {
            item.onclick = option.function;
        }
        item.addEventListener("customtoggle", () => {
            layout.title = item.disabled ? option.hint.disabled : option.hint.enabled;
        });
        layout.append(item);
        layout.onclick = (event) => {
            item.click();
            event.stopPropagation();
        };

        if (option.buddy) {
            const buddy = document.createElement(option.buddy.tag);
            if (option.buddy.type) {
                buddy.type = option.buddy.type;
            }
            if (option.buddy.text) {
                buddy.innerText = option.buddy.text;
            }
            if (option.buddy.tag === "label") {
                buddy.htmlFor = option.name;
            }
            if (option.buddy.classes) {
                buddy.classList.add(...option.buddy.classes);
            }

            if (buddy.type === "file") {
                buddy.accept = option.buddy.accept;
                buddy.onchange = option.buddy.function;

                item.onclick = (event) => {
                    buddy.click();
                    event.stopPropagation();
                };
            } else if (option.buddy.function) {
                buddy.onclick = option.buddy.function;
            }

            layout.append(buddy);
        }

        menu.append(layout);
    }

    const button = document.createElement("button");
    button.id = element.name;
    button.innerText = element.text;
    button.onclick = () => {
        const isHidden = menu.classList.contains("hidden");

        const menus = document.querySelectorAll(".menu");
        for (const menuElement of menus) {
            menuElement.classList.add("hidden");
        }

        openedMenu = null;
        if (isHidden) {
            openedMenu = button.id;
            menu.classList.remove("hidden");
        }
    };
    button.onmouseenter = () => {
        if (!openedMenu) {
            return;
        }

        const menus = document.querySelectorAll(".menu");
        for (const menuElement of menus) {
            menuElement.classList.add("hidden");
        }

        openedMenu = button.id;
        menu.classList.remove("hidden");
    };
    button.append(menu);

    menuBar.append(button);
}

// noinspection SpellCheckingInspection
const menuTabsElements = [
    {
        text: "file0",
        name: "fileButton",
        target: document.querySelector("#fileEditor"),
    },
    {
        text: "undertale.ini",
        name: "iniButton",
        target: document.querySelector("#iniEditor"),
    },
];
const menuTabs = document.querySelector("#menuTabs");
for (const element of menuTabsElements) {
    const image = document.createElement("img");
    image.src = SAVE_ICONS[0];
    image.alt = "Floppy Disk";

    const text = document.createElement("div");
    text.id = `${element.name}Text`;
    text.innerText = element.text;

    const button = document.createElement("button");
    button.id = element.name;
    button.onclick = (event) => {
        document.querySelectorAll(".mainEditor").forEach(editor => editor.classList.add("hidden"));
        document.querySelectorAll("#menuTabs > button").forEach(tab => tab.classList.remove("active"));

        event.currentTarget.classList.add("active");
        element.target.classList.remove("hidden");
    };
    button.append(image);
    button.append(text);

    menuTabs.append(button);
}

// noinspection SpellCheckingInspection
const mainListElements = [
    {
        text: "Player",
        icon: "images/ico_player.png",
        hidden: false,
        target: Pages.PlayerPage(),
    },
    {
        text: "Bosses",
        icon: "images/ico_toriel.png",
        hidden: false,
        target: Pages.BossesPage(),
    },
    {
        text: "Monsters",
        icon: "images/ico_froggit.png",
        hidden: false,
        target: Pages.MonstersPage(),
    },
    {
        text: "Locations",
        icon: "images/ico_savepoint.png",
        hidden: false,
        target: Pages.LocationsPage(),
    },
    {
        text: "Dog Shrine",
        icon: "images/ico_dogshrine.png",
        hidden: true,
        target: Pages.DogShrinePage(),
    },
    {
        text: "Debug",
        icon: "images/ico_debug.png",
        hidden: true,
        target: Pages.DebugPage(),
    },
];

const mainList = document.querySelector("#mainList");
const fileContents = document.querySelector("#fileContents");
for (const element of mainListElements) {
    fileContents.append(element.target);

    const image = document.createElement("img");
    image.src = element.icon;
    image.alt = element.text;

    const text = document.createElement("p");
    text.innerText = element.text;

    const button = document.createElement("button");
    button.onclick = (event) => {
        document.querySelectorAll(".filePage").forEach(page => page.classList.add("hidden"));
        document.querySelectorAll("#mainList > li > button").forEach(item => item.classList.remove("active"));

        event.currentTarget.classList.add("active");
        element.target.classList.remove("hidden");
    };
    button.append(image);
    button.append(text);

    const item = document.createElement("li");
    item.id = `mainList${element.text.replaceAll(/\s/g, "")}`;
    item.title = element.text;
    item.append(button);

    if (element.hidden) {
        item.classList.add("hidden");
    }

    mainList.append(item);
}

document.querySelector("#iniContents").append(Pages.IniPage());
document.querySelector("#yellowNameTool").replaceWith(Pages.YellowNameTool());
document.querySelector("#borderTool").replaceWith(Pages.BorderTool());
document.querySelector("#aboutDialog").replaceWith(Pages.AboutDialog());

document.onclick = (event) => {
    if (openedMenu && (event.target.id !== openedMenu)) {
        document.getElementById(openedMenu).querySelector(".menu").classList.add("hidden");
        openedMenu = null;
    }
};

document.addEventListener("DOMContentLoaded", () => {
    menuTabs.children[0].click();
    mainList.children[0].querySelector("button").click();
    document.querySelector("#useDarkTheme").click();

    toggleControls({ selector: "#fileEditor *", disabled: true });
    toggleControls({ selector: "#iniEditor *", disabled: true });
    toggleControls({ selector: "#menuTabs button", disabled: true });
    toggleControls({ selector: "#save, #yellowName, #borders", disabled: true });

    updateStatus({ message: "Waiting for a file.", color: "inherit" });
});
