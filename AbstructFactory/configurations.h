#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <iostream>

using namespace std;

class Config
{
protected:
    enum TYPE {LANLUAGE, SUBTITLES};
    enum MOVIE_LANGUAGE {ENGLISH, RUSSIAN, UKRAINIAN};

public:
    virtual void showType() = 0;
};

class Language : public Config
{
public:
    virtual void showType() = 0;
};

class EngLanguage : public Language
{
public :
    void showType()
    {
        cout << "English voice" << endl;
    }
};

class RusLanguage : public Language
{
public :
    void showType()
    {
        cout << "Russian voice" << endl;
    }
};

class UkrLanguage : public Language
{
public :
    void showType()
    {
        cout << "Ukrainian voice" << endl;
    }
};

class Subtitles : public Config
{
public:
    virtual void showType() = 0;
};

class EngSubtitles : public Subtitles
{
public:
    void showType()
    {
        cout << "English subtitles" << endl;
    }
};

class RusSubtitles : public Subtitles
{
public:
    void showType()
    {
        cout << "Russian subtitles" << endl;
    }
};

class UkrSubtitles : public Subtitles
{
public:
    void showType()
    {
        cout << "Ukrainian subtitles" << endl;
    }
};

#endif // CONFIGURATIONS_H
