#ifndef GAME_H
#define GAME_H
#include "include.h"
#include "Object.h"
#include "player.h"
#include "projectile.h"
#include "enemy.h"
#include "frog.h"
#include "fly.h"

using namespace std;

class Game
{
private:
    //Variables
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;
    sf::View view;
    float g=20;

    //Priv Functions
    void initVariables();
    void initWindow();

public:
    //Variables
    vector<Object> v_o;
    vector<Enemy> v_e;
    vector<Projectile> v_p;
    vector<Frog> v_f;
    vector<fly> v_fly;
    int lowest_object_y;
    Player player;
    Projectile *p;
    sf::Clock p_clock;
    bool inGame=true;
    //Constructors & Destructors
    Game();
    virtual ~Game();

    //Accessors
    const bool running() const;

    //Functions
    void setObjects();
    void pollEvents(sf::Time elapsed);
    void update(sf::Time elapsed);
    void render();
    void gravity();
};

#endif // GAME_H
