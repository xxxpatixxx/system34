#include "Game.h"


//private functions
void Game::initializeVariables()
{
    this->window = nullptr;
    //Game logic
    int points;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    this->points = 0;
    this->enemySpawnTimerMax = 40.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 10;
    this->mouseHeld = false;
    this->Health = 5;
    this->endgame = false;
    this->isFocus = true;

}

void Game::initWindow()
{   
    this->videoMode.height = 480 * 2;
    this->videoMode.width = 640 * 2;

    this->window = new sf::RenderWindow(this->videoMode, "system34", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);

    

}

void Game::initEnemies()
{
    this->enemy.setPosition(10.0f,10.0f);
    this->enemy.setSize(sf::Vector2f(100.0f, 100.0f));
    //this->enemy.setScale(sf::Vector2f(0.5f,0.5f));
    //this->enemy.setOutlineColor(sf::Color::Green);
    //this->enemy.setOutlineThickness(1.f); 
    //this->enemy.setOrigin(50.0f,50.0f);
}

void Game::initFonts ()
{
    if(!this->font.loadFromFile("Fonts/Comic_Sans_MS.ttf"))
    {
        std::cout << "Error: Faild to load Font" << std::endl;
    }
}
void Game::initTexture ()
{
    if(!this->background.loadFromFile("images/Back.png"))
    {
        std::cout << "Error: Faild to load Texture background" << std::endl;
    }

    if(!this->cicel.loadFromFile("images/circel.png"))
    {
        std::cout << "Error: Faild to load Texture : circel" << std::endl;
    }


}
void Game::initSound ()
{
    if (!this->music.openFromFile("sund/popcorm.wav"))
    {
        std::cout << "Error: Faild to load Sound : music" << std::endl;
    }
    music.play();
    music.setVolume (10);
    music.setLoop(true);
}

void Game::initText ()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(30);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}


//constructur /destruct
Game::Game()
{
    this->initializeVariables();
    this->initWindow();

    this->initFonts();
    this->initTexture();
    this->initSound();
    this->initText();
    
    this->initEnemies();
}

Game::~Game()
{
    delete this->window;
}

//Accessors

const bool Game::running() const
{
    return this->window->isOpen();
}

const bool Game::getEndGame() const
{
    return this->endgame;
}



//functions

void Game::spawnEnemy()
{
   this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f
   ); 

    //Randomize enemy 
    int type = rand() % 5;

    switch(type)
    {
        
    case 0:
        this->enemy.setFillColor(sf::Color::Magenta);
        this->enemy.setSize(sf::Vector2f(50.0f, 50.0f));
        break;
    case 1:
        this->enemy.setFillColor(sf::Color::Blue);
        this->enemy.setSize(sf::Vector2f(70.0f, 70.0f));
        break;
    case 2:
        this->enemy.setFillColor(sf::Color::Yellow);
        this->enemy.setSize(sf::Vector2f(90.0f, 90.0f));
        break;
    case 3:
        this->enemy.setSize(sf::Vector2f(110.0f, 110.0f));
        this->enemy.setFillColor(sf::Color::Cyan);
        
        break;
    case 4:
        this->enemy.setSize(sf::Vector2f(130.0f, 130.0f));
        this->enemy.setFillColor(sf::Color::Green);
        break;

    default:
    
        this->enemy.setSize(sf::Vector2f(210.0f, 210.0f));
        this->enemy.setFillColor(sf::Color::Red);
        break;


    }


   this->enemy.setTexture(&this->cicel);

   this->enemies.push_back(this->enemy);
}

void Game::pollEvents()
{
     //event polling
    while(this->window->pollEvent(this->ev))
        {
            switch(this->ev.type)
            {
                case sf::Event::Closed:
                    this->window->close();
                    break;
                case sf::Event::KeyPressed:
                    if(this->ev.key.code == sf::Keyboard::Escape)
                        this->window->close();
                        break;
                case sf::Event::LostFocus:
                    this->isFocus = false;

                    music.pause();


                    break;
                case sf::Event::GainedFocus:
                    this->isFocus = true;
                    music.play();
                    break;
            }
        }
}

void Game::updateMousePositions()
{
    this->mousPoswindow = sf::Mouse::getPosition(*this->window);
    this->mosePosView = this->window->mapPixelToCoords(this->mousPoswindow);
}

void Game::updateText()
{
    std::stringstream ss;

    ss << "points: " << this->points<< std::endl << "Health: " << this->Health;

    this->uiText.setString(ss.str());

}


void Game::update()
{
    this->pollEvents();

    if(this->endgame == false && isFocus)
        
    {
        this->updateMousePositions();

        this->updateText();

        this->updateEnemies();
    }

    if(this->Health <= 0)
    {
        this->endgame = true;
    }

}

void Game::updateEnemies()
{
    if( this->enemies.size() < this->maxEnemies)
    {
       if(this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
        {
            this->enemySpawnTimer += 1.f;
        }
    }

    for(int i = 0; i < this->enemies.size(); i++)
    {
        bool deleted = false;

        this->enemies[i].move(0.f,4.f);

        if(this->enemies[i].getPosition().y > this->window->getSize().y)
        {
             this->enemies.erase(this->enemies.begin() + i);

             this->Health -= 1;
             //std::cout << "Health: " << this->Health << std::endl;
        }

        if(this->enemies[i].getPosition().x > this->window->getSize().x - 100)
        {
            this->enemies.erase(this->enemies.begin() + i);
        }

         if(this->enemies[i].getPosition().x < 100)
        {
            this->enemies.erase(this->enemies.begin() + i);
        }
   

    }
    

     if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(this->mouseHeld == false)
        {
            this->mouseHeld = true;
            bool deleted = false;
            for(size_t i = 0; i < this->enemies.size() && deleted == false; i++)
            {
                 if(this->enemies[i].getGlobalBounds().contains(this->mosePosView))
                {
                    

                    if(this->enemies[i].getFillColor()== sf::Color::Magenta)
                    {
                        this->points += 10.f;
                    }    
                    else  if(this->enemies[i].getFillColor()== sf::Color::Blue)  
                    {
                        this->points += 7.f;
                    }
                    else  if(this->enemies[i].getFillColor()== sf::Color::Yellow) 
                    {
                        this->points += 5.f;
                    }
                    else  if(this->enemies[i].getFillColor()== sf::Color::Cyan) 
                    {
                        this->points += 3.f;
                    }
                    else  if(this->enemies[i].getFillColor()== sf::Color::Green)
                    {
                        this->points += 1.f;
                    } 

                    //std::cout << "points: " << this->points << std::endl;

                    deleted =true;
                    this->enemies.erase(this->enemies.begin() + i);
                }

            }
        }

       
    }
    else
    {
        this->mouseHeld = false;
    }

  

    

}

void Game::renderText(sf::RenderTarget & target)
{
    target.draw(this->uiText);
}


void Game::renderEnemies(sf::RenderTarget & target)
{
     for(auto &e : this->enemies)
    {
        target.draw(e);
    }
}

void Game::renderBackground(sf::RenderTarget & target)
{
    this->backgroundrec.setPosition(0,0);
    this->backgroundrec.setSize(sf::Vector2f(videoMode.width,videoMode.height));
    this->backgroundrec.setTexture(&this->background);
    this->backgroundrec.setFillColor(sf::Color( 55, 55, 55, 200 ));
    target.draw(this->backgroundrec);
}

void Game::render()//render
{
    this->window->clear();

    
    this->renderBackground(*this->window);
    
    
    this->renderEnemies(*this->window);

    this->renderText(*this->window);

    this->window->display();
}

void Game::pyScore()
{
    try {
        int Score;
        Score = this->points;

    
    
        std::string cmd = "Python3 scoresend.py " + std::to_string(Score);
        int res = std::system(cmd.c_str());
        std::cout << res << std::endl;
      
    }
    catch (int num) {
        throw ("install python");
    }

    
    
}


