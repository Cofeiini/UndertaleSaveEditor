#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication mApp(argc, argv);
	mApp.setOrganizationName("Cofeiini");
	mApp.setApplicationName("Undertale Save Editor");
	mApp.setApplicationVersion("0.4");
	mApp.setWheelScrollLines(1);
	MainWindow mWindow;
	mWindow.show();

	return mApp.exec();
}
