#ifndef SPORTCLUB_H
#define SPORTCLUB_H

#include <iostream>
#include <vector>

using namespace std;

class Club
{
public:
    virtual void showInfo() = 0;
};


class SportClub : public Club
{
    string name;
public:
    SportClub(string _name) { name = _name; }
    void showInfo()
    {
        cout << "sportclub " << name << endl;
    }
};

#endif // SPORTCLUB_H
