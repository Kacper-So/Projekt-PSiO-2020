#include "enemy.h"

Enemy::Enemy()
{
    this->velocity=make_pair(150,0);
}

Enemy::~Enemy()
{

}

void Enemy::define(pair<int, int> k_arg, char type_arg)
{
    this->k_bw=k_arg;
    this->type=type_arg;
}

void Enemy::set()
{
    this->hitbox.setSize(sf::Vector2f(50,50));
    this->hitbox.setPosition(sf::Vector2f(this->k_bw.first,this->k_bw.second));
    this->tex.loadFromFile("textures/enemy_spritesheet.png");
    this->hbU.setSize(sf::Vector2f(this->hitbox.getSize().x,1));
    this->hbU.setPosition(this->hitbox.getPosition().x,this->hitbox.getPosition().y-1);
    this->spr.setTexture(this->tex);
    this->spr.setPosition(this->hitbox.getPosition());
    this->anim_iterator.width=50;
    this->anim_iterator.height=50;
    this->anim_iterator.top=0;
    this->anim_iterator.left=0;
}

void Enemy::refreshTex()
{
    this->tex.loadFromFile("textures/enemy_spritesheet.png");
    this->spr.setTexture(this->tex);
}

bool Enemy::collision_L(vector<Object> &v_o)
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

bool Enemy::collision_R(vector<Object> &v_o)
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

bool Enemy::collision_U(vector<Object> &v_o)
{
    for(int i=0;i<v_o.size();i++)
    {
        if(this->hitbox.getGlobalBounds().intersects(v_o[i].hbU.getGlobalBounds()))
        {
            this->hitbox.setPosition(this->hitbox.getPosition().x,v_o[i].hitbox.getPosition().y-this->hitbox.getSize().y);
            return true;
        }
    }
}

void Enemy::movement(sf::Time elapsed, vector<Object> &v_o)
{
    if(this->collision_L(v_o)==true)
    {
        this->anim_iterator.left=0;
        this->last_collision=1;
    }
    else if(this->collision_R(v_o)==true)
    {
        this->anim_iterator.left=0;
        this->last_collision=2;
    }
    if(last_collision==1)
    {
        this->hitbox.move(-elapsed.asSeconds()*this->velocity.first,0);
        if(this->anim_clock.getElapsedTime()>this->anim_time)
        {
            this->anim_clock.restart();
            if(this->anim_iterator.top==50) this->anim_iterator.top=0;
            this->anim_iterator.left+=anim_iterator_x;
            if(this->anim_iterator.left==100)
            {
                this->anim_iterator.left=0;
            }
        }
        this->k_bw.first-=elapsed.asSeconds()*this->velocity.first;
    }
    else if(last_collision==2)
    {
        this->hitbox.move(elapsed.asSeconds()*this->velocity.first,0);
        if(this->anim_clock.getElapsedTime()>this->anim_time)
        {
            this->anim_clock.restart();
            this->anim_iterator.left+=anim_iterator_x;
            if(this->anim_iterator.top==0) this->anim_iterator.top+=anim_iterator_y;
            if(this->anim_iterator.left==100)
            {
                this->anim_iterator.left=0;
            }
        }
        this->k_bw.first+=elapsed.asSeconds()*this->velocity.first;
    }
    if(this->collision_U(v_o)==true)
    {
        this->inJump=false;
    }
    else if(this->collision_U(v_o)==false)
    {
        this->inJump=true;
        this->hitbox.move(0,elapsed.asSeconds()*this->velocity.second);
    }
}

void Enemy::update(sf::Time elapsed, vector<Object> &v_o)
{
    this->movement(elapsed,v_o);
    this->spr.setPosition(this->hitbox.getPosition());
    this->hbU.setPosition(this->hitbox.getPosition().x,this->hitbox.getPosition().y-1);
    this->spr.setTextureRect(this->anim_iterator);
}
