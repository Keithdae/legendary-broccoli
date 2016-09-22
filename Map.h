#ifndef MAP_H
#define MAP_H

#include "MapGen.h"
#include "Monster.h"
#include <cstdlib>

class Map
{
    public:
        Map();
        virtual ~Map();

        std::vector< std::vector<int> > getMap(){return m_map;}

        bool testCollision(Monster *mob);

        void addMonster(Monster *mob){m_monsters.push_back(mob);mob->setId(m_currId);m_currId++;};
        void spawnMonster();
        void deleteMonster(Monster *mob){m_monsters.erase(std::remove(m_monsters.begin(), m_monsters.end(), mob), m_monsters.end());};

        std::vector<Monster*> getMonsters() const {return m_monsters;};

        void setTimer(int ms){m_timer = ms;};

        void generateWave(std::vector<int> tileNumbers, int maximum);

        bool isWaveOver(){return m_spawns.size() == 0;};

        void gameOver(){m_monsters.clear(); m_spawns.clear();};

        Monster* mobGen(int type, int tileNum);
    protected:
    private:
        std::vector< std::vector<int> > m_map;
        MapGen m_mapgen;
        std::vector<Monster*> m_monsters;
        int m_currId;

        int m_timer;
        sf::Clock clock;

        std::vector<Monster*> m_spawns;
};


#endif // MAP_H
