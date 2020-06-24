#include "fly.h"

fly::fly()
{
    this->velocity=make_pair(200,0);
}

fly::~fly()
{

}

void fly::define(pair<int, int> k_arg, char type_arg)
{
    this->k_bw=k_arg;
    this->type=type_arg;
}

void fly::set()
{
    this->hitbox.setSize(sf::Vector2f(40,40));
    this->hitbox.setPosition(sf::Vector2f(this->k_bw.first,this->k_bw.second));
    this->tex.loadFromFile("textures/fly_spritesheet.png");
    this->hbU.setSize(sf::Vector2f(this->hitbox.getSize().x,1));
    this->hbU.setPosition(this->hitbox.getPosition().x,this->hitbox.getPosition().y-1);
    this->spr.setTexture(this->tex);
    this->spr.setPosition(this->hitbox.getPosition());
    this->anim_iterator.width=50;
    this->anim_iterator.height=30;
    this->anim_iterator.top=0;
    this->anim_iterator.left=0;
}

void fly::refreshTex()
{
    this->tex.loadFromFile("textures/fly_spritesheet.png");
    this->spr.setTexture(this->tex);
}

bool fly::collision_L(vector<Object> &v_o)
{
    for(int i=0;i<v_o.size();i++)
    {
        if(this->hitbox.getGlobalBounds().intersects(v_o[i].hbL.getGlobalBounds()))
        {
            this->hitbox.setPosition(v_o[i].hitbox.getPosition().x-this->hitbox.getSize().x,this->hitbox.getPosition().y);
            return true;
        }
    }
}

bool fly::collision_R(vector<Object> &v_o)
{
    for(int i=0;i<v_o.size();i++)
    {
        if(this->hitbox.getGlobalBounds().intersects(v_o[i].hbR.getGlobalBounds()))
        {
            this->hitbox.setPosition(v_o[i].hbR.getPosition().x,this->hitbox.getPosition().y);
            return true;
        }
    }
}

void fly::movement(sf::Time elapsed, vector<Object> &v_o)
{
    if(this->collision_L(v_o)==true)
    {
        this->anim_iterator.top=0;
        this->last_collision=1;
    }
    else if(this->collision_R(v_o)==true)
    {
        this->anim_iterator.top=anim_iterator_y;
        this->last_collision=2;
    }
    if(last_collision==1)
    {
        if(anim_clock.getElapsedTime()>sf::seconds(0.5))
        {
            this->anim_clock.restart();
            this->anim_iterator.left+=anim_iterator_x;
        }
        if(this->anim_iterator.left==100)
        {
            this->anim_iterator.left=0;
        }
        this->hitbox.move(-elapsed.asSeconds()*this->velocity.first,0);
        if(this->anim_clock.getElapsedTime()>this->anim_time)
        this->k_bw.first-=elapsed.asSeconds()*this->velocity.first;
    }
    else if(last_collision==2)
    {
        if(anim_clock.getElapsedTime()>sf::seconds(0.5))
        {
            this->anim_clock.restart();
            this->anim_iterator.left+=anim_iterator_x;
        }
        if(this->anim_iterator.left==100)
        {
            this->anim_iterator.left=0;
        }
        this->hitbox.move(elapsed.asSeconds()*this->velocity.first,0);
        if(this->anim_clock.getElapsedTime()>this->anim_time)
        this->k_bw.first+=elapsed.asSeconds()*this->velocity.first;
    }
}

void fly::update(sf::Time elapsed, vector<Object> &v_o)
{
    this->movement(elapsed,v_o);
    this->k_bw=make_pair(this->hitbox.getPosition().x,this->hitbox.getPosition().y);
    this->spr.setPosition(this->hitbox.getPosition());
    this->hbU.setPosition(this->hitbox.getPosition().x,this->hitbox.getPosition().y-1);
    this->spr.setTextureRect(this->anim_iterator);
}
