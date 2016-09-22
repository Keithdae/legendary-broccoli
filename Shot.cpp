#include "Shot.h"

Shot::Shot(std::string filename)
{
    //ctor
    m_tileset.loadFromFile(filename);
    m_sprite.setTexture(m_tileset);
}

Shot::Shot() // Deprecated
{
    //ctor
}

Shot::~Shot()
{
    //dtor
}


bool Shot::update()
{
    bool res = true;

    if(m_target->isDead())
    {
        res = false;
    }
    else
    {
        float ang = atan2f(m_target->getPos().y + 24.f - m_sprite.getPosition().y, m_target->getPos().x + 24.f - m_sprite.getPosition().x);
        setRotato(ang);
        setSpeed(20.f * cosf(ang) ,20.f * sinf(ang));
        m_sprite.move(m_speed);
    }

    float x = m_sprite.getPosition().x;
    float y = m_sprite.getPosition().y;
    if(x > 800 || x < 0 || y > 480 || y < 0)
    {
        res = false;
    }

    return res;
}


sf::FloatRect Shot::getRect()
{
    sf::FloatRect res = m_sprite.getGlobalBounds();
    res.height /= 2;
    res.width /= 2;
    return res;
}
