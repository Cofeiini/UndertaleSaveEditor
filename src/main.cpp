#include "src/core/mainwindow.h"
#include "src/helpers.h"

#include <QApplication>
#include <QFontDatabase>
#include <QStyleFactory>

auto main(int argc, char *argv[]) -> int
{
    const QApplication application(argc, argv);

    QApplication::setOrganizationName(Project_Author);
    QApplication::setApplicationName(QStringLiteral("Undertale Save Editor"));
    QApplication::setApplicationVersion(APP_VERSION);
    QApplication::setWindowIcon(QIcon(QStringLiteral(":/icon")));
    QApplication::setStyle(QStyleFactory::create("Fusion")); // Force "Fusion" theme to apply the dark palette properly

    const int fontId = QFontDatabase::addApplicationFont(QStringLiteral(":/common-font"));
    if (fontId > -1)
    {
        QFont font = QFont(QFontDatabase::applicationFontFamilies(fontId).at(0));
        font.setPixelSize(12);
        QApplication::setFont(font);
    }

    MainWindow window;
    window.show();

    return application.exec(); // NOLINT: False positive
}
