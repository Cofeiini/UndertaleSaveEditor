#include <QApplication>
#include <QFontDatabase>
#include <QStyleFactory>

#include "src/core/mainwindow.h"
#include "src/helpers.h"

auto main(int argc, char *argv[]) -> int
{
	QApplication a(argc, argv);
	a.setOrganizationName(Project_Author);
	a.setApplicationName(QStringLiteral("Undertale Save Editor"));
	a.setApplicationVersion(APP_VERSION);
	a.setWindowIcon(QIcon(QStringLiteral(":/icon")));
	a.setStyle(QStyleFactory::create("Fusion")); // Force "Fusion" theme to apply the dark palette properly

	const int fontId = QFontDatabase::addApplicationFont(QStringLiteral(":/common-font"));
	if(fontId > -1)
	{
		QFont font = QFont(QFontDatabase::applicationFontFamilies(fontId).at(0));
		font.setPixelSize(12);
		a.setFont(font);
	}

    MainWindow w;
	w.show();

	return a.exec();
}
