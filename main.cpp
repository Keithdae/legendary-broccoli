#include <SFML/Graphics.hpp>
#include "Map.h"
#include "TileMap.h"
#include "Player.h"



enum GameState{
    GameOver,
    Playing,
    Victory,
    Waiting,
    Menu,
    Buying
};


int main()
{
    // Initialisation de l'aleatoire
    srand(time(NULL));

    // Creation de la carte
    Map level;

    // Creation du stream pour l'affichage de la money
    std::ostringstream out;

    // Creation du joueur
    Player player;
    player.setLife(LIFE);
    player.setMoney(START_MONEY);
    player.initializeTowerSlots(level.getMap());

    // Creation de l'etat de jeu
    GameState state = Waiting;

    // Creation du conteneur de monstre
    std::vector<Monster*> monsters;
    // Creation du conteneur de tir
    std::vector<Shot*> shots;
    bool collision = false;
    // Creation des tours
    std::vector<Tower*> towers;
    std::vector<Tower*> towerTypes;
    //                              Cost | TileNumber | Range | ShotDamage | ShotDelay | Name           |    Filename (Shot texture)
    player.createTowerType(new Tower(75,    10,         150,        17,         900,     "Pampletor",        "rc/textures/shot+pizza.png"));
    player.createTowerType(new Tower(25,    11,         75,         5,          600,     "Brocotorlee",      "rc/textures/shot+pizza.png"));
    player.createTowerType(new Tower(125,   13,         300,        4,          250,     "Atatatatatator",   "rc/textures/shot+atatatata.png"));

    int chosenOne = 0;
    bool hasShot = false;

    // Creation de la liste des positions de tiles de monstre dans le tileset
    std::vector<int> tilesMonster;
    tilesMonster.push_back(12);
    tilesMonster.push_back(7);
    tilesMonster.push_back(9);

    // Creation et generation de la grille de jeu
    TileMap grid;
    if(!grid.load("rc/tileset/test.png",sf::Vector2u(32, 32), level.getMap(), WIDTH, HEIGHT))
        return -1;

    // Geneation d'une vague de 20 monstres
    level.generateWave(tilesMonster, 20);
    // Les monstres apparaitront toutes les 600 ms
    level.setTimer(1200);

    // Creation de la fenetre
    sf::RenderWindow window(sf::VideoMode(800, 480), "Random Tower Defense");
    window.setFramerateLimit(60);

    // Creation du message de GameOver
    sf::Font font;
    if (!font.loadFromFile("rc/font/arial.ttf"))
        return -1;

    sf::Text textGameOver;
    textGameOver.setFont(font);
    textGameOver.setCharacterSize(48);
    textGameOver.setString("G4M3 0V3R");
    textGameOver.setColor(sf::Color::Red);
    textGameOver.setPosition(292, 216);

    // Creation du texte d'attente
    sf::Text textWaiting;
    textWaiting.setFont(font);
    textWaiting.setCharacterSize(24);
    textWaiting.setString("Waiting time, you can build towers \nPress space to start the wave");
    textWaiting.setColor(sf::Color::White);
    textWaiting.setPosition(240, 0);

    // Creation de l'affichage de l'argent du joueur
    out << "Money : " << player.getMoney();
    sf::Text textMoney;
    textMoney.setFont(font);
    textMoney.setCharacterSize(24);
    textMoney.setString(out.str());
    textMoney.setColor(sf::Color::White);
    textMoney.setPosition(10, 0);

    // Creation du texte pour les vies du joueur
    std::ostringstream out2;
    out2 << "LIFE : " << player.getLife();
    sf::Text textLife;
    textLife.setFont(font);
    textLife.setCharacterSize(22);
    textLife.setString(out2.str());
    textLife.setColor(sf::Color::White);
    textLife.setPosition(10, 24);


    // Boucle d'affichage
     sf::Event event;
    while(window.isOpen())
    {

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed :
                    window.close();
                    break;
                case sf::Event::KeyReleased :
                {
                    if(event.key.code == sf::Keyboard::Space) // Le joueur lance la vague
                    {
                        state = Playing;

                    }
                    if(event.key.code == sf::Keyboard::M) // Affichage/Fermeture de la selection des towers
                    {
                        if(state == Waiting)
                            state = Menu;
                        else if(state == Menu)
                            state = Waiting;
                    }
                    break;
                }
                case sf::Event::MouseButtonReleased :
                {
                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        if(state == Menu) // Menu de selection des tours
                        {
                            chosenOne = event.mouseButton.x  / 256 + event.mouseButton.y / 130;
                            if( !(player.getTowerTypes()[chosenOne]->getCost() > player.getMoney()) )
                            {
                                state = Buying;
                            }
                        }
                        else if(state == Buying) // Choix de l'emplacement de la tour
                        {
                            int x = event.mouseButton.x / 32;
                            int y = event.mouseButton.y / 32;
                            if(player.checkSlot(x, y)) // Si l'emplacement est valide (ni chemin ni tour)
                            {
                                player.buyTower(x, y, chosenOne);
                                std::ostringstream temp;
                                temp << player.getMoney();
                                textMoney.setString(temp.str());
                                state = Waiting;
                            }
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }

        window.clear();


        if(state == Playing) // Vague en cours
        {
            // Affichage de la grille, de l'argent et des vies du joueur
            window.draw(grid);
            window.draw(textMoney);
            window.draw(textLife);

            // Demande de faire apparaitre un monstre puis recuperation de la liste des monstres en jeu
            level.spawnMonster();
            monsters = level.getMonsters();

            for(unsigned int i=0; i < monsters.size(); i++)
            {
                if(level.testCollision(monsters[i])) // Fonction qui determine la direction que doit suivre le monstre
                {
                    // On deplace le monstre et on met a jour sa barre de vie puis on l'affiche
                    monsters[i]->move(monsters[i]->getVelocity().x,monsters[i]->getVelocity().y);
                    monsters[i]->update();
                    window.draw(*monsters[i]);
                }
                else // Indique de le monstre a atteint la base du joueur
                {
                    if(player.loseLife()) // Test si le joueur meurt
                    {
                        state = GameOver;
                        level.gameOver();
                    }
                    // On met a jour la vie du joueur
                    std::ostringstream temp2;
                    temp2 << "LIFE : " << player.getLife();
                    textLife.setString(temp2.str());
                }
            }

            // Recuperation de la liste des tours en jeu
            towers = player.getTowers();
            for(unsigned int i=0; i < towers.size(); i++)
            {
                // Affichage des tours
                window.draw(*towers[i]);
                for(unsigned int j=0; j < monsters.size() && !hasShot; j++)
                {
                    float xTarget = monsters[j]->getPos().x + 16.f;
                    float yTarget = monsters[j]->getPos().y + 16.f;
                    if(towers[i]->isInRange(xTarget, yTarget))
                    {
                        towers[i]->fireShot(monsters[j]);
                        hasShot = true;
                    }
                }
                /*if(!hasShot)
                {
                    towers[i]->coolDown();
                }*/
                hasShot = false;
                towers[i]->updateShots();
                shots = towers[i]->getShots();
                for(unsigned int k=0; k < shots.size(); k++)
                {
                    sf::FloatRect shotRect = shots[k]->getRect();
                    for(unsigned int h=0; h < monsters.size() && !collision; h++)
                    {
                        sf::FloatRect mobRect = monsters[h]->getRect();
                        if(shotRect.intersects(mobRect))
                        {
                            collision = true;
                            if(monsters[h]->takeDamage(shots[k]->getDamage()))
                            {
                                player.earnMoney(monsters[h]->getReward());
                                std::ostringstream newOut;
                                newOut << "Money : " << player.getMoney();
                                textMoney.setString(newOut.str());
                                monsters[h]->setDead();
                                level.deleteMonster(monsters[h]);
                            }
                            towers[i]->deleteShot(shots[k]);
                        }
                    }
                    collision = false;
                }
            }
        }
        else if(state == GameOver)
        {
            window.draw(textGameOver);
        }
        else if(state == Waiting) // En attente avant le lancement du jeu
        {
            window.draw(grid);
            towers = player.getTowers();
            for(unsigned int i=0; i < towers.size(); i++)
            {
                window.draw(*towers[i]);
            }
            window.draw(textMoney);
            window.draw(textWaiting);
        }
        else if(state == Menu) // Affichage des descriptions des tours
        {
            window.draw(grid);
            towers = player.getTowers();
            for(unsigned int i=0; i < towers.size(); i++)
            {
                window.draw(*towers[i]);
            }
            towerTypes = player.getTowerTypes();
            for(unsigned int i=0; i<towerTypes.size(); i++)
            {
                sf::Text desc;
                desc.setFont(font);
                desc.setCharacterSize(18);
                desc.setPosition((i%3) * 240.f + 50.f, (i/3) * 110.f + 20.f);
                desc.setString(towerTypes[i]->toString());
                window.draw(desc);
            }
        }
        else if(state == Buying) // Affichage de la grille et des tours pendant le placement de la tour que l'on souhaite acheter
        {
            window.draw(grid);
            towers = player.getTowers();
            for(unsigned int i=0; i < towers.size(); i++)
            {
                window.draw(*towers[i]);
            }
        }

        window.display();
    }

    return 0;
}
