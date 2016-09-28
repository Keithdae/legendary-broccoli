#include "Tower.h"

// Constructeur
Tower::Tower(int cost, int tileNum, int range, int shotDamage, int shotDelay, std::string name, std::string filename)
{
    m_currId = 0;
    int tileNumber = tileNum;
    //ctor
    m_tileNum = tileNumber;
    m_tileset.loadFromFile("rc/tileset/test.png");
    // on en déduit sa position dans la texture du tileset
    int tu = tileNumber % (m_tileset.getSize().x / 32);
    int tv = tileNumber / (m_tileset.getSize().x / 32);

    sf::IntRect rect;

    m_sprite.setTexture(m_tileset);

    rect.height = 32;
    rect.width = 32;

    rect.top = tv * 32;
    rect.left = tu * 32;

    m_sprite.setTextureRect(rect);

    m_cost = cost;
    m_name = name;
    m_shotDelay = shotDelay;
    m_shotDamage = shotDamage;
    m_range = range;
    m_shotFilename = filename;
}

// NEEDS TO BE REMOVED
Tower::Tower()
{
    m_currId = 0;
    //ctor
    int tileNumber = 8;
    m_tileNum = tileNumber;
    m_tileset.loadFromFile("rc/tileset/test.png");
    // on en déduit sa position dans la texture du tileset
    int tu = tileNumber % (m_tileset.getSize().x / 32);
    int tv = tileNumber / (m_tileset.getSize().x / 32);

    sf::IntRect rect;

    m_sprite.setTexture(m_tileset);

    rect.height = 32;
    rect.width = 32;

    rect.top = tv * 32;
    rect.left = tu * 32;

    m_sprite.setTextureRect(rect);
}

Tower::~Tower()
{
    //dtor
}


void Tower::fireShot(Monster* target)
{
    sf::Int32 msecElapsed = clock.getElapsedTime().asMilliseconds(); // On recupere le temps ecoule
    if(msecElapsed >= m_shotDelay)
    {
        float x = m_sprite.getPosition().x + 24.f;
        float y = m_sprite.getPosition().y + 24.f;

        float ang = atan2f(target->getPos().y + 16.f - y, target->getPos().x + 16.f - x);

        Shot* shot = new Shot(m_shotFilename);
        shot->setPos(x,y);
        shot->setRotato(ang);
        shot->setDamage(m_shotDamage);
        shot->setTarget(target);
        shot->setSpeed(20.f * cosf(ang) ,20.f * sinf(ang));


        addShot(shot);
        clock.restart();
    }
}


void Tower::updateShots()
{
    for(unsigned int i=0; i<m_shots.size(); i++)
    {
        if(!m_shots[i]->update())
        {
            deleteShot(m_shots[i]);
        }
    }
}

std::string Tower::toString()
{
    std::ostringstream out;
    out << "Name       : " << getName() << "\n"
        << "Cost         : " << getCost() << "\n"
        << "Range      : " << getRange() << "\n"
        << "Damage   : " << getShotDamage() << "\n"
        << "Att.Speed : " << 1000 / getShotDelay();
    return out.str();
}
