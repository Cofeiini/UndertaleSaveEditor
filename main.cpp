#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setOrganizationName("Cofeiini");
	a.setApplicationName(QString("Undertale Save Editor"));
	a.setApplicationVersion(APP_VERSION);
#if defined(Q_OS_LINUX)
	a.setWindowIcon(QIcon(":/images/icon.png"));
#endif

	int fontId = QFontDatabase::addApplicationFont(":/fonts/Vegur-Regular.otf");
    if(fontId != -1)
    {
		QFont font = QFont("Vegur-Regular");
		font.setPixelSize(13);
		a.setFont(font);
	}

    MainWindow w;
	w.show();

	return a.exec();
}
