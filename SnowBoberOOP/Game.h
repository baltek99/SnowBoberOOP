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
#include "TextBox.h"

class Game
{
public:
     sf::RenderWindow window;
     sf::View view;
     sf::Text text;
     sf::Font font;
     TextBox textBox;

private:
     TexturesManager texturesManager;

     GameState gameState;

     Player player;
     std::vector<std::unique_ptr<Obstacle>> obstacles;
     std::vector<ScorePoint> scorePoints;
     std::vector<Background> backgrounds;

     HighScores highScores;
     std::string highScoresPath = "highscores.json";

     long gameFrame;
     int obstacleFrame;
     int obstacleSpawnRate;
     int currentObstacleSpeed;
     std::string playerName;
     int result;
public :
	Game();

	~Game();

    void updateWorld();

    void renderWorld();

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

    bool intersects(const sf::FloatRect& s, float rotation, const sf::FloatRect& r);

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

