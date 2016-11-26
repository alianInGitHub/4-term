#ifndef NPC_H
#define NPC_H

#include <iostream>
#include <vector>
using namespace std;

class NPC
{
    void teachToWalk()
    {
        for(unsigned i = 0; i < abilities.size(); i++)
            if(abilities[i] == WALK)
                return;
        abilities.push_back(WALK);
    }
    void teachToFly()
    {
        for(unsigned i = 0; i < abilities.size(); i++)
            if(abilities[i] == FLY)
                return;
        abilities.push_back(FLY);
        abilities.push_back(MAGIC);
    }

    void teachMagic()
    {
        for(unsigned i = 0; i < abilities.size(); i++)
            if(abilities[i] == MAGIC)
                return;
        abilities.push_back(MAGIC);
    }
public:
    enum ABILITY {NOTHING, WALK, FLY, MAGIC};
    NPC(bool walk = false, bool fly = false, bool magic = false)
    {
        if(walk)
            teachToWalk();
        if(fly)
            teachToFly();
        if(magic)
            teachMagic();
    }

    virtual void showInfo()
    {
        if(abilities.empty())
            cout << "nothing" << endl;
        else
        {
            for(unsigned i = 0; i <  abilities.size(); i++)
            {
                if(i > 0)
                    cout << ", ";
                switch (abilities[i]) {
                case WALK:
                    cout << "walk";
                    break;
                case FLY:
                    cout << "fly, use magic";
                    i++;
                    break;
                case MAGIC:
                    cout << "use magic";
                    break;
                default:
                    break;
                };
            }
            cout << endl;
        }
    }
private:
    vector<ABILITY> abilities;
};

class Elf : public NPC
{
public:
    Elf(bool walk = 0, bool fly = 0, bool magic = 0) : NPC(walk, fly, magic) {}
    void showInfo()
    {
        cout << "Elf can ";
        NPC::showInfo();
    }
};

class Ork : public NPC
{
public:
    Ork(bool walk = 0, bool fly = 0, bool magic = 0) : NPC(walk, fly, magic) {}
    void showInfo()
    {
        cout << "Ork can ";
        NPC::showInfo();
    }
};

class Wizard : public NPC
{
public:
    Wizard(bool walk = 0, bool fly = 0, bool magic = 0) : NPC(walk, fly, magic) {}
    void showInfo()
    {
        cout << "Wizard can ";
        NPC::showInfo();
    }
};

class Troll : public NPC
{
public:
    Troll(bool walk = 0, bool fly = 0, bool magic = 0) : NPC(walk, fly, magic) {}
    void showInfo()
    {
        cout << "Troll can ";
        NPC::showInfo();
    }
};

class Pegass : public NPC
{
public:
    Pegass(bool walk = 0, bool fly = 0, bool magic = 0) : NPC(walk, fly, magic) {}
    void showInfo()
    {
        cout << "Pegass can ";
        NPC::showInfo();
    }
};

class Vampire : public NPC
{
public:
    Vampire(bool walk = 0, bool fly = 0, bool magic = 0) : NPC(walk, fly, magic) {}
    void showInfo()
    {
        cout << "Vampire can ";
        NPC::showInfo();
    }
};

#endif // NPC_H
