#include "player.h"
using namespace std;

//Constructor & Destructor
Player::Player()
{
    this->velocity=make_pair(500,0);
}

Player::~Player()
{

}

//Functions
void Player::set()
{
    this->hitbox.setSize(sf::Vector2f(40,80));
    this->hitbox.setPosition(sf::Vector2f(this->k_bw.first,this->k_bw.second));
    this->tex.loadFromFile("Textures/player_spritesheet.png");
    this->spr.setTexture(this->tex);
    this->anim_iterator.top=0;this->anim_iterator.left=0;this->anim_iterator.width=this->anim_iterator_x;this->anim_iterator.height=this->anim_iterator_y;
    this->spr.setTextureRect(this->anim_iterator);
    this->spr.setPosition(this->hitbox.getPosition());
}

bool Player::collision_x(vector<Object> &v_o)
{
    for(int i=0;i<v_o.size();i++)
    {
        if(this->hitbox.getGlobalBounds().intersects(v_o[i].hbL.getGlobalBounds()))
        {
            this->hitbox.setPosition(v_o[i].hitbox.getPosition().x-this->hitbox.getSize().x,this->hitbox.getPosition().y);
            this->k_bw=make_pair(this->hitbox.getPosition().x,this->hitbox.getPosition().y);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        if(this->hitbox.getGlobalBounds().intersects(v_o[i].hbR.getGlobalBounds()))
        {
            this->hitbox.setPosition(v_o[i].hbR.getPosition().x,this->hitbox.getPosition().y);
            this->k_bw=make_pair(this->hitbox.getPosition().x,this->hitbox.getPosition().y);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
}

bool Player::collision_U(vector<Object> &v_o)
{
    for(int i=0;i<v_o.size();i++)
    {
        if(this->hitbox.getGlobalBounds().intersects(v_o[i].hbU.getGlobalBounds()) && this->hitbox.getPosition().y<v_o[i].hitbox.getPosition().y-60)
        {
            this->falling_clock.restart();
            this->falling_time=sf::seconds(0.3);
            this->velocity.second=0;
            this->onGround=true;
            this->hitbox.setPosition(sf::Vector2f(this->hitbox.getPosition().x,v_o[i].hitbox.getPosition().y-this->hitbox.getSize().y-1));
            return true;
        }
        else
        {
            this->onGround=false;
        }
    }
}

bool Player::collision_D(vector<Object> &v_o)
{
    for(int i=0;i<v_o.size();i++)
    {
        if(this->hitbox.getGlobalBounds().intersects(v_o[i].hbD.getGlobalBounds()) && this->hitbox.getPosition().y>v_o[i].hitbox.getPosition().y+30)
        {
            this->hitbox.setPosition(this->hitbox.getPosition().x,v_o[i].hbD.getPosition().y);
            return true;
        }
    }
}

void Player::movement(sf::Time elapsed, vector<Object> &v_o)
{
    if(!collision_U(v_o))
    {
        this->hitbox.move(0,elapsed.asSeconds()*this->velocity.second);
        if(collision_U(v_o)==true)
        {
        }
    }
    if(collision_D(v_o))
    {
        this->velocity.second=0;
        this->inJump=false;
        this->hitbox.move(0,1);
        if(collision_D(v_o)==false)
        {
        }
    }
    if(!collision_x(v_o) && sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->hitbox.move(elapsed.asSeconds()*this->velocity.first,0);
        this->k_bw.first+=elapsed.asSeconds()*this->velocity.first;
        if(this->anim_clock.getElapsedTime()>this->anim_time)
        {
            this->anim_clock.restart();
            if(this->onGround==true)
            {
                if(this->anim_iterator.left!=160) this->anim_iterator.left+=this->anim_iterator_x;
                if(this->anim_iterator.top>0)
                {
                    this->anim_iterator.top-=this->anim_iterator_y;
                }
                if(this->anim_iterator.left==160)
                {
                    this->anim_iterator.left=0;
                }
                this->spr.setTextureRect(this->anim_iterator);
            }
            else
            {
                this->anim_iterator.top=0;
                this->anim_iterator.left=160;
                this->spr.setTextureRect(this->anim_iterator);
            }
        }
    }
    if(!collision_x(v_o) && sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->hitbox.move(-elapsed.asSeconds()*this->velocity.first,0);
        this->k_bw.first-=elapsed.asSeconds()*this->velocity.first;
        if(this->anim_clock.getElapsedTime()>this->anim_time)
        {
            this->anim_clock.restart();
            if(this->onGround==true)
            {
                if(this->anim_iterator.left!=160) this->anim_iterator.left+=this->anim_iterator_x;
                if(this->anim_iterator.top==0)
                {
                    this->anim_iterator.top+=this->anim_iterator_y;
                }
                if(this->anim_iterator.left==160)
                {
                    this->anim_iterator.left=0;
                }
                this->spr.setTextureRect(this->anim_iterator);
            }
            else
            {
                this->anim_iterator.top=80;
                this->anim_iterator.left=160;
                this->spr.setTextureRect(this->anim_iterator);
            }
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->onGround==true)
    {
        this->hitbox.move(0,-1);
        this->velocity.second-=1000;
        this->inJump=true;
    }
    if(this->velocity.second>0)
    {
        this->inJump=false;
    }
}

void Player::shoot()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {

    }
}

void Player::update(sf::Time elapsed, vector<Object> &v_o)
{
    this->movement(elapsed,v_o);
    this->falling_time+=this->falling_clock.getElapsedTime();
    this->spr.setPosition(this->hitbox.getPosition());
    if(this->anim_clock.getElapsedTime()>sf::seconds(0.3))
    {
        this->anim_iterator.top=0;
        this->anim_iterator.left=0;
        this->spr.setTextureRect(this->anim_iterator);
    }
}
