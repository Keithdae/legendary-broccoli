#ifndef TOWER_H
#define TOWER_H

#include <SFML/Graphics.hpp>
#include "Shot.h"
#include <sstream>


class Tower : public sf::Drawable, public sf::Transformable
{
    public:
        Tower(int cost, int tileNum, int range, int shotDamage, int shotDelay, std::string name, std::string filename);
        Tower();
        virtual ~Tower();

        int getTileNum() const {return m_tileNum;};

        void setName(std::string n){m_name = n;};
        std::string getName() const {return m_name;};

        void setId(int i){m_id = i;};
        int getId() const {return m_id;};

        void setCost(int c){m_cost = c;};
        int getCost() const {return m_cost;};

        void setPos(float x, float y){m_sprite.setPosition(x,y);};

        inline bool operator== (const Tower &tower) const {return this->getId() == tower.getId();};

        int getShotDelay() const {return m_shotDelay;};

        void setShotDamage(int sd){m_shotDamage = sd;};
        int getShotDamage() const {return m_shotDamage;};

        std::vector<Shot*> getShots() const {return m_shots;};

        void addShot(Shot* shot){m_shots.push_back(shot); shot->setId(m_currId); m_currId++;};
        void deleteShot(Shot* shot){m_shots.erase(std::remove(m_shots.begin(), m_shots.end(), shot), m_shots.end());};

        void fireShot(Monster* target);

        void updateShots();

        void setRange(int r) {m_range = r;};
        int getRange() const {return m_range;};

        bool isInRange (float x, float y) const {return (m_sprite.getPosition().x - x) * (m_sprite.getPosition().x - x) + (m_sprite.getPosition().y - y) * (m_sprite.getPosition().y - y) < m_range * m_range;};

        std::string toString();

        std::string getShotFilename() const {return m_shotFilename;};
        void setShotFilename(std::string filename){m_shotFilename = filename;};
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

            for(unsigned int i = 0; i<m_shots.size(); i++)
                target.draw(*m_shots[i]);
        }
        sf::Sprite m_sprite;
        sf::Texture m_tileset;

        int m_tileNum;

        int m_id;
        int m_cost;

        std::vector<Shot*> m_shots;

        int m_shotDamage;

        int m_shotDelay;
        sf::Clock clock;

        int m_currId;

        int m_range;

        std::string m_name;

        std::string m_shotFilename;
};

#endif // TOWER_H
