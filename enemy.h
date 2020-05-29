#ifndef ENEMY_H
#define ENEMY_H
#include "include.h"
#include "Object.h"
#include "projectile.h"

using namespace std;

class Enemy
{
private:

public:
    //Variables
    pair<float,float> k_bw;
    char type;
    sf::RectangleShape hitbox;
    sf::Sprite spr;
    sf::Texture tex;
    int last_collision=1;
    pair<int,int> velocity;
    bool inJump;
    //Constructors & Destructors
    Enemy();
    virtual ~Enemy();
    //Functions
    void define(pair<int,int> k_arg,char type_arg);
    void set();
    void update(sf::Time elapsed, vector<Object> &v_o);
    bool collision_L(vector<Object> &v_o);
    bool collision_R(vector<Object> &v_o);
    bool collision_U(vector<Object> &v_o);
    void movement(sf::Time elapsed, vector<Object> &v_o);
};

#endif // ENEMY_H
