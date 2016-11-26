#include <QCoreApplication>
#include "Decorator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Club* BoxClub = new Decorator(new Box(new SportClub("Fight Life")));
    BoxClub->showInfo();
    Club* SwimmingClub = new Decorator(new Swimming(new SportClub("Water World")));
    SwimmingClub->showInfo();
    return a.exec();
}
