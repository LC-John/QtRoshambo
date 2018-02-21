#include "mainwindow.h"
#include "roshambo.h"
#include <QApplication>
#include <QDesktopWidget>
#include <cstdlib>
#include <cstdio>
#include <ctime>

int main(int argc, char *argv[])
{
    srand(time(0));

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowFlags(Qt::WindowCloseButtonHint);
    w.show();
    w.move ((QApplication::desktop()->width() - w.width())/2,
            (QApplication::desktop()->height() - w.height())/2);

    return a.exec();
}
