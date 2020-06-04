#include "game.h"
using namespace std;

pair<float,float> d(pair<float,float> a,pair<float,float> b)
{
    return make_pair(a.first-b.first,a.second-b.second);
}

//Priv Functions
void Game::initVariables()
{
    this->window = nullptr;
}

void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode,"Gra",sf::Style::Close | sf::Style::Titlebar);
    this->view.setCenter(sf::Vector2f(0,0));
    this->view.setSize(this->videoMode.width,this->videoMode.height);
    this->window->setFramerateLimit(60);
}

//Constructors & Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
}

Game::~Game()
{
    delete this->window;
}

//Accessors
const bool Game::running() const
{
    return this->window->isOpen();
}

//Functions
void Game::pollEvents(sf::Time elapsed)
{
    while(this->window->pollEvent(this->ev))
    {
        switch(this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        }
    }
}

void Game::setObjects()
{
    for(int i=0;i<this->v_o.size();i++)
    {
        this->v_o[i].set();
    }
    for(int i=0;i<this->v_e.size();i++)
    {
        this->v_e[i].set();
    }
    this->player.set();
}

void Game::gravity()
{
    if(this->player.inJump==true)
    {
        this->player.velocity.second+=g*this->player.falling_time.asSeconds();
    }
    else
    {
        this->player.velocity.second+=20;
    }

    for(int i=0;i<this->v_e.size();i++)
    {
        if(this->v_e[i].inJump)
        {
            this->v_e[i].velocity.second+=20;
        }
        else if(!this->v_e[i].inJump)
        {
            this->v_e[i].velocity.second=0;
        }
    }
}

void Game::update(sf::Time elapsed)
{
    this->pollEvents(elapsed);
    for(int i=0;i<this->v_e.size();i++)
    {
        this->v_e[i].update(elapsed,this->v_o);
    }
    this->player.update(elapsed,v_o);
    this->gravity();
}

void Game::render()
{
    this->window->clear(sf::Color(82,171,240));

    //Drawing objects
    for(int i=0;i<this->v_o.size();i++)
    {
        if(abs(d(this->v_o[i].k_bw,this->player.k_bw).first)<=500)
        {
            this->window->draw(this->v_o[i].spr);
            //this->window->draw(this->v_o[i].hbD);
            //this->window->draw(this->v_o[i].hbR);
            //this->window->draw(this->v_o[i].hbU);
            //this->window->draw(this->v_o[i].hbL);
        }
    }
    for(int i=0;i<this->v_e.size();i++)
    {
        if(abs(d(this->v_e[i].k_bw,this->player.k_bw).first)<=500)
        {
            this->window->draw(this->v_e[i].hitbox);
        }
    }
    this->window->draw(this->player.spr);
    if(this->player.hitbox.getPosition().y>=this->lowest_object_y-370)
    {
        this->view.setCenter(sf::Vector2f(this->player.hitbox.getPosition().x+25,this->lowest_object_y-300));
    }
    if(this->player.hitbox.getPosition().y<this->lowest_object_y-370)
    {
        this->view.setCenter(sf::Vector2f(this->player.hitbox.getPosition().x+25,this->player.hitbox.getPosition().y+70));
    }
    this->window->setView(this->view);
    this->window->display();
}

