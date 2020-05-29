#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "include.h"
#include "Object.h"
#include "player.h"

using namespace std;

class Projectile
{
public:
    pair<float,float> k_bw;
    sf::RectangleShape hitbox;
    sf::Sprite spr;
    sf::Texture tex;
    pair<int,int> velocity;
    Projectile();
    void define();
    void update(sf::Time elapsed);
};

#endif // PROJECTILE_H
