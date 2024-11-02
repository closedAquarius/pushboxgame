#include "start.h"

#include <QApplication>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Start w;
    w.show();
    return a.exec();
}
