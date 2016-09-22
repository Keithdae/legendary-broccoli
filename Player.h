#ifndef PLAYER_H
#define PLAYER_H

#include "Tower.h"
#include "MapGen.h"

#define LIFE 5
#define START_MONEY 200

class Player
{
    public:
        Player();
        virtual ~Player();

        void setLife(int life){m_life = life;};
        int getLife() const {return m_life;};

        void setMoney(int money){m_money = money;};
        void earnMoney(int m){m_money += m;};
        int getMoney() const {return m_money;};

        /** loseLife : Retire 1 pdv au joueur
        *   ReturnValue : Faux si m_life > 0
        *                 Vrai sinon
        */
        bool loseLife(){m_life--; return !(m_life > 0);};

        void addTower(Tower* tower){m_towers.push_back(tower); tower->setId(m_currId); m_currId++;};
        void deleteTower(Tower* tower){m_towers.erase(std::remove(m_towers.begin(), m_towers.end(), tower), m_towers.end());};
        std::vector<Tower*> getTowers() const {return m_towers;};

        bool checkSlot(int x, int y){return !m_towerSlots[y][x];};

        bool buyTower(int posX, int posY, int type);

        void createTowerType(Tower* tower){m_towerTypes.push_back(tower);};

        std::vector<Tower*> getTowerTypes() const {return m_towerTypes;};

        void initializeTowerSlots(std::vector< std::vector<int> > tilemap);
        std::vector< std::vector<bool> > getTowerSlots() const {return m_towerSlots;};
    protected:
    private:
        int m_money;
        int m_life;
        int m_currId;

        std::vector<Tower*> m_towers;

        std::vector<Tower*> m_towerTypes;

        std::vector< std::vector<bool> > m_towerSlots;
};

#endif // PLAYER_H
