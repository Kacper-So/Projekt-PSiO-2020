#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "include.h"
#include "Object.h"
#include "player.h"

using namespace std;

class Projectile
{
public:
    pair<int,int> k_bw;
    sf::RectangleShape hitbox;
    sf::Sprite spr;
    sf::Texture tex;
    bool kierunek;
    pair<int,int> velocity;
    Projectile();
    void define(pair<int,int> k_bw_arg,bool kierunek_arg);
    void update(sf::Time elapsed);
    void movement(sf::Time elapsed);
};

#endif // PROJECTILE_H
