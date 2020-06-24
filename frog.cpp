#include "frog.h"

Frog::Frog()
{
    this->velocity=make_pair(300,0);
}

Frog::~Frog()
{

}

void Frog::define(pair<int, int> k_arg, char type_arg)
{
    this->k_bw=k_arg;
    this->type=type_arg;
}

void Frog::set()
{
    this->hitbox.setSize(sf::Vector2f(50,50));
    this->hitbox.setPosition(sf::Vector2f(this->k_bw.first,this->k_bw.second));
    this->tex.loadFromFile("textures/frog_spritesheet.png");
    this->hbU.setSize(sf::Vector2f(this->hitbox.getSize().x,1));
    this->hbU.setPosition(this->hitbox.getPosition().x,this->hitbox.getPosition().y-1);
    this->spr.setTexture(this->tex);
    this->spr.setPosition(this->hitbox.getPosition());
    this->anim_iterator.width=50;
    this->anim_iterator.height=50;
    this->anim_iterator.top=0;
    this->anim_iterator.left=0;
}

void Frog::refreshTex()
{
    this->tex.loadFromFile("textures/frog_spritesheet.png");
    this->spr.setTexture(this->tex);
}

bool Frog::collision_L(vector<Object> &v_o)
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

bool Frog::collision_R(vector<Object> &v_o)
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

bool Frog::collision_U(vector<Object> &v_o)
{
    for(int i=0;i<v_o.size();i++)
    {
        if(this->hitbox.getGlobalBounds().intersects(v_o[i].hbU.getGlobalBounds()) && this->hitbox.getPosition().y<v_o[i].hitbox.getPosition().y-40)
        {
            this->falling_clock.restart();
            this->velocity.second=0;
            this->hitbox.setPosition(this->hitbox.getPosition().x,v_o[i].hitbox.getPosition().y-50);
            return true;
        }
    }
}

bool Frog::collision_D(vector<Object> &v_o)
{
    for(int i=0;i<v_o.size();i++)
    {
        if(this->hitbox.getGlobalBounds().intersects(v_o[i].hbD.getGlobalBounds()) && this->hitbox.getPosition().y>v_o[i].hitbox.getPosition().y+10)
        {
            this->hitbox.setPosition(this->hitbox.getPosition().x,v_o[i].hbD.getPosition().y);
            return true;
        }
    }
}

void Frog::movement(sf::Time elapsed, vector<Object> &v_o)
{
    if(!this->collision_U(v_o) && !this->collision_R(v_o) && !this->collision_L(v_o))
    {
        if(this->last_collision==1)
        {
            this->anim_iterator.left=0;
            this->anim_iterator.top=50;
            this->hitbox.move(-this->velocity.first*elapsed.asSeconds(),elapsed.asSeconds()*this->velocity.second);
        }
        else
        {
            this->anim_iterator.left=50;
            this->anim_iterator.top=50;
            this->hitbox.move(this->velocity.first*elapsed.asSeconds(),elapsed.asSeconds()*this->velocity.second);
        }
        if(collision_U(v_o)==true)
        {
            if(this->last_collision==1)
            {
                this->anim_iterator.left=0;
                this->anim_iterator.top=0;
            }
            if(this->last_collision==0)
            {
                this->anim_iterator.left=50;
                this->anim_iterator.top=0;
            }
        }
    }
    if(collision_D(v_o) && !this->collision_R(v_o) && !this->collision_L(v_o))
    {
        this->velocity.second=0;
        this->inJump=false;
        this->hitbox.move(0,1);
        if(collision_D(v_o)==false)
        {
        }
    }
    if(this->collision_L(v_o)==true)
    {
        if(!this->collision_U(v_o))
        {
            this->hitbox.move(0,this->velocity.second*elapsed.asSeconds());
            if(this->collision_U(v_o))
            {
                this->hitbox.move(-1,0);
                this->last_collision=1;
            }
        }
    }
    else if(this->collision_R(v_o)==true)
    {
        if(!this->collision_U(v_o))
        {
            this->hitbox.move(0,this->velocity.second*elapsed.asSeconds());
            if(this->collision_U(v_o))
            {
                this->hitbox.move(1,0);
                this->last_collision=0;
            }
        }
    }
    if(this->jump_clock.getElapsedTime()>sf::seconds(2))
    {
        this->hitbox.move(0,-1);
        this->jump_clock.restart();
        this->velocity.second=-500;
        this->inJump=true;
    }
    else if(this->velocity.second>0)
    {
        this->inJump=false;
    }
}

void Frog::update(sf::Time elapsed, vector<Object> &v_o)
{
    this->movement(elapsed,v_o);
    this->falling_time+=this->falling_clock.getElapsedTime();
    this->k_bw=make_pair(this->hitbox.getPosition().x,this->hitbox.getPosition().y);
    this->spr.setPosition(this->hitbox.getPosition());
    this->hbU.setPosition(this->hitbox.getPosition().x,this->hitbox.getPosition().y-1);
    this->spr.setTextureRect(this->anim_iterator);
}
