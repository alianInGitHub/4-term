#ifndef FACTORY_H
#define FACTORY_H
#include "configurations.h"

class Factory
{
public:
    virtual Language* chooseLanguage() = 0;
    virtual Subtitles* chooseSubtitles() = 0;
};

class EngFactory : public Factory
{
public:
    Language* chooseLanguage()
    {
        Language* result = new EngLanguage;
        return result;
    }
    Subtitles* chooseSubtitles()
    {
        Subtitles* result = new EngSubtitles;
        return result;
    }
};

class RusFactory : public Factory
{
public:
    Language* chooseLanguage()
    {
        Language* result = new RusLanguage;
        return result;
    }
    Subtitles* chooseSubtitles()
    {
        Subtitles* result = new RusSubtitles;
        return result;
    }
};

class UkrFactory : public Factory
{
public:
    Language* chooseLanguage()
    {
        Language* result = new UkrLanguage;
        return result;
    }
    Subtitles* chooseSubtitles()
    {
        Subtitles* result = new UkrSubtitles;
        return result;
    }
};
#endif // FACTORY_H
