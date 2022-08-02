#include <QVBoxLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "src/core/pages.h"
#include "src/core/tools.h"
#include "src/core/initools.h"
#include "src/helpers.h"

PlayerPage::PlayerPage(QWidget *parent) : QTabWidget(parent)
{
	tabBar()->setDocumentMode(true);
	tabBar()->setExpanding(true);

//	##### Character #####
	QScrollArea *charArea = new QScrollArea();
	charArea->setWidgetResizable(true);
	QWidget *charWidget = new QWidget();
	QVBoxLayout *charLayout = new QVBoxLayout();
//	##### Character - Stats #####
	QGroupBox *statsGroup = new QGroupBox(QStringLiteral("Stats"));
	QVBoxLayout *statsLayout = new QVBoxLayout();
	statsLayout->addWidget(new CustomLineEdit(1, new QLabel(QStringLiteral("Name"))));
	statsLayout->addWidget(new CustomSpinBox(2, new QLabel(QStringLiteral("LV"))));
	statsLayout->addWidget(new CustomSpinBox(3, new QLabel(QStringLiteral("Max HP"))));
	statsLayout->addWidget(new CustomSpinBox(5, new QLabel(QStringLiteral("AT"))));
	CustomSpinBox *weaponAT = new CustomSpinBox(6, new QLabel(QStringLiteral("Weapon AT")));
	statsLayout->addWidget(weaponAT);
	statsLayout->addWidget(new CustomSpinBox(7, new QLabel(QStringLiteral("DF"))));
	CustomSpinBox *armorDF = new CustomSpinBox(8, new QLabel(QStringLiteral("Armor DF")));
	statsLayout->addWidget(armorDF);
	statsLayout->addWidget(new CustomSpinBox(10, new QLabel(QStringLiteral("EXP"))));
	statsLayout->addWidget(new CustomSpinBox(11, new QLabel(QStringLiteral("Gold"))));
	statsGroup->setLayout(statsLayout);
//	##### Character - Phone #####
	QGroupBox *phoneGroup = new QGroupBox(QStringLiteral("Phone"));
	QVBoxLayout *phoneLayout = new QVBoxLayout();
	for (int i = 14; i <= 28; i += 2)
	{
		phoneLayout->addWidget(new PhoneComboBox(i));
	}
	phoneGroup->setLayout(phoneLayout);
//	##### Character - Other #####
	QGroupBox *otherGroup = new QGroupBox(QStringLiteral("Other"));
	QVBoxLayout *otherLayout = new QVBoxLayout();
	otherLayout->addWidget(new CustomSpinBox(36, new QLabel(QStringLiteral("fun"))));
	otherLayout->addWidget(new PlotEdit(543, new QLabel(QStringLiteral("Plot"))));
	otherLayout->addWidget(new RoomComboBox(548, new QLabel(QStringLiteral("Room"))));
	otherLayout->addWidget(new TimeEdit(549, new QLabel(QStringLiteral("Time"))));
	otherGroup->setLayout(otherLayout);
//	##### Character - Setup #####
	charLayout->addWidget(statsGroup);
	charLayout->addWidget(phoneGroup);
	charLayout->addWidget(otherGroup);
	charLayout->addStretch();
	charWidget->setLayout(charLayout);
	charArea->setWidget(charWidget);

	addTab(charArea , QIcon(QStringLiteral(":menu-player")), QStringLiteral("Character"));

//	##### Equipment #####
	QScrollArea *equipmentArea = new QScrollArea();
	equipmentArea->setWidgetResizable(true);
	QWidget *equipmentWidget = new QWidget();
	QVBoxLayout *equipmentLayout = new QVBoxLayout();
//	##### Equipment - Inventory #####
	QGroupBox *inventoryGroup = new QGroupBox(QStringLiteral("Inventory"));
	QVBoxLayout *inventoryLayout = new QVBoxLayout();
	for (int i = 13; i <= 27; i += 2)
	{
		inventoryLayout->addWidget(new ItemComboBox(i));
	}
	inventoryGroup->setLayout(inventoryLayout);
//	##### Equipment - Dimensional Box A #####
	QGroupBox *dBoxAGroup = new QGroupBox(QStringLiteral("Dimensional Box A"));
	QVBoxLayout *dBoxALayout = new QVBoxLayout();
	for (int i = 331; i <= 340; i++)
	{
		dBoxALayout->addWidget(new ItemComboBox(i));
	}
	dBoxAGroup->setLayout(dBoxALayout);
//	##### Equipment - Dimensional Box B #####
	QGroupBox *dBoxBGroup = new QGroupBox(QStringLiteral("Dimensional Box B"));
	QVBoxLayout *dBoxBLayout = new QVBoxLayout();
	for (int i = 343; i <= 352; i++)
	{
		dBoxBLayout->addWidget(new ItemComboBox(i));
	}
	dBoxBGroup->setLayout(dBoxBLayout);
//	##### Equipment - Setup #####
	equipmentLayout->addWidget(new WeaponComboBox(29, new QLabel(QStringLiteral("Weapon")), weaponAT));
	equipmentLayout->addWidget(new ArmorComboBox(30, new QLabel(QStringLiteral("Armor")), armorDF));
	equipmentLayout->addWidget(inventoryGroup);
	equipmentLayout->addWidget(dBoxAGroup);
	equipmentLayout->addWidget(dBoxBGroup);
	equipmentLayout->addStretch();
	equipmentWidget->setLayout(equipmentLayout);
	equipmentArea->setWidget(equipmentWidget);

	addTab(equipmentArea, QIcon(QStringLiteral(":menu-ribbon")), QStringLiteral("Equipment"));

//	##### Fight #####
	QScrollArea *fightArea = new QScrollArea();
	fightArea->setWidgetResizable(true);
	QWidget *fightWidget = new QWidget();
	QVBoxLayout *fightLayout = new QVBoxLayout();
//	##### Fight - Kills #####
	QGroupBox *killsGroup = new QGroupBox(QStringLiteral("Kills"));
	QVBoxLayout *killsLayout = new QVBoxLayout();
	killsLayout->addWidget(new CustomSpinBox(12, new QLabel(QStringLiteral("Current"))));
	killsLayout->addWidget(new CustomSpinBox(232, new QLabel(QStringLiteral("Total"))));
	killsLayout->addWidget(new CustomSpinBox(233, new QLabel(Str_Ruins)));
	killsLayout->addWidget(new CustomSpinBox(234, new QLabel(Str_Snowdin)));
	killsLayout->addWidget(new CustomSpinBox(235, new QLabel(Str_Waterfall)));
	killsLayout->addWidget(new CustomSpinBox(236, new QLabel(Str_Hotland)));
	killsGroup->setLayout(killsLayout);
//	##### Fight - Previous Fight #####
	QGroupBox *prevFightGroup = new QGroupBox(QStringLiteral("Previous fight"));
	QVBoxLayout *prevFightLayout = new QVBoxLayout();
	CustomRadioButton *prevFight1 = new CustomRadioButton(41, QStringLiteral("Spare"));
	CustomRadioButton *prevFight2 = new CustomRadioButton(42, QStringLiteral("Flee"));
	CustomRadioButton *prevFight3 = new CustomRadioButton(43, QStringLiteral("Kill"));
	CustomRadioButton *prevFight4 = new CustomRadioButton(44, QStringLiteral("Bored"));
	// Unfortunately the custom widget "editor setup" prevents having a shared parent for each radio button
	connect(prevFight1->editor, &QRadioButton::clicked, this, [=] () -> void {
		prevFight2->editor->setChecked(false);
		prevFight3->editor->setChecked(false);
		prevFight4->editor->setChecked(false);
	});
	connect(prevFight2->editor, &QRadioButton::clicked, this, [=] () -> void {
		prevFight1->editor->setChecked(false);
		prevFight3->editor->setChecked(false);
		prevFight4->editor->setChecked(false);
	});
	connect(prevFight3->editor, &QRadioButton::clicked, this, [=] () -> void {
		prevFight1->editor->setChecked(false);
		prevFight2->editor->setChecked(false);
		prevFight4->editor->setChecked(false);
	});
	connect(prevFight4->editor, &QRadioButton::clicked, this, [=] () -> void {
		prevFight1->editor->setChecked(false);
		prevFight2->editor->setChecked(false);
		prevFight3->editor->setChecked(false);
	});
	prevFightLayout->addWidget(prevFight1);
	prevFightLayout->addWidget(prevFight2);
	prevFightLayout->addWidget(prevFight3);
	prevFightLayout->addWidget(prevFight4);
	prevFightGroup->setLayout(prevFightLayout);
//	##### Fight - Setup #####
	fightLayout->addWidget(killsGroup);
	fightLayout->addWidget(prevFightGroup);
	fightLayout->addStretch();
	fightWidget->setLayout(fightLayout);
	fightArea->setWidget(fightWidget);

	addTab(fightArea, QIcon(QStringLiteral(":menu-fight")), QStringLiteral("Fight"));

//	##### Events #####
	QScrollArea *eventsArea = new QScrollArea();
	eventsArea->setWidgetResizable(true);
	QWidget *eventsWidget = new QWidget();
	QVBoxLayout *eventsLayout = new QVBoxLayout();
//	##### Events - Neutral #####
	QGroupBox *neutralGroup = new QGroupBox(QStringLiteral("Neutral"));
	QVBoxLayout *neutralLayout = new QVBoxLayout();
	neutralLayout->addWidget(new CustomCheckBox(37, QStringLiteral("Hard Mode")));
	neutralLayout->addWidget(new CustomCheckBox(39, QStringLiteral("Disable encounters")));
	neutralLayout->addWidget(new CustomCheckBox(109, QStringLiteral("Used Punch Card while wearing Tough Glove")));
	neutralLayout->addWidget(new CustomCheckBox(116, QStringLiteral("Have an umbrella")));
	neutralLayout->addWidget(new CustomCheckBox(291, QStringLiteral("Ate Food")));
	neutralLayout->addWidget(new CustomCheckBox(530, QStringLiteral("Seen the cast/credits")));
	neutralGroup->setLayout(neutralLayout);
//	##### Events - Pacifist #####
	QGroupBox *pacifistGroup = new QGroupBox(QStringLiteral("Pacifist"));
	QVBoxLayout *pacifistLayout = new QVBoxLayout();
	pacifistLayout->addWidget(new CustomCheckBox(52, QStringLiteral("Cooked Instant Noodles")));
	pacifistLayout->addWidget(new CustomCheckBox(58, QStringLiteral("Spared a certain monster")));
	pacifistLayout->addWidget(new CustomCheckBox(511, QStringLiteral("Inside the True Lab")));
	pacifistLayout->addWidget(new CustomCheckBox(38, QStringLiteral("True Pacifist")));
	pacifistGroup->setLayout(pacifistLayout);
//	##### Events - Genocide #####
	QGroupBox *genocideGroup = new QGroupBox(QStringLiteral("Genocide"));
	QVBoxLayout *genocideLayout = new QVBoxLayout();
	genocideLayout->addWidget(new CustomCheckBox(252, QStringLiteral("Genocide in %1").arg(Str_Ruins)));
	genocideLayout->addWidget(new CustomCheckBox(253, QStringLiteral("Genocide in %1").arg(Str_Snowdin)));
	genocideLayout->addWidget(new CustomCheckBox(254, QStringLiteral("Genocide in %1").arg(Str_Waterfall)));
	genocideLayout->addWidget(new CustomCheckBox(255, QStringLiteral("Genocide in %1").arg(Str_Hotland)));
	genocideLayout->addWidget(new CustomCheckBox(256, QStringLiteral("Genocide in %1").arg(Str_Core)));
	genocideGroup->setLayout(genocideLayout);
//	##### Events - Counters #####
	QGroupBox *countersGroup = new QGroupBox(QStringLiteral("Counters"));
	QVBoxLayout *countersLayout = new QVBoxLayout();
	countersLayout->addWidget(new CustomSpinBox(54, new QLabel(QStringLiteral("Spared fights"))));
	countersLayout->addWidget(new CustomSpinBox(55, new QLabel(QStringLiteral("Fled fights"))));
	countersLayout->addWidget(new CustomSpinBox(56, new QLabel(QStringLiteral("Dialog skips"))));
	countersLayout->addWidget(new CustomSpinBox(90, new QLabel(QStringLiteral("Gold spent on Spider Bake Sale"))));
	countersLayout->addWidget(new CustomSpinBox(91, new QLabel(QStringLiteral("Gold spent on Nice Cream"))));
	countersLayout->addWidget(new CustomSpinBox(409, new QLabel(QStringLiteral("Gold spent on Hot Dogs"))));
	countersGroup->setLayout(countersLayout);
//	##### Events - Setup #####
	eventsLayout->addWidget(neutralGroup);
	eventsLayout->addWidget(pacifistGroup);
	eventsLayout->addWidget(genocideGroup);
	eventsLayout->addWidget(countersGroup);
	eventsLayout->addStretch();
	eventsWidget->setLayout(eventsLayout);
	eventsArea->setWidget(eventsWidget);

	addTab(eventsArea, QIcon(QStringLiteral(":menu-spaghetti")), QStringLiteral("Events"));
}

BossesPage::BossesPage(QWidget *parent) : QTabWidget(parent)
{
	tabBar()->setDocumentMode(true);
	tabBar()->setExpanding(true);

	QScrollArea *floweyArea = new QScrollArea();
	floweyArea->setWidgetResizable(true);
	QWidget *floweyWidget = new QWidget();
	QVBoxLayout *floweyLayout = new QVBoxLayout();
	floweyLayout->addWidget(new CustomSpinBox(40, new QLabel(QStringLiteral("%1 stalking").arg(Str_Flowey))));
	floweyLayout->addWidget(new CustomCheckBox(506, QStringLiteral("Killed %1").arg(Str_Flowey)));
	floweyLayout->addStretch();
	floweyWidget->setLayout(floweyLayout);
	floweyArea->setWidget(floweyWidget);

	addTab(floweyArea, QIcon(QStringLiteral(":menu-flowey")), Str_Flowey);

	QScrollArea *torielArea = new QScrollArea();
	torielArea->setWidgetResizable(true);
	QWidget *torielWidget = new QWidget();
	QVBoxLayout *torielLayout = new QVBoxLayout();
	torielLayout->addWidget(new CustomComboBox(68, new QLabel(QStringLiteral("Dog kidnapped %1's phone").arg(Str_Toriel))));
	torielLayout->addWidget(new CustomComboBox(77, new QLabel(QStringLiteral("Chosen flavor of pie"))));
	torielLayout->addWidget(new CustomSpinBox(71, new QLabel(QStringLiteral("Said \"Hello\""))));
	torielLayout->addWidget(new CustomCheckBox(72, QStringLiteral("Flirted with %1").arg(Str_Toriel)));
	torielLayout->addWidget(new CustomCheckBox(73, QStringLiteral("Called %1 \"Mom\"").arg(Str_Toriel)));
	torielLayout->addWidget(new CustomComboBox(76, new QLabel(QStringLiteral("Interaction with %1").arg(Str_Toriel))));
	torielLayout->addWidget(new CustomSpinBox(222, new QLabel(QStringLiteral("Chat with %1 (Pacifist)").arg(Str_Toriel))));
	torielLayout->addWidget(new CustomSpinBox(317, new QLabel(QStringLiteral("Checked messages from %1").arg(Str_Toriel))));
	torielLayout->addWidget(new CustomSpinBox(318, new QLabel(QStringLiteral("Received messages from %1").arg(Str_Toriel))));
	torielLayout->addStretch();
	torielWidget->setLayout(torielLayout);
	torielArea->setWidget(torielWidget);

	addTab(torielArea, QIcon(QStringLiteral(":menu-toriel")), Str_Toriel);

	QScrollArea *sansArea = new QScrollArea();
	sansArea->setWidgetResizable(true);
	QWidget *sansWidget = new QWidget();
	QVBoxLayout *sansLayout = new QVBoxLayout();
	sansLayout->addWidget(new CustomComboBox(78, new QLabel(QStringLiteral("%1 creeping in the forest").arg(Str_sans))));
	sansLayout->addWidget(new CustomComboBox(120, new QLabel(QStringLiteral("Date with %1 at %2's").arg(Str_sans, Str_Grillby))));
	sansLayout->addWidget(new CustomComboBox(422, new QLabel(QStringLiteral("Food ordered at %1's").arg(Str_Grillby))));
	sansLayout->addWidget(new CustomComboBox(444, new QLabel(QStringLiteral("Date with %1 at Mettaton Resort").arg(Str_sans))));
	sansLayout->addWidget(new CustomComboBox(528, new QLabel(QStringLiteral("Got the key to %1's room").arg(Str_sans))));
	sansLayout->addWidget(new CustomSpinBox(223, new QLabel(QStringLiteral("Chat with %1 (Pacifist)").arg(Str_sans))));
	sansLayout->addWidget(new CustomCheckBox(302, QStringLiteral("Fought %1").arg(Str_sans)));
	sansLayout->addWidget(new CustomCheckBox(303, QStringLiteral("Tried to Spare %1").arg(Str_sans)));
	sansLayout->addStretch();
	sansWidget->setLayout(sansLayout);
	sansArea->setWidget(sansWidget);

	addTab(sansArea, QIcon(QStringLiteral(":menu-sans")), Str_sans);

	QScrollArea *papyrusArea = new QScrollArea();
	papyrusArea->setWidgetResizable(true);
	QWidget *papyrusWidget = new QWidget();
	QVBoxLayout *papyrusLayout = new QVBoxLayout();
	papyrusLayout->addWidget(new CustomCheckBox(97, QStringLiteral("Flirted with %1").arg(Str_Papyrus)));
	papyrusLayout->addWidget(new CustomComboBox(98, new QLabel(QStringLiteral("Interaction with %1").arg(Str_Papyrus))));
	papyrusLayout->addWidget(new CustomCheckBox(99, QStringLiteral("Fought %1").arg(Str_Papyrus)));
	papyrusLayout->addWidget(new CustomComboBox(119, new QLabel(QStringLiteral("Date with %1").arg(Str_Papyrus))));
	papyrusLayout->addWidget(new CustomSpinBox(493, new QLabel(QStringLiteral("%1 phone calls").arg(Str_Papyrus))));
	papyrusLayout->addWidget(new CustomSpinBox(226, new QLabel(QStringLiteral("Chat with %1 (Pacifist)").arg(Str_Papyrus))));
	papyrusLayout->addWidget(new CustomCheckBox(322, QStringLiteral("Skipped the Electric Maze puzzle (Genocide)")));
	papyrusLayout->addWidget(new CustomCheckBox(321, QStringLiteral("Skipped %1's Special Attack (Genocide)").arg(Str_Papyrus)));
	papyrusLayout->addStretch();
	papyrusWidget->setLayout(papyrusLayout);
	papyrusArea->setWidget(papyrusWidget);

	addTab(papyrusArea, QIcon(QStringLiteral(":menu-papyrus")), Str_Papyrus);

	QScrollArea *undyneArea = new QScrollArea();
	undyneArea->setWidgetResizable(true);
	QWidget *undyneWidget = new QWidget();
	QVBoxLayout *undyneLayout = new QVBoxLayout();
	undyneLayout->addWidget(new CustomSpinBox(130, new QLabel(QStringLiteral("%1 fights").arg(Str_Undyne))));
	undyneLayout->addWidget(new CustomCheckBox(315, QStringLiteral("%1 got mad at the first bridge").arg(Str_Undyne)));
	undyneLayout->addWidget(new CustomCheckBox(316, QStringLiteral("%1 got mad at the large bridge").arg(Str_Undyne)));
	undyneLayout->addWidget(new CustomComboBox(381, new QLabel(QStringLiteral("Interaction with %1").arg(Str_Undyne))));
	undyneLayout->addWidget(new CustomSpinBox(382, new QLabel(QStringLiteral("%1's remaining HP").arg(Str_Undyne))));
	undyneLayout->addWidget(new CustomCheckBox(383, QStringLiteral("Escaped from %1 back to %2").arg(Str_Undyne, Str_Waterfall)));
	undyneLayout->addWidget(new CustomComboBox(420, new QLabel(QStringLiteral("Date with %1").arg(Str_Undyne))));
	undyneLayout->addWidget(new CustomCheckBox(496, QStringLiteral("%1 moved to %2's place").arg(Str_Undyne, Str_Papyrus)));
	undyneLayout->addWidget(new CustomCheckBox(501, QStringLiteral("%1 talked about the weather").arg(Str_Undyne)));
	undyneLayout->addWidget(new CustomComboBox(525, new QLabel(QStringLiteral("Interaction with %1").arg(Str_Undyne_Letter))));
	undyneLayout->addWidget(new CustomSpinBox(224, new QLabel(QStringLiteral("Chat with %1 (Pacifist)").arg(Str_Undyne))));
	undyneLayout->addWidget(new CustomCheckBox(225, QStringLiteral("%1 asked you to talk to %2 (Pacifist)").arg(Str_Undyne, Str_Napstablook)));
	undyneLayout->addWidget(new CustomCheckBox(282, QStringLiteral("Killed %1").arg(Str_Undyne_the_Undying)));
	undyneLayout->addStretch();
	undyneWidget->setLayout(undyneLayout);
	undyneArea->setWidget(undyneWidget);

	addTab(undyneArea, QIcon(QStringLiteral(":menu-undyne")), Str_Undyne);

	QScrollArea *alphysArea = new QScrollArea();
	alphysArea->setWidgetResizable(true);
	QWidget *alphysWidget = new QWidget();
	QVBoxLayout *alphysLayout = new QVBoxLayout();
	alphysLayout->addWidget(new CustomCheckBox(523, QStringLiteral("Date with %1 is available").arg(Str_Alphys)));
	alphysLayout->addWidget(new CustomComboBox(524, new QLabel(QStringLiteral("Interaction with %1").arg(Str_Alphys))));
	alphysLayout->addWidget(new CustomSpinBox(227, new QLabel(QStringLiteral("Chat with %1 (Pacifist)").arg(Str_Alphys))));
	alphysLayout->addStretch();
	alphysWidget->setLayout(alphysLayout);
	alphysArea->setWidget(alphysWidget);

	addTab(alphysArea, QIcon(QStringLiteral(":menu-alphys")), Str_Alphys);

	QScrollArea *mettatonArea = new QScrollArea();
	mettatonArea->setWidgetResizable(true);
	QWidget *mettatonWidget = new QWidget();
	QVBoxLayout *mettatonLayout = new QVBoxLayout();
	mettatonLayout->addWidget(new CustomCheckBox(319, QStringLiteral("Failed to defuse a bomb")));
	mettatonLayout->addWidget(new CustomCheckBox(309, QStringLiteral("Completed the Multicolor Tile Puzzle")));
	mettatonLayout->addWidget(new CustomCheckBox(320, QStringLiteral("Stepped on a green tile")));
	mettatonLayout->addWidget(new CustomComboBox(416, new QLabel(QStringLiteral("State of the Shooter Mode"))));
	mettatonLayout->addWidget(new CustomComboBox(455, new QLabel(QStringLiteral("Exposed %1's switch").arg(Str_Mettaton))));
	mettatonLayout->addWidget(new CustomSpinBox(229, new QLabel(QStringLiteral("Chat with %1 (Pacifist)").arg(Str_Mettaton))));
	mettatonLayout->addWidget(new CustomCheckBox(456, QStringLiteral("Killed %1").arg(Str_Mettaton)));
	mettatonLayout->addStretch();
	mettatonWidget->setLayout(mettatonLayout);
	mettatonArea->setWidget(mettatonWidget);

	addTab(mettatonArea, QIcon(QStringLiteral(":menu-mettaton")), Str_Mettaton);

	QScrollArea *asgoreArea = new QScrollArea();
	asgoreArea->setWidgetResizable(true);
	QWidget *asgoreWidget = new QWidget();
	QVBoxLayout *asgoreLayout = new QVBoxLayout();
	asgoreLayout->addWidget(new CustomSpinBox(228, new QLabel(QStringLiteral("Chat with %1 (Pacifist)").arg(Str_Asgore))));
	asgoreLayout->addWidget(new CustomCheckBox(507, QStringLiteral("Killed %1").arg(Str_Asgore)));
	asgoreLayout->addStretch();
	asgoreWidget->setLayout(asgoreLayout);
	asgoreArea->setWidget(asgoreWidget);

	addTab(asgoreArea, QIcon(QStringLiteral(":menu-asgore")), Str_Asgore);

	QScrollArea *asrielArea = new QScrollArea();
	asrielArea->setWidgetResizable(true);
	QWidget *asrielWidget = new QWidget();
	QVBoxLayout *asrielLayout = new QVBoxLayout();
	asrielLayout->addWidget(new CustomCheckBox(531, QStringLiteral("Fought %1").arg(Str_Asriel)));
	asrielLayout->addWidget(new CustomComboBox(532, new QLabel(QStringLiteral("Stage of the final fight"))));
	asrielLayout->addWidget(new CustomSpinBox(533, new QLabel(QStringLiteral("How many times re-fused"))));
	asrielLayout->addWidget(new CustomCheckBox(534, QStringLiteral("Used a Dream")));
	asrielLayout->addWidget(new CustomSpinBox(535, new QLabel(QStringLiteral("%1 turn counter").arg(Str_Asriel))));
	asrielLayout->addWidget(new CustomCheckBox(536, QStringLiteral("Saved %1").arg(Str_Undyne)));
	asrielLayout->addWidget(new CustomCheckBox(537, QStringLiteral("Saved %1").arg(Str_Alphys)));
	asrielLayout->addWidget(new CustomCheckBox(538, QStringLiteral("Saved %1 and %2").arg(Str_Papyrus, Str_sans)));
	asrielLayout->addWidget(new CustomCheckBox(539, QStringLiteral("Saved %1 and %2").arg(Str_Toriel, Str_Asgore)));
	asrielLayout->addWidget(new CustomComboBox(540, new QLabel(QStringLiteral("HP display"))));
	asrielLayout->addWidget(new CustomSpinBox(542, new QLabel(QStringLiteral("Chat with child %1").arg(Str_Asriel))));
	asrielLayout->addStretch();
	asrielWidget->setLayout(asrielLayout);
	asrielArea->setWidget(asrielWidget);

	addTab(asrielArea, QIcon(QStringLiteral(":menu-asriel")), Str_Asriel);
}

MonstersPage::MonstersPage(QWidget *parent) : QTabWidget(parent)
{
	tabBar()->setDocumentMode(true);
	tabBar()->setExpanding(true);

//	##### Common #####
	QScrollArea *commonArea = new QScrollArea();
	commonArea->setWidgetResizable(true);
	QWidget *commonWidget = new QWidget();
	QVBoxLayout *commonLayout = new QVBoxLayout();
//	##### Common - Interactions #####
	QGroupBox *interactionGroup = new QGroupBox(QStringLiteral("Interactions"));
	QVBoxLayout *interactionLayout = new QVBoxLayout();
	interactionLayout->addWidget(new CustomComboBox(53, new QLabel(QStringLiteral("Spare name color"))));
	interactionLayout->addWidget(new CustomComboBox(45, new QLabel(QStringLiteral("The first dummy"))));
	interactionLayout->addWidget(new CustomComboBox(83, new QLabel(Str_Doggo)));
	interactionLayout->addWidget(new CustomComboBox(84, new QLabel(Str_Dogamy_and_Dogaressa)));
	interactionLayout->addWidget(new CustomComboBox(85, new QLabel(Str_Greater_Dog)));
	interactionLayout->addWidget(new CustomComboBox(86, new QLabel(Str_Lesser_Dog)));
	interactionLayout->addWidget(new CustomComboBox(87, new QLabel(Str_Snowman)));
	interactionLayout->addWidget(new CustomComboBox(88, new QLabel(Str_Snowdrake)));
	interactionLayout->addWidget(new CustomComboBox(112, new QLabel(Str_Shyren)));
	interactionLayout->addWidget(new CustomComboBox(122, new QLabel(Str_Monster_Kid)));
	interactionLayout->addWidget(new CustomComboBox(312, new QLabel(Str_So_Sorry)));
	interactionLayout->addWidget(new CustomComboBox(284, new QLabel(QStringLiteral("%1 (Genocide)").arg(Str_Snowman))));
	interactionLayout->addStretch();
	interactionGroup->setLayout(interactionLayout);
	commonLayout->addWidget(interactionGroup);
//	##### Common - Neutral #####
	QGroupBox *neutralGroup = new QGroupBox(QStringLiteral("Neutral"));
	QVBoxLayout *neutralLayout = new QVBoxLayout();
	neutralLayout->addWidget(new CustomCheckBox(313, QStringLiteral("Fought %1").arg(Str_Glyde)));
	neutralGroup->setLayout(neutralLayout);
	commonLayout->addWidget(neutralGroup);
//	##### Common - Pacifist #####
	QGroupBox *pacifistGroup = new QGroupBox(QStringLiteral("Pacifist"));
	QVBoxLayout *pacifistLayout = new QVBoxLayout();
	pacifistLayout->addWidget(new CustomCheckBox(161, QStringLiteral("Spared %1").arg(Str_Froggit)));
	pacifistLayout->addWidget(new CustomCheckBox(162, QStringLiteral("Spared %1").arg(Str_Whimsun)));
	pacifistLayout->addWidget(new CustomCheckBox(163, QStringLiteral("Spared %1").arg(Str_Moldsmal)));
	pacifistLayout->addWidget(new CustomCheckBox(164, QStringLiteral("Spared %1").arg(Str_Loox)));
	pacifistLayout->addWidget(new CustomCheckBox(165, QStringLiteral("Spared %1").arg(Str_Vegetoid)));
	pacifistLayout->addWidget(new CustomCheckBox(166, QStringLiteral("Spared %1").arg(Str_Migosp)));
	pacifistLayout->addWidget(new CustomCheckBox(167, QStringLiteral("Spared %1").arg(Str_Snowdrake)));
	pacifistLayout->addWidget(new CustomCheckBox(168, QStringLiteral("Spared %1").arg(Str_Ice_Cap)));
	pacifistLayout->addWidget(new CustomCheckBox(169, QStringLiteral("Spared %1").arg(Str_Gyftrot)));
	pacifistLayout->addWidget(new CustomCheckBox(170, QStringLiteral("Spared %1").arg(Str_Doggo)));
	pacifistLayout->addWidget(new CustomCheckBox(171, QStringLiteral("Spared %1").arg(Str_Dogamy_and_Dogaressa)));
	pacifistLayout->addWidget(new CustomCheckBox(172, QStringLiteral("Spared %1").arg(Str_Lesser_Dog)));
	pacifistLayout->addWidget(new CustomCheckBox(173, QStringLiteral("Spared %1").arg(Str_Greater_Dog)));
	pacifistLayout->addWidget(new CustomCheckBox(174, QStringLiteral("Spared %1").arg(Str_Aaron)));
	pacifistLayout->addWidget(new CustomCheckBox(175, QStringLiteral("Spared %1").arg(Str_Moldbygg)));
	pacifistLayout->addWidget(new CustomCheckBox(176, QStringLiteral("Spared %1").arg(Str_Woshua)));
	pacifistLayout->addWidget(new CustomCheckBox(177, QStringLiteral("Spared %1").arg(Str_Temmie)));
	pacifistLayout->addWidget(new CustomCheckBox(178, QStringLiteral("Spared %1").arg(Str_Mad_Dummy)));
	pacifistLayout->addWidget(new CustomCheckBox(179, QStringLiteral("Spared %1").arg(Str_Vulkin)));
	pacifistLayout->addWidget(new CustomCheckBox(180, QStringLiteral("Spared %1").arg(Str_Tsunderplane)));
	pacifistLayout->addWidget(new CustomCheckBox(181, QStringLiteral("Spared %1").arg(Str_Pyrope)));
	pacifistLayout->addWidget(new CustomCheckBox(182, QStringLiteral("Spared %1").arg(Str_Final_Froggit)));
	pacifistLayout->addWidget(new CustomCheckBox(183, QStringLiteral("Spared %1").arg(Str_Whimsalot)));
	pacifistLayout->addWidget(new CustomCheckBox(184, QStringLiteral("Spared %1").arg(Str_Astigmatism)));
	pacifistLayout->addWidget(new CustomCheckBox(185, QStringLiteral("Spared %1").arg(Str_Madjick)));
	pacifistLayout->addWidget(new CustomCheckBox(186, QStringLiteral("Spared %1").arg(Str_Knight_Knight)));
	pacifistLayout->addWidget(new CustomCheckBox(187, QStringLiteral("Spared %1").arg(Str_Endogeny)));
	pacifistGroup->setLayout(pacifistLayout);
	commonLayout->addWidget(pacifistGroup);
//	##### Common - Genocide #####
	QGroupBox *genocideGroup = new QGroupBox(QStringLiteral("Genocide"));
	QVBoxLayout *genocideLayout = new QVBoxLayout();
	genocideLayout->addWidget(new CustomCheckBox(283, QStringLiteral("Killed %1").arg(Str_Glad_Dummy)));
	genocideLayout->addWidget(new CustomCheckBox(433, QStringLiteral("Killed %1").arg(Str_Royal_Guards)));
	genocideGroup->setLayout(genocideLayout);
	commonLayout->addWidget(genocideGroup);
//	##### Common - Setup #####
	commonLayout->addStretch();
	commonWidget->setLayout(commonLayout);
	commonArea->setWidget(commonWidget);

	addTab(commonArea, QIcon(QStringLiteral(":menu-froggit")), QStringLiteral("Common"));

	QScrollArea *napstablookArea = new QScrollArea();
	napstablookArea->setWidgetResizable(true);
	QWidget *napstablookWidget = new QWidget();
	QVBoxLayout *napstablookLayout = new QVBoxLayout();
	napstablookLayout->addWidget(new CustomComboBox(67, new QLabel(QStringLiteral("%1 encounter").arg(Str_Napstablook))));
	napstablookLayout->addWidget(new CustomComboBox(124, new QLabel(QStringLiteral("Date with %1").arg(Str_Napstablook))));
	napstablookLayout->addWidget(new CustomCheckBox(126, QStringLiteral("Spooked %1").arg(Str_Aaron_and_Woshua)));
	napstablookLayout->addWidget(new CustomCheckBox(440, QStringLiteral("%1 has sent you a friend request").arg(Str_NAPSTABLOOK22)));
	napstablookLayout->addWidget(new CustomCheckBox(489, QStringLiteral("Feel like garbage with %1").arg(Str_Napstablook)));
	napstablookLayout->addWidget(new CustomSpinBox(230, new QLabel(QStringLiteral("Chat with %1 (Pacifist)").arg(Str_Napstablook))));
	napstablookLayout->addStretch();
	napstablookWidget->setLayout(napstablookLayout);
	napstablookArea->setWidget(napstablookWidget);

	addTab(napstablookArea, QIcon(QStringLiteral(":menu-napstablook")), Str_Napstablook);

	QScrollArea *temmieArea = new QScrollArea();
	temmieArea->setWidgetResizable(true);
	QWidget *temmieWidget = new QWidget();
	QVBoxLayout *temmieLayout = new QVBoxLayout();
	temmieLayout->addWidget(new CustomSpinBox(296, new QLabel(QStringLiteral("%1 sale countdown").arg(Str_Temmie))));
	temmieLayout->addWidget(new CustomCheckBox(297, QStringLiteral("%1's special sale").arg(Str_Temmie)));
	temmieLayout->addWidget(new CustomCheckBox(300, QStringLiteral("Talked to the allergic %1").arg(Str_Temmie)));
	temmieLayout->addWidget(new CustomCheckBox(307, QStringLiteral("Sent %1 to \"cool leg\"").arg(Str_Temmie)));
	temmieLayout->addStretch();
	temmieWidget->setLayout(temmieLayout);
	temmieArea->setWidget(temmieWidget);

	addTab(temmieArea, QIcon(QStringLiteral(":menu-temmie")), Str_Temmie);

	QScrollArea *muffetArea = new QScrollArea();
	muffetArea->setWidgetResizable(true);
	QWidget *muffetWidget = new QWidget();
	QVBoxLayout *muffetLayout = new QVBoxLayout();
	muffetLayout->addWidget(new CustomSpinBox(413, new QLabel(QStringLiteral("%1 bribe price").arg(Str_Muffet))));
	muffetLayout->addWidget(new CustomSpinBox(414, new QLabel(QStringLiteral("Gold spent on bribing %1").arg(Str_Muffet))));
	muffetLayout->addWidget(new CustomComboBox(427, new QLabel(QStringLiteral("Conversation with %1").arg(Str_Muffet))));
	muffetLayout->addWidget(new CustomCheckBox(428, QStringLiteral("Killed %1").arg(Str_Muffet)));
	muffetLayout->addStretch();
	muffetWidget->setLayout(muffetLayout);
	muffetArea->setWidget(muffetWidget);

	addTab(muffetArea, QIcon(QStringLiteral(":menu-muffet")), Str_Muffet);

	QScrollArea *riverPersonArea = new QScrollArea();
	riverPersonArea->setWidgetResizable(true);
	QWidget *riverPersonWidget = new QWidget();
	QVBoxLayout *riverPersonLayout = new QVBoxLayout();
	riverPersonLayout->addWidget(new CustomComboBox(490, new QLabel(QStringLiteral("Destination"))));
	riverPersonLayout->addWidget(new CustomSpinBox(491, new QLabel(QStringLiteral("Boat rides"))));
	riverPersonLayout->addWidget(new CustomCheckBox(492, QStringLiteral("The boat is a dog")));
	riverPersonLayout->addStretch();
	riverPersonWidget->setLayout(riverPersonLayout);
	riverPersonArea->setWidget(riverPersonWidget);

	addTab(riverPersonArea, QIcon(QStringLiteral(":menu-riverperson")), Str_River_Person);
}

LocationsPage::LocationsPage(QWidget *parent) : QTabWidget(parent)
{
	tabBar()->setDocumentMode(true);
	tabBar()->setExpanding(true);

	QScrollArea *ruinsArea = new QScrollArea();
	ruinsArea->setWidgetResizable(true);
	QWidget *ruinsWidget = new QWidget();
	QVBoxLayout *ruinsLayout = new QVBoxLayout();
	ruinsLayout->addWidget(new CustomCheckBox(131, QStringLiteral("Found the Faded Ribbon")));
	ruinsLayout->addWidget(new CustomCheckBox(133, QStringLiteral("Found the Toy Knife")));
	ruinsLayout->addWidget(new CustomCheckBox(61, QStringLiteral("Tutorial %1 encountered").arg(Str_Froggit)));
	ruinsLayout->addWidget(new CustomCheckBox(66, QStringLiteral("First rock pushed")));
	ruinsLayout->addWidget(new CustomCheckBox(63, QStringLiteral("Second rock pushed")));
	ruinsLayout->addWidget(new CustomCheckBox(62, QStringLiteral("Third rock pushed")));
	ruinsLayout->addWidget(new CustomCheckBox(64, QStringLiteral("Fourth rock asked to move")));
	ruinsLayout->addWidget(new CustomComboBox(65, new QLabel(QStringLiteral("Monster Candy bowl"))));
	ruinsLayout->addWidget(new CustomSpinBox(74, new QLabel(QStringLiteral("Pillar switch activations"))));
	ruinsLayout->addWidget(new CustomSpinBox(82, new QLabel(QStringLiteral("Wrong pillar switch activations"))));
	ruinsLayout->addWidget(new CustomCheckBox(81, QStringLiteral("Learned about \"water sausages\"")));
	ruinsLayout->addWidget(new CustomComboBox(134, new QLabel(QStringLiteral("%1's pie").arg(Str_Toriel))));
	ruinsLayout->addWidget(new CustomSpinBox(75, new QLabel(QStringLiteral("Tried to exit %1").arg(Str_Ruins))));
	ruinsLayout->addStretch();
	ruinsWidget->setLayout(ruinsLayout);
	ruinsArea->setWidget(ruinsWidget);

	addTab(ruinsArea, QIcon(QStringLiteral(":menu-toriel")), Str_Ruins);

	QScrollArea *snowdinArea = new QScrollArea();
	snowdinArea->setWidgetResizable(true);
	QWidget *snowdinWidget = new QWidget();
	QVBoxLayout *snowdinLayout = new QVBoxLayout();
	snowdinLayout->addWidget(new CustomSpinBox(101, new QLabel(QStringLiteral("Forest encounters"))));
	snowdinLayout->addWidget(new CustomComboBox(306, new QLabel(QStringLiteral("Entering %1 forest").arg(Str_Snowdin))));
	snowdinLayout->addWidget(new CustomCheckBox(285, QStringLiteral("Interacted with %1's puzzle").arg(Str_sans)));
	snowdinLayout->addWidget(new CustomComboBox(89, new QLabel(QStringLiteral("\"Harder\" puzzle"))));
	snowdinLayout->addWidget(new CustomComboBox(93, new QLabel(QStringLiteral("%1's spaghetti trap").arg(Str_Papyrus))));
	snowdinLayout->addWidget(new CustomSpinBox(94, new QLabel(QStringLiteral("XO puzzle resets"))));
	snowdinLayout->addWidget(new CustomComboBox(95, new QLabel(QStringLiteral("Buried switch"))));
	snowdinLayout->addWidget(new CustomCheckBox(96, QStringLiteral("Found 30G in a snow poff")));
	snowdinLayout->addWidget(new CustomCheckBox(308, QStringLiteral("The \"Wrong Number\" event")));
	snowdinLayout->addWidget(new CustomCheckBox(418, QStringLiteral("Won the Ball Game")));
	snowdinLayout->addWidget(new CustomCheckBox(105, QStringLiteral("Placed googly eyes on %1").arg(Str_Gyftrot)));
	snowdinLayout->addWidget(new CustomComboBox(103, new QLabel(QStringLiteral("Interaction with Snowed Inn"))));
	snowdinLayout->addWidget(new CustomCheckBox(104, QStringLiteral("Staying at Snowed Inn")));
	snowdinLayout->addWidget(new CustomCheckBox(113, QStringLiteral("Found %1 in the kitchen").arg(Str_Annoying_Dog)));
	snowdinLayout->addWidget(new CustomCheckBox(114, QStringLiteral("Found 20G inside the \"saggy old couch\"")));
	snowdinLayout->addWidget(new CustomCheckBox(314, QStringLiteral("Checked %1's kitchen after the date").arg(Str_Papyrus)));
	snowdinLayout->addWidget(new CustomCheckBox(292, QStringLiteral("Tried to pet the dog in the \"dev room\"")));
	snowdinLayout->addWidget(new CustomCheckBox(286, QStringLiteral("Stole from the shop (Genocide)")));
	snowdinLayout->addStretch();
	snowdinWidget->setLayout(snowdinLayout);
	snowdinArea->setWidget(snowdinWidget);

	addTab(snowdinArea, QIcon(QStringLiteral(":menu-papyrus")), Str_Snowdin);

	QScrollArea *waterfallArea = new QScrollArea();
	waterfallArea->setWidgetResizable(true);
	QWidget *waterfallWidget = new QWidget();
	QVBoxLayout *waterfallLayout = new QVBoxLayout();
	waterfallLayout->addWidget(new CustomCheckBox(136, QStringLiteral("Found the Old Tutu")));
	waterfallLayout->addWidget(new CustomCheckBox(137, QStringLiteral("Found the Ballet Shoes")));
	waterfallLayout->addWidget(new CustomSpinBox(388, new QLabel(QStringLiteral("%1 (first area) encounters").arg(Str_Waterfall))));
	waterfallLayout->addWidget(new CustomSpinBox(389, new QLabel(QStringLiteral("%1 (second area) encounters").arg(Str_Waterfall))));
	waterfallLayout->addWidget(new CustomCheckBox(417, QStringLiteral("Solved the first Bridge Seed Puzzle")));
	waterfallLayout->addWidget(new CustomCheckBox(135, QStringLiteral("Got the Abandoned Quiche")));
	waterfallLayout->addWidget(new CustomComboBox(106, new QLabel(QStringLiteral("Your armor when %1 called").arg(Str_Papyrus))));
	waterfallLayout->addWidget(new CustomCheckBox(107, QStringLiteral("Lied about your armor")));
	waterfallLayout->addWidget(new CustomComboBox(108, new QLabel(QStringLiteral("Your armor when %1 attacked").arg(Str_Undyne))));
	waterfallLayout->addWidget(new CustomCheckBox(110, QStringLiteral("Talked to Nice Cream Guy at %1").arg(Str_Waterfall)));
	waterfallLayout->addWidget(new CustomSpinBox(111, new QLabel(QStringLiteral("Punch Cards"))));
	waterfallLayout->addWidget(new CustomComboBox(121, new QLabel(QStringLiteral("Met %1 in the rain").arg(Str_Monster_Kid))));
	waterfallLayout->addWidget(new CustomCheckBox(122, QStringLiteral("Interacted with Trash Zone SAVE Point")));
	waterfallLayout->addWidget(new CustomComboBox(139, new QLabel(QStringLiteral("Astronaut Food cooler"))));
	waterfallLayout->addWidget(new CustomComboBox(386, new QLabel(QStringLiteral("Interaction with %1").arg(Str_Mad_Dummy))));
	waterfallLayout->addWidget(new CustomComboBox(125, new QLabel(QStringLiteral("Spooky tune playing"))));
	waterfallLayout->addWidget(new CustomCheckBox(464, QStringLiteral("Unlocked %1's house").arg(Str_Mettaton)));
	waterfallLayout->addWidget(new CustomCheckBox(310, QStringLiteral("Talked to Clam Girl")));
	waterfallLayout->addWidget(new CustomComboBox(127, new QLabel(QStringLiteral("Talked with %1").arg(Str_Gerson))));
	waterfallLayout->addWidget(new CustomCheckBox(117, QStringLiteral("Placed an umbrella on a statue")));
	waterfallLayout->addWidget(new CustomCheckBox(387, QStringLiteral("Solved the Piano Puzzle")));
	waterfallLayout->addWidget(new CustomComboBox(138, new QLabel(QStringLiteral("Legendary artifact"))));
	waterfallLayout->addWidget(new CustomCheckBox(301, QStringLiteral("Solved glowshroom puzzle")));
	waterfallLayout->addWidget(new CustomComboBox(311, new QLabel(QStringLiteral("Interaction with Elder Puzzler"))));
	waterfallLayout->addWidget(new CustomComboBox(527, new QLabel(QStringLiteral("Interaction with %1").arg(Str_Onionsan))));
	waterfallLayout->addWidget(new CustomComboBox(129, new QLabel(QStringLiteral("%1 tripped on a bridge").arg(Str_Monster_Kid))));
	waterfallLayout->addStretch();
	waterfallWidget->setLayout(waterfallLayout);
	waterfallArea->setWidget(waterfallWidget);

	addTab(waterfallArea, QIcon(QStringLiteral(":menu-undyne")), Str_Waterfall);

	QScrollArea *hotlandArea = new QScrollArea();
	hotlandArea->setWidgetResizable(true);
	QWidget *hotlandWidget = new QWidget();
	QVBoxLayout *hotlandLayout = new QVBoxLayout();
	hotlandLayout->addWidget(new CustomCheckBox(141, QStringLiteral("Found the Burnt Pan")));
	hotlandLayout->addWidget(new CustomCheckBox(142, QStringLiteral("Found the Stained Apron")));
	hotlandLayout->addWidget(new CustomSpinBox(439, new QLabel(QStringLiteral("%1 encounters").arg(Str_Hotland))));
	hotlandLayout->addWidget(new CustomComboBox(385, new QLabel(QStringLiteral("%1 calls at the entrance to %2").arg(Str_Papyrus, Str_Hotland))));
	hotlandLayout->addWidget(new CustomCheckBox(397, QStringLiteral("Have a cup of water")));
	hotlandLayout->addWidget(new CustomSpinBox(471, new QLabel(QStringLiteral("Drinks taken from the water cooler"))));
	hotlandLayout->addWidget(new CustomSpinBox(472, new QLabel(QStringLiteral("Drinks wasted in front of %1").arg(Str_Undyne))));
	hotlandLayout->addWidget(new CustomSpinBox(384, new QLabel(QStringLiteral("Water poured on the ground"))));
	hotlandLayout->addWidget(new CustomCheckBox(140, QStringLiteral("Got the Instant Noodles")));
	hotlandLayout->addWidget(new CustomCheckBox(281, QStringLiteral("Nice Cream is sold out")));
	hotlandLayout->addWidget(new CustomSpinBox(400, new QLabel(QStringLiteral("Last message received from %1").arg(Str_Alphys))));
	hotlandLayout->addWidget(new CustomCheckBox(435, QStringLiteral("Pressed all three switches on the conveyor")));
	hotlandLayout->addWidget(new CustomCheckBox(402, QStringLiteral("Deactivated the first group of lasers")));
	hotlandLayout->addWidget(new CustomCheckBox(403, QStringLiteral("Activated lasers at MTT News")));
	hotlandLayout->addWidget(new CustomSpinBox(426, new QLabel(QStringLiteral("Bombs defused during MTT News"))));
	hotlandLayout->addWidget(new CustomCheckBox(404, QStringLiteral("Deactivated the laser near Shooting Puzzle")));
	hotlandLayout->addWidget(new CustomCheckBox(405, QStringLiteral("Solved the west Shooting Puzzle")));
	hotlandLayout->addWidget(new CustomCheckBox(406, QStringLiteral("Solved the east Shooting Puzzle")));
	hotlandLayout->addWidget(new CustomCheckBox(408, QStringLiteral("Failed jet pack sequence")));
	hotlandLayout->addWidget(new CustomSpinBox(410, new QLabel(QStringLiteral("Hot Dogs bought"))));
	hotlandLayout->addWidget(new CustomSpinBox(411, new QLabel(QStringLiteral("Total Hot Dogs placed on head"))));
	hotlandLayout->addWidget(new CustomCheckBox(412, QStringLiteral("Reached the limit on Head-Dogs")));
	hotlandLayout->addWidget(new CustomComboBox(429, new QLabel(QStringLiteral("Current elevator floor"))));
	hotlandLayout->addWidget(new CustomCheckBox(430, QStringLiteral("Solved the south Shooting Puzzle")));
	hotlandLayout->addWidget(new CustomCheckBox(431, QStringLiteral("Solved the north Shooting Puzzle")));
	hotlandLayout->addWidget(new CustomCheckBox(432, QStringLiteral("%1 mentioned mind control").arg(Str_Undyne)));
	hotlandLayout->addWidget(new CustomCheckBox(434, QStringLiteral("Bought something from %1").arg(Str_Muffet)));
	hotlandLayout->addWidget(new CustomComboBox(465, new QLabel(QStringLiteral("Flamey challenge"))));
	hotlandLayout->addWidget(new CustomCheckBox(293, QStringLiteral("Delivered Sea Tea at %1").arg(Str_MTT_Resort)));
	hotlandLayout->addWidget(new CustomCheckBox(294, QStringLiteral("Delivered Cinnamon Bun at %1").arg(Str_MTT_Resort)));
	hotlandLayout->addWidget(new CustomCheckBox(295, QStringLiteral("Delivered Hot Dog at %1").arg(Str_MTT_Resort)));
	hotlandLayout->addWidget(new CustomComboBox(298, new QLabel(QStringLiteral("Staying at %1").arg(Str_MTT_Resort))));
	hotlandLayout->addWidget(new CustomComboBox(436, new QLabel(QStringLiteral("Talked with %1").arg(Str_Bratty_and_Catty))));
	hotlandLayout->addWidget(new CustomComboBox(437, new QLabel(QStringLiteral("Talked with %1 about %2").arg(Str_Bratty_and_Catty, Str_Mettaton))));
	hotlandLayout->addWidget(new CustomComboBox(438, new QLabel(QStringLiteral("Talked with %1 about %2").arg(Str_Bratty_and_Catty, Str_Alphys))));
	hotlandLayout->addWidget(new CustomComboBox(466, new QLabel(QStringLiteral("Interaction with %1").arg(Str_Burger_Pants))));
	hotlandLayout->addWidget(new CustomComboBox(467, new QLabel(QStringLiteral("Talked with %1 about %2").arg(Str_Burger_Pants, Str_Mettaton))));
	hotlandLayout->addWidget(new CustomComboBox(468, new QLabel(QStringLiteral("Chat with %1, %2").arg(Str_Burger_Pants, Str_Bratty_and_Catty))));
	hotlandLayout->addWidget(new CustomCheckBox(473, QStringLiteral("Bought the Empty Gun")));
	hotlandLayout->addWidget(new CustomCheckBox(474, QStringLiteral("Bought the Cowboy Hat")));
	hotlandLayout->addWidget(new CustomCheckBox(475, QStringLiteral("Bought the Mystery Key")));
	hotlandLayout->addWidget(new CustomCheckBox(476, QStringLiteral("Bought the Face Steak")));
	hotlandLayout->addWidget(new CustomCheckBox(398, QStringLiteral("Disable %1's phone calls (Genocide)").arg(Str_Alphys)));
	hotlandLayout->addWidget(new CustomCheckBox(399, QStringLiteral("Disable %1's messages (Genocide)").arg(Str_Alphys)));
	hotlandLayout->addWidget(new CustomCheckBox(287, QStringLiteral("Stole from %1 (Genocide)").arg(Str_Bratty_and_Catty)));
	hotlandLayout->addStretch();
	hotlandWidget->setLayout(hotlandLayout);
	hotlandArea->setWidget(hotlandWidget);

	addTab(hotlandArea, QIcon(QStringLiteral(":menu-muffet")), Str_Hotland);

	QScrollArea *coreArea = new QScrollArea();
	coreArea->setWidgetResizable(true);
	QWidget *coreWidget = new QWidget();
	QVBoxLayout *coreLayout = new QVBoxLayout();
	coreLayout->addWidget(new CustomSpinBox(454, new QLabel(QStringLiteral("%1 (first area) encounters").arg(Str_Core))));
	coreLayout->addWidget(new CustomSpinBox(457, new QLabel(QStringLiteral("%1 (second area) encounters").arg(Str_Core))));
	coreLayout->addWidget(new CustomCheckBox(445, QStringLiteral("Tried to use the elevator in the Core Lobby")));
	coreLayout->addWidget(new CustomCheckBox(446, QStringLiteral("Went right in the Core Lobby")));
	coreLayout->addWidget(new CustomCheckBox(447, QStringLiteral("Went a bit to the right in the first crossroads")));
	coreLayout->addWidget(new CustomCheckBox(448, QStringLiteral("Went up in the first crossroads")));
	coreLayout->addWidget(new CustomCheckBox(143, QStringLiteral("Got a Glamburger from a trashcan")));
	coreLayout->addWidget(new CustomCheckBox(144, QStringLiteral("Got 100G from a trashcan")));
	coreLayout->addWidget(new CustomCheckBox(449, QStringLiteral("Solved the Sage's Path")));
	coreLayout->addWidget(new CustomComboBox(452, new QLabel(QStringLiteral("Ambushed on the Warrior's Path"))));
	coreLayout->addWidget(new CustomCheckBox(450, QStringLiteral("Solved the Warrior's Path")));
	coreLayout->addWidget(new CustomCheckBox(451, QStringLiteral("Waited for 60 seconds on the final force field")));
	coreLayout->addStretch();
	coreWidget->setLayout(coreLayout);
	coreArea->setWidget(coreWidget);

	addTab(coreArea, QIcon(QStringLiteral(":menu-mettaton")), Str_Core);

	QScrollArea *newHomeArea = new QScrollArea();
	newHomeArea->setWidgetResizable(true);
	QWidget *newHomeWidget = new QWidget();
	QVBoxLayout *newHomeLayout = new QVBoxLayout();
	newHomeLayout->addWidget(new CustomCheckBox(145, QStringLiteral("Found the Worn Dagger")));
	newHomeLayout->addWidget(new CustomCheckBox(146, QStringLiteral("Found the Heart Locket")));
	newHomeLayout->addWidget(new CustomComboBox(462, new QLabel(QStringLiteral("Floor of the %1 elevator").arg(Str_Castle))));
	newHomeLayout->addWidget(new CustomCheckBox(463, QStringLiteral("Used the elevator for the first time")));
	newHomeLayout->addWidget(new CustomComboBox(481, new QLabel(QStringLiteral("The Tale of the Fallen Human"))));
	newHomeLayout->addWidget(new CustomCheckBox(483, QStringLiteral("Got the key in the kitchen")));
	newHomeLayout->addWidget(new CustomCheckBox(484, QStringLiteral("Got the key in the hallway")));
	newHomeLayout->addWidget(new CustomComboBox(485, new QLabel(QStringLiteral("Padlocks in the %1").arg(Str_Castle))));
	newHomeLayout->addWidget(new CustomSpinBox(486, new QLabel(QStringLiteral("Story heard (the kitchen)"))));
	newHomeLayout->addWidget(new CustomSpinBox(487, new QLabel(QStringLiteral("Story heard (the hallway)"))));
	newHomeLayout->addWidget(new CustomCheckBox(488, QStringLiteral("Have unfinished business?")));
	newHomeLayout->addWidget(new CustomComboBox(541, new QLabel(QStringLiteral("True Pacifist conversation"))));
	newHomeLayout->addStretch();
	newHomeWidget->setLayout(newHomeLayout);
	newHomeArea->setWidget(newHomeWidget);

	addTab(newHomeArea, QIcon(QStringLiteral(":menu-asgore")), Str_Castle);

	QScrollArea *trueLabArea = new QScrollArea();
	trueLabArea->setWidgetResizable(true);
	QWidget *trueLabWidget = new QWidget();
	QVBoxLayout *trueLabLayout = new QVBoxLayout();
	trueLabLayout->addWidget(new CustomCheckBox(510, QStringLiteral("Entered True Lab lobby")));
	trueLabLayout->addWidget(new CustomSpinBox(526, new QLabel(QStringLiteral("Potato Chisps bought")))); // This is misspelled in purpose, just like in the game
	trueLabLayout->addWidget(new CustomComboBox(512, new QLabel(QStringLiteral("Interaction with Red switch"))));
	trueLabLayout->addWidget(new CustomComboBox(513, new QLabel(QStringLiteral("Interaction with Blue switch"))));
	trueLabLayout->addWidget(new CustomComboBox(514, new QLabel(QStringLiteral("Interaction with Green switch"))));
	trueLabLayout->addWidget(new CustomComboBox(515, new QLabel(QStringLiteral("Interaction with Yellow switch"))));
	trueLabLayout->addWidget(new CustomCheckBox(516, QStringLiteral("Finished talking to %1").arg(Str_Alphys)));
	trueLabLayout->addWidget(new CustomSpinBox(517, new QLabel(QStringLiteral("Sink interactions"))));
	trueLabLayout->addWidget(new CustomComboBox(518, new QLabel(QStringLiteral("Red key location"))));
	trueLabLayout->addWidget(new CustomCheckBox(519, QStringLiteral("Spared %1").arg(Str_Reaper_Bird)));
	trueLabLayout->addWidget(new CustomCheckBox(520, QStringLiteral("Spared %1").arg(Str_Lemon_Bread)));
	trueLabLayout->addWidget(new CustomCheckBox(521, QStringLiteral("Turned on the lab's ventilation")));
	trueLabLayout->addWidget(new CustomCheckBox(522, QStringLiteral("Restored power to the elevator")));
	trueLabLayout->addStretch();
	trueLabWidget->setLayout(trueLabLayout);
	trueLabArea->setWidget(trueLabWidget);

	addTab(trueLabArea, QIcon(QStringLiteral(":menu-alphys")), Str_True_Lab);
}

DebugPage::DebugPage(QWidget *parent) : QScrollArea(parent)
{
	setWidgetResizable(true);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(new CustomCheckBox(35, QStringLiteral("Bypass kill counters")));
	mainLayout->addWidget(new CustomSpinBox(57, new QLabel(QStringLiteral("Murder level override"))));
	mainLayout->addWidget(new CustomCheckBox(59, QStringLiteral("Debug text skip")));
	mainLayout->addStretch();

	QWidget *window = new QWidget();
	window->setLayout(mainLayout);
	setWidget(window);
}

ShrinePage::ShrinePage(QWidget *parent) : QScrollArea(parent)
{
	setWidgetResizable(true);

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(new CustomCheckBox(327, QStringLiteral("Tried to use the donation box")));
	mainLayout->addWidget(new CustomSpinBox(323, new QLabel(QStringLiteral("Gold donated"))));
	mainLayout->addWidget(new CustomSpinBox(324, new QLabel(QStringLiteral("Donation goal"))));
	mainLayout->addWidget(new CustomSpinBox(325, new QLabel(QStringLiteral("Reached donation goal"))));
	mainLayout->addWidget(new CustomSpinBox(326, new QLabel(QStringLiteral("Dog Shrine upgrades"))));
	mainLayout->addStretch();

	QWidget *window = new QWidget();
	window->setLayout(mainLayout);
	setWidget(window);
}

IniPage::IniPage(QWidget *parent) : QScrollArea(parent)
{
	setWidgetResizable(true);

	QVBoxLayout *mainLayout = new QVBoxLayout();

	QGroupBox *generalGroup = new QGroupBox(QStringLiteral("General"));
	QVBoxLayout *generalLayout = new QVBoxLayout();
	generalLayout->addWidget(new IniSpinBox(QStringLiteral("BC"), new QLabel(QStringLiteral("BC"))));
	generalLayout->addWidget(new IniCheckBox("BH", QStringLiteral("BH")));
	generalLayout->addWidget(new IniCheckBox("BP", QStringLiteral("BP")));
	generalLayout->addWidget(new IniCheckBox("BW", QStringLiteral("BW")));
	generalLayout->addWidget(new IniCheckBox("CH", QStringLiteral("CH")));
	generalLayout->addWidget(new IniCheckBox("CP", QStringLiteral("CP")));
	generalLayout->addWidget(new IniSpinBox("Gameover", new QLabel(QStringLiteral("Gameover"))));
	generalLayout->addWidget(new IniSpinBox("Kills", new QLabel(QStringLiteral("Kills"))));
	generalLayout->addWidget(new IniSpinBox("Love", new QLabel(QStringLiteral("Love"))));
	generalLayout->addWidget(new IniLineEdit("Name", new QLabel(QStringLiteral("Name"))));
	generalLayout->addWidget(new IniSpinBox("Room", new QLabel(QStringLiteral("Room"))));
	generalLayout->addWidget(new IniCheckBox("Tale", QStringLiteral("Tale")));
	generalLayout->addWidget(new IniSpinBox("Time", new QLabel(QStringLiteral("Time"))));
	generalLayout->addWidget(new IniCheckBox("Truth", QStringLiteral("Truth")));
	generalLayout->addWidget(new IniSpinBox("Won", new QLabel(QStringLiteral("Won"))));
	generalLayout->addWidget(new IniSpinBox("fun", new QLabel(QStringLiteral("fun"))));
	generalGroup->setLayout(generalLayout);
	mainLayout->addWidget(generalGroup);

	QGroupBox *floweyGroup = new QGroupBox(QStringLiteral("Flowey"));
	QVBoxLayout *floweyLayout = new QVBoxLayout();
	floweyLayout->addWidget(new IniCheckBox("Flowey/AF", QStringLiteral("AF")));
	floweyLayout->addWidget(new IniCheckBox("Flowey/AK", QStringLiteral("AK")));
	floweyLayout->addWidget(new IniCheckBox("Flowey/Alter", QStringLiteral("Alter")));
	floweyLayout->addWidget(new IniSpinBox("Flowey/CHANGE", new QLabel(QStringLiteral("CHANGE"))));
	floweyLayout->addWidget(new IniCheckBox("Flowey/CK", QStringLiteral("CK")));
	floweyLayout->addWidget(new IniSpinBox("Flowey/EX", new QLabel(QStringLiteral("EX"))));
	floweyLayout->addWidget(new IniCheckBox("Flowey/FloweyExplain1", QStringLiteral("FloweyExplain1")));
	floweyLayout->addWidget(new IniCheckBox("Flowey/IK", QStringLiteral("IK")));
	floweyLayout->addWidget(new IniCheckBox("Flowey/K", QStringLiteral("K")));
	floweyLayout->addWidget(new IniSpinBox("Flowey/Met1", new QLabel(QStringLiteral("Met1"))));
	floweyLayout->addWidget(new IniCheckBox("Flowey/NK", QStringLiteral("NK")));
	floweyLayout->addWidget(new IniCheckBox("Flowey/SK", QStringLiteral("SK")));
	floweyLayout->addWidget(new IniCheckBox("Flowey/SPECIALK", QStringLiteral("SPECIALK")));
	floweyLayout->addWidget(new IniCheckBox("Flowey/alter2", QStringLiteral("alter2")));
	floweyLayout->addWidget(new IniCheckBox("Flowey/truename", QStringLiteral("truename")));
	floweyGroup->setLayout(floweyLayout);
	mainLayout->addWidget(floweyGroup);

	QGroupBox *torielGroup = new QGroupBox(QStringLiteral("Toriel"));
	QVBoxLayout *torielLayout = new QVBoxLayout();
	torielLayout->addWidget(new IniSpinBox("Toriel/Bscotch", new QLabel(QStringLiteral("Bscotch"))));
	torielLayout->addWidget(new IniSpinBox("Toriel/TK", new QLabel(QStringLiteral("TK"))));
	torielLayout->addWidget(new IniSpinBox("Toriel/TS", new QLabel(QStringLiteral("TS"))));
	torielGroup->setLayout(torielLayout);
	mainLayout->addWidget(torielGroup);

	QGroupBox *sansGroup = new QGroupBox(QStringLiteral("Sans"));
	QVBoxLayout *sansLayout = new QVBoxLayout();
	sansLayout->addWidget(new IniCheckBox("Sans/EndMet", QStringLiteral("EndMet")));
	sansLayout->addWidget(new IniSpinBox("Sans/F", new QLabel(QStringLiteral("F"))));
	sansLayout->addWidget(new IniSpinBox("Sans/Intro", new QLabel(QStringLiteral("Intro"))));
	sansLayout->addWidget(new IniSpinBox("Sans/M1", new QLabel(QStringLiteral("M1"))));
	sansLayout->addWidget(new IniSpinBox("Sans/MeetLv", new QLabel(QStringLiteral("MeetLv"))));
	sansLayout->addWidget(new IniSpinBox("Sans/MeetLv1", new QLabel(QStringLiteral("MeetLv1"))));
	sansLayout->addWidget(new IniSpinBox("Sans/MeetLv2", new QLabel(QStringLiteral("MeetLv2"))));
	sansLayout->addWidget(new IniSpinBox("Sans/MP", new QLabel(QStringLiteral("MP"))));
	sansLayout->addWidget(new IniSpinBox("Sans/Pass", new QLabel(QStringLiteral("Pass"))));
	sansLayout->addWidget(new IniSpinBox("Sans/SK", new QLabel(QStringLiteral("SK"))));
	sansLayout->addWidget(new IniSpinBox("Sans/SS", new QLabel(QStringLiteral("SS"))));
	sansLayout->addWidget(new IniSpinBox("Sans/SS2", new QLabel(QStringLiteral("SS2"))));
	sansGroup->setLayout(sansLayout);
	mainLayout->addWidget(sansGroup);

	QGroupBox *papyrusGroup = new QGroupBox(QStringLiteral("Papyrus"));
	QVBoxLayout *papyrusLayout = new QVBoxLayout();
	papyrusLayout->addWidget(new IniSpinBox("Papyrus/M1", new QLabel(QStringLiteral("M1"))));
	papyrusLayout->addWidget(new IniSpinBox("Papyrus/PD", new QLabel(QStringLiteral("PD"))));
	papyrusLayout->addWidget(new IniSpinBox("Papyrus/PK", new QLabel(QStringLiteral("PK"))));
	papyrusLayout->addWidget(new IniSpinBox("Papyrus/PS", new QLabel(QStringLiteral("PS"))));
	papyrusGroup->setLayout(papyrusLayout);
	mainLayout->addWidget(papyrusGroup);

	QGroupBox *undyneGroup = new QGroupBox(QStringLiteral("Undyne"));
	QVBoxLayout *undyneLayout = new QVBoxLayout();
	undyneLayout->addWidget(new IniSpinBox("Undyne/UD", new QLabel(QStringLiteral("UD"))));
	undyneGroup->setLayout(undyneLayout);
	mainLayout->addWidget(undyneGroup);

	QGroupBox *alphysGroup = new QGroupBox(QStringLiteral("Alphys"));
	QVBoxLayout *alphysLayout = new QVBoxLayout();
	alphysLayout->addWidget(new IniSpinBox("Alphys/AD", new QLabel(QStringLiteral("AD"))));
	alphysGroup->setLayout(alphysLayout);
	mainLayout->addWidget(alphysGroup);

	QGroupBox *mttGroup = new QGroupBox(QStringLiteral("MTT"));
	QVBoxLayout *mttLayout = new QVBoxLayout();
	mttLayout->addWidget(new IniSpinBox("MTT/EssayNo", new QLabel(QStringLiteral("EssayNo"))));
	mttGroup->setLayout(mttLayout);
	mainLayout->addWidget(mttGroup);

	QGroupBox *mettGroup = new QGroupBox(QStringLiteral("Mett"));
	QVBoxLayout *mettLayout = new QVBoxLayout();
	mettLayout->addWidget(new IniCheckBox("Mett/O", QStringLiteral("O")));
	mettGroup->setLayout(mettLayout);
	mainLayout->addWidget(mettGroup);

	QGroupBox *mettatonGroup = new QGroupBox(QStringLiteral("Mettaton"));
	QVBoxLayout *mettatonLayout = new QVBoxLayout();
	mettatonLayout->addWidget(new IniCheckBox("Mettaton/BossMet", QStringLiteral("BossMet")));
	mettatonGroup->setLayout(mettatonLayout);
	mainLayout->addWidget(mettatonGroup);

	QGroupBox *asgoreGroup = new QGroupBox(QStringLiteral("General"));
	QVBoxLayout *asgoreLayout = new QVBoxLayout();
	asgoreLayout->addWidget(new IniSpinBox("Asgore/KillYou", new QLabel(QStringLiteral("KillYou"))));
	asgoreGroup->setLayout(asgoreLayout);
	mainLayout->addWidget(asgoreGroup);

	QGroupBox *fffffGroup = new QGroupBox(QStringLiteral("FFFFF"));
	QVBoxLayout *fffffLayout = new QVBoxLayout();
	fffffLayout->addWidget(new IniSpinBox("FFFFF/D", new QLabel(QStringLiteral("D"))));
	fffffLayout->addWidget(new IniSpinBox("FFFFF/E", new QLabel(QStringLiteral("E"))));
	fffffLayout->addWidget(new IniSpinBox("FFFFF/F", new QLabel(QStringLiteral("F"))));
	fffffLayout->addWidget(new IniSpinBox("FFFFF/P", new QLabel(QStringLiteral("P"))));
	fffffGroup->setLayout(fffffLayout);
	mainLayout->addWidget(fffffGroup);

	QGroupBox *endFGroup = new QGroupBox(QStringLiteral("EndF"));
	QVBoxLayout *endFLayout = new QVBoxLayout();
	endFLayout->addWidget(new IniSpinBox("EndF/EndF", new QLabel(QStringLiteral("EndF"))));
	endFGroup->setLayout(endFLayout);
	mainLayout->addWidget(endFGroup);

	QGroupBox *f7Group = new QGroupBox(QStringLiteral("F7"));
	QVBoxLayout *f7Layout = new QVBoxLayout();
	f7Layout->addWidget(new IniCheckBox("F7/F7", QStringLiteral("F7")));
	f7Group->setLayout(f7Layout);
	mainLayout->addWidget(f7Group);

	QGroupBox *resetGroup = new QGroupBox(QStringLiteral("reset"));
	QVBoxLayout *resetLayout = new QVBoxLayout();
	resetLayout->addWidget(new IniCheckBox("reset/reset", QStringLiteral("reset")));
	resetLayout->addWidget(new IniCheckBox("reset/s_key", QStringLiteral("s_key")));
	resetGroup->setLayout(resetLayout);
	mainLayout->addWidget(resetGroup);

	QWidget *window = new QWidget();
	window->setLayout(mainLayout);
	setWidget(window);
}
