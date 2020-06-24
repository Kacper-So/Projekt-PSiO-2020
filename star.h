#ifndef STAR_H
#define STAR_H
#include "include.h"
#include "Object.h"
#include "projectile.h"

class Star
{
public:
    Star();
    pair<float,float> k_bw;
    sf::RectangleShape hitbox;
    sf::Sprite spr;
    sf::Texture tex;
    void set();
    void define(pair<int, int> k_arg);
    void refreshTex();
};

#endif // STAR_H
