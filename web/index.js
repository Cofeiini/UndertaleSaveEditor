import * as Pages from "./core/pages.js";

/** @type {string | null} */
let openedMenu = null;

const hideMenus = () => {
    "use strict";

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
                name: "openFile",
                buddy: {
                    tag: "input",
                    type: "file",
                    classes: [
                        "hidden",
                    ],
                    accept: "",
                    function: (event) => {
                        "use strict";

                        const file = event.target.files[0];
                        openFile({ name: file.name, path: URL.createObjectURL(file), });
                        hideMenus();
                    },
                },
            },
            {
                tag: "button",
                text: "Open ini",
                name: "openIni",
                buddy: {
                    tag: "input",
                    type: "file",
                    classes: [
                        "hidden",
                    ],
                    accept: ".ini",
                    function: (event) => {
                        "use strict";

                        const file = event.target.files[0];
                        openIni({ name:file.name, path: URL.createObjectURL(file) });
                        hideMenus();
                    },
                },
            },
            {
                tag: "button",
                text: "Save",
                name: "save",
                function: (event) => {
                    "use strict";

                    let output = "";
                    const tab = document.querySelector(".tabs > button.active");
                    switch (tab.id) {
                        case "fileButton": {
                            for (let i = 1; i < SAVE_LEN; i++) {
                                output += `${SaveData[i]}\n`;
                            }
                            output += SaveData[SAVE_LEN];
                            break;
                        }
                        case "iniButton": {
                            const keys = Object.keys(IniData);
                            for (const key of keys) {
                                let section = `[${key}]\n`;

                                const subKeys = Object.keys(IniData[key]);
                                for (const subKey of subKeys) {
                                    section += `${subKey}="${IniData[key][subKey]}"\n`;
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
                    let saveLocation = "~/.config/UNDERTALE";
                    if (/Windows/.test(userAgent)) {
                        saveLocation = "%LOCALAPPDATA%/UNDERTALE";
                    } else if (/Mac/.test(userAgent)) {
                        // noinspection SpellCheckingInspection
                        saveLocation = "~/Library/Application Support/com.tobyfox.undertale";
                    }
                    updateStatus({ message: `New "${link.download}" downloaded. Replace the old file in <div style='color: white;'>${saveLocation}</div> with it to use it.`, color: "green" });

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
                type: "checkbox",
                name: "showDebug",
                buddy: {
                    tag: "label",
                    text: "Show Debug",
                    function: (event) => { "use strict"; event.stopPropagation(); },
                },
                function: (event) => {
                    "use strict";

                    const element = document.querySelector("#mainListDebug");
                    element.classList.toggle("hidden");
                    event.stopPropagation();
                },
            },
            {
                tag: "input",
                type: "checkbox",
                name: "showDogShrine",
                buddy: {
                    tag: "label",
                    text: "Show Dog Shrine",
                    function: (event) => { "use strict"; event.stopPropagation(); },
                },
                function: (event) => {
                    "use strict";

                    const element = document.querySelector("#mainListDogShrine");
                    element.classList.toggle("hidden");
                    event.stopPropagation();
                },
            },
            {
                tag: "input",
                type: "checkbox",
                name: "useDarkTheme",
                buddy: {
                    tag: "label",
                    text: "Use Dark Theme",
                    function: (event) => { "use strict"; event.stopPropagation(); },
                },
                function: (event) => {
                    "use strict";

                    document.querySelector("body").classList.toggle("dark");
                    document.querySelector(":root").classList.toggle("dark");
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
                name: "yellowName",
                function: () => {
                    "use strict";

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
        ],
    },
    {
        text: "Help",
        name: "helpMenu",
        options: [
            {
                tag: "button",
                text: "About",
                name: "about",
                function: () => {
                    "use strict";

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
        layout.appendChild(item);
        layout.onclick = (event) => {
            "use strict";

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
                    "use strict";

                    buddy.click();
                    event.stopPropagation();
                };
            } else if (option.buddy.function) {
                buddy.onclick = option.buddy.function;
            }

            layout.appendChild(buddy);
        }

        menu.appendChild(layout);
    }

    const button = document.createElement("button");
    button.id = element.name;
    button.innerText = element.text;
    button.onclick = () => {
        "use strict";

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
        "use strict";

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
    button.appendChild(menu);

    menuBar.appendChild(button);
}

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
    }
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
        "use strict";

        document.querySelectorAll(".mainEditor").forEach(editor => editor.classList.add("hidden"));
        document.querySelectorAll("#menuTabs > button").forEach(tab => tab.classList.remove("active"));

        event.currentTarget.classList.add("active");
        element.target.classList.remove("hidden");
    };
    button.appendChild(image);
    button.appendChild(text);

    menuTabs.appendChild(button);
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
        text: "Debug",
        icon: "images/ico_debug.png",
        hidden: true,
        target: Pages.DebugPage(),
    },
    {
        text: "Dog Shrine",
        icon: "images/ico_dogshrine.png",
        hidden: true,
        target: Pages.DogShrinePage(),
    }
];

const mainList = document.querySelector("#mainList");
const fileContents = document.querySelector("#fileContents");
for (const element of mainListElements) {
    fileContents.appendChild(element.target);

    const image = document.createElement("img");
    image.src = element.icon;
    image.alt = element.text;

    const text = document.createElement("p");
    text.innerText = element.text;

    const button = document.createElement("button");
    button.onclick = (event) => {
        "use strict";

        document.querySelectorAll(".filePage").forEach(page => page.classList.add("hidden"));
        document.querySelectorAll("#mainList > li > button").forEach(button => button.classList.remove("active"));

        // if (ClickedTabs[element.text]) {
        //     ClickedTabs[element.text].click();
        // }
        event.currentTarget.classList.add("active");
        element.target.classList.remove("hidden");
    };
    button.appendChild(image);
    button.appendChild(text);

    const item = document.createElement("li");
    item.id = `mainList${element.text.replaceAll(/\s/g, "")}`;
    item.title = element.text;
    item.appendChild(button);

    if (element.hidden) {
        item.classList.add("hidden");
    }

    mainList.appendChild(item);
}

document.querySelector("#iniContents").appendChild(Pages.IniPage());
document.querySelector("#yellowNameTool").replaceWith(Pages.YellowNameTool());
document.querySelector("#aboutDialog").replaceWith(Pages.AboutDialog());

document.onclick = (event) => {
    "use strict";

    if (openedMenu && (event.target.id !== openedMenu)) {
        document.getElementById(openedMenu).querySelector(".menu").classList.add("hidden");
        openedMenu = null;
    }
};

menuTabs.children[0].click();
mainList.children[0].querySelector("button").click();
document.querySelector("#useDarkTheme").click();

toggleControls({ selector: "#fileEditor *", disabled: true, });
toggleControls({ selector: "#iniEditor *", disabled: true, });
toggleControls({ selector: "#menuTabs button", disabled: true, });
toggleControls({ selector: "#save, #yellowName", disabled: true });

updateStatus({ message: "Waiting for a file.", color: "inherit" });

