#include "game.h"
#include "Object.h"
#include "player.h"
#include "enemy.h"
#include "frog.h"
#include "fly.h"

using namespace std;

vector<Object> generateMap(Game &game)
{
    vector<Object> v;
    Object* O=new Object;
    Enemy* E=new Enemy;
    Frog* F=new Frog;
    fly* L=new fly;
    Star* S=new Star;
    int x=0,y=0;
    fstream input_file(game.map,ios::in);
    string line;
    if(input_file.is_open())
    {
        getline(input_file,line);
        while(!input_file.eof())
        {
            getline(input_file,line);
            for(unsigned long long i=0;i<line.size();i++)
            {
                if(line[i]!=' ')
                {
                    if(line[i]=='*')
                    {
                        game.player.k_bw=make_pair(x,y);
                    }
                    else if(line[i]=='e')
                    {
                        E->define(make_pair(x,y),line[i]);
                        game.v_e.push_back(*E);
                    }
                    else if(line[i]=='f')
                    {
                        F->define(make_pair(x,y),line[i]);
                        game.v_f.push_back(*F);
                    }
                    else if(line[i]=='l')
                    {
                        L->define(make_pair(x,y),line[i]);
                        game.v_fly.push_back(*L);
                    }
                    else if(line[i]=='s')
                    {
                        S->define(make_pair(x,y));
                        game.v_s.push_back(*S);
                    }
                    else
                    {
                        O->define(make_pair(x,y),line[i]);
                        v.push_back(*O);
                    }
                }
                x+=50;
            }
            x=0;
            y+=50;
        }
    }
    game.lowest_object_y=y;
    return v;
}

int main()
{
    //Init game
    Game *game=new Game("Map1.txt");
    game->v_o=generateMap(*game);
    game->setObjects();

    sf:: Clock clock;
    sf::Time elapsed;
    //Loop
    while(game->inGame==true)
    {
        elapsed=clock.restart();
        //Update
        game->update(elapsed);
        //Render
        game->render();
    }
    return 0;
}
