#include "star.h"

Star::Star()
{

}

void Star::define(pair<int, int> k_arg)
{
    this->k_bw=k_arg;
}

void Star::set()
{
    this->hitbox.setSize(sf::Vector2f(30,30));
    this->hitbox.setPosition(sf::Vector2f(this->k_bw.first+10,this->k_bw.second+10));
    this->tex.loadFromFile("textures/star.png");
    this->spr.setTexture(this->tex);
    this->spr.setPosition(this->hitbox.getPosition());
}

void Star::refreshTex()
{
    this->tex.loadFromFile("textures/star.png");
    this->spr.setTexture(this->tex);
}
