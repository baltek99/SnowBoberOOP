#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "ConstValues.h"
#include <iostream>

Game::Game() {
    window.create(sf::VideoMode(ConstValues::V_WIDTH, ConstValues::V_HEIGHT), "SnowBober");
    view = sf::View(sf::Vector2f(window.getSize().x/2.f, window.getSize().y/2.f), sf::Vector2f(ConstValues::V_WIDTH, ConstValues::V_HEIGHT));

    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    gameFrame = 0;
    obstacleFrame = 0;
    obstacleSpawnRate = 300;
    currentObstacleSpeed = -3;
    gameState = GameState::MAIN_MENU;
    createMainMenuWorld();
}

Game::~Game() {}

void Game::gameLoop() {

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                resizeView(window, view);
                break;
            }
        }

        window.clear();
        window.setView(view);
        //render part

        drawStart();

        window.display();
    }
}

void Game::createMainMenuWorld() {
    printf("Create Main Menu \n");
    resetWorld();
    sf::Vector2u size = texturesManager.start.getSize();
    float skalaX = float(ConstValues::V_WIDTH) / float(size.x);
    float skalaY = float(ConstValues::V_HEIGHT) / float(size.y);

    Background background = Background(Position(0, ConstValues::V_HEIGHT), Visual(texturesManager.start, skalaX, skalaY), 0);
    backgrounds.push_back(background);
    playerName = "";
}

void Game::createGameWorld(std::string playerName_) {
    resetWorld();
    Background background1 = Background(Position(0, ConstValues::V_HEIGHT), Visual(texturesManager.background, ConstValues::V_WIDTH, ConstValues::V_HEIGHT), -2);
    Background background2 = Background(Position(ConstValues::V_WIDTH, ConstValues::V_HEIGHT), Visual(texturesManager.background, ConstValues::V_WIDTH, ConstValues::V_HEIGHT), -2);
    backgrounds.push_back(background1);
    backgrounds.push_back(background2);
    player = Player(Position(ConstValues::BOBER_DEFAULT_POSITION_X, ConstValues::BOBER_DEFAULT_POSITION_Y),
        Visual(texturesManager.boberStand, ConstValues::BOBER_DEFAULT_WIDTH, ConstValues::BOBER_DEFAULT_HEIGHT), playerName_);
}

void Game::createGameOverWorld(int score) {
    resetWorld();
    result = score;
    highScores.addResult(playerName, result);

    /*
    TODO highscores writing
    try {
        FileWriter writer = new FileWriter(highScoresPath);
        gson.toJson(highScores, writer);
        writer.flush();
        writer.close();
    }
    catch (IOException e) {
        System.out.println("HighScores object serialization failed!");
        e.printStackTrace();
    }*/

    Background background = Background(Position(0, ConstValues::V_HEIGHT), Visual(texturesManager.gameOver, ConstValues::V_WIDTH, ConstValues::V_HEIGHT), 0);
    backgrounds.push_back(background);
}

void Game::createHighScoreWorld() {
    resetWorld();
}

void Game::resetWorld() {
    gameFrame = 0;
    obstacleFrame = 0;
    obstacleSpawnRate = 300;
    currentObstacleSpeed = -3;
    //player = null;
    obstacles.clear();
    scorePoints.clear();
    backgrounds.clear();
}

void Game::drawHighScores() {
    //TODO
}

void Game::drawStart() {
    //printf("Draw Start \n");

    for (Background background : backgrounds) {
        background.render(window);
    }
}

void Game::drawEnd() {}

void Game::drawGame() {}

void Game::move(long gameFrame) {}

void Game::moveEntity(IMovable& entity, long gameFrame) {}

void Game::detectCollisions() {}

CollisionType Game::intersects(Player player, Obstacle* obstacle) { return CollisionType::NONE; }

bool Game::touch(const sf::IntRect& s, const sf::IntRect& r) { return false; }

bool Game::getOffRail(const Rail& rail) { return false; }

void Game::generateObstacle() {}

void Game::createGrid() {}

void Game::createRail() {}

void Game::createBox() {}

void Game::createScorePoint(int extra) {}

void Game::detectInput(long gameFrame) {}

void Game::clearObstacles() {}

void Game::resizeView(sf::RenderWindow& window_, sf::View& view_) {
    float wx = float(window_.getSize().x);
    float wy = float(window_.getSize().y);
    float aspectRatio =  wx / wy;
    float originalRatio = float(ConstValues::V_WIDTH) / float(ConstValues::V_HEIGHT);


    if (aspectRatio > originalRatio) {
        float heightRatio = wy / float(ConstValues::V_HEIGHT);
        float expectedWidth = float(ConstValues::V_WIDTH) * heightRatio;
        float widthDiff = wx - expectedWidth;

        printf("Wymiary : ratio: %f, exW %f curW %f diff %f\n", aspectRatio, expectedWidth, wx, widthDiff);

        view_.setViewport(sf::FloatRect((widthDiff / 4.f) / wx, 0.f, (1.f - (widthDiff / 2.f) / wx), 1.f));

        std::cout << view_.getViewport().left;
    }
    else if (aspectRatio < originalRatio) {
        float widthRatio = wx / float(ConstValues::V_WIDTH);
        float expectedHeight = float(ConstValues::V_HEIGHT) * widthRatio;
        float heightDiff = wy - expectedHeight;

        view_.setViewport(sf::FloatRect(0.f, (heightDiff / 4.f) / wy, 1.f, 1.f - (heightDiff / 2.f) / wy));
    }

}