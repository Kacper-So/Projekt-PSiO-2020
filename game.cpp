#include "game.h"
using namespace std;

pair<float,float> d(pair<float,float> a,pair<float,float> b)
{
    return make_pair(a.first-b.first,a.second-b.second);
}

//Priv Functions
void Game::initVariables(string map_arg)
{
    this->window = nullptr;
    this->p=new Projectile;
    map=map_arg;
    this->p->define(this->player.k_bw,this->player.kierunek);
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
Game::Game(string map_arg)
{
    this->initVariables(map_arg);
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
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->p_clock.getElapsedTime()>sf::seconds(0.5))
    {
        this->p_clock.restart();
        this->p->define(this->player.k_bw,this->player.kierunek);
        this->v_p.push_back(*p);
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
    for(int i=0;i<this->v_f.size();i++)
    {
        this->v_f[i].set();
    }
    for(int i=0;i<this->v_fly.size();i++)
    {
        this->v_fly[i].set();
    }
    for(int i=0;i<this->v_s.size();i++)
    {
        this->v_s[i].set();
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
    for(int i=0;i<this->v_f.size();i++)
    {
        this->v_f[i].velocity.second+=20;
    }
}

void Game::update(sf::Time elapsed)
{
    this->pollEvents(elapsed);
    for(auto i=this->v_p.begin();i!=this->v_p.end();i++)
    {
        i->update(elapsed);
        for(int j=0;j<this->v_o.size();j++)
        {
            if(i->hitbox.getGlobalBounds().intersects(this->v_o[j].hitbox.getGlobalBounds()))
            {
                v_p.erase(i);
                i--;
            }
        }
    }
    for(auto i=this->v_e.begin();i!=this->v_e.end();i++)
    {
        if(this->player.hitbox.getGlobalBounds().intersects(i->hitbox.getGlobalBounds()) && i->hitbox.getPosition().y-this->player.hitbox.getPosition().y>60)
        {
            v_e.erase(i);
            i--;
            for(auto j=this->v_e.begin();j!=this->v_e.end();j++)
            {
                j->refreshTex();
            }
        }
        else if(this->player.hitbox.getGlobalBounds().intersects(i->hitbox.getGlobalBounds()))
        {
            cout<<"Przegrana, zabil cie glut"<<endl;
            this->inGame=false;
        }
        for(auto j=this->v_p.begin();j!=this->v_p.end();j++)
        {
            if(i->hitbox.getGlobalBounds().intersects(j->hitbox.getGlobalBounds()))
            {
                v_e.erase(i);
                i--;
                for(auto k=this->v_e.begin();k!=this->v_e.end();k++)
                {
                    k->refreshTex();
                }
                v_p.erase(j);
                j--;
            }
        }
        if(i->k_bw.second>this->lowest_object_y)
        {
            v_e.erase(i);
            i--;
            for(auto j=this->v_e.begin();j!=this->v_e.end();j++)
            {
                j->refreshTex();
            }
        }
        i->update(elapsed,this->v_o);
    }
    for(auto i=this->v_f.begin();i!=this->v_f.end();i++)
    {
        if(this->player.hitbox.getGlobalBounds().intersects(i->hitbox.getGlobalBounds()) && i->hitbox.getPosition().y-this->player.hitbox.getPosition().y>60)
        {
            v_f.erase(i);
            i--;
            for(auto j=this->v_f.begin();j!=this->v_f.end();j++)
            {
                j->refreshTex();
            }
        }
        else if(this->player.hitbox.getGlobalBounds().intersects(i->hitbox.getGlobalBounds()))
        {
            cout<<"Przegrana, zabila cie zaba"<<endl;
            this->inGame=false;
        }
        for(auto j=this->v_p.begin();j!=this->v_p.end();j++)
        {
            if(i->hitbox.getGlobalBounds().intersects(j->hitbox.getGlobalBounds()))
            {
                v_f.erase(i);
                i--;
                for(auto k=this->v_f.begin();k!=this->v_f.end();k++)
                {
                    k->refreshTex();
                }
                v_p.erase(j);
                j--;
            }
        }
        if(i->k_bw.second>this->lowest_object_y)
        {
            v_f.erase(i);
            i--;
            for(auto j=this->v_f.begin();j!=this->v_f.end();j++)
            {
                j->refreshTex();
            }
        }
        i->update(elapsed,this->v_o);
    }
    for(auto i=this->v_fly.begin();i!=this->v_fly.end();i++)
    {
        if(this->player.hitbox.getGlobalBounds().intersects(i->hitbox.getGlobalBounds()) && i->hitbox.getPosition().y-this->player.hitbox.getPosition().y>60)
        {
            v_fly.erase(i);
            i--;
            for(auto j=this->v_fly.begin();j!=this->v_fly.end();j++)
            {
                j->refreshTex();
            }
        }
        else if(this->player.hitbox.getGlobalBounds().intersects(i->hitbox.getGlobalBounds()))
        {
            cout<<"Przegrana, zabila cie mucha"<<endl;
            this->inGame=false;
        }
        for(auto j=this->v_p.begin();j!=this->v_p.end();j++)
        {
            if(i->hitbox.getGlobalBounds().intersects(j->hitbox.getGlobalBounds()))
            {
                v_fly.erase(i);
                i--;
                for(auto k=this->v_fly.begin();k!=this->v_fly.end();k++)
                {
                    k->refreshTex();
                }
                v_p.erase(j);
                j--;
            }
        }
        if(i->k_bw.second>this->lowest_object_y)
        {
            v_fly.erase(i);
            i--;
            for(auto j=this->v_fly.begin();j!=this->v_fly.end();j++)
            {
                j->refreshTex();
            }
        }
        i->update(elapsed,this->v_o);
    }
    for(auto i=this->v_s.begin();i!=this->v_s.end();i++)
    {
        if(this->player.hitbox.getGlobalBounds().intersects(i->hitbox.getGlobalBounds()))
        {
            v_s.erase(i);
            i--;
            for(auto i=this->v_s.begin();i!=this->v_s.end();i++)
            {
                i->refreshTex();
            }
            if(v_s.empty())
            {
                cout<<"Wygrana, wszystkie gwiazdy zebrane"<<endl;
                this->inGame=false;
            }
            for(int j=0;j<this->v_e.size();j++)
            {
                v_e[j].velocity.first=v_e[j].velocity.first*1.05;
            }
            for(int j=0;j<this->v_f.size();j++)
            {
                v_e[j].velocity.first=v_f[j].velocity.first*1.2;
            }
            for(int j=0;j<this->v_fly.size();j++)
            {
                v_e[j].velocity.first=v_fly[j].velocity.first*1.05;
            }
        }
    }
    if(this->player.k_bw.second>this->lowest_object_y)
    {
        cout<<"Przegrana, spadles"<<endl;
        this->inGame=false;
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
        }
    }
    for(int i=0;i<this->v_e.size();i++)
    {
        if(abs(d(this->v_e[i].k_bw,this->player.k_bw).first)<=500)
        {
            this->window->draw(this->v_e[i].spr);
        }
    }
    for(int i=0;i<this->v_f.size();i++)
    {
        if(abs(d(this->v_f[i].k_bw,this->player.k_bw).first)<=500)
        {
            this->window->draw(this->v_f[i].spr);
        }
    }
    for(int i=0;i<this->v_fly.size();i++)
    {
        if(abs(d(this->v_fly[i].k_bw,this->player.k_bw).first)<=500)
        {
            this->window->draw(this->v_fly[i].spr);
        }
    }
    for(int i=0;i<this->v_p.size();i++)
    {
        if(abs(d(this->v_p[i].k_bw,this->player.k_bw).first)<=500)
        {
            this->window->draw(this->v_p[i].spr);
        }
    }
    for(int i=0;i<this->v_s.size();i++)
    {
        if(abs(d(this->v_s[i].k_bw,this->player.k_bw).first)<=500)
        {
            this->window->draw(this->v_s[i].spr);
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

