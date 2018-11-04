#include "tools.h"

#include <QHBoxLayout>

CustomLineEdit::CustomLineEdit(int id, MainWindow *mainWindow, QWidget *parent) : QLineEdit(parent), id(id), mw(mainWindow)
{
	switch (id)
	{
	case 1:
		setToolTip(tr("if length of the name is >=7 add text \"Easy to change, huh?\" next to the name"));
		break;
	}

	connect(this, SIGNAL(textEdited(QString)), this, SLOT(updateSave(QString)));
	connect(mw, SIGNAL(updateWidgets()), this, SLOT(updateData()));
	connect(this, SIGNAL(dataChanged(bool)), mw, SLOT(fileModified(bool)));
}
void CustomLineEdit::updateSave(QString text)
{
	mw->saveData.replace(id, text);
	emit dataChanged(true);
}
void CustomLineEdit::updateData()
{
	setText(mw->saveData.at(id));
}

CustomComboBox::CustomComboBox(int id, MainWindow *mainWindow, QWidget *parent) : QComboBox(parent), id(id), mw(mainWindow)
{
	switch (id)
	{
	case 45:
		addItem(tr("Fled"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Killed"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Spared"));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("Bored"));
		values.append(3);
		indexes.insert(3, 3);

		setToolTip(tr("set to \"%1\", if bored a monster in Ruins.\n"
					  "changes what Mad Dummy says").arg(itemText(3)));
		break;
	case 53:
		addItem(tr("Yellow"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("White"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Pink"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr("if not \"%1\", there will be a pile of yellow names in the trash").arg(itemText(0)));
		break;
	case 65:
		addItem(tr("No candy taken"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("\"You took a piece of candy.\""));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("\"You took more candy.\""));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("\"You take another piece.\""));
		values.append(3);
		indexes.insert(3, 3);
		addItem(tr("\"You took too much too fast.\""));
		values.append(4);
		indexes.insert(4, 4);

		setToolTip(tr(""));
		break;
	case 67:
		addItem(tr("Blocking the way"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Not blocking the way"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Talked to in a pit"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	case 68:
		addItem(tr("Phone not kidnapped"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Phone kidnapped"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("\"My apologies. A strange dog kidnapped my phone.\""));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	case 76:
		addItem(tr("Arrived at \"Home\""));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Tried to exit Ruins"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Fought"));
		values.append(3);
		indexes.insert(3, 2);
		addItem(tr("Killed"));
		values.append(4);
		indexes.insert(4, 3);
		addItem(tr("Spared"));
		values.append(5);
		indexes.insert(5, 4);

		setToolTip(tr(""));
		break;
	case 77:
		addItem(tr("Cinnamon"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Butterscotch"));
		values.append(1);
		indexes.insert(1, 1);

		setToolTip(tr(""));
		break;
	case 78:
		addItem(tr("Reached the bridge"));
		values.append(-1);
		indexes.insert(-1, 0);
		addItem(tr("Not reached"));
		values.append(0);
		indexes.insert(0, 1);
		addItem(tr("Stick breaks"));
		values.append(2);
		indexes.insert(2, 3);
		addItem(tr("Dark sans appears"));
		values.append(3);
		indexes.insert(3, 4);

		setToolTip(tr(""));
		break;
	case 83:
		addItem(tr("Spared"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Killed"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Used Stick"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	case 84:
		addItem(tr("Spared"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Killed"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Used Stick"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	case 85:
		addItem(tr("Spared"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Killed"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Used Stick"));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("Bored"));
		values.append(3);
		indexes.insert(3, 3);

		setToolTip(tr(""));
		break;
	case 86:
		addItem(tr("Spared"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Killed"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Petted"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	case 87:
		addItem(tr("No interaction"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Got a piece"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Got another piece"));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("Ate the piece in front of him"));
		values.append(4);
		indexes.insert(4, 3);
		addItem(tr("Spoke with after eating a piece"));
		values.append(5);
		indexes.insert(5, 4);

		setToolTip(tr(""));
		break;
	case 88:
		addItem(tr("Not encountered"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Laughed at jokes"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Killed"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr("if \"%1\", Chilldrakes will show up").arg(itemText(2)));
		break;
	case 89:
		addItem(tr("Junior Jumble"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Crossword"));
		values.append(1);
		indexes.insert(1, 1);

		setToolTip(tr(""));
		break;
	case 93:
		addItem(tr("Not set"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Ate it"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Left it"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	case 95:
		addItem(tr("Not pressed"));
		values.append(-1);
		indexes.insert(-1, 0);
		addItem(tr("Available"));
		values.append(0);
		indexes.insert(0, 1);
		addItem(tr("Pressed"));
		values.append(1);
		indexes.insert(1, 2);

		setToolTip(tr(""));
		break;
	case 98:
		addItem(tr("Captured you thrice"));
		values.append(-3);
		indexes.insert(-3, 0);
		addItem(tr("Captured you twice"));
		values.append(-2);
		indexes.insert(-2, 1);
		addItem(tr("Captured you"));
		values.append(-1);
		indexes.insert(-1, 2);
		addItem(tr("Spared"));
		values.append(0);
		indexes.insert(0, 3);
		addItem(tr("Killed"));
		values.append(1);
		indexes.insert(1, 4);

		setToolTip(tr("if \"%1\", skip Papyrus's battle").arg(itemText(0)));
		break;
	case 103:
		addItem(tr("Not visited"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Paid 80G"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Stayed for free"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	case 106:
		addItem(tr("Not reached"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Bandage"));
		values.append(4);
		indexes.insert(4, 1);
		addItem(tr("Faded Ribbon"));
		values.append(12);
		indexes.insert(12, 2);
		addItem(tr("Manly Bandanna"));
		values.append(15);
		indexes.insert(15, 3);
		addItem(tr("Old Tutu"));
		values.append(24);
		indexes.insert(24, 4);

		setToolTip(tr(""));
		break;
	case 108:
		addItem(tr("Not reached"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Bandage"));
		values.append(4);
		indexes.insert(4, 1);
		addItem(tr("Faded Ribbon"));
		values.append(12);
		indexes.insert(12, 2);
		addItem(tr("Manly Bandanna"));
		values.append(15);
		indexes.insert(15, 3);
		addItem(tr("Old Tutu"));
		values.append(24);
		indexes.insert(24, 4);

		setToolTip(tr(""));
		break;
	case 112:
		addItem(tr("Not encountered"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Killed"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Had a musical career"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr("if \"%1\", you'll know the song for Knight Knight and Lemon Bread").arg(itemText(2)));
		break;
	case 119:
		addItem(tr("No date"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Outside the house"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Inside the house"));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("Unlock Papyrus's room"));
		values.append(3);
		indexes.insert(3, 3);
		addItem(tr("Date complete"));
		values.append(4);
		indexes.insert(4, 4);

		setToolTip(tr(""));
		break;
	case 120:
		addItem(tr("No date"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Date started"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Date complete"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	case 121:
		addItem(tr("Not met"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("\"You can't hold an umbrella either?\""));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("\"You got us an umbrella?\""));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("\"Where's the umbrella...?\""));
		values.append(3);
		indexes.insert(3, 3);

		setToolTip(tr(""));
		break;
	case 122:
		addItem(tr("Not met"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Talked about Undyne"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Talked about a school project"));
		values.append(3);
		indexes.insert(3, 2);
		addItem(tr("Talked about teachers"));
		values.append(4);
		indexes.insert(4, 3);
		addItem(tr("Staring at the castle in the distance"));
		values.append(6);
		indexes.insert(6, 4);
		addItem(tr("Helped you climb over a ledge"));
		values.append(10);
		indexes.insert(10, 5);

		setToolTip(tr("this value is also used for \"Interacted with Trash Zone SAVE Point\"-entry"));
		break;
	case 124:
		addItem(tr("No date"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Chatted in the house"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Lied on the ground"));
		values.append(3);
		indexes.insert(3, 2);
		addItem(tr("Didn't lie on the ground"));
		values.append(9);
		indexes.insert(9, 3);

		setToolTip(tr(""));
		break;
	case 125:
		addItem(tr("Not playing"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Spooktunes"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Spookwave"));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("Ghouliday Music"));
		values.append(3);
		indexes.insert(3, 3);

		setToolTip(tr(""));
		break;
	case 127:
		addItem(tr("\"That emblem\""));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("\"Emblem's meaning (NEW)\""));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("\"The prophecy (NEW)\""));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("\"The prophecy\""));
		values.append(3);
		indexes.insert(3, 3);

		setToolTip(tr(""));
		break;
	case 129:
		addItem(tr("You ran away"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("You helped Monster Kid"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("You stood and watched"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	case 134:
		addItem(tr("Pie is cooling"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Pie is ready"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Got a slice"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	case 138:
		addItem(tr("\"It's a legendary artifact.\""));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("\"The artifact is gone.\""));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("\"You're carrying too many dogs.\""));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	case 139:
		addItem(tr("Not checked the cooler"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Two food bars available"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("One food bar available"));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("The cooler is empty"));
		values.append(3);
		indexes.insert(3, 3);

		setToolTip(tr(""));
		break;
	case 284:
		addItem(tr("\"Hello. I am a snowman. I cannot move.\""));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("\"Soon there won't be any of me left...\""));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("\"Stop... Please...\""));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("(A useless pile of snow.)"));
		values.append(3);
		indexes.insert(3, 3);

		setToolTip(tr(""));
		break;
	case 298:
		addItem(tr("Not stayed"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("First time"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Second time"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	case 306:
		addItem(tr("No action"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Heavy stick is broken"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Shadow appeared"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	case 311:
		addItem(tr("Not talked"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Talked"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Tried to push box"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	case 312:
		addItem(tr("Not encountered"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Killed"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Spared"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	case 381:
		addItem(tr("Given water"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Killed"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Spared, but no water"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	case 385:
		addItem(tr("No call"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Unknown"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Called"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	case 386:
		addItem(tr("No interaction"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Punched the dummy"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Stared for a moment"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr("Mad Dummy will comment on this before fighting"));
		break;
	case 416:
		addItem(tr("Not available"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Available"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Activated"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	case 420:
		addItem(tr("No date"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Talking outside"));
		values.append(3);
		indexes.insert(3, 1);
		addItem(tr("Running to Papyrus's place"));
		values.append(4);
		indexes.insert(4, 2);
		addItem(tr("Arrived at Papyrus's place"));
		values.append(5);
		indexes.insert(5, 3);

		setToolTip(tr(""));
		break;
	case 422:
		addItem(tr("Nothing"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Fries"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Burger"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	case 427:
		addItem(tr("\"Did you hear what they said?\""));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("\"They said a human wearing a striped shirt...\""));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("\"I heard that they hate spiders.\""));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("\"I heard that they love to stomp on them.\""));
		values.append(3);
		indexes.insert(3, 3);
		addItem(tr("\"I heard that they like to tear their legs off.\""));
		values.append(4);
		indexes.insert(4, 4);
		addItem(tr("\"I heard...\""));
		values.append(5);
		indexes.insert(5, 5);

		setToolTip(tr(""));
		break;
	case 429:
		addItem(tr("Left Floor 1"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Right Floor 1"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Right Floor 2"));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("Left Floor 2"));
		values.append(3);
		indexes.insert(3, 3);
		addItem(tr("Left Floor 3"));
		values.append(4);
		indexes.insert(4, 4);
		addItem(tr("Right Floor 3"));
		values.append(5);
		indexes.insert(5, 5);

		setToolTip(tr(""));
		break;
	case 436:
		addItem(tr("\"About your wares\""));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("\"Origin of wares (NEW)\""));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("\"Origin of garbage (NEW)\""));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("\"Origin of garbage\""));
		values.append(3);
		indexes.insert(3, 3);

		setToolTip(tr(""));
		break;
	case 437:
		addItem(tr("\"About Mettaton\""));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("\"Origin of Mettaton (NEW)\""));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("\"About Mettaton (OLD?\?\?)\""));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	case 438:
		addItem(tr("\"About Alphys\""));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("\"Royal Scientist (NEW)\""));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("\"About ASGORE (NEW)\""));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("\"About ASGORE\""));
		values.append(3);
		indexes.insert(3, 3);

		setToolTip(tr(""));
		break;
	case 444:
		addItem(tr("No Date"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Date started"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Date complete"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	case 452:
		addItem(tr("Not reached"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Whimsalot and Final Froggit"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Knight Knight and Madjick"));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("Final Froggit, Astigmatism and Whimsalot"));
		values.append(3);
		indexes.insert(3, 3);

		setToolTip(tr(""));
		break;
	case 455:
		addItem(tr("Not encountered"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Can be exposed"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Switch exposed"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	case 462:
		addItem(tr("Core"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Castle"));
		values.append(1);
		indexes.insert(1, 1);

		setToolTip(tr(""));
		break;
	case 465:
		addItem(tr("Not talked"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Remembered the name"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Forgot the name"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	case 466:
		addItem(tr("Not talked"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Bought something"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Talked"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	case 467:
		addItem(tr("\"Mettaton\""));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("\"Why is Mettaton bad (NEW)\""));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("\"Why else is MTT bad (NEW)\""));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("\"Why else is MTT bad\""));
		values.append(3);
		indexes.insert(3, 3);

		setToolTip(tr(""));
		break;
	case 468: // TEST
		addItem(tr("[B.Pants] \"Romance Advice\""));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("[B.Pants] \"Glamburger Story (NEW)\""));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("[B&C] \"Burgerpants (NEW)\""));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("[B&C] \"More Burgerpants (NEW)\""));
		values.append(4);
		indexes.insert(4, 3);
		addItem(tr("[B.Pants] \"Bratty & Catty (NEW)\""));
		values.append(5);
		indexes.insert(5, 4);
		addItem(tr("[B&C] \"Burgerpants hangout (NEW)\""));
		values.append(6);
		indexes.insert(6, 5);
		addItem(tr("[B&C] \"That kind of guy (NEW)\""));
		values.append(7);
		indexes.insert(7, 6);
		addItem(tr("[B.Pants] \"Catty's Invitation (NEW)\""));
		values.append(8);
		indexes.insert(8, 7);
		addItem(tr("[B.Pants] \"Catty's Invitation\""));
		values.append(9);
		indexes.insert(9, 8);

		setToolTip(tr("The conversation takes place in two shops [marked in square brackets]"));
		break;
	case 481:
		addItem(tr("\"A long time ago, a human fell into the RUINS.\""));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("\"ASRIEL, the king's son, heard the human's call.\""));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("\"Over time, ASRIEL and the human became like siblings.\""));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("\"Then... One day...\""));
		values.append(3);
		indexes.insert(3, 3);
		addItem(tr("\"The sick human had only one request.\""));
		values.append(4);
		indexes.insert(4, 4);
		addItem(tr("\"The next day.\""));
		values.append(5);
		indexes.insert(5, 5);
		addItem(tr("\"ASRIEL, wracked with grief, absorbed the human's SOUL.\""));
		values.append(6);
		indexes.insert(6, 6);
		addItem(tr("\"With the human SOUL, ASRIEL crossed through the barrier.\""));
		values.append(7);
		indexes.insert(7, 7);
		addItem(tr("\"ASRIEL reached the center of the village.\""));
		values.append(8);
		indexes.insert(8, 8);
		addItem(tr("\"Suddenly, screams rang out.\""));
		values.append(9);
		indexes.insert(9, 9);
		addItem(tr("\"The humans attacked him with everything they had.\""));
		values.append(10);
		indexes.insert(10, 10);
		addItem(tr("\"But...\""));
		values.append(11);
		indexes.insert(11, 11);
		addItem(tr("\"Wounded, ASRIEL stumbled home.\""));
		values.append(12);
		indexes.insert(12, 12);
		addItem(tr("\"The kingdom fell into despair.\""));
		values.append(13);
		indexes.insert(13, 13);
		addItem(tr("\"The king decided it was time to end our suffering.\""));
		values.append(14);
		indexes.insert(14, 14);
		addItem(tr("\"It's not long now.\""));
		values.append(15);
		indexes.insert(15, 15);
		addItem(tr("\"You should be smiling, too.\""));
		values.append(16);
		indexes.insert(16, 16);
		addItem(tr("\"You're going to be free.\""));
		values.append(17);
		indexes.insert(17, 17);

		setToolTip(tr(""));
		break;
	case 485:
		addItem(tr("(The way is blocked by two padlocks.)"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("(You'll need both keys to get through.)"));
		values.append(0.5);
		indexes.insert(0.5, 1);
		addItem(tr("(You unlocked the chain.)"));
		values.append(1);
		indexes.insert(1, 2);

		setToolTip(tr(""));
		break;
	case 490:
		addItem(tr("Hotland"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Snowdin"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Waterfall"));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("Hotland"));
		values.append(3);
		indexes.insert(3, 3);

		setToolTip(tr(""));
		break;
	case 512:
		addItem(tr("Need to find it"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Found it in the sink"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("(You put it on your keychain.)"));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("(The red switch has been turned on.)"));
		values.append(3);
		indexes.insert(3, 3);

		setToolTip(tr(""));
		break;
	case 513:
		addItem(tr("Need to find it"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Found it in the refrigerator"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("(You put it on your keychain.)"));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("(The blue switch has been turned on.)"));
		values.append(3);
		indexes.insert(3, 3);

		setToolTip(tr(""));
		break;
	case 514:
		addItem(tr("Need to find it"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Found it in the bathtub"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("(You put it on your keychain.)"));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("(The green switch has been turned on.)"));
		values.append(3);
		indexes.insert(3, 3);

		setToolTip(tr(""));
		break;
	case 515:
		addItem(tr("Need to find it"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Found it under the bedsheets"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("(You put it on your keychain.)"));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("(The yellow switch has been turned on.)"));
		values.append(3);
		indexes.insert(3, 3);

		setToolTip(tr(""));
		break;
	case 518:
		addItem(tr("Not checked any sink"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("The left sink"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("The middle sink"));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("The right sink"));
		values.append(3);
		indexes.insert(3, 3);

		setToolTip(tr(""));
		break;
	case 524:
		addItem(tr("No interaction"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Undyne's Letter is available"));
		values.append(8);
		indexes.insert(8, 1);
		addItem(tr("Got Undyne's Letter"));
		values.append(9);
		indexes.insert(9, 2);
		addItem(tr("Date complete"));
		values.append(10);
		indexes.insert(10, 3);
		addItem(tr("Received a call from Papyrus"));
		values.append(11);
		indexes.insert(11, 4);
		addItem(tr("Completed the True Lab"));
		values.append(12);
		indexes.insert(12, 5);

		setToolTip(tr(""));
		break;
	case 525:
		addItem(tr("No interaction"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Lost the letter"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Undyne's Letter"));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("Undyne's Letter EX"));
		values.append(3);
		indexes.insert(3, 3);

		setToolTip(tr(""));
		break;
	case 527:
		addItem(tr("Onionsan doesn't want to talk"));
		values.append(-1);
		indexes.insert(-1, 0);
		addItem(tr("No interaction"));
		values.append(0);
		indexes.insert(0, 1);
		addItem(tr("\"I'm Onionsan!\""));
		values.append(1);
		indexes.insert(1, 2);
		addItem(tr("\"You're visiting Waterfall, huh!\""));
		values.append(2);
		indexes.insert(2, 3);
		addItem(tr("\"Even though, the water's getting so shallow here...\""));
		values.append(3);
		indexes.insert(3, 4);
		addItem(tr("\"Undyne's gonna fix everything, y'hear!\""));
		values.append(4);
		indexes.insert(4, 5);
		addItem(tr("\"That's the end of this room.\""));
		values.append(5);
		indexes.insert(5, 6);
		addItem(tr("\"Yeah, me too...\""));
		values.append(6);
		indexes.insert(6, 7);
		addItem(tr("\"I've been wondering when we're all gonna go free.\""));
		values.append(7);
		indexes.insert(7, 8);

		setToolTip(tr(""));
		break;
	case 528:
		addItem(tr("Haven't got the key"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Got the key"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Entered sans's room"));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("Found the silver key"));
		values.append(3);
		indexes.insert(3, 3);

		setToolTip(tr(""));
		break;
	case 532:
		addItem(tr("Not Reached"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Save everyone"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Save someone else"));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("Save Asriel"));
		values.append(3);
		indexes.insert(3, 3);

		setToolTip(tr(""));
		break;
	case 540:
		addItem(tr("Normal"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("\"00.001\""));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("\"00.0001\""));
		values.append(2);
		indexes.insert(2, 2);
		addItem(tr("\"00.000001\""));
		values.append(3);
		indexes.insert(3, 3);
		addItem(tr("\"00.0000000001\""));
		values.append(4);
		indexes.insert(4, 4);

		setToolTip(tr(""));
		break;
	case 541:
		addItem(tr("Not reached"));
		values.append(0);
		indexes.insert(0, 0);
		addItem(tr("Talked with child Asriel"));
		values.append(1);
		indexes.insert(1, 1);
		addItem(tr("Talked with everyone"));
		values.append(2);
		indexes.insert(2, 2);

		setToolTip(tr(""));
		break;
	}

	connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSave(int)));
	connect(mw, SIGNAL(updateWidgets()), this, SLOT(updateData()));
	connect(this, SIGNAL(dataChanged(bool)), mw, SLOT(fileModified(bool)));
}
void CustomComboBox::updateSave(int i)
{
	mw->saveData.replace(id, QString::number(values[i]));
	emit dataChanged(true);
}
void CustomComboBox::updateData()
{
	setCurrentIndex(indexes.value(mw->saveData.at(id).toInt()));
}

CustomSpinBox::CustomSpinBox(int id, MainWindow *mainWindow, QWidget *parent) : QSpinBox(parent), id(id), mw(mainWindow)
{
	setRange(INT_MIN, INT_MAX);
	switch (id)
	{
	case 2:
		setRange(1, 20);
		break;
	case 10:
		setMaximum(99999);
		break;
	case 56:
		setToolTip(tr("if this is >5, remove a frog from the \"four frog\" room"));
		break;
	case 71:
		setToolTip(tr("if this is >=4, Toriel's reaction stays the same"));
		break;
	case 74:
		setToolTip(tr("if this is >25, you'll make the switches uncomfortable"));
		break;
	case 75:
		setToolTip(tr("if this is >9, Toriel's reaction stays the same"));
		break;
	case 82:
		setToolTip(tr("if this is 2, you'll get a hint about the blue switch in the second room"));
		break;
	case 90:
		setToolTip(tr("if this is >= 9000, skip Muffet battle\n"
					  "checked values during battle: >0, >20, >50\n"
					  "checked values during NPC talk: >=1, >=13, >=25, >=40, >=70, >=100, >=9000"));
		break;
	case 94:
		setToolTip(tr("if this is >5, changes sans's dialog after the puzzle"));
		break;
	case 101: // TEST
		setToolTip(tr("0 = Snowdrake\n"
					  "1 = Ice Cap\n"
					  "2 (if not encountered Doggo) = random\n"
					  "2 (if encountered Doggo) = Lesser Dog\n"
					  "4 = random"));
		break;
	case 232:
		setToolTip(tr("calculated from regular kill counter"));
		break;
	case 317:
		setToolTip(tr("if this is >=17, Toriel has not sent any more messages"));
		break;
	case 318:
		setToolTip(tr("forces player to move to another room to receive a new message"));
		break;
	case 384:
		setToolTip(tr("affects dialog with \"Clamguy\"\n"
					  "if true pacifist and large puddle, a small tree will grow in the puddle"));
		break;
	case 388:
		setToolTip(tr("0 = Aaron\n"
					  "1 = Woshua\n"
					  "2 = Moldsmal\n"
					  ">2 = random"));
		break;
	case 389:
		setToolTip(tr("0 = Temmie\n"
					  "1 = Moldsmal and Moldbygg\n"
					  "2 = Woshua and Aaron\n"
					  "3 = Moldbygg and Woshua\n"
					  ">3 = random"));
		break;
	case 400:
		setToolTip(tr("value 99 skips all messages"));
		break;
	case 439:
		setToolTip(tr("0 = Vulkin\n"
					  "1 = Tsunderplane\n"
					  "2 = Pyrope\n"
					  "3 = Tsunderplane and Vulkin\n"
					  "4 = Pyrope and Pyrope\n"
					  ">4 = random"));
		break;
	case 454:
		setToolTip(tr("0 = Whimsalot and Final Froggit\n"
					  "1 = Whimsalot and Astigmatism\n"
					  "2 = Knight Knight and Madjick\n"
					  ">2 = random"));
		break;
	case 457:
		setToolTip(tr("0 = Astigmatism\n"
					  "1 = Whimsalot and Final Froggit\n"
					  "2 = Whimsalot and Astigmatism\n"
					  "3 = Final Froggit and Astigmatism\n"
					  "4 = Knight Knight and Madjick\n"
					  ">4 = random"));
		break;
	case 493:
		setToolTip(tr("resets after changing rooms"));
		break;
	case 517:
		setToolTip(tr("if this is 2, Memoryhead appears\n"
					  "if this is 13, dialog says \"You really like to wash your hands.\""));
		break;
	case 526:
		setToolTip(tr("if this is 8, the vending machine is empty"));
		break;
	}

	connect(this, SIGNAL(valueChanged(QString)), this, SLOT(updateSave(QString)));
	connect(mw, SIGNAL(updateWidgets()), this, SLOT(updateData()));
	connect(this, SIGNAL(dataChanged(bool)), mw, SLOT(fileModified(bool)));
}
void CustomSpinBox::updateSave(QString text)
{
	mw->saveData.replace(id, text);
	emit dataChanged(true);
}
void CustomSpinBox::updateData()
{
	setValue(mw->saveData.at(id).toInt());
}

CustomCheckBox::CustomCheckBox(int id, MainWindow *mainWindow, QWidget *parent) : QCheckBox(parent), id(id), mw(mainWindow)
{
	switch (id)
	{
	case 35:
		setToolTip(tr("makes Undyne act as if you made no kills"));
		break;
	case 58:
		setToolTip(tr("aborts the genocide-run\n"
					  "set to true if you spare Dogamy and Dogaressa, Doggo, Glad Dummy, Greater Dog,\n"
					  "Lesser Dog, Monster Kid, Muffet, Papyrus, Royal Guard 1, Royal Guard 2, Shyren or Toriel"));
		break;
	case 59:
		setToolTip(tr("hold down C to instantly skip text"));
		break;
	case 72:
		setToolTip(tr("Toriel tells about this to sans in True Pacifist ending"));
		break;
	case 73:
		setToolTip(tr("Toriel tells about this to sans in True Pacifist ending"));
		break;
	case 117:
		setToolTip(tr("music box starts playing"));
		break;
	case 122:
		setToolTip(tr("this value is also used for \"Interaction with Monster Kid\"-entry"));
		break;
	case 281:
		setToolTip(tr("stays false, if Royal Guards are dead"));
		break;
	case 286:
		setToolTip(tr("took 758G from behind the counter"));
		break;
	case 287:
		setToolTip(tr("stole 5G from the till"));
		break;
	case 291:
		setToolTip(tr("sans will comment on this in the ending phone call"));
		break;
	case 293:
		setToolTip(tr("reward is 99G"));
		break;
	case 294:
		setToolTip(tr("reward is 99G"));
		break;
	case 295:
		setToolTip(tr("reward is a Hush Puppy\n"
					  "hint: try to deliver Hot Cat, Dog Salad or Dog Residue"));
		break;
	case 302:
		setToolTip(tr("you're gonna have a bad time"));
		break;
	case 309:
		setToolTip(tr("Papyrus will comment on this"));
		break;
	case 314:
		setToolTip(tr("disables Glyde encounter"));
		break;
	case 315:
		setToolTip(tr("Undyne's spear attacks become very fast\n"
					  "Monster kid comments on how mad Undyne was"));
		break;
	case 316:
		setToolTip(tr("Undyne's spear attacks become very fast"));
		break;
	case 383:
		setToolTip(tr("Undyne says \"I KNEW you would come back here!\" before attacking"));
		break;
	case 432:
		setToolTip(tr("changes Royal Guard dialog during fight"));
		break;
	case 496:
		setToolTip(tr("changes \"Papyrus's Phone\" to \"Papyrus and Undyne\""));
		break;
	case 510:
		setToolTip(tr("starts the True Lab music"));
		break;
	case 511:
		setToolTip(tr("adds a shade on the player"));
		break;
	case 516:
		setToolTip(tr("turns on some diary panels"));
		break;
	}

	connect(this, SIGNAL(stateChanged(int)), this, SLOT(updateSave(int)));
	connect(mw, SIGNAL(updateWidgets()), this, SLOT(updateData()));
	connect(this, SIGNAL(dataChanged(bool)), mw, SLOT(fileModified(bool)));
}
void CustomCheckBox::updateSave(int i)
{
	mw->saveData.replace(id, QString::number(values[i]));
	emit dataChanged(true);
}
void CustomCheckBox::updateData()
{
	setCheckState(states.value(mw->saveData.at(id).toInt()));
}

CustomRadioButton::CustomRadioButton(int id, QString text, MainWindow *mainWindow, QWidget *parent) : QRadioButton(text, parent), id(id), mw(mainWindow)
{
	switch (id)
	{
	case 44:
		setToolTip(tr("only in the Ruins"));
		break;
	}

	connect(this, SIGNAL(toggled(bool)), this, SLOT(updateSave(bool)));
	connect(mw, SIGNAL(updateWidgets()), this, SLOT(updateData()));
	connect(this, SIGNAL(dataChanged(bool)), mw, SLOT(fileModified(bool)));
}
void CustomRadioButton::updateSave(bool checked)
{
	mw->saveData.replace(id, QString::number(checked));
	emit dataChanged(true);
}
void CustomRadioButton::updateData()
{
	setChecked(mw->saveData.at(id).toInt());
}

ItemComboBox::ItemComboBox(int id, MainWindow *mainWindow, QWidget *parent) : QComboBox(parent), id(id), mw(mainWindow)
{
	addItem(tr("None"));
	addItem(tr("Monster Candy"));
	addItem(tr("Croquet Roll"));
	addItem(tr("Stick"));
	addItem(tr("Bandage"));
	addItem(tr("Rock Candy"));
	addItem(tr("Pumpkin Rings"));
	addItem(tr("Spider Donut"));
	addItem(tr("Stoic Onion"));
	addItem(tr("Ghost Fruit"));
	addItem(tr("Spider Cider"));
	addItem(tr("Butterscotch Pie"));
	addItem(tr("Faded Ribbon"));
	addItem(tr("Toy Knife"));
	addItem(tr("Tough Glove"));
	addItem(tr("Manly Bandanna"));
	addItem(tr("Snowman Piece"));
	addItem(tr("Nice Cream"));
	addItem(tr("Puppydough Icecream"));
	addItem(tr("Bisicle"));
	addItem(tr("Unisicle"));
	addItem(tr("Cinnamon Bunny"));
	addItem(tr("Temmie Flakes"));
	addItem(tr("Abandoned Quiche"));
	addItem(tr("Old Tutu"));
	addItem(tr("Ballet Shoes"));
	addItem(tr("Punch Card"));
	addItem(tr("Annoying Dog"));
	addItem(tr("Dog Salad"));
	addItem(tr("Dog Residue"));
	addItem(tr("Dog Residue"));
	addItem(tr("Dog Residue"));
	addItem(tr("Dog Residue"));
	addItem(tr("Dog Residue"));
	addItem(tr("Dog Residue"));
	addItem(tr("Astronaut Food"));
	addItem(tr("Instant Noodles"));
	addItem(tr("Crab Apple"));
	addItem(tr("Hot Dog...?"));
	addItem(tr("Hot Cat"));
	addItem(tr("Glamburger"));
	addItem(tr("Sea Tea"));
	addItem(tr("Starfait"));
	addItem(tr("Legendary Hero"));
	addItem(tr("Cloudy Glasses"));
	addItem(tr("Torn Notebook"));
	addItem(tr("Stained Apron"));
	addItem(tr("Burnt Pan"));
	addItem(tr("Cowboy Hat"));
	addItem(tr("Empty Gun"));
	addItem(tr("Heart Locket"));
	addItem(tr("Worn Dagger"));
	addItem(tr("Real Knife"));
	addItem(tr("The Locket"));
	addItem(tr("Bad Memory"));
	addItem(tr("Dream"));
	addItem(tr("Undyne's Letter"));
	addItem(tr("Undyne's Letter EX"));
	addItem(tr("Popato Chisps"));
	addItem(tr("Junk Food"));
	addItem(tr("Mystery Key"));
	addItem(tr("Face Steak"));
	addItem(tr("Hush Puppy"));
	addItem(tr("Snail Pie"));
	addItem(tr("temy armor"));

	connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSave(int)));
	connect(mw, SIGNAL(updateWidgets()), this, SLOT(updateData()));
	connect(this, SIGNAL(dataChanged(bool)), mw, SLOT(fileModified(bool)));
}
void ItemComboBox::updateSave(int i)
{
	mw->saveData.replace(id, QString::number(i));
	emit dataChanged(true);
}
void ItemComboBox::updateData()
{
	setCurrentIndex(mw->saveData.at(id).toInt());
}

PhoneComboBox::PhoneComboBox(int id, MainWindow *mainWindow, QWidget *parent) : QComboBox(parent), id(id), mw(mainWindow)
{
	addItem(tr("None"));
	addItem(tr("Say Hello"));
	addItem(tr("Puzzle Help"));
	addItem(tr("About Yourself"));
	addItem(tr("Call Her \"Mom\""));
	addItem(tr("Flirt"));
	addItem(tr("Toriel's Phone"));
	addItem(tr("Papyrus's Phone"));
	addItem(tr("Dimensional Box A"));
	addItem(tr("Dimensional Box B"));

	connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSave(int)));
	connect(mw, SIGNAL(updateWidgets()), this, SLOT(updateData()));
	connect(this, SIGNAL(dataChanged(bool)), mw, SLOT(fileModified(bool)));
}
void PhoneComboBox::updateSave(int i)
{
	mw->saveData.replace(id, QString::number(values[i]));
	emit dataChanged(true);
}
void PhoneComboBox::updateData()
{
	setCurrentIndex(indexes.value(mw->saveData.at(id).toInt()));
}

WeaponComboBox::WeaponComboBox(int id, MainWindow *mainWindow, CustomSpinBox *weaponAT, QWidget *parent) : QComboBox(parent), id(id), mw(mainWindow), wat(weaponAT)
{
	addItem(tr("Stick"));
	addItem(tr("Toy Knife"));
	addItem(tr("Tough Glove"));
	addItem(tr("Ballet Shoes"));
	addItem(tr("Torn Notebook"));
	addItem(tr("Burnt Pan"));
	addItem(tr("Empty Gun"));
	addItem(tr("Worn Dagger"));
	addItem(tr("Real Knife"));

	connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSave(int)));
	connect(mw, SIGNAL(updateWidgets()), this, SLOT(updateData()));
	connect(this, SIGNAL(dataChanged(bool)), mw, SLOT(fileModified(bool)));
}
void WeaponComboBox::updateSave(int i)
{
	mw->saveData.replace(id, QString::number(values[i]));
	wat->setValue(atValues[i]);
	emit dataChanged(true);
}
void WeaponComboBox::updateData()
{
	setCurrentIndex(indexes.value(mw->saveData.at(id).toInt()));
}

ArmorComboBox::ArmorComboBox(int id, MainWindow *mainWindow, CustomSpinBox *armorDF, QWidget *parent) : QComboBox(parent), id(id), mw(mainWindow), adf(armorDF)
{
	addItem(tr("Bandage"));
	addItem(tr("Faded Ribbon"));
	addItem(tr("Manly Bandanna"));
	addItem(tr("Old Tutu"));
	addItem(tr("Clouded Glasses"));
	addItem(tr("Stained Apron"));
	addItem(tr("Cowboy Hat"));
	addItem(tr("Heart Locket"));
	addItem(tr("The Locket"));
	addItem(tr("Temmie Armor"));

	connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSave(int)));
	connect(mw, SIGNAL(updateWidgets()), this, SLOT(updateData()));
	connect(this, SIGNAL(dataChanged(bool)), mw, SLOT(fileModified(bool)));
}
void ArmorComboBox::updateSave(int i)
{
	mw->saveData.replace(id, QString::number(values[i]));
	adf->setValue(dfValues[i]);
	emit dataChanged(true);
}
void ArmorComboBox::updateData()
{
	setCurrentIndex(indexes.value(mw->saveData.at(id).toInt()));
}

RoomComboBox::RoomComboBox(int id, MainWindow *mainWindow, QWidget *parent) : QComboBox(parent), id(id), mw(mainWindow)
{
	addItem(QString("Ruins - Entrance"));
	addItem(QString("Ruins - Leaf Pile"));
	addItem(QString("Ruins - Mouse Hole"));
	addItem(QString("Ruins - Home"));
	addItem(QString("Snowdin - Box Road"));
	addItem(QString("Snowdin - Spaghetti"));
	addItem(QString("Snowdin - Dog House"));
	addItem(QString("Snowdin - Town"));
	addItem(QString("Waterfall - Checkpoint"));
	addItem(QString("Waterfall - Hallway"));
	addItem(QString("Waterfall - Crystal"));
	addItem(QString("Waterfall - Bridge"));
	addItem(QString("Waterfall - Trash Zone"));
	addItem(QString("Waterfall - Quiet Area"));
	addItem(QString("Waterfall - Temmie Village"));
	addItem(QString("Waterfall - Undyne Arena"));
	addItem(QString("Hotland - Laboratory Entrance"));
	addItem(QString("Hotland - Magma Chamber"));
	addItem(QString("Hotland - Core View"));
	addItem(QString("Hotland - Bad Opinion Zone"));
	addItem(QString("Hotland - Spider Entrance"));
	addItem(QString("Hotland - Hotel Lobby"));
	addItem(QString("Hotland - Core Branch"));
	addItem(QString("Hotland - Core End"));
	addItem(QString("Castle Elevator"));
	addItem(QString("New Home"));
	addItem(QString("Last Corridor"));
	addItem(QString("Throne Entrance"));
	addItem(QString("Throne Room"));
	addItem(QString("The End"));
	addItem(QString("True Laboratory"));
	addItem(QString("True Lab - Bedroom"));
	addItem(QString("room_start"));
	addItem(QString("room_introstory"));
	addItem(QString("room_introimage"));
	addItem(QString("room_intromenu"));
	addItem(QString("room_area1"));
	addItem(QString("room_area1_2"));
	addItem(QString("Ruins - 2"));
	addItem(QString("Ruins - 3"));
	addItem(QString("Ruins - 4"));
	addItem(QString("Ruins - 5"));
	addItem(QString("Ruins - 6"));
	addItem(QString("Ruins - 7A"));
	addItem(QString("Ruins - 8"));
	addItem(QString("Ruins - 9"));
	addItem(QString("Ruins - 10"));
	addItem(QString("Ruins - 11"));
	addItem(QString("Ruins - 12"));
	addItem(QString("Ruins - 12B"));
	addItem(QString("Ruins - 13"));
	addItem(QString("Ruins - 14"));
	addItem(QString("Ruins - 15A"));
	addItem(QString("Ruins - 15B"));
	addItem(QString("Ruins - 15C"));
	addItem(QString("Ruins - 15D"));
	addItem(QString("Ruins - 15E"));
	addItem(QString("Ruins - 16"));
	addItem(QString("Ruins - 17"));
	addItem(QString("Ruins - 18OLD"));
	addItem(QString("Home - Entrance Hall"));
	addItem(QString("Home - Living Room"));
	addItem(QString("Home - Hall"));
	addItem(QString("Home - Toriel's Room"));
	addItem(QString("Home - Asriel's Room"));
	addItem(QString("Home - Kitchen"));
	addItem(QString("room_basement1"));
	addItem(QString("room_basement2"));
	addItem(QString("room_basement3"));
	addItem(QString("room_basement4"));
	addItem(QString("room_basement5"));
	addItem(QString("Snowdin - Ruins Exit"));
	addItem(QString("Snowdin - 1"));
	addItem(QString("Snowdin - 2"));
	addItem(QString("Snowdin - 3A"));
	addItem(QString("Snowdin - 4"));
	addItem(QString("Snowdin - 5"));
	addItem(QString("Snowdin - 6"));
	addItem(QString("Snowdin - 6A"));
	addItem(QString("Snowdin - 7"));
	addItem(QString("Snowdin - 8"));
	addItem(QString("Snowdin - 8A"));
	addItem(QString("Snowdin - 9"));
	addItem(QString("Snowdin - Snow Puzzle"));
	addItem(QString("Snowdin - XO Puzzle (Small)"));
	addItem(QString("Snowdin - XO Puzzle (Papyrus)"));
	addItem(QString("Snowdin - Tile Puzzle"));
	addItem(QString("Snowdin - icehole"));
	addItem(QString("Snowdin - iceentrance"));
	addItem(QString("Snowdin - iceexit_new"));
	addItem(QString("Snowdin - iceexit"));
	addItem(QString("Snowdin - Snow Poff Zone"));
	addItem(QString("Snowdin - Dangerous Bridge Puzzle"));
	addItem(QString("Snowdin - town2"));
	addItem(QString("Snowdin - Dock"));
	addItem(QString("Snowdin - Snowed Inn"));
	addItem(QString("Snowdin - Snowed Inn (2nd floor)"));
	addItem(QString("Snowdin - Grillby's"));
	addItem(QString("Snowdin - Library"));
	addItem(QString("Snowdin - Garage"));
	addItem(QString("Snowdin - Papyrus's and Sans's House"));
	addItem(QString("Snowdin - Papyrus's Room"));
	addItem(QString("Snowdin - Sans's Room"));
	addItem(QString("Snowdin - Sans's Room (Dark)"));
	addItem(QString("Snowdin - Sans's Basement"));
	addItem(QString("Snowdin - Foggy Hallway"));
	addItem(QString("Waterfall - 1"));
	addItem(QString("Waterfall - 3"));
	addItem(QString("Waterfall - 3A"));
	addItem(QString("Waterfall - bridgepuzz1"));
	addItem(QString("Waterfall - 5"));
	addItem(QString("Waterfall - 5A"));
	addItem(QString("Waterfall - 6"));
	addItem(QString("Waterfall - 7"));
	addItem(QString("Waterfall - 8"));
	addItem(QString("Waterfall - 9"));
	addItem(QString("Waterfall - 11"));
	addItem(QString("Waterfall - nicecream"));
	addItem(QString("Waterfall - 12"));
	addItem(QString("Waterfall - shoe"));
	addItem(QString("Waterfall - bird"));
	addItem(QString("Waterfall - Onionsan"));
	addItem(QString("Waterfall - 14"));
	addItem(QString("Waterfall - Piano Puzzle"));
	addItem(QString("Waterfall - dogroom"));
	addItem(QString("Waterfall - Music Box Statue"));
	addItem(QString("Waterfall - prewaterfall"));
	addItem(QString("Waterfall - waterfall"));
	addItem(QString("Waterfall - waterfall2"));
	addItem(QString("Waterfall - waterfall3"));
	addItem(QString("Waterfall - waterfall4"));
	addItem(QString("Waterfall - undynebridge"));
	addItem(QString("Waterfall - undynebridgeend"));
	addItem(QString("Waterfall - trashzone1"));
	addItem(QString("Waterfall - trashzone2"));
	addItem(QString("Waterfall - Undyne's Yard"));
	addItem(QString("Waterfall - Undyne's House"));
	addItem(QString("Waterfall - Blooky's Yard"));
	addItem(QString("Waterfall - Blooky's House"));
	addItem(QString("Waterfall - hapstablook"));
	addItem(QString("Waterfall - Blook Farm"));
	addItem(QString("Waterfall - prebird"));
	addItem(QString("Waterfall - Gerson's Shop"));
	addItem(QString("Waterfall - Dock"));
	addItem(QString("Waterfall - 15"));
	addItem(QString("Waterfall - 16"));
	addItem(QString("Waterfall - 17"));
	addItem(QString("Waterfall - 18"));
	addItem(QString("Waterfall - 19"));
	addItem(QString("Waterfall - 20"));
	addItem(QString("Waterfall - Puzzle Elder"));
	addItem(QString("Waterfall - Arena Exit"));
	addItem(QString("Waterfall - Hotland Entrance"));
	addItem(QString("Hotland - Sans's Station"));
	addItem(QString("Hotland - Water Cooler"));
	addItem(QString("Hotland - Dock"));
	addItem(QString("Hotland - lab1"));
	addItem(QString("Hotland - lab2"));
	addItem(QString("Hotland - 3"));
	addItem(QString("Hotland - 5"));
	addItem(QString("Hotland - 6A"));
	addItem(QString("Hotland - lasers1"));
	addItem(QString("Hotland - 7"));
	addItem(QString("Hotland - 8"));
	addItem(QString("Hotland - shootguy_2"));
	addItem(QString("Hotland - 9"));
	addItem(QString("Hotland - shootguy_1"));
	addItem(QString("Hotland - turn"));
	addItem(QString("Hotland - cookingshow"));
	addItem(QString("Hotland - elevator_r1"));
	addItem(QString("Hotland - elevator_r2"));
	addItem(QString("Hotland - hotdog"));
	addItem(QString("Hotland - walkandbranch"));
	addItem(QString("Hotland - sorry"));
	addItem(QString("Hotland - apron"));
	addItem(QString("Hotland - 10"));
	addItem(QString("Hotland - rpuzzle"));
	addItem(QString("Hotland - boysnightout"));
	addItem(QString("Hotland - newsreport"));
	addItem(QString("Hotland - coreview2"));
	addItem(QString("Hotland - elevator_l2"));
	addItem(QString("Hotland - elevator_l3"));
	addItem(QString("Hotland - spidershop"));
	addItem(QString("Hotland - walkandbranch2"));
	addItem(QString("Hotland - conveyorlaser"));
	addItem(QString("Hotland - shootguy_3"));
	addItem(QString("Hotland - preshootguy4"));
	addItem(QString("Hotland - shootguy_4"));
	addItem(QString("Hotland - Spider's Web"));
	addItem(QString("Hotland - pacing"));
	addItem(QString("Hotland - operatest"));
	addItem(QString("Hotland - Tile Puzzle EX"));
	addItem(QString("Hotland - hotelfront_1"));
	addItem(QString("Hotland - hotelfront_2"));
	addItem(QString("Hotel - Restaurant"));
	addItem(QString("Hotland - hoteldoors"));
	addItem(QString("Hotland - hotelbed"));
	addItem(QString("Hotland - elevator_r3"));
	addItem(QString("Hotland - precore"));
	addItem(QString("Hotland - core1"));
	addItem(QString("Hotland - core2"));
	addItem(QString("Hotland - core3"));
	addItem(QString("Hotland - core4"));
	addItem(QString("Hotland - core5"));
	addItem(QString("Hotland - core_freebattle"));
	addItem(QString("Hotland - core_laserfun"));
	addItem(QString("Hotland - core_bottomleft"));
	addItem(QString("Hotland - core_left"));
	addItem(QString("Hotland - core_topleft"));
	addItem(QString("Hotland - core_top"));
	addItem(QString("Hotland - core_topright"));
	addItem(QString("Hotland - core_right"));
	addItem(QString("Hotland - core_bottomright"));
	addItem(QString("Hotland - core_center"));
	addItem(QString("Hotland - shootguy_5"));
	addItem(QString("Hotland - core_treasureleft"));
	addItem(QString("Hotland - core_treasureright"));
	addItem(QString("Hotland - core_warrior"));
	addItem(QString("Hotland - core_bridge"));
	addItem(QString("Hotland - core_metttest"));
	addItem(QString("Hotland - core_final"));
	addItem(QString("Hotland - elevator"));
	addItem(QString("Hotland - elevator_l1"));
	addItem(QString("Hotland - finalelevator"));
	addItem(QString("room_castle_precastle"));
	addItem(QString("room_castle_hook"));
	addItem(QString("room_asghouse1"));
	addItem(QString("room_asghouse2"));
	addItem(QString("room_asghouse3"));
	addItem(QString("room_asgoreroom"));
	addItem(QString("room_asrielroom_final"));
	addItem(QString("room_kitchen_final"));
	addItem(QString("room_basement1_final"));
	addItem(QString("room_basement2_final"));
	addItem(QString("room_basement3_final"));
	addItem(QString("room_basement4_final"));
	addItem(QString("room_lastruins_corridor"));
	addItem(QString("room_castle_coffins1"));
	addItem(QString("room_castle_coffins2"));
	addItem(QString("room_castle_barrier"));
	addItem(QString("room_castle_exit"));
	addItem(QString("room_undertale_end"));
	addItem(QString("room_castle_trueexit"));
	addItem(QString("room_outsideworld"));
	addItem(QString("Hotland - labelevator"));
	addItem(QString("True Lab - elevatorinside"));
	addItem(QString("True Lab - elevator"));
	addItem(QString("True Lab - hall1"));
	addItem(QString("True Lab - hall2"));
	addItem(QString("True Lab - operatingroom"));
	addItem(QString("True Lab - Red Lever"));
	addItem(QString("True Lab - prebed"));
	addItem(QString("True Lab - mirror"));
	addItem(QString("True Lab - Blue Lever"));
	addItem(QString("True Lab - hall3"));
	addItem(QString("True Lab - shower"));
	addItem(QString("True Lab - determination"));
	addItem(QString("True Lab - tv"));
	addItem(QString("True Lab - cooler"));
	addItem(QString("True Lab - Green Lever"));
	addItem(QString("True Lab - fan"));
	addItem(QString("True Lab - castle_elevator"));
	addItem(QString("True Lab - prepower"));
	addItem(QString("True Lab - power"));
	addItem(QString("room_gaster"));
	addItem(QString("room_icecave1"));
	addItem(QString("room_ice_dog"));
	addItem(QString("room2"));
	addItem(QString("Waterfall - fakehallway"));
	addItem(QString("room_mysteryman"));
	addItem(QString("room_soundtest"));
	addItem(QString("TESTROOM"));
	addItem(QString("Waterfall - redacted"));
	addItem(QString("Waterfall - 13"));
	addItem(QString("room_overworld"));
	addItem(QString("room_overworld3"));
	addItem(QString("bullettest"));
	addItem(QString("Waterfall - 16A"));
	addItem(QString("room_end_castroll"));
	addItem(QString("room_end_highway"));
	addItem(QString("room_end_beach"));
	addItem(QString("room_end_metta"));
	addItem(QString("room_end_school"));
	addItem(QString("room_end_mtebott"));
	addItem(QString("room_creditsdodger"));
	addItem(QString("room_end_myroom"));
	addItem(QString("room_end_theend"));
	addItem(QString("room_spritecheck"));
	addItem(QString("room_joyconfig"));
	addItem(QString("room_controltest"));
	addItem(QString("room_f_start"));
	addItem(QString("room_f_intro"));
	addItem(QString("room_f_menu"));
	addItem(QString("room_f_room"));
	addItem(QString("room_floweyx"));
	addItem(QString("room_f_phrase"));
	addItem(QString("Hotland - 4"));
	addItem(QString("Hotland - 10_old"));
	addItem(QString("Hotland - 10A_old"));
	addItem(QString("Snowdin - placeholder"));
	addItem(QString("Ruins - 12B_old"));
	addItem(QString("Snowdin - rollsnow"));
	addItem(QString("Waterfall - 7_older"));
	addItem(QString("room_meetundyne_old"));
	addItem(QString("Waterfall - mushroom"));
	addItem(QString("room_monsteralign_test"));
	addItem(QString("room_battle"));
	addItem(QString("room_floweybattle"));
	addItem(QString("room_fastbattle"));
	addItem(QString("room_storybattle"));
	addItem(QString("room_gameover"));
	addItem(QString("room_shop1"));
	addItem(QString("room_shop2"));
	addItem(QString("room_shop3"));
	addItem(QString("room_shop4"));
	addItem(QString("room_shop5"));
	addItem(QString("room_riverman_transition"));
	addItem(QString("room_papdate"));
	addItem(QString("room_adate"));
	addItem(QString("room_flowey_endchoice"));
	addItem(QString("room_flowey_regret"));
	addItem(QString("room_empty"));
	addItem(QString("room_emptywhite"));
	addItem(QString("room_emptyblack"));
	addItem(QString("room_nothingness"));
	addItem(QString("room_undertale"));
	addItem(QString("room_of_dog"));
	addItem(QString("room_quizholder"));
	addItem(QString("room_friendtest"));
	addItem(QString("room_bringitinguys"));
	addItem(QString("room_asrielappears"));
	addItem(QString("room_goodbyeasriel"));
	addItem(QString("room_asrielmemory"));
	addItem(QString("room_asrieltest"));
	addItem(QString("room_afinaltest"));

	connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSave(int)));
	connect(mw, SIGNAL(updateWidgets()), this, SLOT(updateData()));
	connect(this, SIGNAL(dataChanged(bool)), mw, SLOT(fileModified(bool)));
}
void RoomComboBox::updateSave(int i)
{
	mw->saveData.replace(id, QString::number(values[i]));
	emit dataChanged(true);
}
void RoomComboBox::updateData()
{
	setCurrentIndex(indexes.value(mw->saveData.at(id).toInt()));
}

TimeEdit::TimeEdit(int id, MainWindow *mainWindow, QWidget *parent) : QWidget(parent), id(id), mw(mainWindow)
{
	data = new QDoubleSpinBox();
	data->setDecimals(0);
	data->setRange(0, INT64_MAX);
	label = new QLabel(QString("00:00:00"));

	setLayout(new QHBoxLayout());
	layout()->addWidget(label);
	layout()->addWidget(data);

	connect(data, SIGNAL(valueChanged(double)), this, SLOT(updateSave(double)));
	connect(mw, SIGNAL(updateWidgets()), this, SLOT(updateData()));
	connect(this, SIGNAL(dataChanged(bool)), mw, SLOT(fileModified(bool)));
}
void TimeEdit::updateSave(double d)
{
	int h = qRound(d/108000.0);
	int m = qRound(d/1800) % 60;
	int s = qRound(d/30) % 60;
	label->setText(QString("%1:%2:%3").arg(h, 2, 'f', 0, '0').arg(m, 2, 'f', 0, '0').arg(s, 2, 'f', 0, '0'));
	mw->saveData.replace(id, QString::number(d, 'g', 5));
	emit dataChanged(true);
}
void TimeEdit::updateData()
{
	double d = mw->saveData.at(id).toDouble();
	data->setValue(d);
	int h = qRound(d/108000.0);
	int m = qRound(d/1800) % 60;
	int s = qRound(d/30) % 60;
	label->setText(QString("%1:%2:%3").arg(h, 2, 'f', 0, '0').arg(m, 2, 'f', 0, '0').arg(s, 2, 'f', 0, '0'));
}


PlotEdit::PlotEdit(int id, MainWindow *mainWindow, QWidget *parent) : QComboBox(parent), id(id), mw(mainWindow)
{
	addItem(tr("New Game"));
	addItem(tr("Met Flowey"));
	addItem(tr("Toriel escorted you to the next room"));
	addItem(tr("Toriel explained puzzles"));
	addItem(tr("Switch puzzle started"));
	addItem(tr("Pulled first switch"));
	addItem(tr("Pulled second switch"));
	addItem(tr("Practice dummy"));
	addItem(tr("Interacted with the dummy"));
	addItem(tr("Dummy encounter done"));
	addItem(tr("Dangerous puzzle started"));
	addItem(tr("Dangerous puzzle ended"));
	addItem(tr("Independence test started"));
	addItem(tr("Independence test ended"));
	addItem(tr("Toriel called about leaving the room"));
	addItem(tr("Toriel called about pie flavor"));
	addItem(tr("Toriel called again"));
	addItem(tr("Toriel called about allergies"));
	addItem(tr("Cheered Napstablook"));
	addItem(tr("Napstablook encounter done"));
	addItem(tr("Talked with Napstablook"));
	addItem(tr("Napstablook disappeared"));
	addItem(tr("Toriel called about picking up items"));
	addItem(tr("Hit the switch in a pit"));
	addItem(tr("Pressed a blue switch"));
	addItem(tr("Pressed a red switch"));
	addItem(tr("Pressed a green switch"));
	addItem(tr("Met Toriel again"));
	addItem(tr("Toriel told about pie"));
	addItem(tr("Toriel showed you your room"));
	addItem(tr("Talked with Toriel"));
	addItem(tr("Talked with Toriel more"));
	addItem(tr("Talked with Toriel some more"));
	addItem(tr("Listened about snail facts"));
	addItem(tr("You asked \"How to exit the Ruins\""));
	addItem(tr("Toriel has to do something"));
	addItem(tr("Toriel went to the basement"));
	addItem(tr("Toriel is going to destroy the exit"));
	addItem(tr("Toriel warned about Asgore"));
	addItem(tr("Toriel warned you for the last time"));
	addItem(tr("Toriel encounter done"));
	addItem(tr("Talked with Flowey"));
	addItem(tr("Exited Ruins"));
	addItem(tr("Conveniently-shaped lamp"));
	addItem(tr("sans left the area"));
	addItem(tr("Papyrus met the human"));
	addItem(tr("Doggo encounter done"));
	addItem(tr("Doggo went to get dog treats"));
	addItem(tr("Solved the electricity maze"));
	addItem(tr("\"Solved\" sans's puzzle"));
	addItem(tr("Found the buried switch"));
	addItem(tr("Dogamy and Dogaressa encounter done"));
	addItem(tr("Dogamy and Dogaressa left the area"));
	addItem(tr("Solved the first XO puzzle"));
	addItem(tr("Reached the second XO puzzle"));
	addItem(tr("Solved the second XO puzzle"));
	addItem(tr("Skip the XO puzzles"));
	addItem(tr("\"Solved\" the Multicolor Tile Puzzle"));
	addItem(tr("Greater Dog encounter done"));
	addItem(tr("Greater Dog encounter done"));
	addItem(tr("Solved the third XO puzzle"));
	addItem(tr("Greater Dog left the area"));
	addItem(tr("\"Solved\" the final puzzle"));
	addItem(tr("Papyrus encounter done"));
	addItem(tr("Papyrus left the area"));
	addItem(tr("(unused) Monster Kid trigger"));
	addItem(tr("Undyne spotted you in the sea-grass"));
	addItem(tr("Papyrus called about your armor"));
	addItem(tr("Found the hidden door"));
	addItem(tr("(unused) Solved torch puzzle"));
	addItem(tr("Undyne grabbed Monster Kid in the sea-grass"));
	addItem(tr("Encountered Shyren"));
	addItem(tr("Monster Kid offered to help climb a ledge"));
	addItem(tr("Monster Kid left the area"));
	addItem(tr("Wakeup in the Trash Zone"));
	addItem(tr("Mad Dummy encounter done"));
	addItem(tr("Napstablook went home"));
	addItem(tr("Undyne dragged Monster Kid away"));
	addItem(tr("Walked to the end of Echo Flower path"));
	addItem(tr("Monster Kid tripped on a bridge"));
	addItem(tr("Undyne confronted you"));
	addItem(tr("Undyne encounter done"));
	addItem(tr("Mettaton's game show"));
	addItem(tr("Alphys upgraded your phone"));
	addItem(tr("Alphys hung up on you"));
	addItem(tr("Alphys called about the lasers"));
	addItem(tr("Alphys called about the Shooting Puzzles"));
	addItem(tr("Opened the first large door"));
	addItem(tr("Alphys called about the puzzles again"));
	addItem(tr("Alphys called during Mettaton's cooking show"));
	addItem(tr("Mettaton's cooking show done"));
	addItem(tr("Alphys called about the Core"));
	addItem(tr("Alphys called about the conveyor puzzle"));
	addItem(tr("Alphys tried to help with the timing"));
	addItem(tr("Alphys called about going to the bathroom"));
	addItem(tr("Royal Guard encounter done"));
	addItem(tr("Skip Hotland puzzles"));
	addItem(tr("MTT News done"));
	addItem(tr("Alphys called about Asgore"));
	addItem(tr("Alphys called about the Shooting Puzzles"));
	addItem(tr("Opened the second large door"));
	addItem(tr("Muffet encounter done"));
	addItem(tr("Mettaton opera"));
	addItem(tr("Mettaton's Multicolor Tile Puzzle done"));
	addItem(tr("Exited the MTT Resort"));
	addItem(tr("Alphys called at the Core lobby"));
	addItem(tr("Fought mercenaries"));
	addItem(tr("Alphys called about the order of lasers"));
	addItem(tr("Alphys called after the lasers"));
	addItem(tr("Alphys called at the crossroads"));
	addItem(tr("(unused) Laser event"));
	addItem(tr("Alphys called about how everything is under control"));
	addItem(tr("Alphys called at the Core Branch"));
	addItem(tr("Mettaton EX encounter done"));
	addItem(tr("Alphys told the truth"));
	addItem(tr("sans judged you"));
	addItem(tr("Met Asgore"));
	addItem(tr("Asgore told how tense this is"));
	addItem(tr("Asgore entered the barrier room"));
	addItem(tr("True Pacifist"));

	connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(updateSave(int)));
	connect(mw, SIGNAL(updateWidgets()), this, SLOT(updateData()));
	connect(this, SIGNAL(dataChanged(bool)), mw, SLOT(fileModified(bool)));
}
void PlotEdit::updateSave(int i)
{
	mw->saveData.replace(id, QString::number(values[i]));
	emit dataChanged(true);
}
void PlotEdit::updateData()
{
	setCurrentIndex(indexes.value(mw->saveData.at(id).toInt()));
}
