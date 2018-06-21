#include "pages.h"
#include "tools.h"
#include "initools.h"

#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>


PlayerPage::PlayerPage(MainWindow *mainWindow, QWidget *parent) : QScrollArea(parent)
{
	QWidget *window = new QWidget();
	QGridLayout *mainLayout = new QGridLayout();

	QGroupBox *attackGroup = new QGroupBox(tr("Attack"));
	QGridLayout *attackLayout = new QGridLayout();
	attackLayout->addWidget(new QLabel("AT"), 0, 0, Qt::AlignRight);
	attackLayout->addWidget(new CustomSpinBox(5, mainWindow), 0, 1);
	attackLayout->addWidget(new QLabel("Weapon"), 1, 0, Qt::AlignRight);
	attackLayout->addWidget(new WeaponComboBox(29, mainWindow), 1, 1);
	attackLayout->addWidget(new QLabel("Weapon AT"), 2, 0, Qt::AlignRight);
	attackLayout->addWidget(new CustomSpinBox(6, mainWindow), 2, 1);
	attackGroup->setLayout(attackLayout);

	QGroupBox *defenceGroup = new QGroupBox(tr("Defence"));
	QGridLayout *defenceLayout = new QGridLayout();
	defenceLayout->addWidget(new QLabel("DF"), 0, 0, Qt::AlignRight);
	defenceLayout->addWidget(new CustomSpinBox(7, mainWindow), 0, 1);
	defenceLayout->addWidget(new QLabel("Armor"), 1, 0, Qt::AlignRight);
	defenceLayout->addWidget(new ArmorComboBox(30, mainWindow), 1, 1);
	defenceLayout->addWidget(new QLabel("Armor DF"), 2, 0, Qt::AlignRight);
	defenceLayout->addWidget(new CustomSpinBox(8, mainWindow), 2, 1);
	defenceGroup->setLayout(defenceLayout);


	QGroupBox *inventoryGroup = new QGroupBox(tr("Inventory"));
	inventoryGroup->setLayout(new QVBoxLayout());
	for (int i = 13; i <= 27; i += 2)
	{
		inventoryGroup->layout()->addWidget(new ItemComboBox(i, mainWindow));
	}

	QGroupBox *phoneGroup = new QGroupBox(tr("Phone"));
	phoneGroup->setLayout(new QVBoxLayout());
	for (int i = 14; i <= 28; i += 2)
	{
		phoneGroup->layout()->addWidget(new PhoneComboBox(i, mainWindow));
	}

	QGroupBox *dBoxAGroup = new QGroupBox(tr("Dimensional Box A"));
	dBoxAGroup->setLayout(new QVBoxLayout());
	for (int i = 331; i <= 340; i++)
	{
		dBoxAGroup->layout()->addWidget(new ItemComboBox(i, mainWindow));
	}

	QGroupBox *dBoxBGroup = new QGroupBox(tr("Dimensional Box B"));
	dBoxBGroup->setLayout(new QVBoxLayout());
	for (int i = 343; i <= 352; i++)
	{
		dBoxBGroup->layout()->addWidget(new ItemComboBox(i, mainWindow));
	}

	QGroupBox *killsGroup = new QGroupBox(tr("Kills"));
	QGridLayout *killsLayout = new QGridLayout();
	killsLayout->addWidget(new QLabel("Kills"), 0, 0, Qt::AlignRight);
	killsLayout->addWidget(new CustomSpinBox(12, mainWindow), 0, 1);
	killsLayout->addWidget(new QLabel("Total"), 0, 2, Qt::AlignRight);
	killsLayout->addWidget(new CustomSpinBox(232, mainWindow), 0, 3);
	killsLayout->addWidget(new QLabel("Ruins"), 1, 0, Qt::AlignRight);
	killsLayout->addWidget(new CustomSpinBox(233, mainWindow), 1, 1);
	killsLayout->addWidget(new QLabel("Snowdin"), 1, 2, Qt::AlignRight);
	killsLayout->addWidget(new CustomSpinBox(234, mainWindow), 1, 3);
	killsLayout->addWidget(new QLabel("Waterfall"), 1, 4, Qt::AlignRight);
	killsLayout->addWidget(new CustomSpinBox(235, mainWindow), 1, 5);
	killsLayout->addWidget(new QLabel("Hotland"), 1, 6, Qt::AlignRight);
	killsLayout->addWidget(new CustomSpinBox(236, mainWindow), 1, 7);
	killsGroup->setLayout(killsLayout);

	QGroupBox *lastFightGroup = new QGroupBox(tr("Last fight"));
	QGridLayout *lastFightLayout = new QGridLayout();
	lastFightLayout->addWidget(new CustomRadioButton(41, tr("Spare"), mainWindow), 0, 0);
	lastFightLayout->addWidget(new CustomRadioButton(42, tr("Flee"), mainWindow), 0, 1);
	lastFightLayout->addWidget(new CustomRadioButton(43, tr("Kill"), mainWindow), 1, 0);
	lastFightLayout->addWidget(new CustomRadioButton(44, tr("Bored"), mainWindow), 1, 1);
	lastFightGroup->setLayout(lastFightLayout);

	QFormLayout *checkboxLayout = new QFormLayout();
	checkboxLayout->addRow(tr("Hard Mode"), new CustomCheckBox(37, mainWindow));
	checkboxLayout->addRow(tr("True Pacifist"), new CustomCheckBox(38, mainWindow));
	checkboxLayout->addRow(tr("Disable encounters"), new CustomCheckBox(39, mainWindow));
	checkboxLayout->addRow(tr("Cooked Instant Noodles"), new CustomCheckBox(52, mainWindow));
	checkboxLayout->addRow(tr("Spared a certain monster"), new CustomCheckBox(58, mainWindow));
	checkboxLayout->addRow(tr("Used Punch Card while wearing Tough Glove"), new CustomCheckBox(109, mainWindow));
	checkboxLayout->addRow(tr("Have an umbrella"), new CustomCheckBox(116, mainWindow));
	checkboxLayout->addRow(tr("Genocide in Ruins"), new CustomCheckBox(252, mainWindow));
	checkboxLayout->addRow(tr("Genocide in Snowdin"), new CustomCheckBox(253, mainWindow));
	checkboxLayout->addRow(tr("Genocide in Waterfall"), new CustomCheckBox(254, mainWindow));
	checkboxLayout->addRow(tr("Genocide in Hotland"), new CustomCheckBox(255, mainWindow));
	checkboxLayout->addRow(tr("Genocide in Core"), new CustomCheckBox(256, mainWindow));
	checkboxLayout->addRow(tr("Ate Food"), new CustomCheckBox(291, mainWindow));
	checkboxLayout->addRow(tr("Inside the True Lab"), new CustomCheckBox(511, mainWindow));
	checkboxLayout->addRow(tr("Seen the cast"), new CustomCheckBox(530, mainWindow));

	QFormLayout *spinBoxLayout = new QFormLayout();
	spinBoxLayout->addRow(tr("Spare counter"), new CustomSpinBox(54, mainWindow));
	spinBoxLayout->addRow(tr("Flee counter"), new CustomSpinBox(55, mainWindow));
	spinBoxLayout->addRow(tr("Dialog skip counter"), new CustomSpinBox(56, mainWindow));
	spinBoxLayout->addRow(tr("Gold spent on Spider bake sale"), new CustomSpinBox(90, mainWindow));
	spinBoxLayout->addRow(tr("Gold spent on Nice Cream"), new CustomSpinBox(91, mainWindow));
	spinBoxLayout->addRow(tr("Gold spent on Hot Dogs"), new CustomSpinBox(409, mainWindow));

	mainLayout->addWidget(new QLabel("Name"), 0, 0, Qt::AlignRight);
	mainLayout->addWidget(new CustomLineEdit(1, mainWindow), 0, 1);
	mainLayout->addWidget(new QLabel("Plot"), 0, 2, Qt::AlignRight);
	mainLayout->addWidget(new PlotEdit(543, mainWindow), 0, 3);

	mainLayout->addWidget(new QLabel("LV"), 1, 0, Qt::AlignRight);
	mainLayout->addWidget(new CustomSpinBox(2, mainWindow), 1, 1);
	mainLayout->addWidget(new QLabel("fun"), 1, 2, Qt::AlignRight);
	mainLayout->addWidget(new CustomSpinBox(36, mainWindow), 1, 3);

	mainLayout->addWidget(new QLabel("Max HP"), 2, 0, Qt::AlignRight);
	mainLayout->addWidget(new CustomSpinBox(3, mainWindow), 2, 1);

	mainLayout->addWidget(new QLabel("Gold"), 3, 0, Qt::AlignRight);
	mainLayout->addWidget(new CustomSpinBox(11, mainWindow), 3, 1);

	mainLayout->addWidget(new QLabel("EXP"), 4, 0, Qt::AlignRight);
	mainLayout->addWidget(new CustomSpinBox(10, mainWindow), 4, 1);

	mainLayout->addWidget(new QLabel("Time"), 5, 0, Qt::AlignRight);
	mainLayout->addWidget(new TimeEdit(549, mainWindow), 5, 1);
	mainLayout->addWidget(new QLabel("Room"), 5, 2, Qt::AlignRight);
	mainLayout->addWidget(new RoomComboBox(548, mainWindow), 5, 3);

	mainLayout->addWidget(attackGroup, 0, 4, 3, 2);
	mainLayout->addWidget(defenceGroup, 3, 4, 3, 2);
	mainLayout->addWidget(inventoryGroup, 7, 0, 1, 2);
	mainLayout->addWidget(phoneGroup, 7, 2, 1, 2);
	mainLayout->addWidget(dBoxAGroup, 7, 4, 1, 1);
	mainLayout->addWidget(dBoxBGroup, 7, 5, 1, 1);
	mainLayout->addWidget(killsGroup, 8, 0, 1, 4);
	mainLayout->addWidget(lastFightGroup, 8, 4, 1, 2);
	mainLayout->addLayout(checkboxLayout, 9, 0, 1, 2);
	mainLayout->addLayout(spinBoxLayout, 9, 3, 1, 2);

	window->setLayout(mainLayout);
	setWidget(window);
}

BossesPage::BossesPage(MainWindow *mainWindow, QWidget *parent) : QScrollArea(parent)
{
	QWidget *window = new QWidget();
	QVBoxLayout *mainLayout = new QVBoxLayout();

	QGroupBox *floweyGroup = new QGroupBox(QString("Flowey"));
	QFormLayout *floweyLayout = new QFormLayout();
	floweyLayout->addRow(tr("Stalker Flowey counter"), new CustomSpinBox(40, mainWindow));
	floweyLayout->addRow(tr("Killed Flowey"), new CustomCheckBox(506, mainWindow));
	floweyGroup->setLayout(floweyLayout);

	QGroupBox *torielGroup = new QGroupBox(QString("Toriel"));
	QFormLayout *torielLayout = new QFormLayout();
	torielLayout->addRow(tr("Dog kidnapped Toriel's phone"), new CustomComboBox(68, mainWindow));
	torielLayout->addRow(tr("\"Say Hello\" counter"), new CustomSpinBox(71, mainWindow));
	torielLayout->addRow(tr("Flirted with Toriel"), new CustomCheckBox(72, mainWindow));
	torielLayout->addRow(tr("Called Toriel \"Mom\""), new CustomCheckBox(73, mainWindow));
	torielLayout->addRow(tr("Interaction with Toriel"), new CustomComboBox(76, mainWindow));
	torielLayout->addRow(tr("Chosen flavor of pie"), new CustomComboBox(77, mainWindow));
	torielLayout->addRow(tr("Toriel chat counter (Pacifist)"), new CustomSpinBox(222, mainWindow));
	torielLayout->addRow(tr("Checked messages from Toriel counter"), new CustomSpinBox(317, mainWindow));
	torielLayout->addRow(tr("Current messages from Toriel counter"), new CustomSpinBox(318, mainWindow));
	torielGroup->setLayout(torielLayout);

	QGroupBox *sansGroup = new QGroupBox(QString("sans"));
	QFormLayout *sansLayout = new QFormLayout();
	sansLayout->addRow(tr("sans creeping in the forest"), new CustomComboBox(78, mainWindow));
	sansLayout->addRow(tr("Date with sans at Grillby's"), new CustomComboBox(120, mainWindow));
	sansLayout->addRow(tr("sans chat counter (Pacifist)"), new CustomSpinBox(223, mainWindow));
	sansLayout->addRow(tr("Fought sans"), new CustomCheckBox(302, mainWindow));
	sansLayout->addRow(tr("Tried to Spare sans"), new CustomCheckBox(303, mainWindow));
	sansLayout->addRow(tr("Food ordered at Grillby's"), new CustomComboBox(422, mainWindow));
	sansLayout->addRow(tr("Date with Sans at Mettaton Resort"), new CustomComboBox(444, mainWindow));
	sansLayout->addRow(tr("Got the key to sans's room"), new CustomComboBox(528, mainWindow));
	sansGroup->setLayout(sansLayout);

	QGroupBox *papyrusGroup = new QGroupBox(QString("Papyrus"));
	QFormLayout *papyrusLayout = new QFormLayout();
	papyrusLayout->addRow(tr("Flirted with Papyrus"), new CustomCheckBox(97, mainWindow));
	papyrusLayout->addRow(tr("Interaction with Papyrus"), new CustomComboBox(98, mainWindow));
	papyrusLayout->addRow(tr("Fought Papyrus"), new CustomCheckBox(99, mainWindow));
	papyrusLayout->addRow(tr("Date with Papyrus"), new CustomComboBox(119, mainWindow));
	papyrusLayout->addRow(tr("Papyrus chat counter (Pacifist)"), new CustomSpinBox(226, mainWindow));
	papyrusLayout->addRow(tr("Skipped Papyrus's Special Attack (Genocide)"), new CustomCheckBox(321, mainWindow));
	papyrusLayout->addRow(tr("Skipped the Electric Maze puzzle (Genocide)"), new CustomCheckBox(322, mainWindow));
	papyrusLayout->addRow(tr("Papyrus phone call counter"), new CustomSpinBox(493, mainWindow));
	papyrusGroup->setLayout(papyrusLayout);

	QGroupBox *undyneGroup = new QGroupBox(QString("Undyne"));
	QFormLayout *undyneLayout = new QFormLayout();
	undyneLayout->addRow(tr("Undyne fight counter"), new CustomSpinBox(130, mainWindow));
	undyneLayout->addRow(tr("Undyne chat counter (Pacifist)"), new CustomSpinBox(224, mainWindow));
	undyneLayout->addRow(tr("Asked you to talk to Napstablook (Pacifist)"), new CustomCheckBox(225, mainWindow));
	undyneLayout->addRow(tr("Killed Undyne the Undying"), new CustomCheckBox(282, mainWindow));
	undyneLayout->addRow(tr("Undyne got mad at the first bridge"), new CustomCheckBox(315, mainWindow));
	undyneLayout->addRow(tr("Undyne got mad at the large bridge"), new CustomCheckBox(316, mainWindow));
	undyneLayout->addRow(tr("Interaction with Undyne"), new CustomComboBox(381, mainWindow));
	undyneLayout->addRow(tr("Undyne's remaining HP"), new CustomSpinBox(382, mainWindow));
	undyneLayout->addRow(tr("Escaped from Undyne back to Waterfall"), new CustomCheckBox(383, mainWindow));
	undyneLayout->addRow(tr("Date with Undyne"), new CustomComboBox(420, mainWindow));
	undyneLayout->addRow(tr("Undyne moved to Papyrus's place"), new CustomCheckBox(496, mainWindow));
	undyneLayout->addRow(tr("Undyne talked about weather"), new CustomCheckBox(501, mainWindow));
	undyneLayout->addRow(tr("Interaction with Undyne's letter"), new CustomComboBox(525, mainWindow));
	undyneGroup->setLayout(undyneLayout);

	QGroupBox *alphysGroup = new QGroupBox(QString("Alphys"));
	QFormLayout *alphysLayout = new QFormLayout();
	alphysLayout->addRow(tr("Alphys chat counter (Pacifist)"), new CustomSpinBox(227, mainWindow));
	alphysLayout->addRow(tr("Date with Alphys available"), new CustomCheckBox(523, mainWindow));
	alphysLayout->addRow(tr("Interaction with Alphys"), new CustomComboBox(524, mainWindow));
	alphysGroup->setLayout(alphysLayout);

	QGroupBox *mettatonGroup = new QGroupBox(QString("Mettaton"));
	QFormLayout *mettatonLayout = new QFormLayout();
	mettatonLayout->addRow(tr("Mettaton chat counter (Pacifist)"), new CustomSpinBox(229, mainWindow));
	mettatonLayout->addRow(tr("Completed the Multicolor Tile Puzzle"), new CustomCheckBox(309, mainWindow));
	mettatonLayout->addRow(tr("Failed to defuse a bomb"), new CustomCheckBox(319, mainWindow));
	mettatonLayout->addRow(tr("Stepped on a green tile"), new CustomCheckBox(320, mainWindow));
	mettatonLayout->addRow(tr("State of the Shooter Mode"), new CustomComboBox(416, mainWindow));
	mettatonLayout->addRow(tr("Exposed Mettaton's switch"), new CustomComboBox(455, mainWindow));
	mettatonLayout->addRow(tr("Killed Mettaton"), new CustomCheckBox(456, mainWindow));
	mettatonGroup->setLayout(mettatonLayout);

	QGroupBox *asgoreGroup = new QGroupBox(QString("Asgore"));
	QFormLayout *asgoreLayout = new QFormLayout();
	asgoreLayout->addRow(tr("Asgore chat counter (Pacifist)"), new CustomSpinBox(228, mainWindow));
	asgoreLayout->addRow(tr("Killed Asgore"), new CustomCheckBox(507, mainWindow));
	asgoreGroup->setLayout(asgoreLayout);

	QGroupBox *asrielGroup = new QGroupBox(QString("Asriel"));
	QFormLayout *asrielLayout = new QFormLayout();
	asrielLayout->addRow(tr("Fought Asriel"), new CustomCheckBox(531, mainWindow));
	asrielLayout->addRow(tr("Stage of the final fight"), new CustomComboBox(532, mainWindow));
	asrielLayout->addRow(tr("Heart refuse counter"), new CustomSpinBox(533, mainWindow));
	asrielLayout->addRow(tr("Used a Dream"), new CustomCheckBox(534, mainWindow));
	asrielLayout->addRow(tr("Asriel turn counter"), new CustomSpinBox(535, mainWindow));
	asrielLayout->addRow(tr("Saved Undyne"), new CustomCheckBox(536, mainWindow));
	asrielLayout->addRow(tr("Saved Alphys"), new CustomCheckBox(537, mainWindow));
	asrielLayout->addRow(tr("Saved Papyrus and sans"), new CustomCheckBox(538, mainWindow));
	asrielLayout->addRow(tr("Saved Toriel and Asgore"), new CustomCheckBox(539, mainWindow));
	asrielLayout->addRow(tr("HP display"), new CustomComboBox(540, mainWindow));
	asrielLayout->addRow(tr("Child Asriel chat counter"), new CustomSpinBox(542, mainWindow));
	asrielGroup->setLayout(asrielLayout);

	mainLayout->addWidget(floweyGroup);
	mainLayout->addWidget(torielGroup);
	mainLayout->addWidget(sansGroup);
	mainLayout->addWidget(papyrusGroup);
	mainLayout->addWidget(undyneGroup);
	mainLayout->addWidget(alphysGroup);
	mainLayout->addWidget(mettatonGroup);
	mainLayout->addWidget(asgoreGroup);
	mainLayout->addWidget(asrielGroup);
	window->setLayout(mainLayout);
	setWidget(window);
}

MonstersPage::MonstersPage(MainWindow *mainWindow, QWidget *parent) : QScrollArea(parent)
{
	QWidget *window = new QWidget();
	QHBoxLayout *mainLayout = new QHBoxLayout();
	QFormLayout *leftLayout = new QFormLayout();
	leftLayout->addRow(tr("Interaction with the first dummy"), new CustomComboBox(45, mainWindow));
	leftLayout->addRow(tr("Monster spare name color"), new CustomComboBox(53, mainWindow));
	leftLayout->addRow(tr("Interaction with Doggo"), new CustomComboBox(83, mainWindow));
	leftLayout->addRow(tr("Interaction with Dogamy and Dogaressa"), new CustomComboBox(84, mainWindow));
	leftLayout->addRow(tr("Interaction with Greater Dog"), new CustomComboBox(85, mainWindow));
	leftLayout->addRow(tr("Interaction with Lesser Dog"), new CustomComboBox(86, mainWindow));
	leftLayout->addRow(tr("Interaction with Snowman"), new CustomComboBox(87, mainWindow));
	leftLayout->addRow(tr("Interaction with Snowdrake"), new CustomComboBox(88, mainWindow));
	leftLayout->addRow(tr("Placed googly eyes on Gyftrot"), new CustomCheckBox(105, mainWindow));
	leftLayout->addRow(tr("Interaction with Shyren"), new CustomComboBox(112, mainWindow));
	leftLayout->addRow(tr("Interaction with Monster Kid"), new CustomComboBox(122, mainWindow));
	leftLayout->addRow(tr("Monster Kid tripped on a bridge"), new CustomComboBox(129, mainWindow));
	leftLayout->addRow(tr("Spared Frogit"), new CustomCheckBox(161, mainWindow));
	leftLayout->addRow(tr("Spared Whimsun"), new CustomCheckBox(162, mainWindow));
	leftLayout->addRow(tr("Spared Moldsmal"), new CustomCheckBox(163, mainWindow));
	leftLayout->addRow(tr("Spared Loox"), new CustomCheckBox(164, mainWindow));
	leftLayout->addRow(tr("Spared Vegitoid"), new CustomCheckBox(165, mainWindow));
	leftLayout->addRow(tr("Spared Migosp"), new CustomCheckBox(166, mainWindow));
	leftLayout->addRow(tr("Spared Snowdrake"), new CustomCheckBox(167, mainWindow));
	leftLayout->addRow(tr("Spared Ice Cap"), new CustomCheckBox(168, mainWindow));
	leftLayout->addRow(tr("Spared Gyftrot"), new CustomCheckBox(169, mainWindow));
	leftLayout->addRow(tr("Spared Doggo"), new CustomCheckBox(170, mainWindow));
	leftLayout->addRow(tr("Spared Dogamy and Dogaressa"), new CustomCheckBox(171, mainWindow));
	leftLayout->addRow(tr("Spared Lesser Dog"), new CustomCheckBox(172, mainWindow));
	leftLayout->addRow(tr("Spared Greater Dog"), new CustomCheckBox(173, mainWindow));
	leftLayout->addRow(tr("Spared Aaron"), new CustomCheckBox(174, mainWindow));
	leftLayout->addRow(tr("Spared Moldbygg"), new CustomCheckBox(175, mainWindow));
	leftLayout->addRow(tr("Spared Woshua"), new CustomCheckBox(176, mainWindow));
	leftLayout->addRow(tr("Spared Temmie"), new CustomCheckBox(177, mainWindow));
	leftLayout->addRow(tr("Spared Mad Dummy"), new CustomCheckBox(178, mainWindow));
	leftLayout->addRow(tr("Spared Vulkin"), new CustomCheckBox(179, mainWindow));
	leftLayout->addRow(tr("Spared Tsunderplane"), new CustomCheckBox(180, mainWindow));
	leftLayout->addRow(tr("Spared Pyrope"), new CustomCheckBox(181, mainWindow));
	leftLayout->addRow(tr("Spared Final Froggit"), new CustomCheckBox(182, mainWindow));
	leftLayout->addRow(tr("Spared Whimsalot"), new CustomCheckBox(183, mainWindow));
	leftLayout->addRow(tr("Spared Astigmatism"), new CustomCheckBox(184, mainWindow));
	leftLayout->addRow(tr("Spared Madjick"), new CustomCheckBox(185, mainWindow));
	leftLayout->addRow(tr("Spared Knight Knight"), new CustomCheckBox(186, mainWindow));
	leftLayout->addRow(tr("Spared Endogeny"), new CustomCheckBox(187, mainWindow));
	leftLayout->addRow(tr("Killed Glad Dummy"), new CustomCheckBox(283, mainWindow));
	leftLayout->addRow(tr("Interaction with Snowman (Genocide)"), new CustomComboBox(284, mainWindow));
	leftLayout->addRow(tr("Interaction with So Sorry"), new CustomComboBox(312, mainWindow));
	leftLayout->addRow(tr("Fought Glyde"), new CustomCheckBox(313, mainWindow));
	leftLayout->addRow(tr("Killed the Royal Guards"), new CustomCheckBox(433, mainWindow));

	QVBoxLayout *rightLayout = new QVBoxLayout();
	QGroupBox *napstablookGroup = new QGroupBox(QString("Napstablook"));
	QFormLayout *napstablookLayout = new QFormLayout();
	napstablookLayout->addRow(tr("Napstablook encounter"), new CustomComboBox(67, mainWindow));
	napstablookLayout->addRow(tr("Date with Napstablook"), new CustomComboBox(124, mainWindow));
	napstablookLayout->addRow(tr("Spooked Aaron and Woshua with spooky tunes"), new CustomCheckBox(126, mainWindow));
	napstablookLayout->addRow(tr("Napstablook chat counter (Pacifist)"), new CustomSpinBox(230, mainWindow));
	napstablookLayout->addRow(tr("NAPSTABLOOK22 has sent you a friend request"), new CustomCheckBox(440, mainWindow));
	napstablookLayout->addRow(tr("Feel like garbage with Napstablook"), new CustomCheckBox(489, mainWindow));
	napstablookGroup->setLayout(napstablookLayout);

	QGroupBox *temmieGroup = new QGroupBox(QString("Temmie"));
	QFormLayout *temmieLayout = new QFormLayout();
	temmieLayout->addRow(tr("Temmie sale countdown"), new CustomSpinBox(296, mainWindow));
	temmieLayout->addRow(tr("Temmie special sale"), new CustomCheckBox(297, mainWindow));
	temmieLayout->addRow(tr("Talked to allergic Temmie"), new CustomCheckBox(300, mainWindow));
	temmieLayout->addRow(tr("Send tem to \"cool leg\""), new CustomCheckBox(307, mainWindow));
	temmieGroup->setLayout(temmieLayout);

	QGroupBox *muffetGroup = new QGroupBox(QString("Muffet"));
	QFormLayout *muffetLayout = new QFormLayout();
	muffetLayout->addRow(tr("Muffet bribing price"), new CustomSpinBox(413, mainWindow));
	muffetLayout->addRow(tr("Gold spent on bribing Muffet"), new CustomSpinBox(414, mainWindow));
	muffetLayout->addRow(tr("Muffet conversation"), new CustomComboBox(427, mainWindow));
	muffetLayout->addRow(tr("Killed Muffet"), new CustomCheckBox(428, mainWindow));
	muffetGroup->setLayout(muffetLayout);

	QGroupBox *riverPersonGroup = new QGroupBox(QString("River Person"));
	QFormLayout *riverPersonLayout = new QFormLayout();
	riverPersonLayout->addRow(tr("River Person's destination"), new CustomComboBox(490, mainWindow));
	riverPersonLayout->addRow(tr("Boat ride counter"), new CustomSpinBox(491, mainWindow));
	riverPersonLayout->addRow(tr("River Person's boat is a dog"), new CustomCheckBox(492, mainWindow));
	riverPersonGroup->setLayout(riverPersonLayout);

	rightLayout->addWidget(napstablookGroup);
	rightLayout->addWidget(temmieGroup);
	rightLayout->addWidget(muffetGroup);
	rightLayout->addWidget(riverPersonGroup);
	rightLayout->addStretch(1);

	mainLayout->addLayout(leftLayout);
	mainLayout->addLayout(rightLayout);
	window->setLayout(mainLayout);
	setWidget(window);
}

LocationsPage::LocationsPage(MainWindow *mainWindow, QWidget *parent) : QScrollArea(parent)
{
	QWidget *window = new QWidget();
	QVBoxLayout *mainLayout = new QVBoxLayout();

	QGroupBox *ruinsGroup = new QGroupBox(QString("Ruins"));
	QFormLayout *ruinsLayout = new QFormLayout();
	ruinsLayout->addRow(tr("Tutorial Froggit encountered"), new CustomCheckBox(61, mainWindow));
	ruinsLayout->addRow(tr("First rock pushed"), new CustomCheckBox(66, mainWindow));
	ruinsLayout->addRow(tr("Second rock pushed"), new CustomCheckBox(63, mainWindow));
	ruinsLayout->addRow(tr("Third rock pushed"), new CustomCheckBox(62, mainWindow));
	ruinsLayout->addRow(tr("Fourth rock asked to move"), new CustomCheckBox(64, mainWindow));
	ruinsLayout->addRow(tr("Monster Candy taken"), new CustomComboBox(65, mainWindow));
	ruinsLayout->addRow(tr("Pillar switch counter"), new CustomSpinBox(74, mainWindow));
	ruinsLayout->addRow(tr("Tried to exit Ruins counter"), new CustomSpinBox(75, mainWindow));
	ruinsLayout->addRow(tr("Learned about \"water sausage\""), new CustomCheckBox(81, mainWindow));
	ruinsLayout->addRow(tr("Wrong pillar switch counter"), new CustomSpinBox(82, mainWindow));
	ruinsLayout->addRow(tr("Found a Faded Ribbon"), new CustomCheckBox(131, mainWindow));
	ruinsLayout->addRow(tr("Found the Toy Knife"), new CustomCheckBox(133, mainWindow));
	ruinsLayout->addRow(tr("Toriel's pie"), new CustomComboBox(134, mainWindow));
	ruinsGroup->setLayout(ruinsLayout);

	QGroupBox *snowdinGroup = new QGroupBox(QString("Snowdin"));
	QFormLayout *snowdinLayout = new QFormLayout();
	snowdinLayout->addRow(tr("Harder puzzle"), new CustomComboBox(89, mainWindow));
	snowdinLayout->addRow(tr("Papyrus asks about spaghetti trap"), new CustomComboBox(93, mainWindow));
	snowdinLayout->addRow(tr("XO puzzle reset counter"), new CustomSpinBox(94, mainWindow));
	snowdinLayout->addRow(tr("Switch buried under snow"), new CustomComboBox(95, mainWindow));
	snowdinLayout->addRow(tr("Found 30G in a snow poff"), new CustomCheckBox(96, mainWindow));
	snowdinLayout->addRow(tr("Forest encounter counter"), new CustomSpinBox(101, mainWindow));
	snowdinLayout->addRow(tr("Interaction with Snowed Inn"), new CustomComboBox(103, mainWindow));
	snowdinLayout->addRow(tr("Staying at Snowed Inn"), new CustomCheckBox(104, mainWindow));
	snowdinLayout->addRow(tr("Found the Annoying Dog inside tall sink cabinet"), new CustomCheckBox(113, mainWindow));
	snowdinLayout->addRow(tr("Found 20G inside a \"saggy old couch\""), new CustomCheckBox(114, mainWindow));
	snowdinLayout->addRow(tr("Interacted with sans's puzzle"), new CustomCheckBox(285, mainWindow));
	snowdinLayout->addRow(tr("Stole from the shop (Genocide)"), new CustomCheckBox(286, mainWindow));
	snowdinLayout->addRow(tr("Tried to pet the dog in the dev room"), new CustomCheckBox(292, mainWindow));
	snowdinLayout->addRow(tr("Entering Snowdin forest"), new CustomComboBox(306, mainWindow));
	snowdinLayout->addRow(tr("The wrong number/prank call happened"), new CustomCheckBox(308, mainWindow));
	snowdinLayout->addRow(tr("Checked Papyrus's kitchen after the date"), new CustomCheckBox(314, mainWindow));
	snowdinLayout->addRow(tr("Won the Ball Game"), new CustomCheckBox(418, mainWindow));
	snowdinGroup->setLayout(snowdinLayout);

	QGroupBox *waterfallGroup = new QGroupBox(QString("Waterfall"));
	QFormLayout *waterfallLayout = new QFormLayout();
	waterfallLayout->addRow(tr("Armor you are wearing when Papyrus calls"), new CustomComboBox(106, mainWindow));
	waterfallLayout->addRow(tr("Lied about your armor"), new CustomCheckBox(107, mainWindow));
	waterfallLayout->addRow(tr("Armor you are wearing when Undyne attacks"), new CustomComboBox(108, mainWindow));
	waterfallLayout->addRow(tr("Talked to Nice Cream Guy at Waterfall"), new CustomCheckBox(110, mainWindow));
	waterfallLayout->addRow(tr("Punch Card counter"), new CustomSpinBox(111, mainWindow));
	waterfallLayout->addRow(tr("Placed an umbrella on a statue"), new CustomCheckBox(117, mainWindow));
	waterfallLayout->addRow(tr("Met Monster Kid in the rain"), new CustomComboBox(121, mainWindow));
	waterfallLayout->addRow(tr("Interacted with Trash Zone SAVE Point"), new CustomCheckBox(122, mainWindow));
	waterfallLayout->addRow(tr("Spooky tune playing"), new CustomComboBox(125, mainWindow));
	waterfallLayout->addRow(tr("Talked with Gerson"), new CustomComboBox(127, mainWindow));
	waterfallLayout->addRow(tr("Got the Abandoned Quiche"), new CustomCheckBox(135, mainWindow));
	waterfallLayout->addRow(tr("Got the Old Tutu"), new CustomCheckBox(136, mainWindow));
	waterfallLayout->addRow(tr("Got the Ballet Shoes"), new CustomCheckBox(137, mainWindow));
	waterfallLayout->addRow(tr("Legendary artifact"), new CustomComboBox(138, mainWindow));
	waterfallLayout->addRow(tr("Cooler containing Astronaut Food"), new CustomComboBox(139, mainWindow));
	waterfallLayout->addRow(tr("Solved glowshroom puzzle"), new CustomCheckBox(301, mainWindow));
	waterfallLayout->addRow(tr("Talked to Clamgirl"), new CustomCheckBox(310, mainWindow));
	waterfallLayout->addRow(tr("Interaction with Elder Puzzler"), new CustomComboBox(311, mainWindow));
	waterfallLayout->addRow(tr("Interaction with Mad Dummy"), new CustomComboBox(386, mainWindow));
	waterfallLayout->addRow(tr("Solved the Piano Puzzle"), new CustomCheckBox(387, mainWindow));
	waterfallLayout->addRow(tr("Waterfall (first area) encounter counter"), new CustomSpinBox(388, mainWindow));
	waterfallLayout->addRow(tr("Waterfall (second area) encounter counter"), new CustomSpinBox(389, mainWindow));
	waterfallLayout->addRow(tr("Solved the first Bridge Seed Puzzle"), new CustomCheckBox(417, mainWindow));
	waterfallLayout->addRow(tr("Unlocked Mettaton's house"), new CustomCheckBox(464, mainWindow));
	waterfallLayout->addRow(tr("Drinks taken from the water cooler"), new CustomSpinBox(471, mainWindow));
	waterfallLayout->addRow(tr("Drinks poured on the ground in front of Undyne"), new CustomSpinBox(472, mainWindow));
	waterfallLayout->addRow(tr("Interaction with Onionsan"), new CustomComboBox(527, mainWindow));
	waterfallGroup->setLayout(waterfallLayout);

	QGroupBox *hotlandGroup = new QGroupBox(QString("Hotland"));
	QFormLayout *hotlandLayout = new QFormLayout();
	hotlandLayout->addRow(tr("Got the Instant Noodles"), new CustomCheckBox(140, mainWindow));
	hotlandLayout->addRow(tr("Got the Burnt Pan"), new CustomCheckBox(141, mainWindow));
	hotlandLayout->addRow(tr("Got the Stained Apron"), new CustomCheckBox(142, mainWindow));
	hotlandLayout->addRow(tr("Nice Cream is sold out"), new CustomCheckBox(281, mainWindow));
	hotlandLayout->addRow(tr("Stole from Bratty & Catty (Genocide)"), new CustomCheckBox(287, mainWindow));
	hotlandLayout->addRow(tr("Delivered Sea Tea at the MTT Resort"), new CustomCheckBox(293, mainWindow));
	hotlandLayout->addRow(tr("Delivered Cinnamon Bun at the MTT Resort"), new CustomCheckBox(294, mainWindow));
	hotlandLayout->addRow(tr("Delivered Hot Dog at the MTT Resort"), new CustomCheckBox(295, mainWindow));
	hotlandLayout->addRow(tr("Stay at the MTT Resort"), new CustomComboBox(298, mainWindow));
	hotlandLayout->addRow(tr("Water poured on ground"), new CustomSpinBox(384, mainWindow));
	hotlandLayout->addRow(tr("Papyrus calls at the entrance to Hotland"), new CustomComboBox(385, mainWindow));
	hotlandLayout->addRow(tr("Have a cup of water"), new CustomCheckBox(397, mainWindow));
	hotlandLayout->addRow(tr("Disable Alphys's phone calls (Genocide)"), new CustomCheckBox(398, mainWindow));
	hotlandLayout->addRow(tr("Disable Alphys's messages (Genocide)"), new CustomCheckBox(399, mainWindow));
	hotlandLayout->addRow(tr("Current message received from Alphys"), new CustomSpinBox(400, mainWindow));
	hotlandLayout->addRow(tr("Deactivated the first group of lasers"), new CustomCheckBox(402, mainWindow));
	hotlandLayout->addRow(tr("Activated lasers at MTT News"), new CustomCheckBox(403, mainWindow));
	hotlandLayout->addRow(tr("Deactivated laser near Shooting Puzzle"), new CustomCheckBox(404, mainWindow));
	hotlandLayout->addRow(tr("Solved the west Shooting Puzzle"), new CustomCheckBox(405, mainWindow));
	hotlandLayout->addRow(tr("Solved the east Shooting Puzzle"), new CustomCheckBox(406, mainWindow));
	hotlandLayout->addRow(tr("Failed jetpack sequence"), new CustomCheckBox(408, mainWindow));
	hotlandLayout->addRow(tr("Hot Dog buy counter"), new CustomSpinBox(410, mainWindow));
	hotlandLayout->addRow(tr("Total Hot Dogs placed on head"), new CustomSpinBox(411, mainWindow));
	hotlandLayout->addRow(tr("Reached the limit on Head-Dogs"), new CustomCheckBox(412, mainWindow));
	hotlandLayout->addRow(tr("Bombs defused during MTT News"), new CustomSpinBox(426, mainWindow));
	hotlandLayout->addRow(tr("Current elevator floor"), new CustomComboBox(429, mainWindow));
	hotlandLayout->addRow(tr("Solved the south Shooting Puzzle"), new CustomCheckBox(430, mainWindow));
	hotlandLayout->addRow(tr("Solved the north Shooting Puzzle"), new CustomCheckBox(431, mainWindow));
	hotlandLayout->addRow(tr("Undyne mentioned mind control"), new CustomCheckBox(432, mainWindow));
	hotlandLayout->addRow(tr("Bought something from Muffet"), new CustomCheckBox(434, mainWindow));
	hotlandLayout->addRow(tr("Pressed all three switches on the conveyor"), new CustomCheckBox(435, mainWindow));
	hotlandLayout->addRow(tr("Talked with Bratty and Catty"), new CustomComboBox(436, mainWindow));
	hotlandLayout->addRow(tr("Talked with Bratty and Catty about Mettaton"), new CustomComboBox(437, mainWindow));
	hotlandLayout->addRow(tr("Talked with Bratty and Catty about Alphys"), new CustomComboBox(438, mainWindow));
	hotlandLayout->addRow(tr("Hotland encounter counter"), new CustomSpinBox(439, mainWindow));
	hotlandLayout->addRow(tr("Flamey challenge"), new CustomComboBox(465, mainWindow));
	hotlandLayout->addRow(tr("Interaction with Burger Pants"), new CustomComboBox(466, mainWindow));
	hotlandLayout->addRow(tr("Talked with Burger Pants about Mettaton"), new CustomComboBox(467, mainWindow));
	hotlandLayout->addRow(tr("Chat with Burger Pants, Bratty and Catty"), new CustomComboBox(468, mainWindow));
	hotlandLayout->addRow(tr("Bought the Empty Gun"), new CustomCheckBox(473, mainWindow));
	hotlandLayout->addRow(tr("Bought the Cowboy Hat"), new CustomCheckBox(474, mainWindow));
	hotlandLayout->addRow(tr("Bought the Mystery Key"), new CustomCheckBox(475, mainWindow));
	hotlandLayout->addRow(tr("Bought the Face Steak"), new CustomCheckBox(476, mainWindow));
	hotlandGroup->setLayout(hotlandLayout);

	QGroupBox *coreGroup = new QGroupBox(QString("Core"));
	QFormLayout *coreLayout = new QFormLayout();
	coreLayout->addRow(tr("Got the Glamburger from a trashcan"), new CustomCheckBox(143, mainWindow));
	coreLayout->addRow(tr("Got 100G from a trashcan"), new CustomCheckBox(144, mainWindow));
	coreLayout->addRow(tr("Tried to use the elevator in the Core lobby"), new CustomCheckBox(445, mainWindow));
	coreLayout->addRow(tr("Went right in the Core lobby"), new CustomCheckBox(446, mainWindow));
	coreLayout->addRow(tr("Went a bit to the right in the first crossroads"), new CustomCheckBox(447, mainWindow));
	coreLayout->addRow(tr("Went up in the first crossroads"), new CustomCheckBox(448, mainWindow));
	coreLayout->addRow(tr("Solved the Shooting Puzzle at the Sage's Path"), new CustomCheckBox(449, mainWindow));
	coreLayout->addRow(tr("Pressed the button at the Warrior's Path"), new CustomCheckBox(450, mainWindow));
	coreLayout->addRow(tr("Waited for 60 seconds on the final forcefield"), new CustomCheckBox(451, mainWindow));
	coreLayout->addRow(tr("Player ambushed on the Warrior's Path"), new CustomComboBox(452, mainWindow));
	coreLayout->addRow(tr("Core (first area) encounter counter"), new CustomSpinBox(454, mainWindow));
	coreLayout->addRow(tr("Core (second area) encounter counter"), new CustomSpinBox(457, mainWindow));
	coreGroup->setLayout(coreLayout);

	QGroupBox *castleGroup = new QGroupBox(QString("Castle"));
	QFormLayout *castleLayout = new QFormLayout();
	castleLayout->addRow(tr("Got the Worn Dagger"), new CustomCheckBox(145, mainWindow));
	castleLayout->addRow(tr("Got the Heart Locket"), new CustomCheckBox(146, mainWindow));
	castleLayout->addRow(tr("Target floor of the castle elevator"), new CustomComboBox(462, mainWindow));
	castleLayout->addRow(tr("Used the elevator for the first time"), new CustomCheckBox(463, mainWindow));
	castleLayout->addRow(tr("The Tale of the Fallen Human"), new CustomComboBox(481, mainWindow));
	castleLayout->addRow(tr("Got the key in the kitchen"), new CustomCheckBox(483, mainWindow));
	castleLayout->addRow(tr("Got the key in the hallway"), new CustomCheckBox(484, mainWindow));
	castleLayout->addRow(tr("Padlocks in the New Home"), new CustomComboBox(485, mainWindow));
	castleLayout->addRow(tr("Story heard counter (the kitchen)"), new CustomSpinBox(486, mainWindow));
	castleLayout->addRow(tr("Story heard counter (the hallway)"), new CustomSpinBox(487, mainWindow));
	castleLayout->addRow(tr("Have any unfinished business"), new CustomCheckBox(488, mainWindow));
	castleLayout->addRow(tr("True Pacifist conversation"), new CustomComboBox(541, mainWindow));
	castleGroup->setLayout(castleLayout);

	QGroupBox *trueLabGroup = new QGroupBox(QString("True Lab"));
	QFormLayout *trueLabLayout = new QFormLayout();
	trueLabLayout->addRow(tr("Entered True Lab lobby"), new CustomCheckBox(510, mainWindow));
	trueLabLayout->addRow(tr("Interaction with Red switch"), new CustomComboBox(512, mainWindow));
	trueLabLayout->addRow(tr("Interaction with Blue switch"), new CustomComboBox(513, mainWindow));
	trueLabLayout->addRow(tr("Interaction with Green switch"), new CustomComboBox(514, mainWindow));
	trueLabLayout->addRow(tr("Interaction with Yellow switch"), new CustomComboBox(515, mainWindow));
	trueLabLayout->addRow(tr("Finished talking to Alphys"), new CustomCheckBox(516, mainWindow));
	trueLabLayout->addRow(tr("Sink interaction counter"), new CustomSpinBox(517, mainWindow));
	trueLabLayout->addRow(tr("Red key location"), new CustomComboBox(518, mainWindow));
	trueLabLayout->addRow(tr("Spared Reaper Bird"), new CustomCheckBox(519, mainWindow));
	trueLabLayout->addRow(tr("Spared Lemon Bread"), new CustomCheckBox(520, mainWindow));
	trueLabLayout->addRow(tr("Turned on the lab's ventilation"), new CustomCheckBox(521, mainWindow));
	trueLabLayout->addRow(tr("Restored power to the elevator"), new CustomCheckBox(522, mainWindow));
	trueLabLayout->addRow(tr("Potato Chisps buy counter"), new CustomSpinBox(526, mainWindow));
	trueLabGroup->setLayout(trueLabLayout);

	mainLayout->addWidget(ruinsGroup);
	mainLayout->addWidget(snowdinGroup);
	mainLayout->addWidget(waterfallGroup);
	mainLayout->addWidget(hotlandGroup);
	mainLayout->addWidget(castleGroup);
	mainLayout->addWidget(trueLabGroup);
	window->setLayout(mainLayout);
	setWidget(window);
}

DebugPage::DebugPage(MainWindow *mainWindow, QWidget *parent) : QScrollArea(parent)
{
	QWidget *window = new QWidget();
	QFormLayout *mainLayout = new QFormLayout();

	mainLayout->addRow(tr("Bypass counted kills"), new CustomCheckBox(35, mainWindow));
	mainLayout->addRow(tr("Murder level override"), new CustomSpinBox(57, mainWindow));
	mainLayout->addRow(tr("Debug text skip"), new CustomCheckBox(59, mainWindow));
	window->setLayout(mainLayout);
	setWidget(window);
}

DogPage::DogPage(MainWindow *mainWindow, QWidget *parent) : QScrollArea(parent)
{
	QWidget *window = new QWidget();
	QFormLayout *mainLayout = new QFormLayout();

	mainLayout->addRow(tr("Gold donated"), new CustomSpinBox(323, mainWindow));
	mainLayout->addRow(tr("Donation threshold"), new CustomSpinBox(324, mainWindow));
	mainLayout->addRow(tr("Reached donation goal"), new CustomSpinBox(325, mainWindow));
	mainLayout->addRow(tr("Dogshrine upgrades"), new CustomSpinBox(326, mainWindow));
	mainLayout->addRow(tr("Tried to use the donation box"), new CustomCheckBox(327, mainWindow));
	window->setLayout(mainLayout);
	setWidget(window);
}

INIPage::INIPage(MainWindow *mainWindow, QWidget *parent) : QScrollArea(parent)
{
	QWidget *window = new QWidget();
	QGridLayout *mainLayout = new QGridLayout();

	mainLayout->addWidget(new QLabel("General"), 0, 0);
	mainLayout->addWidget(new HorizontalLine(), 0, 1, 1, 4);
	mainLayout->addWidget(new VerticalLine(), 1, 0, 16, 1);
	mainLayout->addWidget(new VerticalLine(), 1, 4, 16, 1);
	mainLayout->addWidget(new QLabel("BC"), 1, 1);
	mainLayout->addWidget(new IniSpinBox("BC", mainWindow), 1, 2);
	mainLayout->addWidget(new QLabel("For those \"Get an item\" trophies"), 1, 3);
	mainLayout->addWidget(new QLabel("BH"), 2, 1);
	mainLayout->addWidget(new IniCheckBox("BH", mainWindow), 2, 2);
	mainLayout->addWidget(new QLabel("Border Hard Mode. Console exclusive stuff"), 2, 3);
	mainLayout->addWidget(new QLabel("BP"), 3, 1);
	mainLayout->addWidget(new IniCheckBox("BP", mainWindow), 3, 2);
	mainLayout->addWidget(new QLabel("Border Pacifist. Console exclusive stuff"), 3, 3);
	mainLayout->addWidget(new QLabel("BW"), 4, 1);
	mainLayout->addWidget(new IniCheckBox("BW", mainWindow), 4, 2);
	mainLayout->addWidget(new QLabel("Border Won. Console exclusive stuff"), 4, 3);
	mainLayout->addWidget(new QLabel("CH"), 5, 1);
	mainLayout->addWidget(new IniCheckBox("CH", mainWindow), 5, 2);
	mainLayout->addWidget(new QLabel("Complete Hard Mode"), 5, 3);
	mainLayout->addWidget(new QLabel("CP"), 6, 1);
	mainLayout->addWidget(new IniCheckBox("CP", mainWindow), 6, 2);
	mainLayout->addWidget(new QLabel("Complete Pacifist"), 6, 3);
	mainLayout->addWidget(new QLabel("Gameover"), 7, 1);
	mainLayout->addWidget(new IniSpinBox("Gameover", mainWindow), 7, 2);
	mainLayout->addWidget(new QLabel("Game Over counter"), 7, 3);
	mainLayout->addWidget(new QLabel("Kills"), 8, 1);
	mainLayout->addWidget(new IniSpinBox("Kills", mainWindow), 8, 2);
	mainLayout->addWidget(new QLabel("Kills counter"), 8, 3);
	mainLayout->addWidget(new QLabel("Love"), 9, 1);
	mainLayout->addWidget(new IniSpinBox("Love", mainWindow), 9, 2);
	mainLayout->addWidget(new QLabel("LV"), 9, 3);
	mainLayout->addWidget(new QLabel("Name"), 10, 1);
	mainLayout->addWidget(new IniLineEdit("Name", mainWindow), 10, 2);
	mainLayout->addWidget(new QLabel("Your name"), 10, 3);
	mainLayout->addWidget(new QLabel("Room"), 11, 1);
	mainLayout->addWidget(new IniSpinBox("Room", mainWindow), 11, 2);
	mainLayout->addWidget(new QLabel("Current room"), 11, 3);
	mainLayout->addWidget(new QLabel("Tale"), 12, 1);
	mainLayout->addWidget(new IniCheckBox("Tale", mainWindow), 12, 2);
	mainLayout->addWidget(new QLabel("Heard the Tale of The Fallen Human"), 12, 3);
	mainLayout->addWidget(new QLabel("Time"), 13, 1);
	mainLayout->addWidget(new IniSpinBox("Time", mainWindow), 13, 2);
	mainLayout->addWidget(new QLabel("Time"), 13, 3);
	mainLayout->addWidget(new QLabel("Truth"), 14, 1);
	mainLayout->addWidget(new IniCheckBox("Truth", mainWindow), 14, 2);
	mainLayout->addWidget(new QLabel("(Never set) Activates \"Activity Level A\" and \"Activity Level B\""), 14, 3);
	mainLayout->addWidget(new QLabel("Won"), 15, 1);
	mainLayout->addWidget(new IniSpinBox("Won", mainWindow), 15, 2);
	mainLayout->addWidget(new QLabel("Reached an ending"), 15, 3);
	mainLayout->addWidget(new QLabel("fun"), 16, 1);
	mainLayout->addWidget(new IniSpinBox("fun", mainWindow), 16, 2);
	mainLayout->addWidget(new QLabel("Randomly generated number at the start of the game"), 16, 3);
	mainLayout->addWidget(new HorizontalLine(), 17, 0, 1, 5);

	mainLayout->addWidget(new QLabel("Flowey"), 18, 0);
	mainLayout->addWidget(new HorizontalLine(), 18, 1, 1, 4);
	mainLayout->addWidget(new VerticalLine(), 19, 0, 15, 1);
	mainLayout->addWidget(new VerticalLine(), 19, 4, 15, 1);
	mainLayout->addWidget(new QLabel("AF"), 19, 1);
	mainLayout->addWidget(new IniCheckBox("Flowey/AF", mainWindow), 19, 2);
	mainLayout->addWidget(new QLabel("Ending where True Lab was unfinished"), 19, 3);
	mainLayout->addWidget(new QLabel("AK"), 20, 1);
	mainLayout->addWidget(new IniCheckBox("Flowey/AK", mainWindow), 20, 2);
	mainLayout->addWidget(new QLabel("Ending where only Asgore was killed"), 20, 3);
	mainLayout->addWidget(new QLabel("Alter"), 21, 1);
	mainLayout->addWidget(new IniCheckBox("Flowey/Alter", mainWindow), 21, 2);
	mainLayout->addWidget(new QLabel("Intro Flowey if truename is 1, IK is over 0 or NK is over 0"), 21, 3);
	mainLayout->addWidget(new QLabel("CHANGE"), 22, 1);
	mainLayout->addWidget(new IniSpinBox("Flowey/CHANGE", mainWindow), 22, 2);
	mainLayout->addWidget(new QLabel("1 after IK is 1, but made no kills. 2 after CHANGE is less than 2 (if NK is 1, CHANGE must be over 0), but made at least 1 kill"), 22, 3);
	mainLayout->addWidget(new QLabel("CK"), 23, 1);
	mainLayout->addWidget(new IniCheckBox("Flowey/CK", mainWindow), 23, 2);
	mainLayout->addWidget(new QLabel("(Never set) (Never used)"), 23, 3);
	mainLayout->addWidget(new QLabel("EX"), 24, 1);
	mainLayout->addWidget(new IniSpinBox("Flowey/EX", mainWindow), 24, 2);
	mainLayout->addWidget(new QLabel("Endings where you killed at least once, but spared Asgore, didn't complete any dates and NK is 1 (or IK is 1)"), 24, 3);
	mainLayout->addWidget(new QLabel("FloweyExplain1"), 25, 1);
	mainLayout->addWidget(new IniCheckBox("Flowey/FloweyExplain1", mainWindow), 25, 2);
	mainLayout->addWidget(new QLabel("First spare Toriel then kill her (or the reverse). Flowey will explain the power of saving"), 25, 3);
	mainLayout->addWidget(new QLabel("IK"), 26, 1);
	mainLayout->addWidget(new IniCheckBox("Flowey/IK", mainWindow), 26, 2);
	mainLayout->addWidget(new QLabel("Ending where you made at least 1 kill (if NK is 0, IK must be 0)"), 26, 3);
	mainLayout->addWidget(new QLabel("K"), 27, 1);
	mainLayout->addWidget(new IniCheckBox("Flowey/K", mainWindow), 27, 2);
	mainLayout->addWidget(new QLabel("Killed Flowey"), 27, 3);
	mainLayout->addWidget(new QLabel("Met1"), 28, 1);
	mainLayout->addWidget(new IniSpinBox("Flowey/Met1", mainWindow), 28, 2);
	mainLayout->addWidget(new QLabel("Intro Flowey counter"), 28, 3);
	mainLayout->addWidget(new QLabel("NK"), 29, 1);
	mainLayout->addWidget(new IniCheckBox("Flowey/NK", mainWindow), 29, 2);
	mainLayout->addWidget(new QLabel("Ending where you made no kills"), 29, 3);
	mainLayout->addWidget(new QLabel("SK"), 30, 1);
	mainLayout->addWidget(new IniCheckBox("Flowey/SK", mainWindow), 30, 2);
	mainLayout->addWidget(new QLabel("Flowey didn't kill Asgore"), 30, 3);
	mainLayout->addWidget(new QLabel("SPECIALK"), 31, 1);
	mainLayout->addWidget(new IniCheckBox("Flowey/SPECIALK", mainWindow), 31, 2);
	mainLayout->addWidget(new QLabel("Ending where \"truename\" is 1"), 31, 3);
	mainLayout->addWidget(new QLabel("alter2"), 32, 1);
	mainLayout->addWidget(new IniCheckBox("Flowey/alter2", mainWindow), 32, 2);
	mainLayout->addWidget(new QLabel("Reached the end of the Ruins while killing everything (Ruins genocide)"), 32, 3);
	mainLayout->addWidget(new QLabel("truename"), 33, 1);
	mainLayout->addWidget(new IniCheckBox("Flowey/truename", mainWindow), 33, 2);
	mainLayout->addWidget(new QLabel("Reached the end of the Ruins while killing everything (Ruins genocide)"), 33, 3);
	mainLayout->addWidget(new HorizontalLine(), 34, 0, 1, 5);

	mainLayout->addWidget(new QLabel("Toriel"), 35, 0);
	mainLayout->addWidget(new HorizontalLine(), 35, 1, 1, 4);
	mainLayout->addWidget(new VerticalLine(), 36, 0, 3, 1);
	mainLayout->addWidget(new VerticalLine(), 36, 4, 3, 1);
	mainLayout->addWidget(new QLabel("Bscotch"), 36, 1);
	mainLayout->addWidget(new IniSpinBox("Toriel/Bscotch", mainWindow), 36, 2);
	mainLayout->addWidget(new QLabel("Chosen flavor of pie. 1 is Butterscotch. 2 is Cinnamon"), 36, 3);
	mainLayout->addWidget(new QLabel("TK"), 37, 1);
	mainLayout->addWidget(new IniSpinBox("Toriel/TK", mainWindow), 37, 2);
	mainLayout->addWidget(new QLabel("Kill counter"), 37, 3);
	mainLayout->addWidget(new QLabel("TS"), 38, 1);
	mainLayout->addWidget(new IniSpinBox("Toriel/TS", mainWindow), 38, 2);
	mainLayout->addWidget(new QLabel("Spare counter"), 38, 3);
	mainLayout->addWidget(new HorizontalLine(), 39, 0, 1, 5);

	mainLayout->addWidget(new QLabel("Sans"), 40, 0);
	mainLayout->addWidget(new HorizontalLine(), 40, 1, 1, 4);
	mainLayout->addWidget(new VerticalLine(), 41, 0, 12, 1);
	mainLayout->addWidget(new VerticalLine(), 41, 4, 12, 1);
	mainLayout->addWidget(new QLabel("EndMet"), 41, 1);
	mainLayout->addWidget(new IniCheckBox("Sans/EndMet", mainWindow), 41, 2);
	mainLayout->addWidget(new QLabel("Met at the judgement hallway"), 41, 3);
	mainLayout->addWidget(new QLabel("F"), 42, 1);
	mainLayout->addWidget(new IniSpinBox("Sans/F", mainWindow), 42, 2);
	mainLayout->addWidget(new QLabel("Fight counter"), 42, 3);
	mainLayout->addWidget(new QLabel("Intro"), 43, 1);
	mainLayout->addWidget(new IniSpinBox("Sans/Intro", mainWindow), 43, 2);
	mainLayout->addWidget(new QLabel("Fight Intro counter"), 43, 3);
	mainLayout->addWidget(new QLabel("M1"), 44, 1);
	mainLayout->addWidget(new IniSpinBox("Sans/M1", mainWindow), 44, 2);
	mainLayout->addWidget(new QLabel("Meeting for the first time counter"), 44, 3);
	mainLayout->addWidget(new QLabel("MeetLv"), 45, 1);
	mainLayout->addWidget(new IniSpinBox("Sans/MeetLv", mainWindow), 45, 2);
	mainLayout->addWidget(new QLabel("Final meeting at LV other than 1 or 2"), 45, 3);
	mainLayout->addWidget(new QLabel("MeetLv1"), 46, 1);
	mainLayout->addWidget(new IniSpinBox("Sans/MeetLv1", mainWindow), 46, 2);
	mainLayout->addWidget(new QLabel("Final meeting at LV 1"), 46, 3);
	mainLayout->addWidget(new QLabel("MeetLv2"), 47, 1);
	mainLayout->addWidget(new IniSpinBox("Sans/MeetLv2", mainWindow), 47, 2);
	mainLayout->addWidget(new QLabel("Final meeting at LV 2"), 47, 3);
	mainLayout->addWidget(new QLabel("MP"), 48, 1);
	mainLayout->addWidget(new IniSpinBox("Sans/MP", mainWindow), 48, 2);
	mainLayout->addWidget(new QLabel("(Never used) Offered to Spare"), 48, 3);
	mainLayout->addWidget(new QLabel("Pass"), 49, 1);
	mainLayout->addWidget(new IniSpinBox("Sans/Pass", mainWindow), 49, 2);
	mainLayout->addWidget(new QLabel("Secret codeword counter. You'll hear the first codeword at the sans' judgement if MeetLv1 is over 0"), 49, 3);
	mainLayout->addWidget(new QLabel("SK"), 50, 1);
	mainLayout->addWidget(new IniSpinBox("Sans/SK", mainWindow), 50, 2);
	mainLayout->addWidget(new QLabel("Kill counter"), 50, 3);
	mainLayout->addWidget(new QLabel("SS"), 51, 1);
	mainLayout->addWidget(new IniSpinBox("Sans/SS", mainWindow), 51, 2);
	mainLayout->addWidget(new QLabel("Spare counter"), 51, 3);
	mainLayout->addWidget(new QLabel("SS2"), 52, 1);
	mainLayout->addWidget(new IniSpinBox("Sans/SS2", mainWindow), 52, 2);
	mainLayout->addWidget(new QLabel("Spare again counter"), 52, 3);
	mainLayout->addWidget(new HorizontalLine(), 53, 0, 1, 5);

	mainLayout->addWidget(new QLabel("Papyrus"), 54, 0);
	mainLayout->addWidget(new HorizontalLine(), 54, 1, 1, 4);
	mainLayout->addWidget(new VerticalLine(), 56, 0, 4, 1);
	mainLayout->addWidget(new VerticalLine(), 56, 4, 4, 1);
	mainLayout->addWidget(new QLabel("M1"), 56, 1);
	mainLayout->addWidget(new IniSpinBox("Papyrus/M1", mainWindow), 56, 2);
	mainLayout->addWidget(new QLabel("Meeting for the first time counter"), 56, 3);
	mainLayout->addWidget(new QLabel("PD"), 57, 1);
	mainLayout->addWidget(new IniSpinBox("Papyrus/PD", mainWindow), 57, 2);
	mainLayout->addWidget(new QLabel("Date complete counter. Changes title menu"), 57, 3);
	mainLayout->addWidget(new QLabel("PK"), 58, 1);
	mainLayout->addWidget(new IniSpinBox("Papyrus/PK", mainWindow), 58, 2);
	mainLayout->addWidget(new QLabel("Kill counter"), 58, 3);
	mainLayout->addWidget(new QLabel("PS"), 59, 1);
	mainLayout->addWidget(new IniSpinBox("Papyrus/PS", mainWindow), 59, 2);
	mainLayout->addWidget(new QLabel("Spare counter"), 59, 3);
	mainLayout->addWidget(new HorizontalLine(), 60, 0, 1, 5);

	mainLayout->addWidget(new QLabel("Undyne"), 61, 0);
	mainLayout->addWidget(new HorizontalLine(), 61, 1, 1, 4);
	mainLayout->addWidget(new VerticalLine(), 62, 0, 1, 1);
	mainLayout->addWidget(new VerticalLine(), 62, 4, 1, 1);
	mainLayout->addWidget(new QLabel("UD"), 62, 1);
	mainLayout->addWidget(new IniSpinBox("Undyne/UD", mainWindow), 62, 2);
	mainLayout->addWidget(new QLabel("Date complete counter. Changes title menu"), 62, 3);
	mainLayout->addWidget(new HorizontalLine(), 63, 0, 1, 5);

	mainLayout->addWidget(new QLabel("Alphys"), 64, 0);
	mainLayout->addWidget(new HorizontalLine(), 64, 1, 1, 4);
	mainLayout->addWidget(new VerticalLine(), 65, 0, 1, 1);
	mainLayout->addWidget(new VerticalLine(), 65, 4, 1, 1);
	mainLayout->addWidget(new QLabel("AD"), 65, 1);
	mainLayout->addWidget(new IniSpinBox("Alphys/AD", mainWindow), 65, 2);
	mainLayout->addWidget(new QLabel("Date complete counter. Changes title menu"), 65, 3);
	mainLayout->addWidget(new HorizontalLine(), 66, 0, 1, 5);

	mainLayout->addWidget(new QLabel("MTT"), 67, 0);
	mainLayout->addWidget(new HorizontalLine(), 67, 1, 1, 4);
	mainLayout->addWidget(new VerticalLine(), 68, 0, 1, 1);
	mainLayout->addWidget(new VerticalLine(), 68, 4, 1, 1);
	mainLayout->addWidget(new QLabel("EssayNo"), 68, 1);
	mainLayout->addWidget(new IniSpinBox("MTT/EssayNo", mainWindow), 68, 2);
	mainLayout->addWidget(new QLabel("Essay counter"), 68, 3);
	mainLayout->addWidget(new HorizontalLine(), 69, 0, 1, 5);

	mainLayout->addWidget(new QLabel("Mett"), 70, 0);
	mainLayout->addWidget(new HorizontalLine(), 70, 1, 1, 4);
	mainLayout->addWidget(new VerticalLine(), 71, 0, 1, 1);
	mainLayout->addWidget(new VerticalLine(), 71, 4, 1, 1);
	mainLayout->addWidget(new QLabel("O"), 71, 1);
	mainLayout->addWidget(new IniCheckBox("Mett/O", mainWindow), 71, 2);
	mainLayout->addWidget(new QLabel("Experienced the Mettaton opera"), 71, 3);
	mainLayout->addWidget(new HorizontalLine(), 72, 0, 1, 5);

	mainLayout->addWidget(new QLabel("Mettaton"), 73, 0);
	mainLayout->addWidget(new HorizontalLine(), 73, 1, 1, 4);
	mainLayout->addWidget(new VerticalLine(), 74, 0, 1, 1);
	mainLayout->addWidget(new VerticalLine(), 74, 4, 1, 1);
	mainLayout->addWidget(new QLabel("BossMet"), 74, 1);
	mainLayout->addWidget(new IniCheckBox("Mettaton/BossMet", mainWindow), 74, 2);
	mainLayout->addWidget(new QLabel("Encountered Mettaton"), 74, 3);
	mainLayout->addWidget(new HorizontalLine(), 75, 0, 1, 5);

	mainLayout->addWidget(new QLabel("Asgore"), 76, 0);
	mainLayout->addWidget(new HorizontalLine(), 76, 1, 1, 4);
	mainLayout->addWidget(new VerticalLine(), 77, 0, 1, 1);
	mainLayout->addWidget(new VerticalLine(), 77, 4, 1, 1);
	mainLayout->addWidget(new QLabel("KillYou"), 77, 1);
	mainLayout->addWidget(new IniSpinBox("Asgore/KillYou", mainWindow), 77, 2);
	mainLayout->addWidget(new QLabel("Your death counter"), 77, 3);
	mainLayout->addWidget(new HorizontalLine(), 78, 0, 1, 5);

	mainLayout->addWidget(new QLabel("FFFFF"), 79, 0);
	mainLayout->addWidget(new HorizontalLine(), 79, 1, 1, 4);
	mainLayout->addWidget(new VerticalLine(), 80, 0, 4, 1);
	mainLayout->addWidget(new VerticalLine(), 80, 4, 4, 1);
	mainLayout->addWidget(new QLabel("D"), 80, 1);
	mainLayout->addWidget(new IniSpinBox("FFFFF/D", mainWindow), 80, 2);
	mainLayout->addWidget(new QLabel("Your death counter"), 80, 3);
	mainLayout->addWidget(new QLabel("E"), 81, 1);
	mainLayout->addWidget(new IniSpinBox("FFFFF/E", mainWindow), 81, 2);
	mainLayout->addWidget(new QLabel("0 after short credits. 1 after Omega Flowey fight. 2 after killing Flowey"), 81, 3);
	mainLayout->addWidget(new QLabel("F"), 82, 1);
	mainLayout->addWidget(new IniSpinBox("FFFFF/F", mainWindow), 82, 2);
	mainLayout->addWidget(new QLabel("0 after short credits. 1 after Omega Flowey fight"), 82, 3);
	mainLayout->addWidget(new QLabel("P"), 83, 1);
	mainLayout->addWidget(new IniSpinBox("FFFFF/P", mainWindow), 83, 2);
	mainLayout->addWidget(new QLabel("1 after starting Omega Flowey fight. 2 after knife part. 3 after glove part. 4 after shoe part. 5 after book part. 6 after pan part. 7 after gun part"), 83, 3);
	mainLayout->addWidget(new HorizontalLine(), 84, 0, 1, 5);

	mainLayout->addWidget(new QLabel("EndF"), 85, 0);
	mainLayout->addWidget(new HorizontalLine(), 85, 1, 1, 4);
	mainLayout->addWidget(new VerticalLine(), 86, 0, 1, 1);
	mainLayout->addWidget(new VerticalLine(), 86, 4, 1, 1);
	mainLayout->addWidget(new QLabel("EndF"), 86, 1);
	mainLayout->addWidget(new IniSpinBox("EndF/EndF", mainWindow), 86, 2);
	mainLayout->addWidget(new QLabel("1 after pacifist ending. 2 after Flowey talks about resetting"), 86, 3);
	mainLayout->addWidget(new HorizontalLine(), 87, 0, 1, 5);

	mainLayout->addWidget(new QLabel("F7"), 88, 0);
	mainLayout->addWidget(new HorizontalLine(), 88, 1, 1, 4);
	mainLayout->addWidget(new VerticalLine(), 89, 0, 1, 1);
	mainLayout->addWidget(new VerticalLine(), 89, 4, 1, 1);
	mainLayout->addWidget(new QLabel("F7"), 89, 1);
	mainLayout->addWidget(new IniCheckBox("F7/F7", mainWindow), 89, 2);
	mainLayout->addWidget(new QLabel("Asriel fight over. Changes title menu"), 89, 3);
	mainLayout->addWidget(new HorizontalLine(), 90, 0, 1, 5);

	mainLayout->addWidget(new QLabel("reset"), 91, 0);
	mainLayout->addWidget(new HorizontalLine(), 91, 1, 1, 4);
	mainLayout->addWidget(new VerticalLine(), 92, 0, 2, 1);
	mainLayout->addWidget(new VerticalLine(), 92, 4, 2, 1);
	mainLayout->addWidget(new QLabel("reset"), 92, 1);
	mainLayout->addWidget(new IniCheckBox("reset/reset", mainWindow), 92, 2);
	mainLayout->addWidget(new QLabel("Set on naming screen. Activates \"Activity Level A\" and \"Activity Level B\""), 92, 3);
	mainLayout->addWidget(new QLabel("s_key"), 93, 1);
	mainLayout->addWidget(new IniCheckBox("reset/s_key", mainWindow), 93, 2);
	mainLayout->addWidget(new QLabel("Set if you hit 0 names on credits. Opens the mysterious door in Snowdin forest"), 93, 3);
	mainLayout->addWidget(new HorizontalLine(), 94, 0, 1, 5);

	window->setLayout(mainLayout);
	setWidget(window);
}
