#include "Object.h"
using namespace std;

//Constructors & Destructors
Object::Object()
{

}

Object::~Object()
{

}

//Functions
void Object::define(pair<int,int> k_arg,char type_arg)
{
    this->k_bw=k_arg;
    this->type=type_arg;
}

void Object::set()
{
    this->hitbox.setSize(sf::Vector2f(50,50));
    this->hitbox.setPosition(sf::Vector2f(this->k_bw.first,this->k_bw.second));
    this->hbU.setSize(sf::Vector2f(this->hitbox.getSize().x,1));
    this->hbD.setSize(sf::Vector2f(this->hitbox.getSize().x,1));
    this->hbL.setSize(sf::Vector2f(1,this->hitbox.getSize().y));
    this->hbR.setSize(sf::Vector2f(1,this->hitbox.getSize().y));
    this->hbU.setPosition(sf::Vector2f(this->hitbox.getPosition().x,this->hitbox.getPosition().y-1));
    this->hbD.setPosition(sf::Vector2f(this->hitbox.getPosition().x,this->hitbox.getPosition().y+this->hitbox.getSize().y));
    this->hbL.setPosition(sf::Vector2f(this->hitbox.getPosition().x-1,this->hitbox.getPosition().y));
    this->hbR.setPosition(sf::Vector2f(this->hitbox.getPosition().x+this->hitbox.getSize().x,this->hitbox.getPosition().y));
    this->tex.loadFromFile("Textures/object_tex.png");
    this->anim.width=this->anim_iterator;
    this->anim.height=this->anim_iterator;
    this->spr.setTexture(this->tex);
    if(this->type=='1') {this->anim.top=0; this->anim.left=0*anim_iterator;}
    if(this->type=='2') {this->anim.top=0; this->anim.left=anim_iterator;}
    if(this->type=='3') {this->anim.top=0; this->anim.left=2*anim_iterator;}
    if(this->type=='4') {this->anim.top=0; this->anim.left=3*anim_iterator;}
    if(this->type=='5') {this->anim.top=0; this->anim.left=4*anim_iterator;}
    this->spr.setTextureRect(this->anim);
    this->spr.setPosition(this->hitbox.getPosition());
}
