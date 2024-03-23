#include "View/MainWindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <TinyHsFFI.h>

int main(int argc, char *argv[])
{
    // First, we initialise the Haskell runtime.
    hs_init(&argc, &argv);

    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "qt-test_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();

    int exitCode = a.exec();

    // We finally shut down the Haskell runtime.
    hs_exit();
    return exitCode;
}
