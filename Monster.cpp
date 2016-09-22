#include "Monster.h"

Monster::Monster()
{
    //ctor
    // on récupère le numéro de tuile courant
    int tileNumber = 7;

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
    m_sprite.setPosition(0.f,7.f*32.f);

    m_dead = false;
}


Monster::Monster(float vel, int hp, int tnumber)
{
    //ctor
    // on récupère le numéro de tuile courant
    int tileNumber = tnumber;

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
    m_sprite.setPosition(0.f,7.f*32.f);

    m_lifeEtext.loadFromFile("rc/textures/lifeEmpty.png");
    m_lifeEmpty.setTexture(m_lifeEtext);
    m_lifeFtext.loadFromFile("rc/textures/lifeFull.png");
    m_lifeFull.setTexture(m_lifeFtext);

    m_hp = m_maxHp = hp;
    setVelocity(vel,0.f);

    m_dead = false;
}

Monster::~Monster()
{
    //dtor
}


bool Monster::takeDamage(int damage)
{
    m_hp = m_hp - damage;
    return m_hp <= 0;
}


void Monster::update()
{
    float x = m_sprite.getPosition().x;
    float y = m_sprite.getPosition().y;
    m_lifeFull.setPosition(x + 4.f, y - 6.f);
    m_lifeEmpty.setPosition(x + 4.f, y - 6.f);
    m_lifeFull.setScale((float)m_hp / (float)m_maxHp, 1);
}
