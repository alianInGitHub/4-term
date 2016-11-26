#include "mainwindow.h"
#include <QApplication>
#include "rbtree.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(w.width(),w.height());
    w.show();
    return a.exec();
}
