#include "projectile.h"

Projectile::Projectile()
{
    this->hitbox.setSize(sf::Vector2f(20,20));
    this->velocity=make_pair(700,0);
    this->tex.loadFromFile("Textures/projectile.png");
    this->spr.setTexture(this->tex);
}

void Projectile::define(pair<int,int> k_bw_arg,bool kierunek_arg)
{
    this->k_bw.first=k_bw_arg.first+20;
    this->k_bw.second=k_bw_arg.second+40;
    this->kierunek=kierunek_arg;
    if(this->kierunek==false) this->anim_iterator.top=0;
    else this->anim_iterator.top=anim_const;
    this->anim_iterator.left=0;
    this->anim_iterator.width=20;
    this->anim_iterator.height=20;
    this->hitbox.setPosition(this->k_bw.first,this->k_bw.second);
}

void Projectile::movement(sf::Time elapsed)
{
    if(this->kierunek==false)
    {
        if(this->anim_clock.getElapsedTime()>=sf::seconds(0.2))
        {
            if(anim_iterator.left==80)
            {
                anim_iterator.left=0;
            }
            this->anim_clock.restart();
            this->anim_iterator.left+=anim_const;
        }
        this->hitbox.move(elapsed.asSeconds()*this->velocity.first,0);
        this->k_bw.first+=elapsed.asSeconds()*this->velocity.first;
    }
    if(this->kierunek==true)
    {
        if(this->anim_clock.getElapsedTime()>=sf::seconds(0.2))
        {
            if(anim_iterator.left==80)
            {
                anim_iterator.left=0;
            }
            this->anim_clock.restart();
            this->anim_iterator.left+=anim_const;
        }
        this->hitbox.move(-elapsed.asSeconds()*this->velocity.first,0);
        this->k_bw.first-=elapsed.asSeconds()*this->velocity.first;
    }
}

void Projectile::update(sf::Time elapsed)
{
    this->spr.setPosition(this->hitbox.getPosition());
    this->movement(elapsed);
    this->spr.setTextureRect(this->anim_iterator);
}
