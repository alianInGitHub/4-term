#include <QCoreApplication>
#include "Strategy.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Contex* client = new Client;
    client->setStrategy(new Strategy1);
    client->useStrategy();

    client->setStrategy(new Strategy2);
    client->useStrategy();
    return a.exec();
}
