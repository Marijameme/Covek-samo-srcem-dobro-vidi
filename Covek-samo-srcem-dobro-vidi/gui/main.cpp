#include "mainwindow.h"

#include <cstring>

#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // --selftest: construct the window, pump one event-loop pass, exit 0.
    // Used by tests/verify.sh to check the GUI links and starts without a display.
    const bool selftest = argc > 1 && std::strcmp(argv[1], "--selftest") == 0;

    MainWindow window;
    window.show();

    if (selftest)
    {
        QTimer::singleShot(0, &app, []() {
            qInfo("selftest: MainWindow constructed OK");
            QCoreApplication::quit();
        });
    }

    return app.exec();
}
