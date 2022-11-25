#ifndef GAME_H
#define GAME_H

#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>







#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
    Clase that acts as a game engine

*/

class Game
{
public:
    //constructor / destuktor
    Game();
    ~Game();
    //Accessors
    const bool running() const;
    const bool getEndGame() const;
   

    //Functions
    void spawnEnemy();

    void pollEvents();
    void updateMousePositions();
    void updateText();
    void updateEnemies();
    void update();
    void pyScore();

    void renderText(sf::RenderTarget & target);
    void renderEnemies(sf::RenderTarget & target);
    void renderBackground(sf::RenderTarget & target);
    
    void render();



 

    

private:
    //Variables
    //window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;

    //mous positin
    sf::Vector2i mousPoswindow;
    sf::Vector2f mosePosView;

    //Resources
    sf::Font font;
    sf::Texture background;
    sf::Texture cicel;
    sf::Image curser;
    
    
    //Sounds
    sf::Music music;
    sf::Music buble;

    //Text
    sf::Text uiText;

    //Game logic
    bool endgame;
    bool isFocus;
    unsigned points;
    int highscore;
    int Health;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    bool mouseHeld;
   

    //game object 
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;
    sf::RectangleShape backgroundrec;


    //private functions
    void initializeVariables();
    void initWindow();
    void initTexture();
    void initSound();
    void initFonts();
    void initText();
    void initCourser();
    void initEnemies();

};

#endif