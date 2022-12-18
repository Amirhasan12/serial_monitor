#include "serial_monitor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("F:\\Practice\\QT\\C++\\gui\\prj3\\Serial_Monitor\\logo.png"));
    app.setApplicationDisplayName("Serial Monitor");
    app.setApplicationVersion("1.0");
    Serial_Monitor main_window;
    main_window.show();
    return app.exec();
}
