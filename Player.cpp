#include "Player.h"

Player::Player()
    : m_towerSlots(HEIGHT, std::vector<bool>(WIDTH))
{
    //ctor
    m_currId = 0;
}

Player::~Player()
{
    //dtor
}


bool Player::buyTower(int posX, int posY, int type)
{
    bool res = true;
    if(m_towerSlots[posY][posX])
    {
        res = false;
    }
    else
    {
        if((unsigned int) type < m_towerTypes.size())
        {
            if(m_money >= m_towerTypes[type]->getCost())
            {
                m_money = m_money - m_towerTypes[type]->getCost();
                m_towerSlots[posY][posX] = true;
                Tower* towerType = m_towerTypes[type];
                Tower* newTower = new Tower(towerType->getCost(), towerType->getTileNum(), towerType->getRange(), towerType->getShotDamage(), towerType->getShotDelay(), towerType->getName(), towerType->getShotFilename());
                newTower->setPos(posX * 32.f, posY * 32.f);
                addTower(newTower);
            }
            else
            {
                res = false;
            }
        }
        else
        {
            res = false;
        }
    }


    return res;
}


void Player::initializeTowerSlots(std::vector< std::vector<int> > tilemap)
{
    for(unsigned int i = 0; i < tilemap.size(); i++)
    {
        for(unsigned int j = 0; j < tilemap[i].size(); j++)
        {
            if(tilemap[i][j] != 2)
            {
                m_towerSlots[i][j] = true;
            }
        }
    }
}

