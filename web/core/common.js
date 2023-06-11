const SAVE_LEN = 549;
const SAVE_ICONS = [ "images/ico_floppy.png", "images/ico_floppy_red.png", ];

/** @type {EditorBase[][]} */
let Widgets = [ [ null ] ];

/** @type {YellowCheckEditor[]} */
let YellowWidgets = [];

/** @type {Object.<string, IniEditorBase>[]} */
let IniWidgets = [];

/** @type {Object.<string, string | null>} */
let OpenedFiles = {
	"file": null,
	"ini": null,
};

/** @type {string[]} */
let SaveData = Array(SAVE_LEN + 1).fill("0");
SaveData[0] = "null"; // Placeholder for unused data. Mostly for debugging
SaveData[1] = "Chara"; // Player name
SaveData[2] = "1"; // Player level
SaveData[3] = "20"; // Max HP
SaveData[4] = "20"; // EXP
SaveData[5] = "10"; // AT stat
SaveData[7] = "10"; // DF stat
SaveData[9] = "4"; // SP stat
SaveData[29] = "3"; // Weapon (Set to "Stick")
SaveData[30] = "4"; // Armor (Set to "Bandage")
SaveData[36] = "100"; // "fun" value
SaveData[331] = "14"; // Box slot 1 (Set to "Tough Glove")

/** @type {Object.<string, Object.<string, string>>} */
let IniData = {};

const statusLog = document.querySelector("#statusLog");
/**
 * @param input
 * @param {string} input.color
 * @param {string} input.message
 */
const updateStatus = (input) => {
	"use strict";

	const date = new Date();
	const hour = date.getHours();
	const minutes = date.getMinutes();
	const seconds = date.getSeconds();

	const item = document.createElement("li");
	item.className = "log";
	item.style.color = input.color;
	item.dataset.time = `${String(hour).padStart(2, "0")}:${String(minutes).padStart(2, "0")}:${String(seconds).padStart(2, "0")}`;
	item.innerHTML = input.message;

	statusLog.insertBefore(item, statusLog.firstChild);
};

/**
 * @param input
 * @param {string} input.selector
 * @param {boolean} input.disabled
 */
const toggleControls = (input) => {
	"use strict";

	document.querySelectorAll(input.selector).forEach((item) => {
		item.disabled = input.disabled;
		item.classList.add("disabled");
		if (!input.disabled) {
			item.classList.remove("disabled");
		}
	});
};

/**
 * @param input
 * @param {string} input.name
 * @param {string} input.path
 */
const openIni = (input) => {
	"use strict";

	updateStatus({ message: `Loading "${input.name}"...`, color: "inherit" });

	fetch(input.path).then(response => {
		if (!response.ok) {
			throw Error(response.statusText);
		}
		return response.text();
	}).then(data => {
		const text = data.split(/[\r\n]+/);
		const regex = {
			section: /^\s*\[\s*([^\]]*)\s*]\s*$/,
			param: /^\s*([^=]+?)\s*=\s*(.*?)\s*$/,
			comment: /^\s*;.*$/
		};
		IniData = {};

		/** @type {string | null} */
		let section = null;
		for (const line of text) {
			if (line.length === 0 && section) {
				section = null;
				continue;
			}

			if (regex.comment.test(line)) {
				continue;
			}

			if (regex.section.test(line)) {
				const match = line.match(regex.section);
				section = match[1];
				IniData[section] = {};
				continue;
			}

			if (regex.param.test(line)) {
				const match = line.match(regex.param);
				const value = match[2].replaceAll(`"`, "");
				if (section) {
					IniData[section][match[1]] = value;
					continue;
				}

				IniData[match[1]] = value;
			}
		}

		Object.keys(IniWidgets).forEach((category) => {
			Object.keys(IniWidgets[category]).forEach((widget) => {
				IniWidgets[category][widget].updateOriginal();
			});
		});

		updateStatus({ message: `"${input.name}" is ready.`, color: "inherit" });

		toggleControls({ selector: "#iniEditor *", disabled: false, });
		toggleControls({ selector: "#iniButton", disabled: false, });
		toggleControls({ selector: "#save", disabled: false });

		document.querySelector("#iniButton").click();
		document.querySelector("#iniButtonText").innerText = input.name;

		OpenedFiles.ini = input.name;
	}).catch((error) => {
		updateStatus({ message: `"${error.toString()}" when parsing "${input.name}"`, color: "red" });

		toggleControls({ selector: "#iniEditor *", disabled: true, });
		toggleControls({ selector: "#iniButton", disabled: true, });

		if (!OpenedFiles.file) {
			toggleControls({ selector: "#save", disabled: true });
		}

		OpenedFiles.ini = null;
	});
};

/**
 * @param input
 * @param {string} input.name
 * @param {string} input.path
 */
const openFile = (input) => {
	"use strict";

	updateStatus({ message: `Loading "${input.name}"...`, color: "inherit" });

	fetch(input.path).then(response => {
		if (!response.ok) {
			throw Error(response.statusText);
		}

		return response.text();
	}).then(data => {
		const text = data.split(/[\r\n]+/);

		for (let i = 1; i < SAVE_LEN; ++i) {
			SaveData[i] = text[i - 1];
		}
		SaveData[SAVE_LEN] = String(parseFloat(text[SAVE_LEN - 1]).toExponential());

		for (const widget of Widgets) {
			if (!widget) {
				continue;
			}
			for (const editor of widget) {
				if (!editor) {
					continue;
				}
				editor.updateOriginal();
			}
		}


		updateStatus({ message: `"${input.name}" is ready.`, color: "inherit" });

		toggleControls({ selector: "#fileEditor *", disabled: false });
		toggleControls({ selector: "#fileButton", disabled: false });
		toggleControls({ selector: "#save, #yellowName", disabled: false });

		document.querySelector("#fileButton").click();
		document.querySelector("#fileButtonText").innerText = input.name;

		OpenedFiles.file = input.name;
	}).catch((error) => {
		updateStatus({ message: `"${error.toString()}" when parsing "${input.name}"`, color: "red" });

		toggleControls({ selector: "#fileEditor *", disabled: true });
		toggleControls({ selector: "#fileButton", disabled: true });
		toggleControls({ selector: "#yellowName", disabled: true });

		if (!OpenedFiles.ini) {
			toggleControls({ selector: "#save", disabled: true });
		}

		OpenedFiles.file = null;
	});
};

/**
 * @param input
 * @param {string} input.title
 * @param {string} input.id
 * @param {string} input.data
 * @param {string | string[]} input.expected
 * @param {string} input.value
 *
 * @return {string}
 */
const corruptedError = (input) => {
	"use strict";

    return `Corrupted data found at ${input.title} (ID ${input.id}). Got ${input.data}, but expected ${input.expected}. Using ${input.value} as fallback.`;
};

/**
 * @typedef ConfigObject
 * @type {Object}
 * @property {string} image
 * @property {string} text
 */
/**
 * @typedef PageObject
 * @type {Object}
 * @property {ConfigObject} config
 * @property {HTMLDivElement} target
 */
/**
 * @param {Object} input
 * @param {string} input.clickTarget
 * @param {PageObject[]} input.tabPages
 *
 * @return {HTMLDivElement}
 */
const buildPages = (input) => {
	"use strict";

	const tabs = document.createElement("div");
	tabs.id = `${input.clickTarget}Tabs`;
	tabs.className = "tabs";
	tabs.onwheel = (event) => {
		// noinspection JSSuspiciousNameCombination
		tabs.scrollLeft += event.deltaY;
		event.preventDefault();
	};

	const contents = document.createElement("div");
	contents.className = "filePage hidden";
	contents.appendChild(tabs);

	for (const page of input.tabPages) {
		const image = document.createElement("img");
		image.src = page.config.image;

		const label = document.createElement("div");
		label.innerText = page.config.text;

		const item = document.createElement("button");
		item.className = "tabButton";
		item.title = `${input.clickTarget} - ${page.config.text}`;

		item.appendChild(image);
		item.appendChild(label);

		item.onclick = () => {
			const pageElements = contents.querySelectorAll(".pageContent");
			for (const element of pageElements) {
				element.classList.add("hidden");
			}
			page.target.classList.remove("hidden");

			for (const button of tabs.children) {
				button.classList.remove("active");
			}
			item.classList.add("active");
		};

		tabs.appendChild(item);
		page.target.className = "pageContent hidden";
		page.target.title = item.title;

		contents.appendChild(page.target);
	}

	tabs.children[0].click();

	return contents;
};

/**
 * @param input
 * @param {string} input.title
 * @param {function} input.closeFunction
 *
 * @return {HTMLDivElement}
 */
const buildDialogHeader = (input) => {
	"use strict";

	const header = document.createElement("div");
	header.className = "dialogHeader";

	const icon = document.createElement("img");
	icon.src = "images/icon.png";
	icon.alt = "Icon";

	const title = document.createElement("div");
	title.innerText = input.title;

	const xButton = document.createElement("button");
	xButton.innerText = "X";
	xButton.onclick = input.closeFunction;

	header.appendChild(icon);
	header.appendChild(title);
	header.appendChild(xButton);

	return header;
};

class GroupBox {
	constructor(labelText) {
		this.label = document.createElement("legend");
		this.label.innerText = labelText;

		this.content = document.createElement("fieldset");
		this.content.appendChild(this.label);

		this.container = document.createElement("div");
		this.container.className = "groupBox";
		this.container.title = labelText;

		setTimeout(() => {
			let parentLabel = labelText;
			let parent = this.container.parentElement;
			while (parent) {
				if (parent.title) {
					parentLabel = `${parent.title} - ${parentLabel}`;
				}

				parent = parent.parentElement;
			}

			this.container.title = parentLabel;
		}, 20);

		this.container.appendChild(this.content);
	}
}
