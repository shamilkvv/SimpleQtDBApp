#include <QApplication>
#include "gui.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DbGui gui;
    gui.show();

    return app.exec();
}
