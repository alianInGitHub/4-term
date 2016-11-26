#include <QCoreApplication>
#include "movie.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MovieFactory factory;
    factory.chooseMovie(MovieFactory::ENGLISH);
    factory.getProduct().showInfo();
    cout <<endl << "Changing..." << endl << endl;
    factory.chooseMovie(MovieFactory::UKRAINIAN);
    factory.getProduct().showInfo();
    return a.exec();
}
