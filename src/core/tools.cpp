#include <QHBoxLayout>

#include "src/core/mainwindow.h"
#include "src/core/tools.h"
#include "src/helpers.h"

template<typename T>
CustomEditor::CustomEditor(const int identifier, T **editorWidget, QWidget *buddyWidget) : editor(new T()), id(identifier), buddy(buddyWidget)
{
	MainWindow::editors.insert(id, this);
	*editorWidget = qobject_cast<T *>(editor); // Have to do some evil pointer hack to get this working

	setObjectName(QString::number(id));
	auto *hLayout = new QHBoxLayout();
	if (buddy)
	{
		hLayout->addWidget(buddy);
	}
	hLayout->addWidget(editor);
	vLayout->addLayout(hLayout);
	vLayout->setSpacing(0);
	setLayout(vLayout);


	connect(MainWindow::instance, &MainWindow::updateWidgets, this, &CustomEditor::updateData);
	connect(MainWindow::instance, &MainWindow::toggleDarkMode, this, [this] (const bool isDarkMode) -> void {
		const QString fontColor = isDarkMode ? QStringLiteral("white") : QStringLiteral("black");
		setStyleSheet(QStringLiteral("CustomEditor > QLabel { color: %1; } CustomEditor:hover { padding: 4px; border: 1px solid gray; }").arg(fontColor));
	});
	connect(this, &CustomEditor::dataChanged, MainWindow::instance, &MainWindow::fileModified);
}

CustomEditor::~CustomEditor()
{
	if (MainWindow::exists)
	{
		MainWindow::editors.remove(id, this); // Clean up this editor from the main map
		for (CustomEditor *item : MainWindow::editors.values(id)) // Update any other editor that might share this id
		{
			const bool changed = MainWindow::originalFile.at(id) != MainWindow::saveData.at(id);
			item->updateData();
			item->updateSave(changed);
		}
	}
}

void CustomEditor::addHintText(const QString &text)
{
	label = new QLabel(text);
	label->setStyleSheet(QStringLiteral("color: gray; font-size: 8pt;"));
	label->setWordWrap(true);
	label->setTextFormat(Qt::MarkdownText);

	vLayout->addWidget(label);
}

void CustomEditor::updateSave(const bool hasChanged)
{
	updateStyle(hasChanged);
	emit dataChanged(hasChanged);
	callback();
}

void CustomEditor::updateStyle(const bool hasChanged)
{
	const QString style = hasChanged ? QStringLiteral("font-weight: bold;") : QStringLiteral("font-weight: normal;");
	editor->setStyleSheet(style);
	if (buddy)
	{
		buddy->setStyleSheet(style);
	}
}

CustomLineEdit::CustomLineEdit(const int id, QWidget *buddyWidget) : CustomEditor(id, &editor, buddyWidget)
{
	editor->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

	switch (id)
	{
		case 1:
		{
			const QString hintText = QStringLiteral("Used in dialog and menus");
			addHintText(hintText);
			callback = [this, hintText]() -> void {
				label->setText((editor->text().size() > 6) ? QStringLiteral("Easy to change, huh?") : hintText);
			};
			break;
		}
	}

	connect(editor, &QLineEdit::textEdited, this, &CustomLineEdit::updateSave);
}

void CustomLineEdit::updateSave(const QString &data)
{
	MainWindow::saveData.replace(id, data);
	CustomEditor::updateSave(data != MainWindow::originalFile.at(id));
}

void CustomLineEdit::updateData()
{
	QSignalBlocker blocker(editor);

	editor->setText(MainWindow::saveData.at(id));
	updateStyle(false);
	callback();
}

CustomComboBox::CustomComboBox(int id, QWidget *buddyWidget) : CustomEditor(id, &editor, buddyWidget)
{
	switch (id)
	{
		case 45:
		{
			editor->addItem(QStringLiteral("Fled"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Killed"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Spared"));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("Bored"));
			indexes.insert(3, 3);

			addHintText(QStringLiteral("If set to \"%1\" in %2, %3 will mention it").arg(editor->itemText(3), Str_Ruins, Str_Mad_Dummy));
			break;
		}
		case 53:
		{
			editor->addItem(QStringLiteral("Yellow"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("White"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Pink"));
			indexes.insert(2, 2);

			addHintText(QStringLiteral("If not \"%1\", there will be a pile of yellow names in the Trash Zone").arg(editor->itemText(0)));
			break;
		}
		case 65:
		{
			editor->addItem(QStringLiteral("No candy taken"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("\"You took a piece of candy.\""));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("\"You took more candy.\""));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("\"You take another piece.\""));
			indexes.insert(3, 3);
			editor->addItem(QStringLiteral("\"You took too much too fast.\""));
			indexes.insert(4, 4);
			break;
		}
		case 67:
		{
			editor->addItem(QStringLiteral("Blocking the way"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Not blocking the way"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Talked to in a pit"));
			indexes.insert(2, 2);
			break;
		}
		case 68:
		{
			editor->addItem(QStringLiteral("Phone not kidnapped"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Phone kidnapped"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("\"My apologies. A strange dog kidnapped my phone.\""));
			indexes.insert(2, 2);
			break;
		}
		case 76:
		{
			editor->addItem(QStringLiteral("Arrived at \"Home\""));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Tried to exit %1").arg(Str_Ruins));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Fought"));
			indexes.insert(3, 2);
			editor->addItem(QStringLiteral("Killed"));
			indexes.insert(4, 3);
			editor->addItem(QStringLiteral("Spared"));
			indexes.insert(5, 4);
			break;
		}
		case 77:
		{
			editor->addItem(QStringLiteral("Cinnamon"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Butterscotch"));
			indexes.insert(1, 1);
			break;
		}
		case 78:
		{
			editor->addItem(QStringLiteral("Reached the bridge"));
			indexes.insert(-1, 0);
			editor->addItem(QStringLiteral("Not reached"));
			indexes.insert(0, 1);
			editor->addItem(QStringLiteral("Stick breaks"));
			indexes.insert(2, 3);
			editor->addItem(QStringLiteral("Shadow appears"));
			indexes.insert(3, 4);
			break;
		}
		case 83:
		{
			editor->addItem(QStringLiteral("Spared"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Killed"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Used Stick"));
			indexes.insert(2, 2);
			break;
		}
		case 84:
		{
			editor->addItem(QStringLiteral("Spared"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Killed"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Used Stick"));
			indexes.insert(2, 2);
			break;
		}
		case 85:
		{
			editor->addItem(QStringLiteral("Spared"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Killed"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Used Stick"));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("Bored"));
			indexes.insert(3, 3);
			break;
		}
		case 86:
		{
			editor->addItem(QStringLiteral("Spared"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Killed"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Petted"));
			indexes.insert(2, 2);
			break;
		}
		case 87:
		{
			editor->addItem(QStringLiteral("No interaction"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Got a piece"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Got another piece"));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("Ate the piece in front of them"));
			indexes.insert(4, 3);
			editor->addItem(QStringLiteral("Spoke after eating a piece"));
			indexes.insert(5, 4);
			break;
		}
		case 88:
		{
			editor->addItem(QStringLiteral("Not encountered"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Laughed at jokes"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Killed"));
			indexes.insert(2, 2);

			addHintText(QStringLiteral("If \"%1\", Chilldrakes will begin to show up").arg(editor->itemText(2)));
			break;
		}
		case 89:
		{
			editor->addItem(QStringLiteral("Junior Jumble"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Crossword"));
			indexes.insert(1, 1);
			break;
		}
		case 93:
		{
			editor->addItem(QStringLiteral("Not set"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Ate it"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Left it"));
			indexes.insert(2, 2);
			break;
		}
		case 95:
		{
			editor->addItem(QStringLiteral("Not pressed"));
			indexes.insert(-1, 0);
			editor->addItem(QStringLiteral("Available"));
			indexes.insert(0, 1);
			editor->addItem(QStringLiteral("Pressed"));
			indexes.insert(1, 2);
			break;
		}
		case 98:
		{
			editor->addItem(QStringLiteral("Captured you thrice"));
			indexes.insert(-3, 0);
			editor->addItem(QStringLiteral("Captured you twice"));
			indexes.insert(-2, 1);
			editor->addItem(QStringLiteral("Captured you"));
			indexes.insert(-1, 2);
			editor->addItem(QStringLiteral("Spared"));
			indexes.insert(0, 3);
			editor->addItem(QStringLiteral("Killed"));
			indexes.insert(1, 4);

			addHintText(QStringLiteral("If \"%1\", skip %2' battle").arg(editor->itemText(0), Str_Papyrus));
			break;
		}
		case 103:
		{
			editor->addItem(QStringLiteral("Not visited"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Paid 80G"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Stayed for free"));
			indexes.insert(2, 2);
			break;
		}
		case 106:
		{
			editor->addItem(QStringLiteral("Not reached"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Bandage"));
			indexes.insert(4, 1);
			editor->addItem(QStringLiteral("Faded Ribbon"));
			indexes.insert(12, 2);
			editor->addItem(QStringLiteral("Manly Bandanna"));
			indexes.insert(15, 3);
			editor->addItem(QStringLiteral("Old Tutu"));
			indexes.insert(24, 4);
			break;
		}
		case 108:
		{
			editor->addItem(QStringLiteral("Not reached"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Bandage"));
			indexes.insert(4, 1);
			editor->addItem(QStringLiteral("Faded Ribbon"));
			indexes.insert(12, 2);
			editor->addItem(QStringLiteral("Manly Bandanna"));
			indexes.insert(15, 3);
			editor->addItem(QStringLiteral("Old Tutu"));
			indexes.insert(24, 4);
			break;
		}
		case 112:
		{
			editor->addItem(QStringLiteral("Not encountered"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Killed"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Had a musical career"));
			indexes.insert(2, 2);

			addHintText(QStringLiteral("If \"%1\", you'll know the song for %2 and %3").arg(editor->itemText(2), Str_Knight_Knight, Str_Lemon_Bread));
			break;
		}
		case 119:
		{
			editor->addItem(QStringLiteral("No date"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Outside the house"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Inside the house"));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("Unlocked %1's room").arg(Str_Papyrus));
			indexes.insert(3, 3);
			editor->addItem(QStringLiteral("Date complete"));
			indexes.insert(4, 4);
			break;
		}
		case 120:
		{
			editor->addItem(QStringLiteral("No date"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Date started"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Date complete"));
			indexes.insert(2, 2);
			break;
		}
		case 121:
		{
			editor->addItem(QStringLiteral("Not met"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("\"You can't hold an umbrella either?\""));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("\"You got us an umbrella?\""));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("\"Where's the umbrella...?\""));
			indexes.insert(3, 3);
			break;
		}
		case 122:
		{
			editor->addItem(QStringLiteral("Not met"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Talked about %1").arg(Str_Undyne));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Talked about a school project"));
			indexes.insert(3, 2);
			editor->addItem(QStringLiteral("Talked about teachers"));
			indexes.insert(4, 3);
			editor->addItem(QStringLiteral("Staring at the castle in the distance"));
			indexes.insert(6, 4);
			editor->addItem(QStringLiteral("Helped you climb over a ledge"));
			indexes.insert(10, 5);

			addHintText(QStringLiteral("This value is also used for Trash Zone SAVE Point entry"));
			break;
		}
		case 124:
		{
			editor->addItem(QStringLiteral("No date"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Chatted in the house"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Lied on the ground"));
			indexes.insert(3, 2);
			editor->addItem(QStringLiteral("Didn't lie on the ground"));
			indexes.insert(9, 3);
			break;
		}
		case 125:
		{
			editor->addItem(QStringLiteral("Not playing"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Spooktunes"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Spookwave"));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("Ghouliday Music"));
			indexes.insert(3, 3);
			break;
		}
		case 127:
		{
			editor->addItem(QStringLiteral("\"That emblem\""));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("\"Emblem's meaning (NEW)\""));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("\"The prophecy (NEW)\""));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("\"The prophecy\""));
			indexes.insert(3, 3);
			break;
		}
		case 129:
		{
			editor->addItem(QStringLiteral("You ran away"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("You helped %1").arg(Str_Monster_Kid));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("You stood and watched"));
			indexes.insert(2, 2);

			addHintText(QStringLiteral("%1, %2, and %3 will comment on this").arg(Str_Papyrus, Str_Undyne, Str_Monster_Kid));
			break;
		}
		case 134:
		{
			editor->addItem(QStringLiteral("The pie is cooling"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("The pie is ready"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Got a slice"));
			indexes.insert(2, 2);
			break;
		}
		case 138:
		{
			editor->addItem(QStringLiteral("\"It's a legendary artifact.\""));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("\"The artifact is gone.\""));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("\"You're carrying too many dogs.\""));
			indexes.insert(2, 2);
			break;
		}
		case 139:
		{
			editor->addItem(QStringLiteral("Not checked the cooler"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Two food bars available"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("One food bar available"));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("The cooler is empty"));
			indexes.insert(3, 3);
			break;
		}
		case 284:
		{
			editor->addItem(QStringLiteral("\"Hello. I am a snowman. I cannot move.\""));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("\"Soon there won't be any of me left...\""));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("\"Stop... Please...\""));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("(An useless pile of snow.)"));
			indexes.insert(3, 3);
			break;
		}
		case 298:
		{
			editor->addItem(QStringLiteral("Not stayed"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("First time"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Second time"));
			indexes.insert(2, 2);
			break;
		}
		case 306:
		{
			editor->addItem(QStringLiteral("No action"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Heavy stick is broken"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Shadow appeared"));
			indexes.insert(2, 2);
			break;
		}
		case 311:
		{
			editor->addItem(QStringLiteral("Not talked"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Talked"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Tried to push the box"));
			indexes.insert(2, 2);
			break;
		}
		case 312:
		{
			editor->addItem(QStringLiteral("Not encountered"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Killed"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Spared"));
			indexes.insert(2, 2);
			break;
		}
		case 381:
		{
			editor->addItem(QStringLiteral("Given water"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Killed"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Spared without water"));
			indexes.insert(2, 2);
			break;
		}
		case 385:
		{
			editor->addItem(QStringLiteral("No call"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Entered the Winding Path room"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Called"));
			indexes.insert(2, 2);
			break;
		}
		case 386:
		{
			editor->addItem(QStringLiteral("No interaction"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Punched the dummy"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Stared for a moment"));
			indexes.insert(2, 2);

			addHintText(QStringLiteral("%1 will comment on this before fighting").arg(Str_Mad_Dummy));
			break;
		}
		case 416:
		{
			editor->addItem(QStringLiteral("Not available"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Available"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Activated"));
			indexes.insert(2, 2);
			break;
		}
		case 420:
		{
			editor->addItem(QStringLiteral("No date"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Talking outside"));
			indexes.insert(3, 1);
			editor->addItem(QStringLiteral("Running to %1's place").arg(Str_Papyrus));
			indexes.insert(4, 2);
			editor->addItem(QStringLiteral("Arrived at %1's place").arg(Str_Papyrus));
			indexes.insert(5, 3);
			break;
		}
		case 422:
		{
			editor->addItem(QStringLiteral("Nothing"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Fries"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Burger"));
			indexes.insert(2, 2);
			break;
		}
		case 427:
		{
			editor->addItem(QStringLiteral("\"Did you hear what they said?\""));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("\"They said a human wearing a striped shirt...\""));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("\"I heard that they hate spiders.\""));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("\"I heard that they love to stomp on them.\""));
			indexes.insert(3, 3);
			editor->addItem(QStringLiteral("\"I heard that they like to tear their legs off.\""));
			indexes.insert(4, 4);
			editor->addItem(QStringLiteral("\"I heard...\""));
			indexes.insert(5, 5);
			break;
		}
		case 429:
		{
			editor->addItem(QStringLiteral("Left Floor 1"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Right Floor 1"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Right Floor 2"));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("Left Floor 2"));
			indexes.insert(3, 3);
			editor->addItem(QStringLiteral("Left Floor 3"));
			indexes.insert(4, 4);
			editor->addItem(QStringLiteral("Right Floor 3"));
			indexes.insert(5, 5);
			break;
		}
		case 436:
		{
			editor->addItem(QStringLiteral("\"About your wares\""));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("\"Origin of wares (NEW)\""));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("\"Origin of garbage (NEW)\""));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("\"Origin of garbage\""));
			indexes.insert(3, 3);
			break;
		}
		case 437:
		{
			editor->addItem(QStringLiteral("\"About %1\"").arg(Str_Mettaton));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("\"Origin of %1 (NEW)\"").arg(Str_Mettaton));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("\"About %1 (OLD\?\?\?)\"").arg(Str_Mettaton));
			indexes.insert(2, 2);
			break;
		}
		case 438:
		{
			editor->addItem(QStringLiteral("\"About %1\"").arg(Str_Alphys));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("\"Royal Scientist (NEW)\""));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("\"About %1 (NEW)\"").arg(Str_Asgore.toUpper()));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("\"About %1\"").arg(Str_Asgore.toUpper()));
			indexes.insert(3, 3);
			break;
		}
		case 444:
		{
			editor->addItem(QStringLiteral("No Date"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Date started"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Date complete"));
			indexes.insert(2, 2);
			break;
		}
		case 452:
		{
			editor->addItem(QStringLiteral("Not reached"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("%1 and %2").arg(Str_Whimsalot, Str_Final_Froggit));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("%1 and %2").arg(Str_Knight_Knight, Str_Madjick));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("%1, %2, and %3").arg(Str_Final_Froggit, Str_Astigmatism, Str_Whimsalot));
			indexes.insert(3, 3);
			break;
		}
		case 455:
		{
			editor->addItem(QStringLiteral("Not encountered"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Can be exposed"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Switch exposed"));
			indexes.insert(2, 2);
			break;
		}
		case 462:
		{
			editor->addItem(Str_Core);
			indexes.insert(0, 0);
			editor->addItem(Str_Castle);
			indexes.insert(1, 1);
			break;
		}
		case 465:
		{
			editor->addItem(QStringLiteral("Not talked"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Remembered the name"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Forgot the name"));
			indexes.insert(2, 2);
			break;
		}
		case 466:
		{
			editor->addItem(QStringLiteral("Not talked"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Bought something"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Talked"));
			indexes.insert(2, 2);
			break;
		}
		case 467:
		{
			editor->addItem(QStringLiteral("\"%1\"").arg(Str_Mettaton));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("\"Why is %1 bad (NEW)\"").arg(Str_Mettaton));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("\"Why else is MTT bad (NEW)\""));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("\"Why else is MTT bad\""));
			indexes.insert(3, 3);
			break;
		}
		case 468:
		{
			editor->addItem(QStringLiteral("[B.Pants] \"Romance Advice\""));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("[B.Pants] \"Glamburger Story (NEW)\""));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("[B&C] \"%1 (NEW)\"").arg(Str_Burger_Pants));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("[B&C] \"More %1 (NEW)\"").arg(Str_Burger_Pants));
			indexes.insert(4, 3);
			editor->addItem(QStringLiteral("[B.Pants] \"%1 (NEW)\"").arg(Str_Bratty_and_Catty));
			indexes.insert(5, 4);
			editor->addItem(QStringLiteral("[B&C] \"%1 hangout (NEW)\"").arg(Str_Burger_Pants));
			indexes.insert(6, 5);
			editor->addItem(QStringLiteral("[B&C] \"That kind of guy (NEW)\""));
			indexes.insert(7, 6);
			editor->addItem(QStringLiteral("[B.Pants] \"%1's Invitation (NEW)\"").arg(Str_Catty));
			indexes.insert(8, 7);
			editor->addItem(QStringLiteral("[B.Pants] \"%1's Invitation\"").arg(Str_Catty));
			indexes.insert(9, 8);

			addHintText(QStringLiteral("The conversation takes place in two shops [marked in square brackets]"));
			break;
		}
		case 481:
		{
			editor->addItem(QStringLiteral("\"A long time ago, a human fell into %1.\"").arg(Str_Ruins.toUpper()));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("\"%1, the king's son, heard the human's call.\"").arg(Str_Asriel.toUpper()));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("\"Over time, %1 and the human became like siblings.\"").arg(Str_Asriel.toUpper()));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("\"Then... One day...\""));
			indexes.insert(3, 3);
			editor->addItem(QStringLiteral("\"The sick human had only one request.\""));
			indexes.insert(4, 4);
			editor->addItem(QStringLiteral("\"The next day.\""));
			indexes.insert(5, 5);
			editor->addItem(QStringLiteral("\"%1, wracked with grief, absorbed the human's SOUL.\"").arg(Str_Asriel.toUpper()));
			indexes.insert(6, 6);
			editor->addItem(QStringLiteral("\"With the human SOUL, %1 crossed through the barrier.\"").arg(Str_Asriel.toUpper()));
			indexes.insert(7, 7);
			editor->addItem(QStringLiteral("\"%1 reached the center of the village.\"").arg(Str_Asriel.toUpper()));
			indexes.insert(8, 8);
			editor->addItem(QStringLiteral("\"Suddenly, screams rang out.\""));
			indexes.insert(9, 9);
			editor->addItem(QStringLiteral("\"The humans attacked him with everything they had.\""));
			indexes.insert(10, 10);
			editor->addItem(QStringLiteral("\"But...\""));
			indexes.insert(11, 11);
			editor->addItem(QStringLiteral("\"Wounded, %1 stumbled home.\"").arg(Str_Asriel.toUpper()));
			indexes.insert(12, 12);
			editor->addItem(QStringLiteral("\"The kingdom fell into despair.\""));
			indexes.insert(13, 13);
			editor->addItem(QStringLiteral("\"The king decided it was time to end our suffering.\""));
			indexes.insert(14, 14);
			editor->addItem(QStringLiteral("\"It's not long now.\""));
			indexes.insert(15, 15);
			editor->addItem(QStringLiteral("\"You should be smiling, too.\""));
			indexes.insert(16, 16);
			editor->addItem(QStringLiteral("\"You're going to be free.\""));
			indexes.insert(17, 17);
			break;
		}
		case 485:
		{
			editor->addItem(QStringLiteral("(The way is blocked by two padlocks.)"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("(You'll need both keys to get through.)"));
			indexes.insert(0.5, 1);
			editor->addItem(QStringLiteral("(You unlocked the chain.)"));
			indexes.insert(1, 2);
			break;
		}
		case 490:
		{
			editor->addItem(QStringLiteral("%1 (Fallback)").arg(Str_Hotland));
			indexes.insert(0, 0);
			editor->addItem(Str_Snowdin);
			indexes.insert(1, 1);
			editor->addItem(Str_Waterfall);
			indexes.insert(2, 2);
			editor->addItem(Str_Hotland);
			indexes.insert(3, 3);
			break;
		}
		case 512:
		{
			editor->addItem(QStringLiteral("Need to find it"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Found it in the sink"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("(You put it on your keychain.)"));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("(The red switch has been turned on.)"));
			indexes.insert(3, 3);
			break;
		}
		case 513:
		{
			editor->addItem(QStringLiteral("Need to find it"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Found it in the refrigerator"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("(You put it on your keychain.)"));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("(The blue switch has been turned on.)"));
			indexes.insert(3, 3);
			break;
		}
		case 514:
		{
			editor->addItem(QStringLiteral("Need to find it"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Found it in the bathtub"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("(You put it on your keychain.)"));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("(The green switch has been turned on.)"));
			indexes.insert(3, 3);
			break;
		}
		case 515:
		{
			editor->addItem(QStringLiteral("Need to find it"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Found it under the bedsheets"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("(You put it on your keychain.)"));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("(The yellow switch has been turned on.)"));
			indexes.insert(3, 3);
			break;
		}
		case 518:
		{
			editor->addItem(QStringLiteral("Not checked any sink"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("The left sink"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("The middle sink"));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("The right sink"));
			indexes.insert(3, 3);
			break;
		}
		case 524:
		{
			editor->addItem(QStringLiteral("No interaction"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("%1 is available").arg(Str_Undyne_Letter));
			indexes.insert(8, 1);
			editor->addItem(QStringLiteral("Got %1").arg(Str_Undyne_Letter));
			indexes.insert(9, 2);
			editor->addItem(QStringLiteral("Date complete"));
			indexes.insert(10, 3);
			editor->addItem(QStringLiteral("Received a call from %1").arg(Str_Papyrus));
			indexes.insert(11, 4);
			editor->addItem(QStringLiteral("Completed %1").arg(Str_True_Lab));
			indexes.insert(12, 5);
			break;
		}
		case 525:
		{
			editor->addItem(QStringLiteral("No interaction"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Lost the letter"));
			indexes.insert(1, 1);
			editor->addItem(Str_Undyne_Letter);
			indexes.insert(2, 2);
			editor->addItem(Str_Undyne_Letter_EX);
			indexes.insert(3, 3);
			break;
		}
		case 527:
		{
			editor->addItem(QStringLiteral("%1 doesn't want to talk").arg(Str_Onionsan));
			indexes.insert(-1, 0);
			editor->addItem(QStringLiteral("No interaction"));
			indexes.insert(0, 1);
			editor->addItem(QStringLiteral("\"I'm %1!\"").arg(Str_Onionsan));
			indexes.insert(1, 2);
			editor->addItem(QStringLiteral("\"You're visiting %1, huh!\"").arg(Str_Waterfall));
			indexes.insert(2, 3);
			editor->addItem(QStringLiteral("\"Even though, the water's getting so shallow here...\""));
			indexes.insert(3, 4);
			editor->addItem(QStringLiteral("\"%1's gonna fix everything, y'hear!\"").arg(Str_Undyne));
			indexes.insert(4, 5);
			editor->addItem(QStringLiteral("\"That's the end of this room.\""));
			indexes.insert(5, 6);
			editor->addItem(QStringLiteral("\"Yeah, me too...\""));
			indexes.insert(6, 7);
			editor->addItem(QStringLiteral("\"I've been wondering when we're all gonna go free.\""));
			indexes.insert(7, 8);
			break;
		}
		case 528:
		{
			editor->addItem(QStringLiteral("Haven't got the key"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Got the key"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Entered %1's room").arg(Str_sans));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("Found the silver key"));
			indexes.insert(3, 3);
			break;
		}
		case 532:
		{
			editor->addItem(QStringLiteral("Not Reached"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Save everyone"));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Save someone else"));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("Save %1").arg(Str_Asriel));
			indexes.insert(3, 3);
			break;
		}
		case 540:
		{
			editor->addItem(QStringLiteral("Normal"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("\"00.001\""));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("\"00.0001\""));
			indexes.insert(2, 2);
			editor->addItem(QStringLiteral("\"00.000001\""));
			indexes.insert(3, 3);
			editor->addItem(QStringLiteral("\"00.0000000001\""));
			indexes.insert(4, 4);
			break;
		}
		case 541:
		{
			editor->addItem(QStringLiteral("Not reached"));
			indexes.insert(0, 0);
			editor->addItem(QStringLiteral("Talked with child %1").arg(Str_Asriel));
			indexes.insert(1, 1);
			editor->addItem(QStringLiteral("Talked with everyone"));
			indexes.insert(2, 2);
			break;
		}
	}

	connect(editor, &QComboBox::currentIndexChanged, this, &CustomComboBox::updateSave);
}

void CustomComboBox::updateSave(const int data)
{
	const QString saved = QString::number(indexes.key(data, -1));
	MainWindow::saveData.replace(id, saved);
	CustomEditor::updateSave(saved != MainWindow::originalFile.at(id));
}

void CustomComboBox::updateData()
{
	QSignalBlocker blocker(editor);

	const int data = indexes.value(MainWindow::saveData.at(id).toInt());
	editor->setCurrentIndex(data);
	updateStyle(false);
	callback();
}

CustomSpinBox::CustomSpinBox(int id, QWidget *buddyWidget) : CustomEditor(id, &editor, buddyWidget)
{
	editor->setRange(0, __DBL_MAX__);
	editor->setDecimals(0);

	switch (id)
	{
		case 2:
		{
			editor->setRange(1, 20);
			break;
		}
		case 5:
		{
			addHintText(QStringLiteral("Base attack power"));
			break;
		}
		case 6:
		{
			addHintText(QStringLiteral("Attack power from your weapon"));
			break;
		}
		case 7:
		{
			addHintText(QStringLiteral("Base defense"));
			break;
		}
		case 8:
		{
			addHintText(QStringLiteral("Defense from your armor"));
			break;
		}
		case 10:
		{
			editor->setRange(0, 99999);
			break;
		}
		case 12:
		{
			addHintText(QStringLiteral("Total amount of kills"));
			break;
		}
		case 36:
		{
			editor->setRange(1, 100);
			const QString hintTitle = QStringLiteral("Used to determine random events.");
			addHintText(hintTitle);

			callback = [this, hintTitle]() -> void {
				const double value = editor->value();
				QString hintText = QStringLiteral("No event");

				if ((value >= 2) && (value <= 39)) { hintText = QStringLiteral("Wrong Number Song"); }
				else if ((value >= 40) && (value <= 45)) { hintText = QStringLiteral("sans's call"); }
				else if ((value >= 46) && (value <= 50)) { hintText = QStringLiteral("Alphys's call"); }
				else if ((value >= 56) && (value <= 57)) { hintText = QStringLiteral("Nightmare Mode"); }
				else if (value == 61) { hintText = QStringLiteral("Gaster Follower #2"); }
				else if (value == 62) { hintText = QStringLiteral("Gaster Follower #1"); }
				else if (value == 63) { hintText = QStringLiteral("Gaster Follower #3"); }
				else if (value == 65) { hintText = QStringLiteral("Sound Test Room"); }
				else if (value == 66) { hintText = QStringLiteral("Fake Hallway"); }
				else if ((value >= 80) && (value <= 89)) { hintText = QStringLiteral("Clam Girl"); }
				else if ((value >= 91) && (value <= 100)) { hintText = QStringLiteral("Goner Kid"); }

				label->setText(QStringLiteral("%1<br />Possible event: **%2**").arg(hintTitle, hintText));
			};
			break;
		}
		case 40:
		{
			addHintText(QStringLiteral("Sometimes when backtracking %1 will appear briefly and burrow into the ground").arg(Str_Flowey));
			break;
		}
		case 56:
		{
			addHintText(QStringLiteral("If this is >5, remove a frog from the \"four frog\" room"));
			break;
		}
		case 57:
		{
			editor->setRange(0, 50);
			addHintText(QStringLiteral("Overrides your \"progress\" through the genocide route when this is >0"));
			break;
		}
		case 71:
		{
			addHintText(QStringLiteral("If this is >3, %1's reaction stays the same").arg(Str_Toriel));
			break;
		}
		case 74:
		{
			addHintText(QStringLiteral("If this is >25, you'll make the switches uncomfortable"));
			break;
		}
		case 75:
		{
			addHintText(QStringLiteral("If this is >9, %1's reaction stays the same").arg(Str_Toriel));
			break;
		}
		case 82:
		{
			addHintText(QStringLiteral("If this is 2, you'll get a hint about the blue switch in the second room"));
			break;
		}
		case 90:
		{
			addHintText(QStringLiteral("Checked values during battle: >0, >20, >50<br />Checked values during NPC talk: >0, >12, >24, >39, >69, >99, >8999<br />If this is > 8999, skip %1's battle").arg(Str_Muffet));
			break;
		}
		case 94:
		{
			addHintText(QStringLiteral("If this is >5, changes %1's dialog after the puzzle").arg(Str_sans));
			break;
		}
		case 101:
		{
			addHintText(QStringLiteral("0 = %1<br />1 = %2<br />2 (before %3) = random<br />2 (after %3) = %4<br />4 = random").arg(Str_Snowdrake, Str_Ice_Cap, Str_Doggo, Str_Lesser_Dog));
			break;
		}
		case 232:
		{
			addHintText(QStringLiteral("Calculated from regular kills"));
			break;
		}
		case 317:
		{
			addHintText(QStringLiteral("If this is >16, %1 has not sent any more messages").arg(Str_Toriel));
			break;
		}
		case 318:
		{
			addHintText(QStringLiteral("Gives you a new message when you move to another room"));
			break;
		}
		case 384:
		{
			addHintText(QStringLiteral("Affects dialog with \"Clamguy\"<br />If True Pacifist and the puddle is large, a small tree will begin to grow"));
			break;
		}
		case 388:
		{
			addHintText(QStringLiteral("0 = %1<br />1 = %2<br />2 = %3<br />>2 = random").arg(Str_Aaron, Str_Woshua, Str_Moldsmal));
			break;
		}
		case 389:
		{
			addHintText(QStringLiteral("0 = %1<br />1 = %2 and %3<br />2 = %4 and %5<br />3 = %3 and %4<br />>3 = random").arg(Str_Temmie, Str_Moldsmal, Str_Moldbygg, Str_Woshua, Str_Aaron));
			break;
		}
		case 400:
		{
			addHintText(QStringLiteral("Value 99 skips all messages"));
			break;
		}
		case 439:
		{
			addHintText(QStringLiteral("0 = %1<br />1 = %2<br />2 = %3<br />3 = %2 and %1<br />4 = %3 and %3<br />>4 = random").arg(Str_Vulkin, Str_Tsunderplane, Str_Pyrope));
			break;
		}
		case 454:
		{
			addHintText(QStringLiteral("0 = %1 and %2<br />1 = %1 and %3<br />2 = %4 and %5<br />>2 = random").arg(Str_Whimsalot, Str_Final_Froggit, Str_Astigmatism, Str_Knight_Knight, Str_Madjick));
			break;
		}
		case 457:
		{
			addHintText(QStringLiteral("0 = %1<br />1 = %2 and %3<br />2 = %2 and %1<br />3 = %3 and %1<br />4 = %4 and %5<br />>4 = random").arg(Str_Astigmatism, Str_Whimsalot, Str_Final_Froggit, Str_Knight_Knight, Str_Madjick));
			break;
		}
		case 493:
		{
			addHintText(QStringLiteral("Resets after changing rooms<br />Most rooms have more than one conversation"));
			break;
		}
		case 517:
		{
			addHintText(QStringLiteral("If this is 2, %1 appears<br />If this is 13, you'll get new dialog").arg(Str_Memoryhead));
			break;
		}
		case 526:
		{
			addHintText(QStringLiteral("If this is 8, the vending machine will be empty"));
			break;
		}
		case 535:
		{
			addHintText(QStringLiteral("Essentially measuring the progress of the fight"));
			break;
		}
	}

	connect(editor, &QDoubleSpinBox::valueChanged, this, &CustomSpinBox::updateSave);
}

void CustomSpinBox::updateSave(const double data)
{
	const QString saved = QString::number(data);
	MainWindow::saveData.replace(id, saved);
	CustomEditor::updateSave(saved != MainWindow::originalFile.at(id));
}

void CustomSpinBox::updateData()
{
	QSignalBlocker blocker(editor);

	editor->setValue(MainWindow::saveData.at(id).toInt());
	updateStyle(false);
	callback();
}

CustomCheckBox::CustomCheckBox(int id, const QString &text, QWidget *buddyWidget) : CustomEditor(id, &editor, buddyWidget)
{
	editor->setText(text);

	switch (id)
	{
		case 35:
		{
			addHintText(QStringLiteral("Makes %1 act as if you made no kills").arg(Str_Undyne));
			break;
		}
		case 39:
		{
			addHintText(QStringLiteral("Turned on after either completing the date with %1 or killing %2").arg(Str_Undyne, Str_Mettaton));
			break;
		}
		case 52:
		{
			addHintText(QStringLiteral("Determines if the Noodle cooking gag is used"));
			break;
		}
		case 58:
		{
			addHintText(QStringLiteral("Aborts the genocide run if you spare **%1**, **%2**, **%3**, **%4**, **%5**, **%6**, **%7**, **%8**, **%9**, **%10** or **%11**").arg(Str_Toriel, Str_Doggo, Str_Lesser_Dog, Str_Greater_Dog, Str_Dogamy_and_Dogaressa, Str_Papyrus, Str_Shyren, Str_Royal_Guards, Str_Muffet, Str_Glad_Dummy, Str_Monster_Kid));
			break;
		}
		case 59:
		{
			addHintText(QStringLiteral("Hold down C to instantly skip text"));
			break;
		}
		case 72:
		{
			addHintText(QStringLiteral("%1 tells %2 about this in True Pacifist ending").arg(Str_Toriel, Str_sans));
			break;
		}
		case 73:
		{
			addHintText(QStringLiteral("%1 tells %2 about this in True Pacifist ending").arg(Str_Toriel, Str_sans));
			break;
		}
		case 81:
		{
			addHintText(QStringLiteral("Changes dialog when interacting with the plants"));
			break;
		}
		case 117:
		{
			addHintText(QStringLiteral("Music box starts playing"));
			break;
		}
		case 122:
		{
			addHintText(QStringLiteral("This value is also used for \"Interaction with %1\"").arg(Str_Monster_Kid));
			break;
		}
		case 126:
		{
			addHintText(QStringLiteral("Encountered while %1's music is playing").arg(Str_Napstablook));
			break;
		}
		case 281:
		{
			addHintText(QStringLiteral("Stays false if %1 are dead").arg(Str_Royal_Guards));
			break;
		}
		case 285:
		{
			addHintText(QStringLiteral("There's dialog for both interacting and ignoring"));
			break;
		}
		case 286:
		{
			addHintText(QStringLiteral("Took 758G from behind the counter"));
			break;
		}
		case 287:
		{
			addHintText(QStringLiteral("Stole 5G from the till"));
			break;
		}
		case 291:
		{
			addHintText(QStringLiteral("%1 will comment on this in the ending phone call").arg(Str_sans));
			break;
		}
		case 293:
		{
			addHintText(QStringLiteral("Reward is 99G"));
			break;
		}
		case 294:
		{
			addHintText(QStringLiteral("Reward is 99G"));
			break;
		}
		case 295:
		{
			addHintText(QStringLiteral("Reward is a Hush Puppy.<br />Try delivering Hot Cat, Dog Salad or Dog Residue first"));
			break;
		}
		case 302:
		{
			addHintText(QStringLiteral("You're gonna have a bad time"));
			break;
		}
		case 303:
		{
			addHintText(QStringLiteral("Are you gonna have a badder time?"));
			break;
		}
		case 308:
		{
			addHintText(QStringLiteral("This applies only if \"fun value\" is correct"));
			break;
		}
		case 309:
		{
			addHintText(QStringLiteral("%1 will comment on this").arg(Str_Papyrus));
			break;
		}
		case 310:
		{
			addHintText(QStringLiteral("This applies only if \"fun value\" is correct"));
			break;
		}
		case 319:
		{
			addHintText(QStringLiteral("%1 will comment on this and try to save the show").arg(Str_Mettaton));
			break;
		}
		case 314:
		{
			addHintText(QStringLiteral("Disables %1 encounter").arg(Str_Glyde));
			break;
		}
		case 315:
		{
			addHintText(QStringLiteral("%1's spear attacks become very fast.<br />%2 comments on how mad %1 was").arg(Str_Undyne, Str_Monster_Kid));
			break;
		}
		case 316:
		{
			addHintText(QStringLiteral("%1's spear attacks become very fast").arg(Str_Undyne));
			break;
		}
		case 320:
		{
			addHintText(QStringLiteral("%1's will comment on this").arg(Str_Mettaton));
			break;
		}
		case 327:
		{
			addHintText(QStringLiteral("Begins the \"quest\""));
			break;
		}
		case 383:
		{
			addHintText(QStringLiteral("%1 says something new before attacking").arg(Str_Undyne));
			break;
		}
		case 408:
		{
			addHintText(QStringLiteral("%1 will comment on this and try to save the show").arg(Str_Mettaton));
			break;
		}
		case 432:
		{
			addHintText(QStringLiteral("Changes %1's dialog during the fight").arg(Str_Royal_Guards));
			break;
		}
		case 435:
		{
			addHintText(QStringLiteral("%1 will comment on this").arg(Str_Alphys));
			break;
		}
		case 445:
		{
			addHintText(QStringLiteral("%1 will comment on this").arg(Str_Alphys));
			break;
		}
		case 446:
		{
			addHintText(QStringLiteral("%1 will comment on this").arg(Str_Alphys));
			break;
		}
		case 447:
		{
			addHintText(QStringLiteral("%1 will interrupt you").arg(Str_Alphys));
			break;
		}
		case 448:
		{
			addHintText(QStringLiteral("%1 will comment on this").arg(Str_Alphys));
			break;
		}
		case 463:
		{
			addHintText(QStringLiteral("Skips the long elevator ride"));
			break;
		}
		case 496:
		{
			addHintText(QStringLiteral("Changes \"%1's Phone\" to \"%1 and %2\"").arg(Str_Papyrus, Str_Undyne));
			break;
		}
		case 510:
		{
			addHintText(QStringLiteral("Starts %1 music").arg(Str_True_Lab));
			break;
		}
		case 511:
		{
			addHintText(QStringLiteral("Adds a shade on the player"));
			break;
		}
		case 516:
		{
			addHintText(QStringLiteral("Turns on some diary panels"));
			break;
		}
		case 530:
		{
			addHintText(QStringLiteral("Skips a portion of the credits"));
			break;
		}
		case 534:
		{
			addHintText(QStringLiteral("Skips the item use text"));
			break;
		}
	}

	connect(editor, &QCheckBox::stateChanged, this, &CustomCheckBox::updateSave);
}

void CustomCheckBox::updateSave(const int data)
{
	const QString saved = QString::number(values.at(data));
	MainWindow::saveData.replace(id, saved);
	CustomEditor::updateSave(saved != MainWindow::originalFile.at(id));
}

void CustomCheckBox::updateData()
{
	QSignalBlocker blocker(editor);

	const int data = MainWindow::saveData.at(id).toInt();
	editor->setCheckState(states.value(data));
	updateStyle(false);
	callback();
}

CustomRadioButton::CustomRadioButton(int id, const QString &text, QWidget *buddyWidget) : CustomEditor(id, &editor, buddyWidget)
{
	editor->setText(text);

	switch (id)
	{
		case 44:
		{
			addHintText(QStringLiteral("Only in %1").arg(Str_Ruins));
			break;
		}
	}

	connect(editor, &QRadioButton::toggled, this, &CustomRadioButton::updateSave);
}

void CustomRadioButton::updateSave(const bool data)
{
	const QString saved = QString::number(data);
	MainWindow::saveData.replace(id, saved);
	CustomEditor::updateSave(saved != MainWindow::originalFile.at(id));
}

void CustomRadioButton::updateData()
{
	QSignalBlocker blocker(editor);

	const bool data = MainWindow::saveData.at(id).toInt();
	editor->setChecked(data);
	updateStyle(false);
	callback();
}

ItemComboBox::ItemComboBox(int id, QWidget *buddyWidget) : CustomEditor(id, &editor, buddyWidget)
{
	editor->addItem(QStringLiteral("None"));
	editor->addItem(QStringLiteral("Monster Candy"));
	editor->addItem(QStringLiteral("Croquet Roll"));
	editor->addItem(QStringLiteral("Stick"));
	editor->addItem(QStringLiteral("Bandage"));
	editor->addItem(QStringLiteral("Rock Candy"));
	editor->addItem(QStringLiteral("Pumpkin Rings"));
	editor->addItem(QStringLiteral("Spider Donut"));
	editor->addItem(QStringLiteral("Stoic Onion"));
	editor->addItem(QStringLiteral("Ghost Fruit"));
	editor->addItem(QStringLiteral("Spider Cider"));
	editor->addItem(QStringLiteral("Butterscotch Pie"));
	editor->addItem(QStringLiteral("Faded Ribbon"));
	editor->addItem(QStringLiteral("Toy Knife"));
	editor->addItem(QStringLiteral("Tough Glove"));
	editor->addItem(QStringLiteral("Manly Bandanna"));
	editor->addItem(QStringLiteral("Snowman Piece"));
	editor->addItem(QStringLiteral("Nice Cream"));
	editor->addItem(QStringLiteral("Puppydough Ice cream"));
	editor->addItem(QStringLiteral("Bisicle"));
	editor->addItem(QStringLiteral("Unisicle"));
	editor->addItem(QStringLiteral("Cinnamon Bunny"));
	editor->addItem(QStringLiteral("Temmie Flakes"));
	editor->addItem(QStringLiteral("Abandoned Quiche"));
	editor->addItem(QStringLiteral("Old Tutu"));
	editor->addItem(QStringLiteral("Ballet Shoes"));
	editor->addItem(QStringLiteral("Punch Card"));
	editor->addItem(QStringLiteral("Annoying Dog"));
	editor->addItem(QStringLiteral("Dog Salad"));
	editor->addItem(QStringLiteral("Dog Residue (1)"));
	editor->addItem(QStringLiteral("Dog Residue (2)"));
	editor->addItem(QStringLiteral("Dog Residue (3)"));
	editor->addItem(QStringLiteral("Dog Residue (4)"));
	editor->addItem(QStringLiteral("Dog Residue (5)"));
	editor->addItem(QStringLiteral("Dog Residue (6)"));
	editor->addItem(QStringLiteral("Astronaut Food"));
	editor->addItem(QStringLiteral("Instant Noodles"));
	editor->addItem(QStringLiteral("Crab Apple"));
	editor->addItem(QStringLiteral("Hot Dog...?"));
	editor->addItem(QStringLiteral("Hot Cat"));
	editor->addItem(QStringLiteral("Glamburger"));
	editor->addItem(QStringLiteral("Sea Tea"));
	editor->addItem(QStringLiteral("Starfait"));
	editor->addItem(QStringLiteral("Legendary Hero"));
	editor->addItem(QStringLiteral("Cloudy Glasses"));
	editor->addItem(QStringLiteral("Torn Notebook"));
	editor->addItem(QStringLiteral("Stained Apron"));
	editor->addItem(QStringLiteral("Burnt Pan"));
	editor->addItem(QStringLiteral("Cowboy Hat"));
	editor->addItem(QStringLiteral("Empty Gun"));
	editor->addItem(QStringLiteral("Heart Locket"));
	editor->addItem(QStringLiteral("Worn Dagger"));
	editor->addItem(QStringLiteral("Real Knife"));
	editor->addItem(QStringLiteral("The Locket"));
	editor->addItem(QStringLiteral("Bad Memory"));
	editor->addItem(QStringLiteral("Dream"));
	editor->addItem(Str_Undyne_Letter);
	editor->addItem(Str_Undyne_Letter_EX);
	editor->addItem(QStringLiteral("Potato Chisps"));
	editor->addItem(QStringLiteral("Junk Food"));
	editor->addItem(QStringLiteral("Mystery Key"));
	editor->addItem(QStringLiteral("Face Steak"));
	editor->addItem(QStringLiteral("Hush Puppy"));
	editor->addItem(QStringLiteral("Snail Pie"));
	editor->addItem(QStringLiteral("temy armor"));

	connect(editor, &QComboBox::currentIndexChanged, this, &ItemComboBox::updateSave);
}

void ItemComboBox::updateSave(const int data)
{
	const QString saved = QString::number(data);
	MainWindow::saveData.replace(id, saved);
	CustomEditor::updateSave(saved != MainWindow::originalFile.at(id));
}

void ItemComboBox::updateData()
{
	QSignalBlocker blocker(editor);

	const int data = MainWindow::saveData.at(id).toInt();
	editor->setCurrentIndex(data);
	updateStyle(false);
	callback();
}

PhoneComboBox::PhoneComboBox(int id, QWidget *buddyWidget) : CustomEditor(id, &editor, buddyWidget)
{
	editor->addItem(QStringLiteral("None"));
	editor->addItem(QStringLiteral("Say Hello"));
	editor->addItem(QStringLiteral("Puzzle Help"));
	editor->addItem(QStringLiteral("About Yourself"));
	editor->addItem(QStringLiteral("Call Her \"Mom\""));
	editor->addItem(QStringLiteral("Flirt"));
	editor->addItem(QStringLiteral("Toriel's Phone"));
	editor->addItem(QStringLiteral("Papyrus's Phone"));
	editor->addItem(QStringLiteral("Dimensional Box A"));
	editor->addItem(QStringLiteral("Dimensional Box B"));

	connect(editor, &QComboBox::currentIndexChanged, this, &PhoneComboBox::updateSave);
}

void PhoneComboBox::updateSave(const int data)
{
	const QString saved = QString::number(indexes.key(data, -1));
	MainWindow::saveData.replace(id, saved);
	CustomEditor::updateSave(saved != MainWindow::originalFile.at(id));
}

void PhoneComboBox::updateData()
{
	QSignalBlocker blocker(editor);

	const int data = indexes.value(MainWindow::saveData.at(id).toInt());
	editor->setCurrentIndex(data);
	updateStyle(false);
	callback();
}

WeaponComboBox::WeaponComboBox(int id, QWidget *buddyWidget, CustomSpinBox *weaponAT) : CustomEditor(id, &editor, buddyWidget), wat(weaponAT)
{
	editor->addItem(QStringLiteral("Stick"));
	editor->addItem(QStringLiteral("Toy Knife"));
	editor->addItem(QStringLiteral("Tough Glove"));
	editor->addItem(QStringLiteral("Ballet Shoes"));
	editor->addItem(QStringLiteral("Torn Notebook"));
	editor->addItem(QStringLiteral("Burnt Pan"));
	editor->addItem(QStringLiteral("Empty Gun"));
	editor->addItem(QStringLiteral("Worn Dagger"));
	editor->addItem(QStringLiteral("Real Knife"));

	connect(editor, &QComboBox::currentIndexChanged, this, &WeaponComboBox::updateSave);
}

void WeaponComboBox::updateSave(const int data)
{
	QSignalBlocker blocker(wat->editor);
	const int other = atValues.at(data);
	wat->editor->setValue(other);
	wat->updateSave(other);

	const QString saved = QString::number(indexes.key(data, -1));
	MainWindow::saveData.replace(id, saved);
	CustomEditor::updateSave(saved != MainWindow::originalFile.at(id));
}

void WeaponComboBox::updateData()
{
	QSignalBlocker blocker(editor);

	const int data = indexes.value(MainWindow::saveData.at(id).toInt());
	editor->setCurrentIndex(data);
	updateStyle(false);
	callback();
}

ArmorComboBox::ArmorComboBox(int id, QWidget *buddyWidget, CustomSpinBox *armorDF) : CustomEditor(id, &editor, buddyWidget), adf(armorDF)
{
	editor->addItem(QStringLiteral("Bandage"));
	editor->addItem(QStringLiteral("Faded Ribbon"));
	editor->addItem(QStringLiteral("Manly Bandanna"));
	editor->addItem(QStringLiteral("Old Tutu"));
	editor->addItem(QStringLiteral("Clouded Glasses"));
	editor->addItem(QStringLiteral("Stained Apron"));
	editor->addItem(QStringLiteral("Cowboy Hat"));
	editor->addItem(QStringLiteral("Heart Locket"));
	editor->addItem(QStringLiteral("The Locket"));
	editor->addItem(QStringLiteral("Temmie Armor"));

	connect(editor, &QComboBox::currentIndexChanged, this, &ArmorComboBox::updateSave);
}

void ArmorComboBox::updateSave(const int data)
{
	QSignalBlocker blocker(adf->editor);
	const int other = dfValues.at(data);
	adf->editor->setValue(other);
	adf->updateSave(other);

	const QString saved = QString::number(indexes.key(data, -1));
	MainWindow::saveData.replace(id, saved);
	CustomEditor::updateSave(saved != MainWindow::originalFile.at(id));
}

void ArmorComboBox::updateData()
{
	QSignalBlocker blocker(editor);

	const int data = indexes.value(MainWindow::saveData.at(id).toInt());
	editor->setCurrentIndex(data);
	updateStyle(false);
	callback();
}

RoomComboBox::RoomComboBox(int id, QWidget *buddyWidget) : CustomEditor(id, &editor, buddyWidget)
{
	editor->addItem(QStringLiteral("Ruins - Entrance"));
	editor->addItem(QStringLiteral("Ruins - Leaf Pile"));
	editor->addItem(QStringLiteral("Ruins - Mouse Hole"));
	editor->addItem(QStringLiteral("Ruins - Home"));
	editor->addItem(QStringLiteral("Snowdin - Box Road"));
	editor->addItem(QStringLiteral("Snowdin - Spaghetti"));
	editor->addItem(QStringLiteral("Snowdin - Dog House"));
	editor->addItem(QStringLiteral("Snowdin - Town"));
	editor->addItem(QStringLiteral("Waterfall - Checkpoint"));
	editor->addItem(QStringLiteral("Waterfall - Hallway"));
	editor->addItem(QStringLiteral("Waterfall - Crystal"));
	editor->addItem(QStringLiteral("Waterfall - Bridge"));
	editor->addItem(QStringLiteral("Waterfall - Trash Zone"));
	editor->addItem(QStringLiteral("Waterfall - Quiet Area"));
	editor->addItem(QStringLiteral("Waterfall - Temmie Village"));
	editor->addItem(QStringLiteral("Waterfall - Undyne Arena"));
	editor->addItem(QStringLiteral("Hotland - Laboratory Entrance"));
	editor->addItem(QStringLiteral("Hotland - Magma Chamber"));
	editor->addItem(QStringLiteral("Hotland - Core View"));
	editor->addItem(QStringLiteral("Hotland - Bad Opinion Zone"));
	editor->addItem(QStringLiteral("Hotland - Spider Entrance"));
	editor->addItem(QStringLiteral("Hotland - Hotel Lobby"));
	editor->addItem(QStringLiteral("Hotland - Core Branch"));
	editor->addItem(QStringLiteral("Hotland - Core End"));
	editor->addItem(QStringLiteral("Castle Elevator"));
	editor->addItem(QStringLiteral("New Home"));
	editor->addItem(QStringLiteral("Last Corridor"));
	editor->addItem(QStringLiteral("Throne Entrance"));
	editor->addItem(QStringLiteral("Throne Room"));
	editor->addItem(QStringLiteral("The End"));
	editor->addItem(QStringLiteral("True Laboratory"));
	editor->addItem(QStringLiteral("True Lab - Bedroom"));
	editor->addItem(QStringLiteral("room_start"));
	editor->addItem(QStringLiteral("room_introstory"));
	editor->addItem(QStringLiteral("room_introimage"));
	editor->addItem(QStringLiteral("room_intromenu"));
	editor->addItem(QStringLiteral("room_area1"));
	editor->addItem(QStringLiteral("room_area1_2"));
	editor->addItem(QStringLiteral("Ruins - 2"));
	editor->addItem(QStringLiteral("Ruins - 3"));
	editor->addItem(QStringLiteral("Ruins - 4"));
	editor->addItem(QStringLiteral("Ruins - 5"));
	editor->addItem(QStringLiteral("Ruins - 6"));
	editor->addItem(QStringLiteral("Ruins - 7A"));
	editor->addItem(QStringLiteral("Ruins - 8"));
	editor->addItem(QStringLiteral("Ruins - 9"));
	editor->addItem(QStringLiteral("Ruins - 10"));
	editor->addItem(QStringLiteral("Ruins - 11"));
	editor->addItem(QStringLiteral("Ruins - 12"));
	editor->addItem(QStringLiteral("Ruins - 12B"));
	editor->addItem(QStringLiteral("Ruins - 13"));
	editor->addItem(QStringLiteral("Ruins - 14"));
	editor->addItem(QStringLiteral("Ruins - 15A"));
	editor->addItem(QStringLiteral("Ruins - 15B"));
	editor->addItem(QStringLiteral("Ruins - 15C"));
	editor->addItem(QStringLiteral("Ruins - 15D"));
	editor->addItem(QStringLiteral("Ruins - 15E"));
	editor->addItem(QStringLiteral("Ruins - 16"));
	editor->addItem(QStringLiteral("Ruins - 17"));
	editor->addItem(QStringLiteral("Ruins - 18OLD"));
	editor->addItem(QStringLiteral("Home - Entrance Hall"));
	editor->addItem(QStringLiteral("Home - Living Room"));
	editor->addItem(QStringLiteral("Home - Hall"));
	editor->addItem(QStringLiteral("Home - Toriel's Room"));
	editor->addItem(QStringLiteral("Home - Asriel's Room"));
	editor->addItem(QStringLiteral("Home - Kitchen"));
	editor->addItem(QStringLiteral("room_basement1"));
	editor->addItem(QStringLiteral("room_basement2"));
	editor->addItem(QStringLiteral("room_basement3"));
	editor->addItem(QStringLiteral("room_basement4"));
	editor->addItem(QStringLiteral("room_basement5"));
	editor->addItem(QStringLiteral("Snowdin - Ruins Exit"));
	editor->addItem(QStringLiteral("Snowdin - 1"));
	editor->addItem(QStringLiteral("Snowdin - 2"));
	editor->addItem(QStringLiteral("Snowdin - 3A"));
	editor->addItem(QStringLiteral("Snowdin - 4"));
	editor->addItem(QStringLiteral("Snowdin - 5"));
	editor->addItem(QStringLiteral("Snowdin - 6"));
	editor->addItem(QStringLiteral("Snowdin - 6A"));
	editor->addItem(QStringLiteral("Snowdin - 7"));
	editor->addItem(QStringLiteral("Snowdin - 8"));
	editor->addItem(QStringLiteral("Snowdin - 8A"));
	editor->addItem(QStringLiteral("Snowdin - 9"));
	editor->addItem(QStringLiteral("Snowdin - Snow Puzzle"));
	editor->addItem(QStringLiteral("Snowdin - XO Puzzle (Small)"));
	editor->addItem(QStringLiteral("Snowdin - XO Puzzle (Papyrus)"));
	editor->addItem(QStringLiteral("Snowdin - Tile Puzzle"));
	editor->addItem(QStringLiteral("Snowdin - icehole"));
	editor->addItem(QStringLiteral("Snowdin - iceentrance"));
	editor->addItem(QStringLiteral("Snowdin - iceexit_new"));
	editor->addItem(QStringLiteral("Snowdin - iceexit"));
	editor->addItem(QStringLiteral("Snowdin - Snow Poff Zone"));
	editor->addItem(QStringLiteral("Snowdin - Dangerous Bridge Puzzle"));
	editor->addItem(QStringLiteral("Snowdin - town2"));
	editor->addItem(QStringLiteral("Snowdin - Dock"));
	editor->addItem(QStringLiteral("Snowdin - Snowed Inn"));
	editor->addItem(QStringLiteral("Snowdin - Snowed Inn (2nd floor)"));
	editor->addItem(QStringLiteral("Snowdin - Grillby's"));
	editor->addItem(QStringLiteral("Snowdin - Library"));
	editor->addItem(QStringLiteral("Snowdin - Garage"));
	editor->addItem(QStringLiteral("Snowdin - Papyrus's and sans's House"));
	editor->addItem(QStringLiteral("Snowdin - Papyrus's Room"));
	editor->addItem(QStringLiteral("Snowdin - sans's Room"));
	editor->addItem(QStringLiteral("Snowdin - sans's Room (Dark)"));
	editor->addItem(QStringLiteral("Snowdin - sans's Basement"));
	editor->addItem(QStringLiteral("Snowdin - Foggy Hallway"));
	editor->addItem(QStringLiteral("Waterfall - 1"));
	editor->addItem(QStringLiteral("Waterfall - 3"));
	editor->addItem(QStringLiteral("Waterfall - 3A"));
	editor->addItem(QStringLiteral("Waterfall - bridgepuzz1"));
	editor->addItem(QStringLiteral("Waterfall - 5"));
	editor->addItem(QStringLiteral("Waterfall - 5A"));
	editor->addItem(QStringLiteral("Waterfall - 6"));
	editor->addItem(QStringLiteral("Waterfall - 7"));
	editor->addItem(QStringLiteral("Waterfall - 8"));
	editor->addItem(QStringLiteral("Waterfall - 9"));
	editor->addItem(QStringLiteral("Waterfall - 11"));
	editor->addItem(QStringLiteral("Waterfall - nicecream"));
	editor->addItem(QStringLiteral("Waterfall - 12"));
	editor->addItem(QStringLiteral("Waterfall - shoe"));
	editor->addItem(QStringLiteral("Waterfall - bird"));
	editor->addItem(QStringLiteral("Waterfall - Onionsan"));
	editor->addItem(QStringLiteral("Waterfall - 14"));
	editor->addItem(QStringLiteral("Waterfall - Piano Puzzle"));
	editor->addItem(QStringLiteral("Waterfall - dogroom"));
	editor->addItem(QStringLiteral("Waterfall - Music Box Statue"));
	editor->addItem(QStringLiteral("Waterfall - prewaterfall"));
	editor->addItem(QStringLiteral("Waterfall - waterfall"));
	editor->addItem(QStringLiteral("Waterfall - waterfall2"));
	editor->addItem(QStringLiteral("Waterfall - waterfall3"));
	editor->addItem(QStringLiteral("Waterfall - waterfall4"));
	editor->addItem(QStringLiteral("Waterfall - undynebridge"));
	editor->addItem(QStringLiteral("Waterfall - undynebridgeend"));
	editor->addItem(QStringLiteral("Waterfall - trashzone1"));
	editor->addItem(QStringLiteral("Waterfall - trashzone2"));
	editor->addItem(QStringLiteral("Waterfall - Undyne's Yard"));
	editor->addItem(QStringLiteral("Waterfall - Undyne's House"));
	editor->addItem(QStringLiteral("Waterfall - Blooky's Yard"));
	editor->addItem(QStringLiteral("Waterfall - Blooky's House"));
	editor->addItem(QStringLiteral("Waterfall - hapstablook"));
	editor->addItem(QStringLiteral("Waterfall - Blook Farm"));
	editor->addItem(QStringLiteral("Waterfall - prebird"));
	editor->addItem(QStringLiteral("Waterfall - Gerson's Shop"));
	editor->addItem(QStringLiteral("Waterfall - Dock"));
	editor->addItem(QStringLiteral("Waterfall - 15"));
	editor->addItem(QStringLiteral("Waterfall - 16"));
	editor->addItem(QStringLiteral("Waterfall - 17"));
	editor->addItem(QStringLiteral("Waterfall - 18"));
	editor->addItem(QStringLiteral("Waterfall - 19"));
	editor->addItem(QStringLiteral("Waterfall - 20"));
	editor->addItem(QStringLiteral("Waterfall - Puzzle Elder"));
	editor->addItem(QStringLiteral("Waterfall - Arena Exit"));
	editor->addItem(QStringLiteral("Waterfall - Hotland Entrance"));
	editor->addItem(QStringLiteral("Hotland - sans's Station"));
	editor->addItem(QStringLiteral("Hotland - Water Cooler"));
	editor->addItem(QStringLiteral("Hotland - Dock"));
	editor->addItem(QStringLiteral("Hotland - lab1"));
	editor->addItem(QStringLiteral("Hotland - lab2"));
	editor->addItem(QStringLiteral("Hotland - 3"));
	editor->addItem(QStringLiteral("Hotland - 5"));
	editor->addItem(QStringLiteral("Hotland - 6A"));
	editor->addItem(QStringLiteral("Hotland - lasers1"));
	editor->addItem(QStringLiteral("Hotland - 7"));
	editor->addItem(QStringLiteral("Hotland - 8"));
	editor->addItem(QStringLiteral("Hotland - shootguy_2"));
	editor->addItem(QStringLiteral("Hotland - 9"));
	editor->addItem(QStringLiteral("Hotland - shootguy_1"));
	editor->addItem(QStringLiteral("Hotland - turn"));
	editor->addItem(QStringLiteral("Hotland - cookingshow"));
	editor->addItem(QStringLiteral("Hotland - elevator_r1"));
	editor->addItem(QStringLiteral("Hotland - elevator_r2"));
	editor->addItem(QStringLiteral("Hotland - hotdog"));
	editor->addItem(QStringLiteral("Hotland - walkandbranch"));
	editor->addItem(QStringLiteral("Hotland - sorry"));
	editor->addItem(QStringLiteral("Hotland - apron"));
	editor->addItem(QStringLiteral("Hotland - 10"));
	editor->addItem(QStringLiteral("Hotland - rpuzzle"));
	editor->addItem(QStringLiteral("Hotland - boysnightout"));
	editor->addItem(QStringLiteral("Hotland - newsreport"));
	editor->addItem(QStringLiteral("Hotland - coreview2"));
	editor->addItem(QStringLiteral("Hotland - elevator_l2"));
	editor->addItem(QStringLiteral("Hotland - elevator_l3"));
	editor->addItem(QStringLiteral("Hotland - spidershop"));
	editor->addItem(QStringLiteral("Hotland - walkandbranch2"));
	editor->addItem(QStringLiteral("Hotland - conveyorlaser"));
	editor->addItem(QStringLiteral("Hotland - shootguy_3"));
	editor->addItem(QStringLiteral("Hotland - preshootguy4"));
	editor->addItem(QStringLiteral("Hotland - shootguy_4"));
	editor->addItem(QStringLiteral("Hotland - Spider's Web"));
	editor->addItem(QStringLiteral("Hotland - pacing"));
	editor->addItem(QStringLiteral("Hotland - operatest"));
	editor->addItem(QStringLiteral("Hotland - Tile Puzzle EX"));
	editor->addItem(QStringLiteral("Hotland - hotelfront_1"));
	editor->addItem(QStringLiteral("Hotland - hotelfront_2"));
	editor->addItem(QStringLiteral("Hotel - Restaurant"));
	editor->addItem(QStringLiteral("Hotland - hoteldoors"));
	editor->addItem(QStringLiteral("Hotland - hotelbed"));
	editor->addItem(QStringLiteral("Hotland - elevator_r3"));
	editor->addItem(QStringLiteral("Hotland - precore"));
	editor->addItem(QStringLiteral("Hotland - core1"));
	editor->addItem(QStringLiteral("Hotland - core2"));
	editor->addItem(QStringLiteral("Hotland - core3"));
	editor->addItem(QStringLiteral("Hotland - core4"));
	editor->addItem(QStringLiteral("Hotland - core5"));
	editor->addItem(QStringLiteral("Hotland - core_freebattle"));
	editor->addItem(QStringLiteral("Hotland - core_laserfun"));
	editor->addItem(QStringLiteral("Hotland - core_bottomleft"));
	editor->addItem(QStringLiteral("Hotland - core_left"));
	editor->addItem(QStringLiteral("Hotland - core_topleft"));
	editor->addItem(QStringLiteral("Hotland - core_top"));
	editor->addItem(QStringLiteral("Hotland - core_topright"));
	editor->addItem(QStringLiteral("Hotland - core_right"));
	editor->addItem(QStringLiteral("Hotland - core_bottomright"));
	editor->addItem(QStringLiteral("Hotland - core_center"));
	editor->addItem(QStringLiteral("Hotland - shootguy_5"));
	editor->addItem(QStringLiteral("Hotland - core_treasureleft"));
	editor->addItem(QStringLiteral("Hotland - core_treasureright"));
	editor->addItem(QStringLiteral("Hotland - core_warrior"));
	editor->addItem(QStringLiteral("Hotland - core_bridge"));
	editor->addItem(QStringLiteral("Hotland - core_metttest"));
	editor->addItem(QStringLiteral("Hotland - core_final"));
	editor->addItem(QStringLiteral("Hotland - elevator"));
	editor->addItem(QStringLiteral("Hotland - elevator_l1"));
	editor->addItem(QStringLiteral("Hotland - finalelevator"));
	editor->addItem(QStringLiteral("room_castle_precastle"));
	editor->addItem(QStringLiteral("room_castle_hook"));
	editor->addItem(QStringLiteral("room_asghouse1"));
	editor->addItem(QStringLiteral("room_asghouse2"));
	editor->addItem(QStringLiteral("room_asghouse3"));
	editor->addItem(QStringLiteral("room_asgoreroom"));
	editor->addItem(QStringLiteral("room_asrielroom_final"));
	editor->addItem(QStringLiteral("room_kitchen_final"));
	editor->addItem(QStringLiteral("room_basement1_final"));
	editor->addItem(QStringLiteral("room_basement2_final"));
	editor->addItem(QStringLiteral("room_basement3_final"));
	editor->addItem(QStringLiteral("room_basement4_final"));
	editor->addItem(QStringLiteral("room_lastruins_corridor"));
	editor->addItem(QStringLiteral("room_castle_coffins1"));
	editor->addItem(QStringLiteral("room_castle_coffins2"));
	editor->addItem(QStringLiteral("room_castle_barrier"));
	editor->addItem(QStringLiteral("room_castle_exit"));
	editor->addItem(QStringLiteral("room_undertale_end"));
	editor->addItem(QStringLiteral("room_castle_trueexit"));
	editor->addItem(QStringLiteral("room_outsideworld"));
	editor->addItem(QStringLiteral("Hotland - labelevator"));
	editor->addItem(QStringLiteral("True Lab - elevatorinside"));
	editor->addItem(QStringLiteral("True Lab - elevator"));
	editor->addItem(QStringLiteral("True Lab - hall1"));
	editor->addItem(QStringLiteral("True Lab - hall2"));
	editor->addItem(QStringLiteral("True Lab - operatingroom"));
	editor->addItem(QStringLiteral("True Lab - Red Lever"));
	editor->addItem(QStringLiteral("True Lab - prebed"));
	editor->addItem(QStringLiteral("True Lab - mirror"));
	editor->addItem(QStringLiteral("True Lab - Blue Lever"));
	editor->addItem(QStringLiteral("True Lab - hall3"));
	editor->addItem(QStringLiteral("True Lab - shower"));
	editor->addItem(QStringLiteral("True Lab - determination"));
	editor->addItem(QStringLiteral("True Lab - tv"));
	editor->addItem(QStringLiteral("True Lab - cooler"));
	editor->addItem(QStringLiteral("True Lab - Green Lever"));
	editor->addItem(QStringLiteral("True Lab - fan"));
	editor->addItem(QStringLiteral("True Lab - castle_elevator"));
	editor->addItem(QStringLiteral("True Lab - prepower"));
	editor->addItem(QStringLiteral("True Lab - power"));
	editor->addItem(QStringLiteral("room_gaster"));
	editor->addItem(QStringLiteral("room_icecave1"));
	editor->addItem(QStringLiteral("room_ice_dog"));
	editor->addItem(QStringLiteral("room2"));
	editor->addItem(QStringLiteral("Waterfall - fakehallway"));
	editor->addItem(QStringLiteral("room_mysteryman"));
	editor->addItem(QStringLiteral("room_soundtest"));
	editor->addItem(QStringLiteral("TESTROOM"));
	editor->addItem(QStringLiteral("Waterfall - redacted"));
	editor->addItem(QStringLiteral("Waterfall - 13"));
	editor->addItem(QStringLiteral("room_overworld"));
	editor->addItem(QStringLiteral("room_overworld3"));
	editor->addItem(QStringLiteral("bullettest"));
	editor->addItem(QStringLiteral("Waterfall - 16A"));
	editor->addItem(QStringLiteral("room_end_castroll"));
	editor->addItem(QStringLiteral("room_end_highway"));
	editor->addItem(QStringLiteral("room_end_beach"));
	editor->addItem(QStringLiteral("room_end_metta"));
	editor->addItem(QStringLiteral("room_end_school"));
	editor->addItem(QStringLiteral("room_end_mtebott"));
	editor->addItem(QStringLiteral("room_creditsdodger"));
	editor->addItem(QStringLiteral("room_end_myroom"));
	editor->addItem(QStringLiteral("room_end_theend"));
	editor->addItem(QStringLiteral("room_spritecheck"));
	editor->addItem(QStringLiteral("room_joyconfig"));
	editor->addItem(QStringLiteral("room_controltest"));
	editor->addItem(QStringLiteral("room_f_start"));
	editor->addItem(QStringLiteral("room_f_intro"));
	editor->addItem(QStringLiteral("room_f_menu"));
	editor->addItem(QStringLiteral("room_f_room"));
	editor->addItem(QStringLiteral("room_floweyx"));
	editor->addItem(QStringLiteral("room_f_phrase"));
	editor->addItem(QStringLiteral("Hotland - 4"));
	editor->addItem(QStringLiteral("Hotland - 10_old"));
	editor->addItem(QStringLiteral("Hotland - 10A_old"));
	editor->addItem(QStringLiteral("Snowdin - placeholder"));
	editor->addItem(QStringLiteral("Ruins - 12B_old"));
	editor->addItem(QStringLiteral("Snowdin - rollsnow"));
	editor->addItem(QStringLiteral("Waterfall - 7_older"));
	editor->addItem(QStringLiteral("room_meetundyne_old"));
	editor->addItem(QStringLiteral("Waterfall - mushroom"));
	editor->addItem(QStringLiteral("room_monsteralign_test"));
	editor->addItem(QStringLiteral("room_battle"));
	editor->addItem(QStringLiteral("room_floweybattle"));
	editor->addItem(QStringLiteral("room_fastbattle"));
	editor->addItem(QStringLiteral("room_storybattle"));
	editor->addItem(QStringLiteral("room_gameover"));
	editor->addItem(QStringLiteral("room_shop1"));
	editor->addItem(QStringLiteral("room_shop2"));
	editor->addItem(QStringLiteral("room_shop3"));
	editor->addItem(QStringLiteral("room_shop4"));
	editor->addItem(QStringLiteral("room_shop5"));
	editor->addItem(QStringLiteral("room_riverman_transition"));
	editor->addItem(QStringLiteral("room_papdate"));
	editor->addItem(QStringLiteral("room_adate"));
	editor->addItem(QStringLiteral("room_flowey_endchoice"));
	editor->addItem(QStringLiteral("room_flowey_regret"));
	editor->addItem(QStringLiteral("room_empty"));
	editor->addItem(QStringLiteral("room_emptywhite"));
	editor->addItem(QStringLiteral("room_emptyblack"));
	editor->addItem(QStringLiteral("room_nothingness"));
	editor->addItem(QStringLiteral("room_undertale"));
	editor->addItem(QStringLiteral("room_of_dog"));
	editor->addItem(QStringLiteral("room_quizholder"));
	editor->addItem(QStringLiteral("room_friendtest"));
	editor->addItem(QStringLiteral("room_bringitinguys"));
	editor->addItem(QStringLiteral("room_asrielappears"));
	editor->addItem(QStringLiteral("room_goodbyeasriel"));
	editor->addItem(QStringLiteral("room_asrielmemory"));
	editor->addItem(QStringLiteral("room_asrieltest"));
	editor->addItem(QStringLiteral("room_afinaltest"));

	addHintText(QStringLiteral("Determines the room where you will spawn.<br />Some rooms are unavailable and will trigger \"Dogcheck\" without a modified game"));

	connect(editor, &QComboBox::currentIndexChanged, this, &RoomComboBox::updateSave);
}

void RoomComboBox::updateSave(const int data)
{
	const QString saved = QString::number(indexes.key(data, -1));
	MainWindow::saveData.replace(id, saved);
	CustomEditor::updateSave(saved != MainWindow::originalFile.at(id));
}

void RoomComboBox::updateData()
{
	QSignalBlocker blocker(editor);

	const int data = indexes.value(MainWindow::saveData.at(id).toInt());
	editor->setCurrentIndex(data);
	updateStyle(false);
	callback();
}

TimeEdit::TimeEdit(int id, QWidget *buddyWidget) : CustomEditor(id, &editor, buddyWidget)
{
	editor->setRange(0, __DBL_MAX__);
	editor->setDecimals(0);

	addHintText(QStringLiteral("00:00:00"));
	callback = [this] () {
		const double data = editor->value();
		const auto h = static_cast<quint64>(data * 0.000009259); // 1800 * 60 = 108000 frames
		const auto m = static_cast<quint8>(static_cast<quint64>(data * 0.000555555) % 60); // 30 * 60 = 1800 frames
		const auto s = static_cast<quint8>(static_cast<quint64>(data * 0.033333333) % 60); // 30 frames
		label->setText(QStringLiteral("Your estimated play time is **%1:%2:%3**.<br />This is calculated from in-game frames").arg(h, 2, 10, QChar('0')).arg(m, 2, 10, QChar('0')).arg(s, 2, 10, QChar('0')));
	};

	connect(editor, &QDoubleSpinBox::valueChanged, this, &TimeEdit::updateSave);
}

void TimeEdit::updateSave(const int)
{
	const QString saved = editor->text();
	MainWindow::saveData.replace(id, saved);
	CustomEditor::updateSave(saved != MainWindow::originalFile.at(id));
}

void TimeEdit::updateData()
{
	QSignalBlocker blocker(editor);

	const double data = MainWindow::saveData.at(id).toDouble();
	editor->setValue(data);
	updateStyle(false);
	callback();
}

PlotEdit::PlotEdit(int id, QWidget *buddyWidget) : CustomEditor(id, &editor, buddyWidget)
{
	editor->addItem(QStringLiteral("New Game"));
	editor->addItem(QStringLiteral("Met %1").arg(Str_Flowey));
	editor->addItem(QStringLiteral("%1 escorted you to the next room").arg(Str_Toriel));
	editor->addItem(QStringLiteral("%1 explained puzzles").arg(Str_Toriel));
	editor->addItem(QStringLiteral("Switch puzzle started"));
	editor->addItem(QStringLiteral("Pulled first switch"));
	editor->addItem(QStringLiteral("Pulled second switch"));
	editor->addItem(QStringLiteral("Practice dummy"));
	editor->addItem(QStringLiteral("Interacted with the dummy"));
	editor->addItem(QStringLiteral("Dummy encounter done"));
	editor->addItem(QStringLiteral("Dangerous puzzle started"));
	editor->addItem(QStringLiteral("Dangerous puzzle ended"));
	editor->addItem(QStringLiteral("Independence test started"));
	editor->addItem(QStringLiteral("Independence test ended"));
	editor->addItem(QStringLiteral("%1 called about leaving the room").arg(Str_Toriel));
	editor->addItem(QStringLiteral("%1 called about pie flavor").arg(Str_Toriel));
	editor->addItem(QStringLiteral("%1 called again").arg(Str_Toriel));
	editor->addItem(QStringLiteral("%1 called about allergies").arg(Str_Toriel));
	editor->addItem(QStringLiteral("Cheered %1").arg(Str_Napstablook));
	editor->addItem(QStringLiteral("%1 encounter done").arg(Str_Napstablook));
	editor->addItem(QStringLiteral("Talked with %1").arg(Str_Napstablook));
	editor->addItem(QStringLiteral("%1 disappeared").arg(Str_Napstablook));
	editor->addItem(QStringLiteral("%1 called about picking up items").arg(Str_Toriel));
	editor->addItem(QStringLiteral("Hit the switch in a pit"));
	editor->addItem(QStringLiteral("Pressed a blue switch"));
	editor->addItem(QStringLiteral("Pressed a red switch"));
	editor->addItem(QStringLiteral("Pressed a green switch"));
	editor->addItem(QStringLiteral("Met %1 again").arg(Str_Toriel));
	editor->addItem(QStringLiteral("%1 told about pie").arg(Str_Toriel));
	editor->addItem(QStringLiteral("%1 showed your room").arg(Str_Toriel));
	editor->addItem(QStringLiteral("Talked with %1").arg(Str_Toriel));
	editor->addItem(QStringLiteral("Talked with %1 more").arg(Str_Toriel));
	editor->addItem(QStringLiteral("Talked with %1 some more").arg(Str_Toriel));
	editor->addItem(QStringLiteral("Listened about snail facts"));
	editor->addItem(QStringLiteral("You asked \"How to exit the %1\"").arg(Str_Ruins));
	editor->addItem(QStringLiteral("%1 has to do something").arg(Str_Toriel));
	editor->addItem(QStringLiteral("%1 went to the basement").arg(Str_Toriel));
	editor->addItem(QStringLiteral("%1 is planning to destroy the exit").arg(Str_Toriel));
	editor->addItem(QStringLiteral("%1 warned about %2").arg(Str_Toriel, Str_Asgore));
	editor->addItem(QStringLiteral("%1 warned you for the last time").arg(Str_Toriel));
	editor->addItem(QStringLiteral("%1 encounter done").arg(Str_Toriel));
	editor->addItem(QStringLiteral("Talked with %1").arg(Str_Flowey));
	editor->addItem(QStringLiteral("Exited %1").arg(Str_Ruins));
	editor->addItem(QStringLiteral("Conveniently-shaped lamp"));
	editor->addItem(QStringLiteral("%1 left the area").arg(Str_sans));
	editor->addItem(QStringLiteral("%1 met the human").arg(Str_Papyrus));
	editor->addItem(QStringLiteral("%1 encounter done").arg(Str_Doggo));
	editor->addItem(QStringLiteral("%1 went to get dog treats").arg(Str_Doggo));
	editor->addItem(QStringLiteral("Solved the electricity maze"));
	editor->addItem(QStringLiteral("\"Solved\" %1's puzzle").arg(Str_sans));
	editor->addItem(QStringLiteral("Found the buried switch"));
	editor->addItem(QStringLiteral("%1 encounter done").arg(Str_Dogamy_and_Dogaressa));
	editor->addItem(QStringLiteral("%1 left the area").arg(Str_Dogamy_and_Dogaressa));
	editor->addItem(QStringLiteral("Solved the first XO puzzle"));
	editor->addItem(QStringLiteral("Reached the second XO puzzle"));
	editor->addItem(QStringLiteral("Solved the second XO puzzle"));
	editor->addItem(QStringLiteral("Skipped the XO puzzles"));
	editor->addItem(QStringLiteral("\"Solved\" the Multicolor Tile Puzzle"));
	editor->addItem(QStringLiteral("%1 encounter done").arg(Str_Greater_Dog));
	editor->addItem(QStringLiteral("%1 left the area").arg(Str_Greater_Dog));
	editor->addItem(QStringLiteral("Solved the third XO puzzle"));
	editor->addItem(QStringLiteral("%1 left the area").arg(Str_Greater_Dog));
	editor->addItem(QStringLiteral("\"Solved\" the final puzzle"));
	editor->addItem(QStringLiteral("%1 encounter done").arg(Str_Papyrus));
	editor->addItem(QStringLiteral("%1 left the area").arg(Str_Papyrus));
	editor->addItem(QStringLiteral("(unused) %1 trigger").arg(Str_Monster_Kid));
	editor->addItem(QStringLiteral("%1 spotted you in the sea-grass").arg(Str_Undyne));
	editor->addItem(QStringLiteral("%1 called about your armor").arg(Str_Papyrus));
	editor->addItem(QStringLiteral("Found the hidden door"));
	editor->addItem(QStringLiteral("(unused) Solved the torch puzzle"));
	editor->addItem(QStringLiteral("%1 grabbed %2 in the sea-grass").arg(Str_Undyne, Str_Monster_Kid));
	editor->addItem(QStringLiteral("Encountered %1").arg(Str_Shyren));
	editor->addItem(QStringLiteral("%1 offered to help climb a ledge").arg(Str_Monster_Kid));
	editor->addItem(QStringLiteral("%1 left the area").arg(Str_Monster_Kid));
	editor->addItem(QStringLiteral("Woke up in the Trash Zone"));
	editor->addItem(QStringLiteral("%1 encounter done").arg(Str_Mad_Dummy));
	editor->addItem(QStringLiteral("%1 went home").arg(Str_Napstablook));
	editor->addItem(QStringLiteral("%1 dragged %2 away").arg(Str_Undyne, Str_Monster_Kid));
	editor->addItem(QStringLiteral("Walked to the end of the Echo Flower path"));
	editor->addItem(QStringLiteral("%1 tripped on a bridge").arg(Str_Monster_Kid));
	editor->addItem(QStringLiteral("%1 confronted you").arg(Str_Undyne));
	editor->addItem(QStringLiteral("%1 encounter done").arg(Str_Undyne));
	editor->addItem(QStringLiteral("%1's game show").arg(Str_Mettaton));
	editor->addItem(QStringLiteral("%1 upgraded your phone").arg(Str_Alphys));
	editor->addItem(QStringLiteral("%1 hung up on you").arg(Str_Alphys));
	editor->addItem(QStringLiteral("%1 called about the lasers").arg(Str_Alphys));
	editor->addItem(QStringLiteral("%1 called about the Shooting Puzzles").arg(Str_Alphys));
	editor->addItem(QStringLiteral("Opened the first large door"));
	editor->addItem(QStringLiteral("%1 called about the puzzles again").arg(Str_Alphys));
	editor->addItem(QStringLiteral("%1 called during %2's cooking show").arg(Str_Alphys, Str_Mettaton));
	editor->addItem(QStringLiteral("%1's cooking show done").arg(Str_Mettaton));
	editor->addItem(QStringLiteral("%1 called about %2").arg(Str_Alphys, Str_Core));
	editor->addItem(QStringLiteral("%1 called about the conveyor puzzle").arg(Str_Alphys));
	editor->addItem(QStringLiteral("%1 tried to help with the timing").arg(Str_Alphys));
	editor->addItem(QStringLiteral("%1 called about going to the bathroom").arg(Str_Alphys));
	editor->addItem(QStringLiteral("%1 encounter done").arg(Str_Royal_Guards));
	editor->addItem(QStringLiteral("Skip %1 puzzles").arg(Str_Hotland));
	editor->addItem(QStringLiteral("MTT News done"));
	editor->addItem(QStringLiteral("%1 called about %2").arg(Str_Alphys, Str_Asgore));
	editor->addItem(QStringLiteral("%1 called about the Shooting Puzzles").arg(Str_Alphys));
	editor->addItem(QStringLiteral("Opened the second large door"));
	editor->addItem(QStringLiteral("%1 encounter done").arg(Str_Muffet));
	editor->addItem(QStringLiteral("%1 opera").arg(Str_Mettaton));
	editor->addItem(QStringLiteral("%1's Multicolor Tile Puzzle done").arg(Str_Mettaton));
	editor->addItem(QStringLiteral("Exited %1").arg(Str_MTT_Resort));
	editor->addItem(QStringLiteral("%1 called at %2 lobby").arg(Str_Alphys, Str_Core));
	editor->addItem(QStringLiteral("Fought the mercenaries"));
	editor->addItem(QStringLiteral("%1 called about the order of lasers").arg(Str_Alphys));
	editor->addItem(QStringLiteral("%1 called after the lasers").arg(Str_Alphys));
	editor->addItem(QStringLiteral("%1 called at the crossroads").arg(Str_Alphys));
	editor->addItem(QStringLiteral("(unused) Laser event"));
	editor->addItem(QStringLiteral("%1 called about how everything is under control").arg(Str_Alphys));
	editor->addItem(QStringLiteral("%1 called at the Core Branch").arg(Str_Alphys));
	editor->addItem(QStringLiteral("%1 encounter done").arg(Str_Mettaton_EX));
	editor->addItem(QStringLiteral("%1 told the truth").arg(Str_Alphys));
	editor->addItem(QStringLiteral("%1 judged you").arg(Str_sans));
	editor->addItem(QStringLiteral("Met %1").arg(Str_Asgore));
	editor->addItem(QStringLiteral("%1 told how tense this is").arg(Str_Asgore));
	editor->addItem(QStringLiteral("%1 entered the barrier room").arg(Str_Asgore));
	editor->addItem(QStringLiteral("True Pacifist"));

	addHintText(QStringLiteral("Approximated events for the plot progression"));

	connect(editor, &QComboBox::currentIndexChanged, this, &PlotEdit::updateSave);
}

void PlotEdit::updateSave(const int data)
{
	const QString saved = QString::number(indexes.key(data, -1));
	MainWindow::saveData.replace(id, saved);
	CustomEditor::updateSave(saved != MainWindow::originalFile.at(id));
}

void PlotEdit::updateData()
{
	QSignalBlocker blocker(editor);

	const int data = indexes.value(MainWindow::saveData.at(id).toInt());
	editor->setCurrentIndex(data);
	updateStyle(false);
	callback();
}

YellowCheckBox::YellowCheckBox(int id, const QString &text, QWidget *buddyWidget) : CustomCheckBox(id, text, buddyWidget)
{
	switch (id) {
		case 67:
		{
			editor->setTristate(true);
			values = { 0, 1, 2 };
			states = { { 0, Qt::Unchecked }, { 1, Qt::PartiallyChecked }, { 2, Qt::Checked } };

			addHintText(QStringLiteral(""));
			callback = [this] () {
				switch (editor->checkState())
				{
					case Qt::Unchecked:
					{
						label->setText(QStringLiteral("Blocking the path in %1").arg(Str_Ruins));
						break;
					}
					case Qt::PartiallyChecked:
					{
						label->setText(QStringLiteral("Moved into a pit in %1").arg(Str_Ruins));
						break;
					}
					case Qt::Checked:
					{
						label->setText(QStringLiteral("Talked to while in a pit"));
						break;
					}
				}
			};
			break;
		}
		case 112:
		{
			values = { 0, 0, 2 };
			states = { { 0, Qt::Unchecked }, { 1, Qt::Unchecked }, { 2, Qt::Checked } };
			break;
		}
	}
}

void YellowCheckBox::updateSave(const int data)
{
	const QString saved = QString::number(values.at(data));
	MainWindow::saveData.replace(id, saved);
	CustomEditor::updateSave(saved != MainWindow::originalFile.at(id));
}

void YellowCheckBox::updateData()
{
	QSignalBlocker blocker(editor);

	const int data = MainWindow::saveData.at(id).toInt();
	editor->setCheckState(states.value(data));
	updateStyle(false);
	callback();
}
