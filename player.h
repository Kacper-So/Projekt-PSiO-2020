#ifndef PLAYER_H
#define PLAYER_H
#include "include.h"
#include "Object.h"
#include "projectile.h"
#include "enemy.h"

using namespace std;

class Player
{
private:

public:
    //Variables
    pair<float,float> k_bw;
    sf::RectangleShape hitbox;
    sf::Sprite spr;
    sf::Texture tex;
    sf::Clock falling_clock,anim_clock;
    sf::Time falling_time,anim_time=sf::seconds(0.2);
    sf::IntRect anim_iterator;
    int anim_iterator_x=40,anim_iterator_y=80;
    pair<int,int> velocity;
    bool onGround;
    bool inJump;
    //Constructors & Destructors
    Player();
    virtual ~Player();
    //Functions
    void set();
    void update(sf::Time elapsed, vector<Object> &v_o);
    bool collision_x(vector<Object> &v_o);
    bool collision_U(vector<Object> &v_o);
    bool collision_D(vector<Object> &v_o);
    void movement(sf::Time elapsed, vector<Object> &v_o);
    void shoot();
};

#endif // PLAYER_H
