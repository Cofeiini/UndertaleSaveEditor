// noinspection SpellCheckingInspection

import * as Tools from "./tools.js";
import * as IniTools from "./initools.js";

export const PlayerPage = () => {
    /** @type {PageObject[]} */
    const tabPages = [
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_player.png",
                text: "Character",
            },
        },
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_ribbon.png",
                text: "Equipment",
            },
        },
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_fight.png",
                text: "Fight",
            },
        },
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_spaghetti.png",
                text: "Events",
            },
        },
    ];
    let pageIndex = 0;

    let page = tabPages[pageIndex++];
    const stats = new GroupBox("Stats");
    stats.content.append(new Tools.LineEditor({ id: 1, label: "Name" }).container);
    stats.content.append(new Tools.SpinEditor({ id: 2, label: "LV" }).container);
    stats.content.append(new Tools.SpinEditor({ id: 3, label: "Max HP" }).container);
    stats.content.append(new Tools.SpinEditor({ id: 5, label: "AT" }).container);
    const weaponAT = new Tools.SpinEditor({ id: 6, label: "Weapon AT" });
    stats.content.append(weaponAT.container);
    stats.content.append(new Tools.SpinEditor({ id: 7, label: "DF" }).container);
    const armorDF = new Tools.SpinEditor({ id: 8, label: "Armor DF" });
    stats.content.append(armorDF.container);
    stats.content.append(new Tools.SpinEditor({ id: 10, label: "EXP" }).container);
    stats.content.append(new Tools.SpinEditor({ id: 11, label: "Gold" }).container);
    page.target.append(stats.container);

    const phone = new GroupBox("Phone");
    for (let i = 14; i <= 28; i += 2) {
        phone.content.append(new Tools.PhoneEditor({ id: i, title: `Slot ${(i / 2) - 6}` }).container);
    }
    page.target.append(phone.container);

    const other = new GroupBox("Other");
    other.content.append(new Tools.SpinEditor({ id: 36, label: "fun" }).container);
    other.content.append(new Tools.PlotEditor({ id: 543, label: "Plot" }).container);
    other.content.append(new Tools.RoomEditor({ id: 548, label: "Room" }).container);
    other.content.append(new Tools.TimeEditor({ id: 549, label: "Time" }).container);
    page.target.append(other.container);

    page = tabPages[pageIndex++];
    page.target.append(new Tools.WeaponEditor({ id: 29, label: "Weapon", buddy: weaponAT }).container);
    page.target.append(new Tools.ArmorEditor({ id: 30, label: "Armor", buddy: armorDF }).container);

    const inventory = new GroupBox("Inventory");
    for (let i = 13; i <= 27; i += 2) {
        inventory.content.append(new Tools.ItemEditor({ id: i, title: `Slot ${((i + 1) / 2) - 6}` }).container);
    }
    page.target.append(inventory.container);

    const dimensionalBoxA = new GroupBox("Dimensional Box A");
    for (let i = 331; i <= 340; ++i) {
        dimensionalBoxA.content.append(new Tools.ItemEditor({ id: i, title: `Slot ${i - 330}` }).container);
    }
    page.target.append(dimensionalBoxA.container);

    const dimensionalBoxB = new GroupBox("Dimensional Box B");
    for (let i = 343; i <= 352; ++i) {
        dimensionalBoxB.content.append(new Tools.ItemEditor({ id: i, title: `Slot ${i - 342}` }).container);
    }
    page.target.append(dimensionalBoxB.container);

    page = tabPages[pageIndex++];
    const kills = new GroupBox("Kills");
    kills.content.append(new Tools.SpinEditor({ id: 12, label: "Current" }).container);
    kills.content.append(new Tools.SpinEditor({ id: 232, label: "Total" }).container);
    kills.content.append(new Tools.SpinEditor({ id: 233, label: Str_Ruins }).container);
    kills.content.append(new Tools.SpinEditor({ id: 234, label: Str_Snowdin }).container);
    kills.content.append(new Tools.SpinEditor({ id: 235, label: Str_Waterfall }).container);
    kills.content.append(new Tools.SpinEditor({ id: 236, label: Str_Hotland }).container);
    page.target.append(kills.container);

    const prevFight = new GroupBox("Previous Fight");
    const radioButtons = [
        new Tools.RadioEditor({ id: 41, name: "prevFight", label: "Spare" }),
        new Tools.RadioEditor({ id: 42, name: "prevFight", label: "Kill" }),
        new Tools.RadioEditor({ id: 43, name: "prevFight", label: "Flee" }),
        new Tools.RadioEditor({ id: 44, name: "prevFight", label: "Bored" }),
    ];
    for (let y = 0; y < 4; ++y) {
        prevFight.content.append(radioButtons[y].container);
        radioButtons[y].validateInput = () => {
            for (let x = 0; x < 4; x++) {
                if (x === y) {
                    continue;
                }

                radioButtons[x].updateSave();
            }
        };
    }
    page.target.append(prevFight.container);

    page = tabPages[pageIndex++];
    const neutral = new GroupBox("Neutral");
    neutral.content.append(new Tools.CheckEditor({ id: 37, label: "Hard Mode" }).container);
    neutral.content.append(new Tools.CheckEditor({ id: 39, label: "Disable encounters" }).container);
    neutral.content.append(new Tools.CheckEditor({ id: 109, label: "Used Punch Card while wearing Tough Glove" }).container);
    neutral.content.append(new Tools.CheckEditor({ id: 116, label: "Have an umbrella" }).container);
    neutral.content.append(new Tools.CheckEditor({ id: 291, label: "Ate Food" }).container);
    neutral.content.append(new Tools.CheckEditor({ id: 530, label: "Seen the cast/credits" }).container);
    page.target.append(neutral.container);

    const pacifist = new GroupBox("Pacifist");
    pacifist.content.append(new Tools.CheckEditor({ id: 52, label: "Cooked Instant Noodles" }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 58, label: "Spared a certain monster" }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 511, label: "Inside the True Lab" }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 38, label: "True Pacifist" }).container);
    page.target.append(pacifist.container);

    const genocide = new GroupBox("Genocide");
    genocide.content.append(new Tools.CheckEditor({ id: 252, label: `Genocide in ${Str_Ruins}` }).container);
    genocide.content.append(new Tools.CheckEditor({ id: 253, label: `Genocide in ${Str_Snowdin}` }).container);
    genocide.content.append(new Tools.CheckEditor({ id: 254, label: `Genocide in ${Str_Waterfall}` }).container);
    genocide.content.append(new Tools.CheckEditor({ id: 255, label: `Genocide in ${Str_Hotland}` }).container);
    genocide.content.append(new Tools.CheckEditor({ id: 256, label: `Genocide in ${Str_Core}` }).container);
    page.target.append(genocide.container);

    const counters = new GroupBox("Counters");
    counters.content.append(new Tools.SpinEditor({ id: 54, label: "Spared fights" }).container);
    counters.content.append(new Tools.SpinEditor({ id: 55, label: "Fled fights" }).container);
    counters.content.append(new Tools.SpinEditor({ id: 56, label: "Dialog skips" }).container);
    counters.content.append(new Tools.SpinEditor({ id: 90, label: "Gold spent on Spider Bake Sale" }).container);
    counters.content.append(new Tools.SpinEditor({ id: 91, label: "Gold spent on Nice Cream" }).container);
    counters.content.append(new Tools.SpinEditor({ id: 409, label: "Gold spent on Hot Dogs" }).container);
    page.target.append(counters.container);

    return buildPages({ tabPages: tabPages, clickTarget: "Player" });
};

export const BossesPage = () => {
    /** @type {PageObject[]} */
    const tabPages = [
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_flowey.png",
                text: Str_Flowey,
            },
        },
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_toriel.png",
                text: Str_Toriel,
            },
        },
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_sans.png",
                text: Str_sans,
            },
        },
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_papyrus.png",
                text: Str_Papyrus,
            },
        },
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_undyne.png",
                text: Str_Undyne,
            },
        },
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_alphys.png",
                text: Str_Alphys,
            },
        },
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_mettaton.png",
                text: Str_Mettaton,
            },
        },
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_asgore.png",
                text: Str_Asgore,
            },
        },
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_asriel.png",
                text: Str_Asriel,
            },
        },
    ];
    let pageIndex = 0;

    let page = tabPages[pageIndex++];
    page.target.append(new Tools.SpinEditor({ id: 40, label: `${Str_Flowey} stalking` }).container);
    page.target.append(new Tools.CheckEditor({ id: 506, label: `Killed ${Str_Flowey}` }).container);

    page = tabPages[pageIndex++];
    page.target.append(new Tools.ComboEditor({ id: 68, label: `Dog kidnapped ${Str_Toriel}'s phone` }).container);
    page.target.append(new Tools.ComboEditor({ id: 77, label: "Chosen flavor of pie" }).container);
    page.target.append(new Tools.SpinEditor({ id: 71, label: `Said "Hello"` }).container);
    page.target.append(new Tools.CheckEditor({ id: 72, label: `Flirted with ${Str_Toriel}` }).container);
    page.target.append(new Tools.CheckEditor({ id: 73, label: `Called ${Str_Toriel} "Mom"` }).container);
    page.target.append(new Tools.ComboEditor({ id: 76, label: `Interaction with ${Str_Toriel}` }).container);
    page.target.append(new Tools.SpinEditor({ id: 222, label: `Chat with ${Str_Toriel} (Pacifist)` }).container);
    page.target.append(new Tools.SpinEditor({ id: 317, label: `Checked messages from ${Str_Toriel}` }).container);
    page.target.append(new Tools.SpinEditor({ id: 318, label: `Received messages from ${Str_Toriel}` }).container);

    page = tabPages[pageIndex++];
    page.target.append(new Tools.ComboEditor({ id: 78, label: `${Str_sans} creeping in the forest` }).container);
    page.target.append(new Tools.ComboEditor({ id: 120, label: `Date with ${Str_sans} at ${Str_Grillby}'s` }).container);
    page.target.append(new Tools.ComboEditor({ id: 422, label: `Food ordered at ${Str_Grillby}'s` }).container);
    page.target.append(new Tools.ComboEditor({ id: 444, label: `Date with ${Str_sans} at ${Str_MTT_Resort}` }).container);
    page.target.append(new Tools.ComboEditor({ id: 528, label: `Got the key to ${Str_sans}'s room` }).container);
    page.target.append(new Tools.SpinEditor({ id: 223, label: `Chat with ${Str_sans} (Pacifist)` }).container);
    page.target.append(new Tools.CheckEditor({ id: 302, label: `Fought ${Str_sans}` }).container);
    page.target.append(new Tools.CheckEditor({ id: 303, label: `Tried to Spare ${Str_sans}` }).container);

    page = tabPages[pageIndex++];
    page.target.append(new Tools.CheckEditor({ id: 97, label: `Flirted with ${Str_Papyrus}` }).container);
    page.target.append(new Tools.ComboEditor({ id: 98, label: `Interaction with ${Str_Papyrus}` }).container);
    page.target.append(new Tools.CheckEditor({ id: 99, label: `Fought ${Str_Papyrus}` }).container);
    page.target.append(new Tools.ComboEditor({ id: 119, label: `Date with ${Str_Papyrus}` }).container);
    page.target.append(new Tools.SpinEditor({ id: 493, label: `${Str_Papyrus} phone calls` }).container);
    page.target.append(new Tools.SpinEditor({ id: 226, label: `Chat with ${Str_Papyrus} (Pacifist)` }).container);
    page.target.append(new Tools.CheckEditor({ id: 322, label: "Skipped the Electric Maze puzzle (Genocide)" }).container);
    page.target.append(new Tools.CheckEditor({ id: 321, label: `Skipped ${Str_Papyrus}'s Special Attack (Genocide)` }).container);

    page = tabPages[pageIndex++];
    page.target.append(new Tools.SpinEditor({ id: 130, label: `${Str_Undyne} fights` }).container);
    page.target.append(new Tools.CheckEditor({ id: 315, label: `${Str_Undyne} got mad at the first bridge` }).container);
    page.target.append(new Tools.CheckEditor({ id: 316, label: `${Str_Undyne} got mad at the large bridge` }).container);
    page.target.append(new Tools.ComboEditor({ id: 381, label: `Interaction with ${Str_Undyne}` }).container);
    page.target.append(new Tools.SpinEditor({ id: 382, label: `${Str_Undyne}'s remaining HP` }).container);
    page.target.append(new Tools.CheckEditor({ id: 383, label: `Escaped from ${Str_Undyne} back to ${Str_Waterfall}` }).container);
    page.target.append(new Tools.ComboEditor({ id: 420, label: `Date with ${Str_Undyne}` }).container);
    page.target.append(new Tools.CheckEditor({ id: 496, label: `${Str_Undyne} moved to ${Str_Papyrus}'s place` }).container);
    page.target.append(new Tools.CheckEditor({ id: 501, label: `${Str_Undyne} talked about the weather` }).container);
    page.target.append(new Tools.ComboEditor({ id: 525, label: `Interaction with ${Str_Undyne_Letter}` }).container);
    page.target.append(new Tools.SpinEditor({ id: 224, label: `Chat with ${Str_Undyne} (Pacifist)` }).container);
    page.target.append(new Tools.CheckEditor({ id: 225, label: `${Str_Undyne} asked you to talk to ${Str_Napstablook} (Pacifist)` }).container);
    page.target.append(new Tools.CheckEditor({ id: 282, label: `Killed ${Str_Undyne_the_Undying}` }).container);

    page = tabPages[pageIndex++];
    page.target.append(new Tools.CheckEditor({ id: 523, label: `Date with ${Str_Alphys} is available` }).container);
    page.target.append(new Tools.ComboEditor({ id: 524, label: `Interaction with ${Str_Alphys}` }).container);
    page.target.append(new Tools.SpinEditor({ id: 227, label: `Chat with ${Str_Alphys} (Pacifist)` }).container);

    page = tabPages[pageIndex++];
    page.target.append(new Tools.CheckEditor({ id: 319, label: "Failed to defuse a bomb" }).container);
    page.target.append(new Tools.CheckEditor({ id: 309, label: "Completed the Multicolor Tile Puzzle" }).container);
    page.target.append(new Tools.CheckEditor({ id: 320, label: "Stepped on a green tile" }).container);
    page.target.append(new Tools.ComboEditor({ id: 416, label: "State of the Shooter Mode" }).container);
    page.target.append(new Tools.ComboEditor({ id: 455, label: `Exposed ${Str_Mettaton}'s switch` }).container);
    page.target.append(new Tools.SpinEditor({ id: 229, label: `Chat with ${Str_Mettaton} (Pacifist)` }).container);
    page.target.append(new Tools.CheckEditor({ id: 456, label: `Killed ${Str_Mettaton}` }).container);

    page = tabPages[pageIndex++];
    page.target.append(new Tools.SpinEditor({ id: 228, label: `Chat with ${Str_Asgore} (Pacifist)` }).container);
    page.target.append(new Tools.CheckEditor({ id: 507, label: `Killed ${Str_Asgore}` }).container);

    page = tabPages[pageIndex++];
    page.target.append(new Tools.CheckEditor({ id: 531, label: `Fought ${Str_Asriel}` }).container);
    page.target.append(new Tools.ComboEditor({ id: 532, label: "Stage of the final fight" }).container);
    page.target.append(new Tools.SpinEditor({ id: 533, label: "How many times re-fused" }).container);
    page.target.append(new Tools.CheckEditor({ id: 534, label: "Used a Dream" }).container);
    page.target.append(new Tools.SpinEditor({ id: 535, label: `${Str_Asriel} turn counter` }).container);
    page.target.append(new Tools.CheckEditor({ id: 536, label: `Saved ${Str_Undyne}` }).container);
    page.target.append(new Tools.CheckEditor({ id: 537, label: `Saved ${Str_Alphys}` }).container);
    page.target.append(new Tools.CheckEditor({ id: 538, label: `Saved ${Str_Papyrus} and ${Str_sans}` }).container);
    page.target.append(new Tools.CheckEditor({ id: 539, label: `Saved ${Str_Toriel} and ${Str_Asgore}` }).container);
    page.target.append(new Tools.ComboEditor({ id: 540, label: "HP display" }).container);
    page.target.append(new Tools.SpinEditor({ id: 542, label: `Chat with child ${Str_Asriel}` }).container);

    return buildPages({ tabPages: tabPages, clickTarget: "Bosses" });
};

export const MonstersPage = () => {
    /** @type {PageObject[]} */
    const tabPages = [
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_froggit.png",
                text: "Common",
            },
        },
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_napstablook.png",
                text: "Napstablook",
            },
        },
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_temmie.png",
                text: "Temmie",
            },
        },
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_muffet.png",
                text: "Muffet",
            },
        },
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_riverperson.png",
                text: "River Person",
            },
        },
    ];
    let pageIndex = 0;

    let page = tabPages[pageIndex++];
    const interactions = new GroupBox("Interactions");
    interactions.content.append(new Tools.ComboEditor({ id: 53, label: "Spare name color" }).container);
    interactions.content.append(new Tools.ComboEditor({ id: 45, label: "The first dummy" }).container);
    interactions.content.append(new Tools.ComboEditor({ id: 83, label: Str_Doggo }).container);
    interactions.content.append(new Tools.ComboEditor({ id: 84, label: Str_Dogamy_and_Dogaressa }).container);
    interactions.content.append(new Tools.ComboEditor({ id: 85, label: Str_Greater_Dog }).container);
    interactions.content.append(new Tools.ComboEditor({ id: 86, label: Str_Lesser_Dog }).container);
    interactions.content.append(new Tools.ComboEditor({ id: 87, label: Str_Snowman }).container);
    interactions.content.append(new Tools.ComboEditor({ id: 88, label: Str_Snowdrake }).container);
    interactions.content.append(new Tools.ComboEditor({ id: 112, label: Str_Shyren }).container);
    interactions.content.append(new Tools.ComboEditor({ id: 122, label: Str_Monster_Kid }).container);
    interactions.content.append(new Tools.ComboEditor({ id: 312, label: Str_So_Sorry }).container);
    interactions.content.append(new Tools.ComboEditor({ id: 284, label: `${Str_Snowman} (Genocide)` }).container);
    page.target.append(interactions.container);

    const neutral = new GroupBox("Neutral");
    neutral.content.append(new Tools.CheckEditor({ id: 313, label: `Fought ${Str_Glyde}` }).container);
    page.target.append(neutral.container);

    const pacifist = new GroupBox("Pacifist");
    pacifist.content.append(new Tools.CheckEditor({ id: 161, label: `Spared ${Str_Froggit}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 162, label: `Spared ${Str_Whimsun}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 163, label: `Spared ${Str_Moldsmal}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 164, label: `Spared ${Str_Loox}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 165, label: `Spared ${Str_Vegetoid}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 166, label: `Spared ${Str_Migosp}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 167, label: `Spared ${Str_Snowdrake}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 168, label: `Spared ${Str_Ice_Cap}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 169, label: `Spared ${Str_Gyftrot}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 170, label: `Spared ${Str_Doggo}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 171, label: `Spared ${Str_Dogamy_and_Dogaressa}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 172, label: `Spared ${Str_Lesser_Dog}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 173, label: `Spared ${Str_Greater_Dog}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 174, label: `Spared ${Str_Aaron}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 175, label: `Spared ${Str_Moldbygg}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 176, label: `Spared ${Str_Woshua}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 177, label: `Spared ${Str_Temmie}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 178, label: `Spared ${Str_Mad_Dummy}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 179, label: `Spared ${Str_Vulkin}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 180, label: `Spared ${Str_Tsunderplane}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 181, label: `Spared ${Str_Pyrope}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 182, label: `Spared ${Str_Final_Froggit}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 183, label: `Spared ${Str_Whimsalot}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 184, label: `Spared ${Str_Astigmatism}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 185, label: `Spared ${Str_Madjick}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 186, label: `Spared ${Str_Knight_Knight}` }).container);
    pacifist.content.append(new Tools.CheckEditor({ id: 187, label: `Spared ${Str_Endogeny}` }).container);
    page.target.append(pacifist.container);

    const genocide = new GroupBox("Genocide");
    genocide.content.append(new Tools.CheckEditor({ id: 283, label: `Killed ${Str_Glad_Dummy}` }).container);
    genocide.content.append(new Tools.CheckEditor({ id: 433, label: `Killed ${Str_Royal_Guards}` }).container);
    page.target.append(genocide.container);

    page = tabPages[pageIndex++];
    page.target.append(new Tools.ComboEditor({ id: 67, label: `${Str_Napstablook} encounter` }).container);
    page.target.append(new Tools.ComboEditor({ id: 124, label: `Date with ${Str_Napstablook}` }).container);
    page.target.append(new Tools.CheckEditor({ id: 126, label: `Spooked ${Str_Aaron_and_Woshua}` }).container);
    page.target.append(new Tools.CheckEditor({ id: 440, label: `${Str_NAPSTABLOOK22} has sent you a friend request` }).container);
    page.target.append(new Tools.CheckEditor({ id: 489, label: `Feel like garbage with ${Str_Napstablook}` }).container);
    page.target.append(new Tools.SpinEditor({ id: 230, label: `Chat with ${Str_Napstablook} (Pacifist)` }).container);

    page = tabPages[pageIndex++];
    page.target.append(new Tools.SpinEditor({ id: 296, label: `${Str_Temmie} sale countdown` }).container);
    page.target.append(new Tools.CheckEditor({ id: 297, label: `${Str_Temmie}'s special sale` }).container);
    page.target.append(new Tools.CheckEditor({ id: 300, label: `Talked to the allergic ${Str_Temmie}` }).container);
    page.target.append(new Tools.CheckEditor({ id: 307, label: `Sent ${Str_Temmie} to "cool leg"` }).container);

    page = tabPages[pageIndex++];
    page.target.append(new Tools.SpinEditor({ id: 413, label: `${Str_Muffet} bribe price` }).container);
    page.target.append(new Tools.SpinEditor({ id: 414, label: `Gold spent on bribing ${Str_Muffet}` }).container);
    page.target.append(new Tools.ComboEditor({ id: 427, label: `Conversation with ${Str_Muffet}` }).container);
    page.target.append(new Tools.CheckEditor({ id: 428, label: `Killed ${Str_Muffet}` }).container);

    page = tabPages[pageIndex++];
    page.target.append(new Tools.ComboEditor({ id: 490, label: "Destination" }).container);
    page.target.append(new Tools.SpinEditor({ id: 491, label: "Boat rides" }).container);
    page.target.append(new Tools.CheckEditor({ id: 492, label: "The boat is a dog" }).container);

    return buildPages({ tabPages: tabPages, clickTarget: "Monsters" });
};

export const LocationsPage = () => {
    /** @type {PageObject[]} */
    const tabPages = [
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_toriel.png",
                text: "Ruins",
            },
        },
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_papyrus.png",
                text: "Snowdin",
            },
        },
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_undyne.png",
                text: "Waterfall",
            },
        },
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_muffet.png",
                text: "Hotland",
            },
        },
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_mettaton.png",
                text: "Core",
            },
        },
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_asgore.png",
                text: "Castle",
            },
        },
        {
            target: document.createElement("div"),
            config: {
                image: "images/ico_alphys.png",
                text: "True Lab",
            },
        },
    ];
    let pageIndex = 0;

    let page = tabPages[pageIndex++];
    page.target.append(new Tools.CheckEditor({ id: 131, label: "Found the Faded Ribbon" }).container);
    page.target.append(new Tools.CheckEditor({ id: 133, label: "Found the Toy Knife" }).container);
    page.target.append(new Tools.CheckEditor({ id: 61, label: `Tutorial ${Str_Froggit} encountered` }).container);
    page.target.append(new Tools.CheckEditor({ id: 66, label: "First rock pushed" }).container);
    page.target.append(new Tools.CheckEditor({ id: 63, label: "Second rock pushed" }).container);
    page.target.append(new Tools.CheckEditor({ id: 62, label: "Third rock pushed" }).container);
    page.target.append(new Tools.CheckEditor({ id: 64, label: "Fourth rock asked to move" }).container);
    page.target.append(new Tools.ComboEditor({ id: 65, label: "Monster Candy bowl" }).container);
    page.target.append(new Tools.SpinEditor({ id: 74, label: "Pillar switch activations" }).container);
    page.target.append(new Tools.SpinEditor({ id: 82, label: "Wrong pillar switch activations" }).container);
    page.target.append(new Tools.CheckEditor({ id: 81, label: `Learned about "water sausages"` }).container);
    page.target.append(new Tools.ComboEditor({ id: 134, label: `${Str_Toriel}'s pie` }).container);
    page.target.append(new Tools.SpinEditor({ id: 75, label: `Tried to exit ${Str_Ruins}` }).container);

    page = tabPages[pageIndex++];
    page.target.append(new Tools.SpinEditor({ id: 101, label: "Forest encounters" }).container);
    page.target.append(new Tools.ComboEditor({ id: 306, label: `Entering ${Str_Snowdin} forest` }).container);
    page.target.append(new Tools.CheckEditor({ id: 285, label: `Interacted with ${Str_sans}'s puzzle` }).container);
    page.target.append(new Tools.ComboEditor({ id: 89, label: `"Harder" puzzle` }).container);
    page.target.append(new Tools.ComboEditor({ id: 93, label: `${Str_Papyrus}'s spaghetti trap` }).container);
    page.target.append(new Tools.SpinEditor({ id: 94, label: "XO puzzle resets" }).container);
    page.target.append(new Tools.ComboEditor({ id: 95, label: "Buried switch" }).container);
    page.target.append(new Tools.CheckEditor({ id: 96, label: "Found 30G in a snow poff" }).container);
    page.target.append(new Tools.CheckEditor({ id: 308, label: `The "Wrong Number" event` }).container);
    page.target.append(new Tools.CheckEditor({ id: 418, label: "Won the Ball Game" }).container);
    page.target.append(new Tools.CheckEditor({ id: 105, label: `Placed googly eyes on ${Str_Gyftrot}` }).container);
    page.target.append(new Tools.ComboEditor({ id: 103, label: "Interaction with Snowed Inn" }).container);
    page.target.append(new Tools.CheckEditor({ id: 104, label: "Staying at Snowed Inn" }).container);
    page.target.append(new Tools.CheckEditor({ id: 113, label: `Found ${Str_Annoying_Dog} in the kitchen` }).container);
    page.target.append(new Tools.CheckEditor({ id: 114, label: `Found 20G inside the "saggy old couch"` }).container);
    page.target.append(new Tools.CheckEditor({ id: 314, label: `Checked ${Str_Papyrus}'s kitchen after the date` }).container);
    page.target.append(new Tools.CheckEditor({ id: 292, label: `Tried to pet the dog in the "dev room"` }).container);
    page.target.append(new Tools.CheckEditor({ id: 286, label: "Stole from the shop (Genocide)" }).container);

    page = tabPages[pageIndex++];
    page.target.append(new Tools.CheckEditor({ id: 136, label: "Found the Old Tutu" }).container);
    page.target.append(new Tools.CheckEditor({ id: 137, label: "Found the Ballet Shoes" }).container);
    page.target.append(new Tools.SpinEditor({ id: 388, label: `${Str_Waterfall} (first area) encounters` }).container);
    page.target.append(new Tools.SpinEditor({ id: 389, label: `${Str_Waterfall} (second area) encounters` }).container);
    page.target.append(new Tools.CheckEditor({ id: 417, label: "Solved the first Bridge Seed Puzzle" }).container);
    page.target.append(new Tools.CheckEditor({ id: 135, label: "Got the Abandoned Quiche" }).container);
    page.target.append(new Tools.ComboEditor({ id: 106, label: `Your armor when ${Str_Papyrus} called` }).container);
    page.target.append(new Tools.CheckEditor({ id: 107, label: "Lied about your armor" }).container);
    page.target.append(new Tools.ComboEditor({ id: 108, label: `Your armor when ${Str_Undyne} attacked` }).container);
    page.target.append(new Tools.CheckEditor({ id: 110, label: `Talked to Nice Cream Guy at ${Str_Waterfall}` }).container);
    page.target.append(new Tools.SpinEditor({ id: 111, label: "Punch Cards" }).container);
    page.target.append(new Tools.ComboEditor({ id: 121, label: `Met ${Str_Monster_Kid} in the rain` }).container);
    page.target.append(new Tools.CheckEditor({ id: 122, label: "Interacted with Trash Zone SAVE Point" }).container);
    page.target.append(new Tools.ComboEditor({ id: 139, label: "Astronaut Food cooler" }).container);
    page.target.append(new Tools.ComboEditor({ id: 386, label: `Interaction with ${Str_Mad_Dummy}` }).container);
    page.target.append(new Tools.ComboEditor({ id: 125, label: "Spooky tune playing" }).container);
    page.target.append(new Tools.CheckEditor({ id: 464, label: `Unlocked ${Str_Mettaton}'s house` }).container);
    page.target.append(new Tools.CheckEditor({ id: 310, label: "Talked to Clam Girl" }).container);
    page.target.append(new Tools.ComboEditor({ id: 127, label: `Talked with ${Str_Gerson}` }).container);
    page.target.append(new Tools.CheckEditor({ id: 117, label: "Placed an umbrella on a statue" }).container);
    page.target.append(new Tools.CheckEditor({ id: 387, label: "Solved the Piano Puzzle" }).container);
    page.target.append(new Tools.ComboEditor({ id: 138, label: "Legendary artifact" }).container);
    page.target.append(new Tools.CheckEditor({ id: 301, label: "Solved the glowshroom puzzle" }).container);
    page.target.append(new Tools.ComboEditor({ id: 311, label: "Interaction with Elder Puzzler" }).container);
    page.target.append(new Tools.ComboEditor({ id: 527, label: `Interaction with ${Str_Onionsan}` }).container);
    page.target.append(new Tools.ComboEditor({ id: 129, label: `${Str_Monster_Kid} tripped on a bridge` }).container);

    page = tabPages[pageIndex++];
    page.target.append(new Tools.CheckEditor({ id: 141, label: "Found the Burnt Pan" }).container);
    page.target.append(new Tools.CheckEditor({ id: 142, label: "Found the Stained Apron" }).container);
    page.target.append(new Tools.SpinEditor({ id: 439, label: `${Str_Hotland} encounters` }).container);
    page.target.append(new Tools.ComboEditor({ id: 385, label: `${Str_Papyrus} calls at the entrance to ${Str_Hotland}` }).container);
    page.target.append(new Tools.CheckEditor({ id: 397, label: "Have a cup of water" }).container);
    page.target.append(new Tools.SpinEditor({ id: 471, label: "Drinks taken from the water cooler" }).container);
    page.target.append(new Tools.SpinEditor({ id: 472, label: `Drinks wasted in front of ${Str_Undyne}` }).container);
    page.target.append(new Tools.SpinEditor({ id: 384, label: "Water poured on the ground" }).container);
    page.target.append(new Tools.CheckEditor({ id: 140, label: "Got the Instant Noodles" }).container);
    page.target.append(new Tools.CheckEditor({ id: 281, label: "Nice Cream is sold out" }).container);
    page.target.append(new Tools.SpinEditor({ id: 400, label: `Last message received from ${Str_Alphys}` }).container);
    page.target.append(new Tools.CheckEditor({ id: 435, label: "Pressed all three switches on the conveyor" }).container);
    page.target.append(new Tools.CheckEditor({ id: 402, label: "Deactivated the first group of lasers" }).container);
    page.target.append(new Tools.CheckEditor({ id: 403, label: "Activated lasers at MTT News" }).container);
    page.target.append(new Tools.SpinEditor({ id: 426, label: "Bombs defused during MTT News" }).container);
    page.target.append(new Tools.CheckEditor({ id: 404, label: "Deactivated the laser near Shooting Puzzle" }).container);
    page.target.append(new Tools.CheckEditor({ id: 405, label: "Solved the west Shooting Puzzle" }).container);
    page.target.append(new Tools.CheckEditor({ id: 406, label: "Solved the east Shooting Puzzle" }).container);
    page.target.append(new Tools.CheckEditor({ id: 408, label: "Failed jet pack sequence" }).container);
    page.target.append(new Tools.SpinEditor({ id: 410, label: "Hot Dogs bought" }).container);
    page.target.append(new Tools.SpinEditor({ id: 411, label: "Total Hot Dogs placed on head" }).container);
    page.target.append(new Tools.CheckEditor({ id: 412, label: "Reached the limit on Head-Dogs" }).container);
    page.target.append(new Tools.ComboEditor({ id: 429, label: "Current elevator floor" }).container);
    page.target.append(new Tools.CheckEditor({ id: 430, label: "Solved the south Shooting Puzzle" }).container);
    page.target.append(new Tools.CheckEditor({ id: 431, label: "Solved the north Shooting Puzzle" }).container);
    page.target.append(new Tools.CheckEditor({ id: 432, label: `${Str_Undyne} mentioned mind control` }).container);
    page.target.append(new Tools.CheckEditor({ id: 434, label: `Bought something from ${Str_Muffet}` }).container);
    page.target.append(new Tools.ComboEditor({ id: 465, label: "Flamey challenge" }).container);
    page.target.append(new Tools.CheckEditor({ id: 293, label: `Delivered Sea Tea at ${Str_MTT_Resort}` }).container);
    page.target.append(new Tools.CheckEditor({ id: 294, label: `Delivered Cinnamon Bun at ${Str_MTT_Resort}` }).container);
    page.target.append(new Tools.CheckEditor({ id: 295, label: `Delivered Hot Dog at ${Str_MTT_Resort}` }).container);
    page.target.append(new Tools.ComboEditor({ id: 298, label: `Staying at ${Str_MTT_Resort}` }).container);
    page.target.append(new Tools.ComboEditor({ id: 436, label: `Talked with ${Str_Bratty_and_Catty}` }).container);
    page.target.append(new Tools.ComboEditor({ id: 437, label: `Talked with ${Str_Bratty_and_Catty} about ${Str_Mettaton}` }).container);
    page.target.append(new Tools.ComboEditor({ id: 438, label: `Talked with ${Str_Bratty_and_Catty} about ${Str_Alphys}` }).container);
    page.target.append(new Tools.ComboEditor({ id: 466, label: `Interaction with ${Str_Burger_Pants}` }).container);
    page.target.append(new Tools.ComboEditor({ id: 467, label: `Talked with ${Str_Burger_Pants} about ${Str_Mettaton}` }).container);
    page.target.append(new Tools.ComboEditor({ id: 468, label: `Chat with ${Str_Burger_Pants}, ${Str_Bratty_and_Catty}` }).container);
    page.target.append(new Tools.CheckEditor({ id: 473, label: "Bought the Empty Gun" }).container);
    page.target.append(new Tools.CheckEditor({ id: 474, label: "Bought the Cowboy Hat" }).container);
    page.target.append(new Tools.CheckEditor({ id: 475, label: "Bought the Mystery Key" }).container);
    page.target.append(new Tools.CheckEditor({ id: 476, label: "Bought the Face Steak" }).container);
    page.target.append(new Tools.CheckEditor({ id: 398, label: `Disable ${Str_Alphys}'s phone calls (Genocide)` }).container);
    page.target.append(new Tools.CheckEditor({ id: 399, label: `Disable ${Str_Alphys}'s messages (Genocide)` }).container);
    page.target.append(new Tools.CheckEditor({ id: 287, label: `Stole from ${Str_Bratty_and_Catty} (Genocide)` }).container);

    page = tabPages[pageIndex++];
    page.target.append(new Tools.SpinEditor({ id: 454, label: `${Str_Core} (first area) encounters` }).container);
    page.target.append(new Tools.SpinEditor({ id: 457, label: `${Str_Core} (second area) encounters` }).container);
    page.target.append(new Tools.CheckEditor({ id: 445, label: "Tried to use the elevator in the Core Lobby" }).container);
    page.target.append(new Tools.CheckEditor({ id: 446, label: "Went right in the Core Lobby" }).container);
    page.target.append(new Tools.CheckEditor({ id: 447, label: "Went a bit to the right in the first crossroads" }).container);
    page.target.append(new Tools.CheckEditor({ id: 448, label: "Went up in the first crossroads" }).container);
    page.target.append(new Tools.CheckEditor({ id: 143, label: "Got a Glamburger from a trashcan" }).container);
    page.target.append(new Tools.CheckEditor({ id: 144, label: "Got 100G from a trashcan" }).container);
    page.target.append(new Tools.CheckEditor({ id: 449, label: "Solved the Sage's Path" }).container);
    page.target.append(new Tools.ComboEditor({ id: 452, label: "Ambushed on the Warrior's Path" }).container);
    page.target.append(new Tools.CheckEditor({ id: 450, label: "Solved the Warrior's Path" }).container);
    page.target.append(new Tools.CheckEditor({ id: 451, label: "Waited for 60 seconds on the final force field" }).container);

    page = tabPages[pageIndex++];
    page.target.append(new Tools.CheckEditor({ id: 145, label: "Found the Worn Dagger" }).container);
    page.target.append(new Tools.CheckEditor({ id: 146, label: "Found the Heart Locket" }).container);
    page.target.append(new Tools.ComboEditor({ id: 462, label: `Floor of the ${Str_Castle} elevator` }).container);
    page.target.append(new Tools.CheckEditor({ id: 463, label: "Used the elevator for the first time" }).container);
    page.target.append(new Tools.ComboEditor({ id: 481, label: "The Tale of the Fallen Human" }).container);
    page.target.append(new Tools.CheckEditor({ id: 483, label: "Got the key in the kitchen" }).container);
    page.target.append(new Tools.CheckEditor({ id: 484, label: "Got the key in the hallway" }).container);
    page.target.append(new Tools.ComboEditor({ id: 485, label: `Padlocks in the ${Str_Castle}` }).container);
    page.target.append(new Tools.SpinEditor({ id: 486, label: "Story heard (the kitchen)" }).container);
    page.target.append(new Tools.SpinEditor({ id: 487, label: "Story heard (the hallway)" }).container);
    page.target.append(new Tools.CheckEditor({ id: 488, label: "Have unfinished business?" }).container);
    page.target.append(new Tools.ComboEditor({ id: 541, label: "True Pacifist conversation" }).container);

    page = tabPages[pageIndex++];
    page.target.append(new Tools.CheckEditor({ id: 510, label: "Entered True Lab lobby" }).container);
    page.target.append(new Tools.SpinEditor({ id: 526, label: "Potato Chisps bought" }).container); // This is misspelled in purpose, just like in the game
    page.target.append(new Tools.ComboEditor({ id: 512, label: "Interaction with Red switch" }).container);
    page.target.append(new Tools.ComboEditor({ id: 513, label: "Interaction with Blue switch" }).container);
    page.target.append(new Tools.ComboEditor({ id: 514, label: "Interaction with Green switch" }).container);
    page.target.append(new Tools.ComboEditor({ id: 515, label: "Interaction with Yellow switch" }).container);
    page.target.append(new Tools.CheckEditor({ id: 516, label: `Finished talking to ${Str_Alphys}` }).container);
    page.target.append(new Tools.SpinEditor({ id: 517, label: "Sink interactions" }).container);
    page.target.append(new Tools.ComboEditor({ id: 518, label: "Red key location" }).container);
    page.target.append(new Tools.CheckEditor({ id: 519, label: `Spared ${Str_Reaper_Bird}` }).container);
    page.target.append(new Tools.CheckEditor({ id: 520, label: `Spared ${Str_Lemon_Bread}` }).container);
    page.target.append(new Tools.CheckEditor({ id: 521, label: "Turned on the lab's ventilation" }).container);
    page.target.append(new Tools.CheckEditor({ id: 522, label: "Restored power to the elevator" }).container);

    return buildPages({ tabPages: tabPages, clickTarget: "Locations" });
};

export const DebugPage = () => {
    const contents = document.createElement("div");
    contents.className = "filePage pageContent hidden";

    contents.append(new Tools.CheckEditor({ id: 35, label: "Bypass kill counters" }).container);
    contents.append(new Tools.SpinEditor({ id: 57, label: "Murder level override" }).container);
    contents.append(new Tools.CheckEditor({ id: 59, label: "Debug text skip" }).container);

    return contents;
};

export const DogShrinePage = () => {
    const contents = document.createElement("div");
    contents.className = "filePage pageContent hidden";

    contents.append(new Tools.CheckEditor({ id: 327, label: "Tried to use the donation box" }).container);
    contents.append(new Tools.SpinEditor({ id: 323, label: "Gold donated" }).container);
    contents.append(new Tools.SpinEditor({ id: 324, label: "Donation goal" }).container);
    contents.append(new Tools.SpinEditor({ id: 325, label: "Reached donation goal" }).container);
    contents.append(new Tools.SpinEditor({ id: 326, label: "Dog Shrine upgrades" }).container);

    return contents;
};

export const IniPage = () => {
    const contents = document.createElement("div");
    contents.className = "iniPage iniContent";

    const general = new GroupBox("General");
    general.content.append(new IniTools.IniSpinEditor({ id: "General/BC", label: "BC" }).container);
    general.content.append(new IniTools.IniCheckEditor({ id: "General/BH", label: "BH" }).container);
    general.content.append(new IniTools.IniCheckEditor({ id: "General/BP", label: "BP" }).container);
    general.content.append(new IniTools.IniCheckEditor({ id: "General/BW", label: "BW" }).container);
    general.content.append(new IniTools.IniCheckEditor({ id: "General/CH", label: "CH" }).container);
    general.content.append(new IniTools.IniCheckEditor({ id: "General/CP", label: "CP" }).container);
    general.content.append(new IniTools.IniSpinEditor({ id: "General/Gameover", label: "Gameover" }).container);
    general.content.append(new IniTools.IniSpinEditor({ id: "General/Kills", label: "Kills" }).container);
    general.content.append(new IniTools.IniSpinEditor({ id: "General/Love", label: "Love" }).container);
    general.content.append(new IniTools.IniLineEditor({ id: "General/Name", label: "Name" }).container);
    general.content.append(new IniTools.IniSpinEditor({ id: "General/Room", label: "Room" }).container);
    general.content.append(new IniTools.IniCheckEditor({ id: "General/Tale", label: "Tale" }).container);
    general.content.append(new IniTools.IniSpinEditor({ id: "General/Time", label: "Time" }).container);
    general.content.append(new IniTools.IniCheckEditor({ id: "General/Truth", label: "Truth" }).container);
    general.content.append(new IniTools.IniSpinEditor({ id: "General/Won", label: "Won" }).container);
    general.content.append(new IniTools.IniSpinEditor({ id: "General/Fun", label: "fun" }).container);
    contents.append(general.container);

    const flowey = new GroupBox("Flowey");
    flowey.content.append(new IniTools.IniCheckEditor({ id: "Flowey/AF", label: "AF" }).container);
    flowey.content.append(new IniTools.IniCheckEditor({ id: "Flowey/AK", label: "AK" }).container);
    flowey.content.append(new IniTools.IniCheckEditor({ id: "Flowey/Alter", label: "Alter" }).container);
    flowey.content.append(new IniTools.IniSpinEditor({ id: "Flowey/CHANGE", label: "CHANGE" }).container);
    flowey.content.append(new IniTools.IniCheckEditor({ id: "Flowey/CK", label: "CK" }).container);
    flowey.content.append(new IniTools.IniSpinEditor({ id: "Flowey/EX", label: "EX" }).container);
    flowey.content.append(new IniTools.IniCheckEditor({ id: "Flowey/FloweyExplain1", label: "FloweyExplain1" }).container);
    flowey.content.append(new IniTools.IniCheckEditor({ id: "Flowey/IK", label: "IK" }).container);
    flowey.content.append(new IniTools.IniCheckEditor({ id: "Flowey/K", label: "K" }).container);
    flowey.content.append(new IniTools.IniSpinEditor({ id: "Flowey/Met1", label: "Met1" }).container);
    flowey.content.append(new IniTools.IniCheckEditor({ id: "Flowey/NK", label: "NK" }).container);
    flowey.content.append(new IniTools.IniCheckEditor({ id: "Flowey/SK", label: "SK" }).container);
    flowey.content.append(new IniTools.IniCheckEditor({ id: "Flowey/SPECIALK", label: "SPECIALK" }).container);
    flowey.content.append(new IniTools.IniCheckEditor({ id: "Flowey/alter2", label: "alter2" }).container);
    flowey.content.append(new IniTools.IniCheckEditor({ id: "Flowey/truename", label: "truename" }).container);
    contents.append(flowey.container);
    const toriel = new GroupBox("Toriel");
    toriel.content.append(new IniTools.IniSpinEditor({ id: "Toriel/Bscotch", label: "Bscotch" }).container);
    toriel.content.append(new IniTools.IniSpinEditor({ id: "Toriel/TK", label: "TK" }).container);
    toriel.content.append(new IniTools.IniSpinEditor({ id: "Toriel/TS", label: "TS" }).container);
    contents.append(toriel.container);

    const sans = new GroupBox("Sans");
    sans.content.append(new IniTools.IniCheckEditor({ id: "Sans/EndMet", label: "EndMet" }).container);
    sans.content.append(new IniTools.IniSpinEditor({ id: "Sans/F", label: "F" }).container);
    sans.content.append(new IniTools.IniSpinEditor({ id: "Sans/Intro", label: "Intro" }).container);
    sans.content.append(new IniTools.IniSpinEditor({ id: "Sans/M1", label: "M1" }).container);
    sans.content.append(new IniTools.IniSpinEditor({ id: "Sans/MeetLv", label: "MeetLv" }).container);
    sans.content.append(new IniTools.IniSpinEditor({ id: "Sans/MeetLv1", label: "MeetLv1" }).container);
    sans.content.append(new IniTools.IniSpinEditor({ id: "Sans/MeetLv2", label: "MeetLv2" }).container);
    sans.content.append(new IniTools.IniSpinEditor({ id: "Sans/MP", label: "MP" }).container);
    sans.content.append(new IniTools.IniSpinEditor({ id: "Sans/Pass", label: "Pass" }).container);
    sans.content.append(new IniTools.IniSpinEditor({ id: "Sans/SK", label: "SK" }).container);
    sans.content.append(new IniTools.IniSpinEditor({ id: "Sans/SS", label: "SS" }).container);
    sans.content.append(new IniTools.IniSpinEditor({ id: "Sans/SS2", label: "SS2" }).container);
    contents.append(sans.container);

    const papyrus = new GroupBox("Papyrus");
    papyrus.content.append(new IniTools.IniSpinEditor({ id: "Papyrus/M1", label: "M1" }).container);
    papyrus.content.append(new IniTools.IniSpinEditor({ id: "Papyrus/PD", label: "PD" }).container);
    papyrus.content.append(new IniTools.IniSpinEditor({ id: "Papyrus/PK", label: "PK" }).container);
    papyrus.content.append(new IniTools.IniSpinEditor({ id: "Papyrus/PS", label: "PS" }).container);
    contents.append(papyrus.container);
    const undyne = new GroupBox("Undyne");
    undyne.content.append(new IniTools.IniSpinEditor({ id: "Undyne/UD", label: "UD" }).container);
    contents.append(undyne.container);
    const alphys = new GroupBox("Alphys");
    alphys.content.append(new IniTools.IniSpinEditor({ id: "Alphys/AD", label: "AD" }).container);
    contents.append(alphys.container);

    const mtt = new GroupBox("MTT");
    mtt.content.append(new IniTools.IniSpinEditor({ id: "MTT/EssayNo", label: "EssayNo" }).container);
    contents.append(mtt.container);
    const mett = new GroupBox("Mett");
    mett.content.append(new IniTools.IniCheckEditor({ id: "Mett/O", label: "O" }).container);
    contents.append(mett.container);
    const mettaton = new GroupBox("Mettaton");
    mettaton.content.append(new IniTools.IniCheckEditor({ id: "Mettaton/BossMet", label: "BossMet" }).container);
    contents.append(mettaton.container);
    const asgore = new GroupBox("Asgore");
    asgore.content.append(new IniTools.IniSpinEditor({ id: "Asgore/KillYou", label: "KillYou" }).container);
    contents.append(asgore.container);
    const fffff = new GroupBox("FFFFF");
    fffff.content.append(new IniTools.IniSpinEditor({ id: "FFFFF/D", label: "D" }).container);
    fffff.content.append(new IniTools.IniSpinEditor({ id: "FFFFF/E", label: "E" }).container);
    fffff.content.append(new IniTools.IniSpinEditor({ id: "FFFFF/F", label: "F" }).container);
    fffff.content.append(new IniTools.IniSpinEditor({ id: "FFFFF/P", label: "P" }).container);
    contents.append(fffff.container);

    const endF = new GroupBox("EndF");
    endF.content.append(new IniTools.IniSpinEditor({ id: "EndF/EndF", label: "EndF" }).container);
    contents.append(endF.container);

    const f7 = new GroupBox("F7");
    f7.content.append(new IniTools.IniCheckEditor({ id: "F7/F7", label: "F7" }).container);
    contents.append(f7.container);

    const reset = new GroupBox("reset");
    reset.content.append(new IniTools.IniCheckEditor({ id: "reset/reset", label: "reset" }).container);
    reset.content.append(new IniTools.IniCheckEditor({ id: "reset/s_key", label: "s_key" }).container);
    contents.append(reset.container);

    return contents;
};

export const YellowNameTool = () => {
    YellowWidgets = [
        new Tools.YellowCheckEditor({ id: 161, label: Str_Froggit }),
        new Tools.YellowCheckEditor({ id: 162, label: Str_Whimsun }),
        new Tools.YellowCheckEditor({ id: 163, label: Str_Moldsmal }),
        new Tools.YellowCheckEditor({ id: 164, label: Str_Loox }),
        new Tools.YellowCheckEditor({ id: 165, label: Str_Vegetoid }),
        new Tools.YellowCheckEditor({ id: 166, label: Str_Migosp }),
        new Tools.YellowCheckEditor({ id: 67, label: Str_Napstablook }),
        new Tools.YellowCheckEditor({ id: 167, label: Str_Snowdrake }),
        new Tools.YellowCheckEditor({ id: 168, label: Str_Ice_Cap }),
        new Tools.YellowCheckEditor({ id: 169, label: Str_Gyftrot }),
        new Tools.YellowCheckEditor({ id: 170, label: Str_Doggo }),
        new Tools.YellowCheckEditor({ id: 171, label: Str_Dogamy_and_Dogaressa }),
        new Tools.YellowCheckEditor({ id: 172, label: Str_Lesser_Dog }),
        new Tools.YellowCheckEditor({ id: 173, label: Str_Greater_Dog }),
        new Tools.YellowCheckEditor({ id: 126, label: Str_Aaron_and_Woshua }),
        new Tools.YellowCheckEditor({ id: 175, label: Str_Moldbygg }),
        new Tools.YellowCheckEditor({ id: 176, label: Str_Woshua }),
        new Tools.YellowCheckEditor({ id: 177, label: Str_Temmie }),
        new Tools.YellowCheckEditor({ id: 178, label: Str_Mad_Dummy }),
        new Tools.YellowCheckEditor({ id: 112, label: Str_Shyren }),
        new Tools.YellowCheckEditor({ id: 179, label: Str_Vulkin }),
        new Tools.YellowCheckEditor({ id: 180, label: Str_Tsunderplane }),
        new Tools.YellowCheckEditor({ id: 181, label: Str_Pyrope }),
        new Tools.YellowCheckEditor({ id: 182, label: Str_Final_Froggit }),
        new Tools.YellowCheckEditor({ id: 183, label: Str_Whimsalot }),
        new Tools.YellowCheckEditor({ id: 184, label: Str_Astigmatism }),
        new Tools.YellowCheckEditor({ id: 185, label: Str_Madjick }),
        new Tools.YellowCheckEditor({ id: 186, label: Str_Knight_Knight }),
        new Tools.YellowCheckEditor({ id: 187, label: Str_Amalgamates }),
    ];

    const closeFunction = () => {
        const tool = document.querySelector("#yellowNameTool");

        const isQuit = parseInt(tool.getAttribute("isQuit")) > 0;
        for (const yellowCheckEditor of YellowWidgets) {
            if (isQuit) {
                SaveData[yellowCheckEditor.saveID] = yellowCheckEditor.originalValue;
                continue;
            }

            const widgets = Widgets[yellowCheckEditor.saveID];
            for (const widget of widgets) {
                if (widget.editor !== yellowCheckEditor.editor) {
                    widget.updateData();
                    widget.updateStyle();
                }
            }
        }

        tool.classList.add("hidden");
    };

    /**
     * @param {boolean} isChecked
     */
    const checkFunction = (isChecked) => {
        for (const yellowCheckEditor of YellowWidgets) {
            if (yellowCheckEditor.editor.checked !== isChecked) {
                yellowCheckEditor.editor.dispatchEvent(new MouseEvent("click"));
            }
        }
    };

    const contents = document.createElement("div");
    contents.setAttribute("isQuit", "1");
    contents.id = "yellowNameTool";
    contents.title = "Yellow Monster Name Tool";
    contents.className = "dialog hidden";

    const container = document.createElement("div");
    container.className = "dialogContainer";

    const toolButtons = document.createElement("div");
    toolButtons.id = "toolButtons";

    const checkAllButton = document.createElement("button");
    checkAllButton.className = "dialogButton";
    checkAllButton.innerText = "Check All";
    checkAllButton.onclick = () => {
        checkFunction(true);
    };

    const uncheckAllButton = document.createElement("button");
    uncheckAllButton.className = "dialogButton";
    uncheckAllButton.innerText = "Uncheck All";
    uncheckAllButton.onclick = () => {
        checkFunction(false);
    };

    toolButtons.append(checkAllButton);
    toolButtons.append(uncheckAllButton);

    const scrollView = document.createElement("div");
    scrollView.id = "yellowNameScrollView";
    scrollView.className = "dialogScrollView";

    for (const yellowCheckEditor of YellowWidgets) {
        scrollView.append(yellowCheckEditor.container);
    }

    const footer = document.createElement("div");
    footer.className = "dialogFooter";

    const spacer = document.createElement("div");
    spacer.className = "dialogSpacer";

    const applyButton = document.createElement("button");
    applyButton.className = "dialogButton";
    applyButton.innerText = "Apply";
    applyButton.onclick = () => {
        const tool = document.querySelector("#yellowNameTool");
        tool.setAttribute("isQuit", "0");
        closeFunction();
    };

    const closeButton = document.createElement("button");
    closeButton.className = "dialogButton";
    closeButton.innerText = "Close";
    closeButton.onclick = closeFunction;

    footer.append(spacer);
    footer.append(applyButton);
    footer.append(closeButton);

    container.append(toolButtons);
    container.append(scrollView);
    container.append(footer);

    contents.append(buildDialogHeader({ title: "Yellow monster names for the credits", closeFunction: closeFunction }));
    contents.append(container);

    return contents;
};

export const AboutDialog = () => {
    const closeFunction = () => {
        document.querySelector("#aboutDialog").classList.add("hidden");
    };

    const contents = document.createElement("div");
    contents.id = "aboutDialog";
    contents.className = "dialog hidden";

    const container = document.createElement("div");
    container.className = "dialogContainer";

    const name = document.createElement("div");
    name.id = "aboutName";
    name.innerText = document.title;

    const details = document.createElement("p");
    details.id = "aboutDetails";
    details.innerHTML = `The project can be found here:<br><a href="${GitHub_Url}" target="_blank">${GitHub_Url}</a>`;

    const thanks = document.createElement("div");
    thanks.id = "aboutThanks";
    thanks.innerText = "Special Thanks";

    const credits = document.createElement("div");
    credits.id = "aboutCredits";
    credits.innerHTML = Project_Credits.join("<br>");

    const footer = document.createElement("div");
    footer.className = "dialogFooter";

    const author = document.createElement("div");
    author.innerHTML = `Made by &nbsp; <b>${Project_Author}</b>`;

    const closeButton = document.createElement("button");
    closeButton.className = "dialogButton";
    closeButton.innerText = "Close";
    closeButton.onclick = closeFunction;

    footer.append(author);
    footer.append(closeButton);

    container.append(name);
    container.append(details);
    container.append(thanks);
    container.append(credits);
    container.append(footer);

    contents.append(buildDialogHeader({ title: "About", closeFunction: closeFunction }));
    contents.append(container);

    return contents;
};
