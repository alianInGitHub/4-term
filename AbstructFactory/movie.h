#ifndef MOVIE_H
#define MOVIE_H

#include "factory.h"

class MovieFactory;

class Movie
{
    friend class MovieFactory;
    Language* voice;
    Subtitles* subs;
public:
    Movie(Language* _voice, Subtitles* _subs)
    {
        voice = _voice;
        subs =_subs;
    }

    void showInfo()
    {
        voice->showType();
        subs->showType();
    }
};

class MovieFactory
{
    Movie* product = nullptr;
public:
    enum MOVIE_LANGUAGE {ENGLISH, RUSSIAN, UKRAINIAN};
    void chooseMovie(MOVIE_LANGUAGE language)
    {
        Factory* creator = nullptr;
        switch (language) {
        case ENGLISH:
            creator = new EngFactory;
            break;
        case RUSSIAN:
            creator = new RusFactory;
            break;
        case UKRAINIAN:
            creator = new UkrFactory;
            break;
        default:
            break;
        }
        product = new Movie(creator->chooseLanguage(), creator->chooseSubtitles());
    }

    Movie getProduct()
    {
            if (product)
            {
                return *product;
            }
            throw notCreatedEx();
        }

        class notCreatedEx: public exception {};
};

#endif // MOVIE_H
