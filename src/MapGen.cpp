#include "MapGen.h"

MapGen::MapGen()
{
    //ctor
}

MapGen::~MapGen()
{
    //dtor
}


std::vector< std::vector<int> > MapGen::generateMap()
{
    std::vector< std::vector<int> > res(HEIGHT, std::vector<int> (WIDTH));
    for(int i=0; i < WIDTH; i++)
    {
        for(int j=0; j < HEIGHT; j++)
        {
            res[j][i] = 2;
        }
    }

    generatePath(res);

    return res;
}


void MapGen::generatePath(std::vector< std::vector<int> > &map)
{
    bool up = false;

    map[HEIGHT/2][0] = 1;
    map[HEIGHT/2][WIDTH - 1] = 3;
    for(int i = 1; i<5; i++)
        map[HEIGHT/2][i] = 1;

    for(int i = WIDTH - 2; i>WIDTH - 5; i--)
        map[HEIGHT/2][i] = 1;

    for(int j = WIDTH/5 - 1; j < (WIDTH * 4) / 5 + 1; j+=4 )
    {
        for(int i = 1; i < HEIGHT-1; i++)
        {
            map[i][j] = 1;
        }
        if(up)
        {
            map[1][j+1] = 1;
            map[1][j+2] = 1;
            map[1][j+3] = 1;
            up = false;
        }
        else
        {
            map[HEIGHT-2][j+1] = 1;
            map[HEIGHT-2][j+2] = 1;
            map[HEIGHT-2][j+3] = 1;
            up = true;
        }
    }

   for(int i=1; i<7;i++)
        map[i][4] = 2;

    map[13][23] = 2;
    map[13][22] = 2;
    map[13][21] = 2;

    for(int i=13; i>7; i--)
        map[i][20] = 2;
}
