#ifndef OBJECT_H
#define OBJECT_H
#include "include.h"
using namespace std;
class Object
{
private:

public:
    //Variables
    pair<float,float> k_bw;
    char type;
    sf::RectangleShape hitbox;
    sf::Sprite spr;
    sf::Texture tex;
    sf::RectangleShape hbR,hbL,hbU,hbD;
    sf::IntRect anim;
    int anim_iterator=50;
    //Constructors & Destructors
    Object();
    virtual ~Object();
    //Functions
    void define(pair<int,int> k_arg,char type_arg);
    void set();
};

#endif // OBJECT_H
