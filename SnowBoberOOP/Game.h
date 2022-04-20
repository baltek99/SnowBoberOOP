#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Player.h"
#include "Obstacle.h"
#include "ScorePoint.h"
#include "Background.h"
#include "HighScores.h"
#include "Rail.h"
#include "TexturesManager.h"

class Game
{
public:
     sf::RenderWindow window;
     sf::View view;

private:
     TexturesManager texturesManager;

     GameState gameState;

     Player player;
     std::vector<Obstacle> obstacles;
     std::vector<ScorePoint> scorePoints;
     std::vector<Background> backgrounds;

     HighScores highScores;
     std::string highScoresPath = "highscores.json";
     //Gson gson;

     long gameFrame;
     int obstacleFrame;
     int obstacleSpawnRate;
     int currentObstacleSpeed;
     std::string playerName;
     int result;
public :
	Game();

	~Game();

    void gameLoop();

    void createMainMenuWorld();

    void createGameWorld(std::string playerName_);

    void createGameOverWorld(int score);

    void createHighScoreWorld();

    void resetWorld();

    void drawHighScores();

    void drawStart();

    void drawEnd();

    void drawGame();

    void move(long gameFrame);

    void moveEntity(IMovable &entity, long gameFrame);

    void detectCollisions();

    CollisionType intersects(Player player, Obstacle* obstacle);

    bool touch(const sf::IntRect &s, const sf::IntRect &r);

    bool getOffRail(const Rail &rail);

    void generateObstacle();

    void createGrid();

    void createRail();

    void createBox();

    void createScorePoint(int extra);

    void detectInput(long gameFrame);

    void clearObstacles();

    void resizeView(sf::RenderWindow& window_, sf::View& view_);
};

