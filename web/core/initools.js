import {CommonEditor} from "./tools.js";

class IniEditorBase extends CommonEditor {
	/**
	 * @param args
	 * @param {string} args.id
	 * @param {string} args.element
	 * @param {string} args.type
	 * @param {string} args.title
	 * @param {string} args.label
	 */
	constructor(args) {
		super({...args});

		const keys = args.id.split("/");
		this.saveID = keys[0];
		this.saveKey = keys[1];

		this.editor.id = `editor_${this.saveID}_${this.saveKey}`;
		this.editor.name = `editor_${this.saveID}_${this.saveKey}`;

		if (args.label) {
			this.label.htmlFor = this.editor.id;
		}

		if (!IniWidgets[this.saveID]) {
			IniWidgets[this.saveID] = {};
		}
		IniWidgets[this.saveID][this.saveKey] = this;
	}

	/**
	 * @param input
	 * @param {string | string[]} input.data
	 * @param {number | string} input.value
	 */
	logError(input) {
		const message = corruptedError({
			id: `${this.saveID}/${this.saveKey}`,
			title: this.editor.title,
			expected: input.data,
			data: IniData[this.saveID][this.saveKey],
			value: input.value,
		});
		console.warn(message);
		updateStatus({message: message, color: "yellow"});
	}

	validateSave() {
		const data = parseFloat(IniData[this.saveID][this.saveKey]);
		switch (this.editor.type) {
			case "number": {
				const max = parseInt(this.editor.max);
				const min = parseInt(this.editor.min);

				if ((data < min) || (data > max)) {
					const value = String(Math.min(max, Math.max(min, data)));
					this.logError({data: `between ${min} and ${max}`, value: value});

					IniData[this.saveID][this.saveKey] = value;
					this.editor.value = value;
				}
				break;
			}
			case "checkbox": {
				const max = parseInt(this.editor.max);
				const min = parseInt(this.editor.min);
				if ((data !== min) && (data !== max)) {
					const value = Math.min(max, Math.max(min, data));
					this.logError({data: `${this.editor.min} or ${this.editor.max}`, value: value});

					IniData[this.saveID][this.saveKey] = String(value);
					this.editor.checked = value > 0;
				}
			}
		}

		this.updateStyle();
	}

	updateOriginal() {
		if (!IniData[this.saveID]) {
			IniData[this.saveID] = {};
		}
		if (!IniData[this.saveID][this.saveKey]) {
			IniData[this.saveID][this.saveKey] = "0.000000"; // The .ini file uses a special notation with its numbers, so we need to add some zeroes
		}

		this.originalValue = IniData[this.saveID][this.saveKey];
		this.validateSave();
		this.updateData();
	}

	/**
	 * @param {string} [data]
	 */
	updateSave(data) {
		if (!data) {
			data = `${this.editor.value}.000000`; // The .ini file uses a special notation with its numbers, so we need to add some zeroes
		}

		if (data === IniData[this.saveID][this.saveKey]) {
			return;
		}

		console.log(`Value of ${this.editor.title} changed from ${IniData[this.saveID][this.saveKey]} to ${data}`);
		IniData[this.saveID][this.saveKey] = data;
		this.updateStyle();
	}

	/**
	 * @param {string} [data]
	 */
	updateData(data) {
		if (!data) {
			data = IniData[this.saveID][this.saveKey];
		}
		super.updateData(data);
	}

	/**
	 * @param {string} [data]
	 */
	updateStyle(data) {
		if (!data) {
			data = IniData[this.saveID][this.saveKey];
		}
		super.updateStyle(data);
	}
}

export class IniLineEditor extends IniEditorBase {
	constructor(args) {
		args.element = "input";
		args.type = "text";
		super({...args});

		switch (args.id) {
			case "General/Name": {
				// noinspection SpellCheckingInspection
				this.addHintText("Your name. Flowey and some menus will reference this");
				break;
			}
		}
	}
}

export class IniSpinEditor extends IniEditorBase {
	constructor(args) {
		args.element = "input";
		args.type = "number";
		super({...args});

		this.editor.min = "0";
		this.editor.max = String(Number.MAX_SAFE_INTEGER);

		// noinspection SpellCheckingInspection
		switch (args.id) {
			case "General/BC": {
				this.addHintText("For those \"Get an item\" trophies on PlayStation");
				break;
			}
			case "General/Gameover": {
				this.addHintText("Keeps track of how many Game Overs you have gotten");
				break;
			}
			case "General/Kills": {
				this.addHintText("Counts how many kills you have made. Used in some menus");
				break;
			}
			case "General/Love": {
				this.addHintText("Your LV. Used in some menus");
				break;
			}
			case "General/Room": {
				this.addHintText("The identifier of the last room you saved in");
				break;
			}
			case "General/Time": {
				this.addHintText("Play time counted using in-game frames");
				break;
			}
			case "General/Won": {
				this.addHintText("Counts how many times you reached an ending");
				break;
			}
			case "General/Fun": {
				this.addHintText("Randomly generated number at the start of the game that determines random events. This value is used in tandem with the \"fun\" in the save file");
				break;
			}
			case "Flowey/CHANGE": {
				this.addHintText("Changes based on if you did or didn't kill on the previous run and did the opposite this run. Can happen twice");
				break;
			}
			case "Flowey/EX": {
				// noinspection SpellCheckingInspection
				this.addHintText("Conversation with Flowey at the end which is unlocked by reaching an ending where you killed at least once, but spared Asgore, didn't complete any dates, and IK or NK is 1");
				break;
			}
			case "Flowey/Met1": {
				// noinspection SpellCheckingInspection
				this.addHintText("Counts how many times you have encountered Flowey for the first time");
				break;
			}
			case "Toriel/Bscotch": {
				// noinspection SpellCheckingInspection
				this.addHintText("Chosen flavor of pie. Toriel will remember this during the phone call. 1 = Butterscotch. 2 = Cinnamon");
				break;
			}
			case "Toriel/TK": {
				// noinspection SpellCheckingInspection
				this.addHintText("Counts how many times you have killed Toriel");
				break;
			}
			case "Toriel/TS": {
				// noinspection SpellCheckingInspection
				this.addHintText("Counts how many times you have spared Toriel");
				break;
			}
			case "Sans/F": {
				this.addHintText("Counts how many times you have fought sans");
				break;
			}
			case "Sans/Intro": {
				// noinspection SpellCheckingInspection
				this.addHintText("Counts how many times you have seen sans's fight intro. It keeps changing based on this number");
				break;
			}
			case "Sans/M1": {
				this.addHintText("Counts how many times you have met sans for the first time");
				break;
			}
			case "Sans/MeetLv": {
				this.addHintText("Counts how many times you have met sans in the judgment hallway while having more than 2 LV");
				break;
			}
			case "Sans/MeetLv1": {
				this.addHintText("Counts how many times you have met sans in the judgment hallway while having 1 LV");
				break;
			}
			case "Sans/MeetLv2": {
				this.addHintText("Counts how many times you have met sans in the judgment hallway while having 2 LV");
				break;
			}
			case "Sans/MP": {
				this.addHintText("(Never used) Counts how many times you have been offered to spare sans");
				break;
			}
			case "Sans/Pass": {
				this.addHintText("Secret codeword counter. You'll hear the first codeword in the judgment hallway, if MeetLv1 is more than 0");
				break;
			}
			case "Sans/SK": {
				this.addHintText("Counts how many times you have killed sans");
				break;
			}
			case "Sans/SS": {
				this.addHintText("Counts how many times you have spared sans");
				break;
			}
			case "Sans/SS2": {
				this.addHintText("Counts how many times you have spared sans again after the first attempt");
				break;
			}
			case "Papyrus/M1": {
				this.addHintText("Counts how many times you have met Papyrus for the first time");
				break;
			}
			case "Papyrus/PD": {
				this.addHintText("Counts how many dates you have completed with Papyrus. Changes title menu");
				break;
			}
			case "Papyrus/PK": {
				this.addHintText("Counts how many times you have killed Papyrus");
				break;
			}
			case "Papyrus/PS": {
				this.addHintText("Counts how many times you have spared Papyrus");
				break;
			}
			case "Undyne/UD": {
				// noinspection SpellCheckingInspection
				this.addHintText("Counts how many dates you have completed with Undyne. Changes title menu");
				break;
			}
			case "Alphys/AD": {
				// noinspection SpellCheckingInspection
				this.addHintText("Counts how many dates you have completed with Alphys. Changes title menu");
				break;
			}
			case "MTT/EssayNo": {
				// noinspection SpellCheckingInspection
				this.addHintText("Counts how many essays you have written about Mettaton");
				break;
			}
			case "Asgore/KillYou": {
				// noinspection SpellCheckingInspection
				this.addHintText("Counts how many times you have died at the Asgore fight. Changes some of the fight dialog");
				break;
			}
			case "FFFFF/D": {
				// noinspection SpellCheckingInspection
				this.addHintText("Counts how many times you have died at the Omega Flowey fight. Changes the dialog when restarting the game");
				break;
			}
			case "FFFFF/E": {
				// noinspection SpellCheckingInspection
				this.addHintText("Sets to 0 after the short credits, 1 after the Omega Flowey fight, and 2 after killing Flowey");
				break;
			}
			case "FFFFF/F": {
				// noinspection SpellCheckingInspection
				this.addHintText("Sets to 0 after the short credits and 1 after the Omega Flowey fight");
				break;
			}
			case "FFFFF/P": {
				// noinspection SpellCheckingInspection
				this.addHintText("Stages of Omega Flowey fight. 1 = start. 2 = knife. 3 = glove. 4 = shoe. 5 = book. 6 = pan. 7 = gun");
				break;
			}
			case "EndF/EndF": {
				// noinspection SpellCheckingInspection
				this.addHintText("Sets to 1 after reaching the True Pacifist ending and 2 after Flowey talks about resetting");
				break;
			}
		}
	}
}

export class IniCheckEditor extends IniEditorBase {
	constructor(args) {
		// noinspection DuplicatedCode
		args.element = "input";
		args.type = "checkbox";
		args.title = args.label;
		super({...args});

		this.retargetContainer();

		this.editorLayout.appendChild(this.label);

		this.editor.min = "0";
		this.editor.max = "1";

		// noinspection SpellCheckingInspection
		switch (args.id) {
			case "General/BH": {
				this.addHintText("Border Hard Mode. Console exclusive stuff");
				break;
			}
			case "General/BP": {
				this.addHintText("Border Pacifist. Console exclusive stuff");
				break;
			}
			case "General/BW": {
				this.addHintText("Border Won. Console exclusive stuff");
				break;
			}
			case "General/CH": {
				this.addHintText("Complete Hard Mode");
				break;
			}
			case "General/CP": {
				this.addHintText("Complete Pacifist");
				break;
			}
			case "General/Tale": {
				this.addHintText("Heard the Tale of the Fallen Human");
				break;
			}
			case "General/Truth": {
				this.addHintText(`(Never set) Activates "Activity Level A" and "Activity Level B"`);
				break;
			}
			case "Flowey/AF": {
				this.addHintText("Reached an ending without finishing True Lab");
				break;
			}
			case "Flowey/AK": {
				// noinspection SpellCheckingInspection
				this.addHintText("Reached an ending where only Asgore was killed");
				break;
			}
			case "Flowey/Alter": {
				// noinspection SpellCheckingInspection
				this.addHintText("Set to true if truename, IK or NK is true. Changes Flowey dialog and interactions");
				break;
			}
			case "Flowey/CK": {
				// noinspection SpellCheckingInspection
				this.addHintText("(Never set) (Never used) Is loaded at the final Flowey conversation, but does nothing");
				break;
			}
			case "Flowey/FloweyExplain1": {
				// noinspection SpellCheckingInspection
				this.addHintText("First kill Toriel then reload and spare her (or the reverse). Flowey will explain the power of saving");
				break;
			}
			case "Flowey/IK": {
				this.addHintText("Reached an ending where you made at least 1 kill (if NK is false, IK must be also false)");
				break;
			}
			case "Flowey/K": {
				// noinspection SpellCheckingInspection
				this.addHintText("Managed to kill Flowey");
				break;
			}
			case "Flowey/NK": {
				this.addHintText("Reached an ending where you made no kills");
				break;
			}
			case "Flowey/SK": {
				// noinspection SpellCheckingInspection
				this.addHintText("Flowey killed Asgore");
				break;
			}
			case "Flowey/SPECIALK": {
				// noinspection SpellCheckingInspection
				this.addHintText(`Reached an ending while "truename" is 1`);
				break;
			}
			case "Flowey/alter2": {
				this.addHintText("Reached the end of Ruins while killing everything (Ruins genocide)");
				break;
			}
			case "Flowey/truename": {
				this.addHintText("Reached the end of Ruins while killing everything (Ruins genocide)");
				break;
			}
			case "Sans/EndMet": {
				this.addHintText("Met sans at the judgment hallway");
				break;
			}
			case "Mett/O": {
				// noinspection SpellCheckingInspection
				this.addHintText("Experienced the Mettaton Opera");
				break;
			}
			case "Mettaton/BossMet": {
				// noinspection SpellCheckingInspection
				this.addHintText("Encountered Mettaton. Skips turning Mettaton around");
				break;
			}
			case "F7/F7": {
				// noinspection SpellCheckingInspection
				this.addHintText("Finished the Asriel fight. Changes title menu");
				break;
			}
			case "reset/reset": {
				this.addHintText(`Set on naming screen after a true reset. Activates "Activity Level A" and "Activity Level B"`);
				break;
			}
			case "reset/s_key": {
				// noinspection SpellCheckingInspection
				this.addHintText("Set if you hit 0 names on credits. Opens the mysterious door in a cave near Snowdin");
				break;
			}
		}
	}

	/**
	 * @param {string} [data]
	 */
	updateSave(data) {
		if (!data) {
			data = `${this.editor.checked ? this.editor.max : this.editor.min}.000000`;
		}
		super.updateSave(data);
	}
}