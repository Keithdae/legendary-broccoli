#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/Graphics.hpp>

class Monster : public sf::Drawable, public sf::Transformable
{
    public:
        Monster(float vel, int hp, int tnumber);
        Monster();
        virtual ~Monster();

        sf::Vector2f getPos(){return m_sprite.getPosition();};

        void setVelocity(float x, float y){m_velocity.x = x;m_velocity.y = y;};
        inline sf::Vector2f getVelocity() const {return m_velocity;};

        inline int getId() const {return m_id;};
        inline void setId(int i){m_id = i;};

        inline int getHp() const {return m_hp;};
        inline void setHp(int i){m_hp = i;};

        int getReward() const {return m_reward;};
        void setReward(int r){m_reward = r;};

        void move(float x, float y){m_sprite.move(x,y);};

        sf::FloatRect getRect() const {return m_sprite.getGlobalBounds();};

        bool takeDamage(int damage);

        inline bool operator==(const Monster &mob) const {return this->getId() == mob.getId();}

        bool isDead() const {return m_dead;};
        void setDead(){m_dead = true;};
        void update();
    protected:
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            // on applique la transformation
            states.transform *= getTransform();

            // on applique la texture du tileset
            states.texture = &m_tileset;

            // et on dessine enfin le sprite
            target.draw(m_sprite, states);

            target.draw(m_lifeEmpty);
            target.draw(m_lifeFull);
        }
        sf::Sprite m_sprite;
        sf::Sprite m_lifeFull;
        sf::Sprite m_lifeEmpty;
        sf::Texture m_tileset;
        sf::Texture m_lifeFtext;
        sf::Texture m_lifeEtext;
        sf::Vector2f m_velocity;
        int m_id;
        int m_hp, m_maxHp;

        int m_reward;

        bool m_dead;
};



#endif // MONSTER_H
