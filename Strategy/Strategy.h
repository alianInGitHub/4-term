#ifndef STRATEGY_H
#define STRATEGY_H

#include "NPC.h"

class Strategy
{
public:
    Strategy(void){}
    virtual void use() = 0;
};

class Strategy1 : public Strategy
{
    vector<NPC*> npc;
public:
    Strategy1(void)
    {
        NPC* gamer = new Elf(true, true);
        npc.push_back(gamer);
        gamer = new Ork(true);
        npc.push_back(gamer);
        gamer= new Vampire(false, true);
        npc.push_back(gamer);
    }
    void use()
    {
        cout << "   Strategy 1 :" << endl;
        for(unsigned i = 0; i < npc.size(); i++)
        {
            npc[i]->showInfo();
        }
        cout << endl;
    }
};

class Strategy2 : public Strategy
{
    vector<NPC*> npc;
public:
    Strategy2(void)
    {
        NPC* gamer = new Elf(true, true);
        npc.push_back(gamer);
        gamer = new Ork(true);
        npc.push_back(gamer);
        gamer= new Pegass(true, true);
        npc.push_back(gamer);
        gamer = new Wizard(true, false, true);
        npc.push_back(gamer);
        gamer = new Troll(true);
        npc.push_back(gamer);
    }
    void use()
    {
        cout << "   Strategy 2 :" << endl;
        for(unsigned i = 0; i < npc.size(); i++)
        {
            npc[i]->showInfo();
        }
        cout << endl;
    }
};

class Contex
{
public:
    virtual void useStrategy() = 0;
    virtual void setStrategy(Strategy* s) = 0;
};

class Client : public Contex
{
    Strategy* myStr = nullptr;
public:
    void setStrategy(Strategy* s)
    {
        myStr = s;
    }
    void useStrategy()
    {
        myStr->use();
    }

};

#endif // STRATEGY_H
