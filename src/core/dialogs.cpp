#include <QApplication>
#include <QBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>

#include "src/core/mainwindow.h"
#include "src/core/dialogs.h"
#include "src/core/tools.h"
#include "src/helpers.h"

AboutDialog::AboutDialog(QWidget *parent, Qt::WindowFlags flags) : QDialog(parent, flags)
{
	setModal(true);
	setMinimumSize(QSize(410, 240));
	setWindowTitle(QStringLiteral("About %1").arg(QApplication::applicationName()));

	auto *aboutAppLabel = new QLabel(QStringLiteral("### %1 (%2)").arg(QApplication::applicationName(), QApplication::applicationVersion()));
	aboutAppLabel->setTextFormat(Qt::MarkdownText);
	aboutAppLabel->setAlignment(Qt::AlignHCenter);

	auto *aboutProjectLabel = new QLabel(QStringLiteral("The project can be found here:  \n<%1>").arg(GitHub_Url));
	aboutProjectLabel->setTextFormat(Qt::MarkdownText);

	auto *aboutThanksLabel = new QLabel(QStringLiteral("__Special Thanks__"));
	aboutThanksLabel->setTextFormat(Qt::MarkdownText);
	aboutThanksLabel->setAlignment(Qt::AlignHCenter);
	auto *aboutThanksNames = new QLabel(GetCredits());
	aboutThanksNames->setTextFormat(Qt::MarkdownText);
	aboutThanksNames->setAlignment(Qt::AlignHCenter);
	auto *aboutThanksArea = new QScrollArea();
	aboutThanksArea->setAlignment(Qt::AlignHCenter);
	aboutThanksArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	aboutThanksArea->setWidget(aboutThanksNames);

	auto *aboutMadeByLabel = new QLabel(QStringLiteral("Made by **%1**").arg(Project_Author));
	aboutMadeByLabel->setTextFormat(Qt::MarkdownText);

	auto *closeButton = new QPushButton(QStringLiteral("Close"));
	connect(closeButton, &QPushButton::clicked, this, &QDialog::close);

	auto *bottomLayout = new QHBoxLayout;
	bottomLayout->addWidget(aboutMadeByLabel);
	bottomLayout->addStretch();
	bottomLayout->addWidget(closeButton);

	auto *aboutLayout = new QVBoxLayout();
	aboutLayout->addWidget(aboutAppLabel);
	aboutLayout->addWidget(aboutProjectLabel);
	aboutLayout->addWidget(aboutThanksLabel);
	aboutLayout->addWidget(aboutThanksArea);
	aboutLayout->addLayout(bottomLayout);

	setLayout(aboutLayout);
}

auto AboutDialog::GetCredits() -> QString
{
	QStringList names = Project_Credits.split(',');
	for (QString &n : names)
	{
		n = QStringLiteral("**%1**").arg(n); // Just for making the entry bold
	}

	return names.join(QStringLiteral("  \n"));
}

YellowNamesDialog::YellowNamesDialog(QWidget *parent, Qt::WindowFlags flags) : QDialog(parent, flags)
{
	setModal(true);
	setWindowTitle(QStringLiteral("Yellow monster names for the credits"));
	setMinimumWidth(420);

	auto *checkAllButton = new QPushButton(QStringLiteral("Check All"));
	auto *uncheckAllButton = new QPushButton(QStringLiteral("Uncheck All"));
	auto *applyButton = new QPushButton(QStringLiteral("Apply"));
	auto *cancelButton = new QPushButton(QStringLiteral("Cancel"));

	auto *topLayout = new QHBoxLayout();
	topLayout->addWidget(checkAllButton);
	topLayout->addWidget(uncheckAllButton);
	topLayout->addStretch();

	// Turning the list into a shared pointer will allow it to be referenced inside other functions and clean it up after the dialog is destroyed
	std::shared_ptr<QList<CustomCheckBox *>> widgetList = std::make_shared<QList<CustomCheckBox *>>(QList<CustomCheckBox *> {
		new CustomCheckBox(161, Str_Froggit),
		new CustomCheckBox(162, Str_Whimsun),
		new CustomCheckBox(163, Str_Moldsmal),
		new CustomCheckBox(164, Str_Loox),
		new CustomCheckBox(165, Str_Vegetoid),
		new CustomCheckBox(166, Str_Migosp),
		new CustomCheckBox(67, Str_Napstablook),
		new CustomCheckBox(167, Str_Snowdrake),
		new CustomCheckBox(168, Str_Ice_Cap),
		new CustomCheckBox(169, Str_Gyftrot),
		new CustomCheckBox(170, Str_Doggo),
		new CustomCheckBox(171, Str_Dogamy_and_Dogaressa),
		new CustomCheckBox(172, Str_Lesser_Dog),
		new CustomCheckBox(173, Str_Greater_Dog),
		new CustomCheckBox(126, Str_Aaron_and_Woshua),
		new CustomCheckBox(175, Str_Moldbygg),
		new CustomCheckBox(176, Str_Woshua),
		new CustomCheckBox(177, Str_Temmie),
		new CustomCheckBox(178, Str_Mad_Dummy),
		new CustomCheckBox(112, Str_Shyren),
		new CustomCheckBox(179, Str_Vulkin),
		new CustomCheckBox(180, Str_Tsunderplane),
		new CustomCheckBox(181, Str_Pyrope),
		new CustomCheckBox(182, Str_Final_Froggit),
		new CustomCheckBox(183, Str_Whimsalot),
		new CustomCheckBox(184, Str_Astigmatism),
		new CustomCheckBox(185, Str_Madjick),
		new CustomCheckBox(186, Str_Knight_Knight),
		new CustomCheckBox(187, Str_Amalgamates)
	});

	auto *scrollLayout = new QVBoxLayout();
	for (CustomCheckBox *item : *widgetList)
	{
		item->updateData();
		scrollLayout->addWidget(item);
	}

	auto *scrollWindow = new QWidget();
	scrollWindow->setLayout(scrollLayout);

	auto *scrollArea = new QScrollArea();
	scrollArea->setWidget(scrollWindow);

	auto *bottomLayout = new QHBoxLayout();
	bottomLayout->addStretch();
	bottomLayout->addWidget(applyButton);
	bottomLayout->addWidget(cancelButton);

	auto *layout = new QVBoxLayout();
	layout->addLayout(topLayout);
	layout->addWidget(scrollArea);
	layout->addLayout(bottomLayout);

	connect(checkAllButton, &QPushButton::clicked, this, [widgetList] () -> void {
		for (CustomCheckBox *w : *widgetList)
		{
			w->editor->setChecked(true);
		}
	});
	connect(uncheckAllButton, &QPushButton::clicked, this, [widgetList] () -> void {
		for (CustomCheckBox *w : *widgetList)
		{
			w->editor->setChecked(false);
		}
	});
	connect(applyButton, &QPushButton::clicked, this, [this] () -> void {
		isQuit = false; // Important to flip this to keep the changes
		close();
	});
	connect(cancelButton, &QPushButton::clicked, this, &QDialog::close); // Destroy event will handle the cleanup
	connect(this, &QDialog::destroyed, this, [this, widgetList] () -> void {
		if (!isQuit)
		{
			return;
		}

		for (CustomCheckBox *w : *widgetList)
		{
			MainWindow::saveData.replace(w->id, MainWindow::originalFile.at(w->id));
		}
	});

	setLayout(layout);
}
