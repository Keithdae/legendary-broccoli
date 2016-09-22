#ifndef SHOT_H
#define SHOT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Monster.h>
#include <math.h>

class Shot : public sf::Drawable, public sf::Transformable
{
    public:
        Shot(std::string filename);
        Shot();
        virtual ~Shot();

        int getDamage() const {return m_damage;};
        void setDamage(int d) {m_damage = d;};

        int getId() const {return m_id;};
        void setId(int i) {m_id = i;};

        sf::Vector2f getSpeed() const {return m_speed;};
        void setSpeed(float x, float y) {m_speed.x = x; m_speed.y = y;};

        void setPos(float x, float y) {m_sprite.setPosition(x,y);};
        void setRotato(float ang) {m_sprite.setRotation(ang * 57.2957795131);};

        void setTarget(Monster* target){m_target = target;};

        sf::FloatRect getRect();

        bool update();

        inline bool operator== (const Shot &shot) const {return this->getId() == shot.getId();};
    protected:
    private:
        sf::Sprite m_sprite;
        sf::Texture m_tileset;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            // on applique la transformation
            states.transform *= getTransform();

            // on applique la texture du tileset
            states.texture = &m_tileset;

            // et on dessine enfin le sprite
            target.draw(m_sprite, states);
        }

        sf::Vector2f m_speed;

        int m_damage;

        Monster* m_target;

        int m_id;

};

#endif // SHOT_H
