#include "mainwindow.h"
#include <QApplication>
#include "Commander.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    ICommand* createcommand = new Create();
    ICommand* drawCommand = new Draw(new Player, new Player);
    createcommand->execute();
    //drawCommand->execute();
    return a.exec();
}
