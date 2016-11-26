#ifndef DECORATOR_H
#define DECORATOR_H

#include "SportClub.h"
#include <vector>

class Decorator : public Club
{
    Club* myClub;
public:
    Decorator(Club* s) { myClub = s; }
    void showInfo() { myClub->showInfo(); }
};

class Box : public Decorator
{
public:
    Box(Club* s) :Decorator(s) {}
    void showInfo()
    {
        cout << "Box ";
        Decorator::showInfo();
    }
};

class Thekwando : public Decorator
{
public:
    Thekwando(Club* s) :Decorator(s) {}
    void showInfo()
    {
        cout << "Thekwando ";
        Decorator::showInfo();
    }
};

class Swimming : public Decorator
{
public:
    Swimming(Club* s) :Decorator(s) {}
    void showInfo()
    {
        cout << "Swimming ";
        Decorator::showInfo();
    }
};

class BallroomDance : public Decorator
{
public:
    BallroomDance(Club* s) :Decorator(s) {}
    void showInfo()
    {
        cout << "Ballroom dance ";
        Decorator::showInfo();
    }
};

class Pilatess : public Decorator
{
public:
    Pilatess(Club* s) :Decorator(s) { }
    void showInfo()
    {
        cout << "Pilatess ";
        Decorator::showInfo();
    }
};


#endif // DECORATOR_H
