#include "src/core/initools.h"

#include "src/core/mainwindow.h"

#include <utility>

// NOLINTNEXTLINE: Have a single static map instead of several copies in widgets
const QHash<QString, int> iniData::idMap = {
    { "BC", 0 },
    { "BH", 1 },
    { "BP", 2 },
    { "BW", 3 },
    { "CH", 4 },
    { "CP", 5 },
    { "Gameover", 6 },
    { "Kills", 7 },
    { "Love", 8 },
    { "Name", 9 },
    { "Room", 10 },
    { "Tale", 11 },
    { "Time", 12 },
    { "Truth", 13 },
    { "Won", 14 },
    { "fun", 15 },
    { "Flowey/AF", 16 },
    { "Flowey/AK", 17 },
    { "Flowey/Alter", 18 },
    { "Flowey/CHANGE", 19 },
    { "Flowey/CK", 20 },
    { "Flowey/EX", 21 },
    { "Flowey/FloweyExplain1", 22 },
    { "Flowey/IK", 23 },
    { "Flowey/K", 24 },
    { "Flowey/Met1", 25 },
    { "Flowey/NK", 26 },
    { "Flowey/SK", 27 },
    { "Flowey/SPECIALK", 28 },
    { "Flowey/alter2", 29 },
    { "Flowey/truename", 30 },
    { "Toriel/Bscotch", 31 },
    { "Toriel/TK", 32 },
    { "Toriel/TS", 33 },
    { "Sans/EndMet", 34 },
    { "Sans/F", 35 },
    { "Sans/Intro", 36 },
    { "Sans/M1", 37 },
    { "Sans/MeetLv", 38 },
    { "Sans/MeetLv1", 39 },
    { "Sans/MeetLv2", 40 },
    { "Sans/MP", 41 },
    { "Sans/Pass", 42 },
    { "Sans/SK", 43 },
    { "Sans/SS", 44 },
    { "Sans/SS2", 45 },
    { "Papyrus/M1", 46 },
    { "Papyrus/PD", 47 },
    { "Papyrus/PK", 48 },
    { "Papyrus/PS", 49 },
    { "Undyne/UD", 50 },
    { "Alphys/AD", 51 },
    { "MTT/EssayNo", 52 },
    { "Mett/O", 53 },
    { "Mettaton/BossMet", 54 },
    { "Asgore/KillYou", 55 },
    { "FFFFF/D", 56 },
    { "FFFFF/E", 57 },
    { "FFFFF/F", 58 },
    { "FFFFF/P", 59 },
    { "EndF/EndF", 60 },
    { "F7/F7", 61 },
    { "reset/reset", 62 },
    { "reset/s_key", 63 }
};

template<typename T>
CustomIniEditor::CustomIniEditor(QString identifier, T *editorWidget, QWidget *buddyWidget) :
    editor(editorWidget), id(std::move(identifier)), buddy(buddyWidget)
{
    editor->setFocusPolicy(Qt::StrongFocus);
    editor->installEventFilter(this);

    auto *hLayout = new QHBoxLayout();
    if (buddy)
    {
        hLayout->addWidget(buddy);
    }
    hLayout->addWidget(editor);
    vLayout->addLayout(hLayout);
    vLayout->setSpacing(0);
    setLayout(vLayout);

    connect(MainWindow::instance, &MainWindow::updateIniWidgets, this, &CustomIniEditor::updateData);
    connect(MainWindow::instance, &MainWindow::toggleDarkMode, this, [this](const bool isDarkMode) -> void {
        const QString fontColor = isDarkMode ? QStringLiteral("white") : QStringLiteral("black");
        const QString hoverColor = isDarkMode ? QStringLiteral("gray") : QStringLiteral("black");
        setStyleSheet(QStringLiteral("CustomIniEditor > QLabel { color: %1; } CustomIniEditor:hover { padding: 4px; border: 1px solid %2; }").arg(fontColor, hoverColor));
    });
    connect(this, &CustomIniEditor::dataChanged, MainWindow::instance, &MainWindow::iniModified);
}

bool CustomIniEditor::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::Wheel && !editor->hasFocus())
    {
        event->ignore();
        return true;
    }

    return QFrame::eventFilter(watched, event);
}

void CustomIniEditor::addHintText(const QString &text)
{
    label = new QLabel(text);
    label->setStyleSheet(QStringLiteral("color: gray; font-size: 8pt;"));
    label->setWordWrap(true);
    label->setTextFormat(Qt::MarkdownText);

    vLayout->addWidget(label);
}

void CustomIniEditor::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        editor->setFocus();
    }
}

void CustomIniEditor::updateSave(const bool hasChanged)
{
    const QString style = hasChanged ? QStringLiteral("font-weight: bold;") : QStringLiteral("font-weight: normal;");
    editor->setStyleSheet(style);
    if (buddy != nullptr)
    {
        buddy->setStyleSheet(style);
    }
    emit dataChanged(hasChanged);
    callback();
}

// NOLINTNEXTLINE: Necessary exception to make the system work
IniCheckBox::IniCheckBox(const QString &editorId, const QString &text, QWidget *buddyWidget) :
    CustomIniEditor(editorId, editor = new QCheckBox(), buddyWidget)
{
    editor->setText(text);

    switch (iniData::idMap.value(editorId))
    {
        case 1: // General/BH
        {
            addHintText(QStringLiteral("Border Hard Mode. Console exclusive stuff"));
            break;
        }
        case 2: // General/BP
        {
            addHintText(QStringLiteral("Border Pacifist. Console exclusive stuff"));
            break;
        }
        case 3: // General/BW
        {
            addHintText(QStringLiteral("Border Won. Console exclusive stuff"));
            break;
        }
        case 4: // General/CH
        {
            addHintText(QStringLiteral("Complete Hard Mode"));
            break;
        }
        case 5: // General/CP
        {
            addHintText(QStringLiteral("Complete Pacifist"));
            break;
        }
        case 11: // General/Tale
        {
            addHintText(QStringLiteral("Heard the Tale of the Fallen Human"));
            break;
        }
        case 13: // General/Truth
        {
            addHintText(QStringLiteral(R"((Never set) Activates "Activity Level A" and "Activity Level B")"));
            break;
        }
        case 16: // Flowey/AF
        {
            addHintText(QStringLiteral("Reached an ending without finishing True Lab"));
            break;
        }
        case 17: // Flowey/AK
        {
            addHintText(QStringLiteral("Reached an ending where only Asgore was killed"));
            break;
        }
        case 18: // Flowey/Alter
        {
            addHintText(QStringLiteral("Set to true if truename, IK or NK is true. Changes Flowey dialog and interactions"));
            break;
        }
        case 20: // Flowey/CK
        {
            addHintText(QStringLiteral("(Never set) (Never used) Is loaded at the final Flowey conversation, but does nothing"));
            break;
        }
        case 22: // Flowey/FloweyExplain1
        {
            addHintText(QStringLiteral("First kill Toriel then reload and spare her (or the reverse). Flowey will explain the power of saving"));
            break;
        }
        case 23: // Flowey/IK
        {
            addHintText(QStringLiteral("Reached an ending where you made at least 1 kill (if NK is false, IK must be also false)"));
            break;
        }
        case 24: // Flowey/K
        {
            addHintText(QStringLiteral("Managed to kill Flowey"));
            break;
        }
        case 26: // Flowey/NK
        {
            addHintText(QStringLiteral("Reached an ending where you made no kills"));
            break;
        }
        case 27: // Flowey/SK
        {
            addHintText(QStringLiteral("Flowey killed Asgore"));
            break;
        }
        case 28: // Flowey/SPECIALK
        {
            addHintText(QStringLiteral(R"(Reached an ending while "truename" is 1)"));
            break;
        }
        case 29: // Flowey/alter2
        case 30: // Flowey/truename
        {
            addHintText(QStringLiteral("Reached the end of Ruins while killing everything (Ruins genocide)"));
            break;
        }
        case 34: // Sans/EndMet
        {
            addHintText(QStringLiteral("Met sans at the judgment hallway"));
            break;
        }
        case 53: // Mett/O
        {
            addHintText(QStringLiteral("Experienced the Mettaton Opera"));
            break;
        }
        case 54: // Mettaton/BossMet
        {
            addHintText(QStringLiteral("Encountered Mettaton. Skips turning Mettaton around"));
            break;
        }
        case 61: // F7/F7
        {
            addHintText(QStringLiteral("Finished the Asriel fight. Changes title menu"));
            break;
        }
        case 62: // reset/reset
        {
            addHintText(QStringLiteral(R"(Set on naming screen after a true reset. Activates "Activity Level A" and "Activity Level B")"));
            break;
        }
        case 63: // reset/s_key
        {
            addHintText(QStringLiteral("Set if you hit 0 names on credits. Opens the mysterious door in a cave near Snowdin"));
            break;
        }
        default:
        {
            addHintText(QStringLiteral("(Fallback entry for the ini editor)"));
            break;
        }
    }

    connect(editor, &QCheckBox::stateChanged, this, &IniCheckBox::updateSave);
}

void IniCheckBox::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        editor->click();
    }
}

void IniCheckBox::updateSave(const int data)
{
    MainWindow::iniData.insert(id, data);
    CustomIniEditor::updateSave(data != MainWindow::originalIni.value(id).toDouble());
}

void IniCheckBox::updateData()
{
    const QSignalBlocker blocker(editor);

    const int data = static_cast<int>(MainWindow::iniData.value(id).toDouble());
    editor->setCheckState(states.value(data));
    callback();
}

// NOLINTNEXTLINE: Necessary exception to make the system work
IniLineEdit::IniLineEdit(const QString &editorId, QWidget *buddyWidget) :
    CustomIniEditor(editorId, editor = new QLineEdit(), buddyWidget)
{
    editor->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    switch (iniData::idMap.value(editorId))
    {
        case 9: // General/Name
        {
            addHintText(QStringLiteral("Your name. Flowey and some menus will reference this"));
            break;
        }
        default:
        {
            addHintText(QStringLiteral("(Fallback entry for the ini editor)"));
            break;
        }
    }

    connect(editor, &QLineEdit::textEdited, this, &IniLineEdit::updateSave);
}

void IniLineEdit::updateSave(const QString &data)
{
    MainWindow::iniData.insert(id, data);
    CustomIniEditor::updateSave(data != MainWindow::originalIni.value(id).toString());
}

void IniLineEdit::updateData()
{
    const QSignalBlocker blocker(editor);

    editor->setText(MainWindow::iniData.value(id).toString());
    callback();
}

// NOLINTNEXTLINE: Necessary exception to make the system work
IniSpinBox::IniSpinBox(const QString &editorId, QWidget *buddyWidget) :
    CustomIniEditor(editorId, editor = new QDoubleSpinBox(), buddyWidget)
{
    editor->setRange(0, std::numeric_limits<double>::max());
    editor->setDecimals(0);

    switch (iniData::idMap.value(editorId))
    {
        case 0: // General/BC
        {
            addHintText(QStringLiteral(R"(For those "Get an item" trophies on PlayStation)"));
            break;
        }
        case 6: // General/Gameover
        {
            addHintText(QStringLiteral("Keeps track of how many Game Overs you have gotten"));
            break;
        }
        case 7: // General/Kills
        {
            addHintText(QStringLiteral("Counts how many kills you have made. Used in some menus"));
            break;
        }
        case 8: // General/Love
        {
            addHintText(QStringLiteral("Your LV. Used in some menus"));
            break;
        }
        case 10: // General/Room
        {
            addHintText(QStringLiteral("The identifier of last room you saved in"));
            break;
        }
        case 12: // General/Time
        {
            addHintText(QStringLiteral("Play time counted using in-game frames"));
            break;
        }
        case 14: // General/Won
        {
            addHintText(QStringLiteral("Counts how many times you reached an ending"));
            break;
        }
        case 15: // General/fun
        {
            addHintText(QStringLiteral(R"(Randomly generated number at the start of the game that determines random events. This value is used in tandem with the "fun" in the save file)"));
            break;
        }
        case 19: // Flowey/CHANGE
        {
            addHintText(QStringLiteral("Changes based on if you did or didn't kill on the previous run and did the opposite this run. Can happen twice"));
            break;
        }
        case 21: // Flowey/EX
        {
            addHintText(QStringLiteral("Conversation with Flowey at the end which is unlocked by reaching an ending where you killed at least once, but spared Asgore, didn't complete any dates, and IK or NK is 1"));
            break;
        }
        case 25: // Flowey/Met1
        {
            addHintText(QStringLiteral("Counts how many times you have encountered Flowey for the first time"));
            break;
        }
        case 31: // Toriel/Bscotch
        {
            addHintText(QStringLiteral("Chosen flavor of pie. Toriel will remember this during the phone call. 1 = Butterscotch. 2 = Cinnamon"));
            break;
        }
        case 32: // Toriel/TK
        {
            addHintText(QStringLiteral("Counts how many times you have killed Toriel"));
            break;
        }
        case 33: // Toriel/TS
        {
            addHintText(QStringLiteral("Counts how many times you have spared Toriel"));
            break;
        }
        case 35: // Sans/F
        {
            addHintText(QStringLiteral("Counts how many times you have fought sans"));
            break;
        }
        case 36: // Sans/Intro
        {
            addHintText(QStringLiteral("Counts how many times you have seen sans's fight intro. It keeps changing based on this number"));
            break;
        }
        case 37: // Sans/M1
        {
            addHintText(QStringLiteral("Counts how many times you have met sans for the first time"));
            break;
        }
        case 38: // Sans/MeetLv
        {
            addHintText(QStringLiteral("Counts how many times you have met sans in the judgment hallway while having more than 2 LV"));
            break;
        }
        case 39: // Sans/MeetLv1
        {
            addHintText(QStringLiteral("Counts how many times you have met sans in the judgment hallway while having 1 LV"));
            break;
        }
        case 40: // Sans/MeetLv2
        {
            addHintText(QStringLiteral("Counts how many times you have met sans in the judgment hallway while having 2 LV"));
            break;
        }
        case 41: // Sans/MP
        {
            addHintText(QStringLiteral("(Never used) Counts how many times you have been offered to spare sans"));
            break;
        }
        case 42: // Sans/Pass
        {
            addHintText(QStringLiteral("Secret codeword counter. You'll hear the first codeword in the judgment hallway, if MeetLv1 is more than 0"));
            break;
        }
        case 43: // Sans/SK
        {
            addHintText(QStringLiteral("Counts how many times you have killed sans"));
            break;
        }
        case 44: // Sans/SS
        {
            addHintText(QStringLiteral("Counts how many times you have spared sans"));
            break;
        }
        case 45: // Sans/SS2
        {
            addHintText(QStringLiteral("Counts how many times you have spared sans again after the first attempt"));
            break;
        }
        case 46: // Papyrus/M1
        {
            addHintText(QStringLiteral("Counts how many times you have met Papyrus for the first time"));
            break;
        }
        case 47: // Papyrus/PD
        {
            addHintText(QStringLiteral("Counts how many dates you have completed with Papyrus. Changes title menu"));
            break;
        }
        case 48: // Papyrus/PK
        {
            addHintText(QStringLiteral("Counts how many times you have killed Papyrus"));
            break;
        }
        case 49: // Papyrus/PS
        {
            addHintText(QStringLiteral("Counts how many times you have spared Papyrus"));
            break;
        }
        case 50: // Undyne/UD
        {
            addHintText(QStringLiteral("Counts how many dates you have completed with Undyne. Changes title menu"));
            break;
        }
        case 51: // Alphys/AD
        {
            addHintText(QStringLiteral("Counts how many dates you have completed with Alphys. Changes title menu"));
            break;
        }
        case 52: // MTT/EssayNo
        {
            addHintText(QStringLiteral("Counts how many essays you have written about Mettaton"));
            break;
        }
        case 55: // Asgore/KillYou
        {
            addHintText(QStringLiteral("Counts how many times you have died at the Asgore fight. Changes some of the fight dialog"));
            break;
        }
        case 56: // FFFFF/D
        {
            addHintText(QStringLiteral("Counts how many times you have died at the Omega Flowey fight. Changes the dialog when restarting the game"));
            break;
        }
        case 57: // FFFFF/E
        {
            addHintText(QStringLiteral("Sets to 0 after the short credits, 1 after the Omega Flowey fight, and 2 after killing Flowey"));
            break;
        }
        case 58: // FFFFF/F
        {
            addHintText(QStringLiteral("Sets to 0 after the short credits and 1 after the Omega Flowey fight"));
            break;
        }
        case 59: // FFFFF/P
        {
            addHintText(QStringLiteral("Sets to 1 after starting the Omega Flowey fight.<br />2 after the knife part.<br />3 after the glove part.<br />4 after the shoe part.<br />5 after the book part.<br />6 after the pan part.<br />7 after the gun part"));
            break;
        }
        case 60: // EndF/EndF
        {
            addHintText(QStringLiteral("Sets to 1 after reaching the True Pacifist ending and 2 after Flowey talks about resetting"));
            break;
        }
        default:
        {
            addHintText(QStringLiteral("(Fallback entry for the ini editor)"));
            break;
        }
    }

    connect(editor, &QDoubleSpinBox::valueChanged, this, &IniSpinBox::updateSave);
}

void IniSpinBox::updateSave(const double data)
{
    MainWindow::iniData.insert(id, data);
    CustomIniEditor::updateSave(data != MainWindow::originalIni.value(id).toDouble());
}

void IniSpinBox::updateData()
{
    const QSignalBlocker blocker(editor);

    editor->setValue(MainWindow::iniData.value(id).toDouble());
    callback();
}
