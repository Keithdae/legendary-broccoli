#include "Map.h"

Map::Map()
{
    m_mapgen = MapGen();
    m_map = m_mapgen.generateMap();
}

Map::~Map()
{
    //dtor
}



bool Map::testCollision(Monster *mob)
{
    float x = mob->getPos().x;
    float y = mob->getPos().y;

    float offsetX = mob->getVelocity().x;
    float offsetY = mob->getVelocity().y;

    if(offsetX > 0.f)
    {
        if( m_map[(int) (y / 32.f)][(int) ((x + 32.f) / 32.f)] == 2 )
        {
            if(m_map[(int) ((y + 32.f) /32.f)][(int) (x / 32.f)] == 2)
            {
                mob->setVelocity(0.f, -offsetX);
            }
            else
            {
                mob->setVelocity(0.f, offsetX);
            }
        }
        else if(m_map[(int) (y / 32.f)][(int) ((x + offsetX + 32.f) / 32.f)] == 3)
        {
            deleteMonster(mob);
            delete mob;
            return false;
        }
    }
    else if(offsetY > 0.f)
    {
        if( m_map[(int) ((y + offsetY + 32.f) /32.f)][(int) (x / 32.f)] == 2)
        {
            mob->setVelocity(offsetY, 0.f);
        }
    }
    else
    {
        if(  m_map[(int) ((y + offsetY) /32.f)][(int) (x / 32.f)] == 2)
        {
            mob->setVelocity(-offsetY, 0.f);
        }
    }
    return true;
}


void Map::spawnMonster()
{
    if(!isWaveOver())
    {
        sf::Int32 msecElapsed = clock.getElapsedTime().asMilliseconds(); // On recupere le temps ecoule
        if(msecElapsed > m_timer) // Si on a depasse la limite de temps de spawn
        {
            Monster *mob = m_spawns.back();
            m_spawns.pop_back();
            addMonster(mob);
            std::cout << clock.restart().asSeconds() << std::endl;
        }
    }
}


void Map::generateWave(std::vector<int> tileNumbers, int maximum)
{
    Monster* mob;
    // Generation du boss
    mob = mobGen(2, tileNumbers[2]);
    m_spawns.push_back(mob);

    // Generation alternee de monstre lent et rapide
    for(int i = 0; i < maximum - 1; i++)
    {
        if(i%2 == 0)
        {
            mob = mobGen(0, tileNumbers[0]);
            m_spawns.push_back(mob);
        }
        else
        {
            mob = mobGen(1, tileNumbers[1]);
            m_spawns.push_back(mob);
        }
    }
}


Monster* Map::mobGen(int type, int tileNum)
{
    Monster* mob; // Params : Velocity, HP, TileSetPosition
    switch(type)
    {
        case 0: // Type gros et lent
        {
            mob = new Monster(1.5 , 42, tileNum);
            mob->setReward(10);
            break;
        }
        case 1: // Type rapide
        {
            mob = new Monster(4.f , 16, tileNum);
            mob->setReward(7);
            break;
        }
        case 2: // Type like a boss
        {
            mob = new Monster(2.5f, 150, tileNum);
            mob->setReward(60);
            break;
        }
    }
    return mob;
}
