#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <WinBase.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <cmath> 
#include "Game.h"
#include "ConstValues.h"
#include "Grid.h"
#include "GridStick.h"
#include "Box.h"
#include "RotatedRectangle.h"

Game::Game() {
    window.create(sf::VideoMode(unsigned int(ConstValues::V_WIDTH), unsigned int(ConstValues::V_HEIGHT)), "SnowBober");
    view = sf::View(sf::Vector2f(window.getSize().x/2.f, window.getSize().y/2.f), sf::Vector2f(ConstValues::V_WIDTH, ConstValues::V_HEIGHT));
    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    font.loadFromFile("assets/cour.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);

    textBox = TextBox(25, sf::Color::Red, true);
    textBox.setFont(font);
    textBox.setPosition({300, 450});

    highScores.readHighScores();

    gameMusic.openFromFile("assets/boberMusic.wav");
    gameMusic.setLoop(true);
    gameMusic.setVolume(50);

    srand(time(0));
    gameFrame = 0;
    obstacleFrame = 0;
    obstacleSpawnRate = 300;
    currentObstacleSpeed = -3;
    gameState = GameState::MAIN_MENU;
    createMainMenuWorld();
}

Game::~Game() {}

void Game::gameLoop() {
    int fps = 100;
    std::chrono::milliseconds timestep = std::chrono::milliseconds(1000/fps);

    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

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
            case sf::Event::TextEntered:
                if (gameState == GameState::MAIN_MENU) {
                    textBox.typedOn(event);
                }
            case sf::Event::KeyPressed:
                if (gameState == GameState::GAMEPLAY) {
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Space:
                        player.jump(gameFrame);break;
                    case sf::Keyboard::LControl:
                        player.crouch();break;
                    case sf::Keyboard::Escape:
                        gameState = GameState::PAUSE;
                        gameMusic.pause();
                        break;
                    }break;
                }
                else if (gameState == GameState::MAIN_MENU || gameState == GameState::GAME_OVER) {
                    if (event.key.code == sf::Keyboard::Tab) {
                        gameState = GameState::HIGH_SCORES;
                        createHighScoreWorld();
                    }
                }
                else if (gameState == GameState::HIGH_SCORES) {
                    if (event.key.code == sf::Keyboard::Tab) {
                        gameState = GameState::MAIN_MENU;
                        createMainMenuWorld();
                    }
                }
                else if (gameState == GameState::PAUSE) {
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Escape:
                        gameState = GameState::MAIN_MENU;
                        createMainMenuWorld();
                        gameMusic.stop();
                        break;
                    case sf::Keyboard::Enter:
                        gameMusic.play();
                        gameState = GameState::GAMEPLAY;
                        break;
                    }break;
                }
            }
        }

        window.clear();
        window.setView(view);

        std::chrono::milliseconds current_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

        if (current_ms > ms + timestep && gameState != GameState::PAUSE) {
            gameFrame++;
            updateWorld();
            ms = current_ms;
        }

        renderWorld();

        window.display();
    }
}


void Game::updateWorld() {
   if (gameState == GameState::MAIN_MENU) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
            playerName = textBox.getText();
        }
        if (playerName != "") {
            gameState = GameState::GAMEPLAY;
            createGameWorld(playerName);
        }

    }
    else if (gameState == GameState::GAMEPLAY) {
        detectInput(gameFrame);

        move(gameFrame);

        generateObstacle();

        detectCollisions();

        clearObstacles();

        if (player.getLives().size() == 0) {
            gameState = GameState::GAME_OVER;
            createGameOverWorld(player.getScore());
        }
    }
    else if (gameState == GameState::GAME_OVER) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            gameState = GameState::GAMEPLAY;
            createGameWorld(playerName);
        }
    }
}

void Game::renderWorld() {
    switch (gameState) {
        case GameState::HIGH_SCORES: drawHighScores(); break;
        case GameState::MAIN_MENU: drawStart(); break;
        case GameState::GAMEPLAY: drawGame(); break;
        case GameState::GAME_OVER: drawEnd(); break;
        case GameState::PAUSE: drawGame(); break;
    }
}

void Game::createMainMenuWorld() {
    resetWorld();
    textBox.clear();

    sf::Vector2u size = texturesManager.start.getSize();
    float scaleX = ConstValues::V_WIDTH / float(size.x);
    float scaleY = ConstValues::V_HEIGHT / float(size.y);

    Background background = Background(Position(0, 0), Visual(texturesManager.start, scaleX, scaleY), 0);
    backgrounds.push_back(background);
    playerName = "";
}

void Game::createGameWorld(std::string playerName_) {
    resetWorld();

    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

    sf::Vector2u size = texturesManager.background.getSize();
    float scaleX = ConstValues::V_WIDTH / float(size.x);
    float scaleY = ConstValues::V_HEIGHT / float(size.y);

    Background background1 = Background(Position(0, 0), Visual(texturesManager.background, scaleX, scaleY), -2);
    Background background2 = Background(Position(ConstValues::V_WIDTH, 0), Visual(texturesManager.background, scaleX, scaleY), -2);
    backgrounds.push_back(background1);
    backgrounds.push_back(background2);
    player = Player(Position(ConstValues::BOBER_DEFAULT_POSITION_X, ConstValues::BOBER_DEFAULT_POSITION_Y),
        Visual(texturesManager.boberStand, ConstValues::BOBER_DEFAULT_WIDTH, ConstValues::BOBER_DEFAULT_HEIGHT), playerName_);

    gameMusic.play();
}

void Game::createGameOverWorld(int score) {
    resetWorld();

    gameMusic.stop();

    result = score;

    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    highScores.addResult(playerName, result);

    highScores.writeHighScores();

    sf::Vector2u size = texturesManager.background.getSize();
    float scaleX = ConstValues::V_WIDTH / float(size.x);
    float scaleY = ConstValues::V_HEIGHT / float(size.y);

    Background background = Background(Position(0, 0), Visual(texturesManager.gameOver, scaleX, scaleY), 0);
    backgrounds.push_back(background);
}

void Game::createHighScoreWorld() {
    resetWorld();

    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

    sf::Vector2u size = texturesManager.highScores.getSize();
    float scaleX = ConstValues::V_WIDTH / float(size.x);
    float scaleY = ConstValues::V_HEIGHT / float(size.y);

    Background background = Background(Position(0, 0), Visual(texturesManager.highScores, scaleX, scaleY), 0);
    backgrounds.push_back(background);
}

void Game::resetWorld() {
    gameFrame = 0;
    obstacleFrame = 0;
    obstacleSpawnRate = 300;
    currentObstacleSpeed = -3;
    obstacles.clear();
    scorePoints.clear();
    backgrounds.clear();
}

void Game::drawHighScores() {
    for (Background& background : backgrounds) {
        background.render(window);
    }

    int size = highScores.getScores().size();
    if (size != 0) {
        int inc = ConstValues::V_HEIGHT / size;

        for (int i = size - 1; i >= 0; i--) {
            text.setString(std::to_string(size - i) + ". " + highScores.getScores().at(i).toString());
            text.setPosition(350, ConstValues::V_HEIGHT - (i + 1) * inc);
            window.draw(text);
        }
    }
}

void Game::drawStart() {
    for (Background& background : backgrounds) {
        background.render(window);
    }

    textBox.draw(window);
}

void Game::drawEnd() {
    for (Background& background : backgrounds) {
        background.render(window);
    }
    text.setString("Name: " + playerName + "    Score: " + std::to_string(player.getScore()));
    text.setPosition(300, 500);
    window.draw(text);
}

void Game::drawGame() {
    for (Background& background : backgrounds) {
        background.render(window);
    }

    for (unsigned int i = 0; i < obstacles.size(); i++) {
        if (obstacles.at(i)->getZIndex() == 0) {
            obstacles.at(i)->render(window);
        }
    }

    player.render(window);
    text.setString("Score: " + std::to_string(player.getScore()));
    text.setPosition(ConstValues::SCORE_POSITION_X, ConstValues::SCORE_POSITION_Y);
    window.draw(text);

    for (Life& life : player.getLives()) {
        life.render(window);
    }

    for (unsigned int i = 0; i < obstacles.size(); i++) {
        if (obstacles.at(i)->getZIndex() == 1) {
            obstacles.at(i)->render(window);
        }
    }
}

void Game::move(long gameFrame) {
    for (Background& background : backgrounds) {
        background.fixPosition();
        moveEntity(background, gameFrame);
    }

    moveEntity(player, gameFrame);

    for (unsigned int i = 0; i < obstacles.size(); i++) {
        moveEntity(*obstacles.at(i), gameFrame);
    }

    for (ScorePoint& scorePoint : scorePoints) {
        moveEntity(scorePoint, gameFrame);
    }

    if (gameFrame % ConstValues::NUMBER_OF_FRAMES_TO_INCREMENT == 0) {
        currentObstacleSpeed--;
    }
}

void Game::moveEntity(IMovable& entity, long gameFrame) {
    entity.move(gameFrame);
    entity.speedUp(gameFrame);
}

void Game::detectCollisions() {
    for (unsigned int i = 0; i < scorePoints.size(); i++) {
        CollisionType type = intersects(player, &scorePoints.at(i));
        if (type == CollisionType::NONE) {
            continue;
        }
        player.collide(&scorePoints.at(i));
        scorePoints.erase(scorePoints.begin() + i);
    }

    if (player.isImmortal()) {
        player.updateImmortal();
        return;
    }

    for (unsigned int i = 0; i < obstacles.size(); i++) {
        Obstacle* obs_p = obstacles.at(i).get();
        CollisionType type = intersects(player, obs_p);
        
        bool collisionFlag = true;
        if (player.getPlayerState() == PlayerState::SLIDING) {
            Rail* rail = (Rail*)(obs_p);
            collisionFlag = getOffRail(*rail);
        }
        if (type == CollisionType::NONE) {
            continue;
        }
        
        if (collisionFlag) {
            player.collide(obs_p);
            obs_p->collide(&player);
        }
    }
}

CollisionType Game::intersects(Player player, Obstacle* obstacle) { 

    CollisionInfo playerInfo = player.getCollisionInfo();
    CollisionInfo obstacleInfo = obstacle->getCollisionInfo();
    if (obstacle->getObstacleType() == ObstacleType::RAIL && obstacleInfo.rectangle.height < 1.f) {
        return CollisionType::NONE;
    }

    sf::RectangleShape rsh;
    rsh.setTextureRect(sf::IntRect(player.getVisual().getSprite().getGlobalBounds()));
    rsh.setSize(sf::Vector2f(player.getVisual().getSprite().getLocalBounds().width * player.getVisual().getScaleX(),
        player.getVisual().getSprite().getLocalBounds().height * player.getVisual().getScaleY()));
    rsh.setOrigin(rsh.getSize().x / 2, rsh.getSize().y / 2);
    rsh.setPosition(player.getPosition().getX() + rsh.getSize().x / 2, player.getPosition().getY() + rsh.getSize().y / 2);

    playerInfo.rectangle = sf::IntRect(rsh.getGlobalBounds());

    obstacleInfo.rectangle.left = obstacle->getPosition().getX();
    obstacleInfo.rectangle.top = obstacle->getPosition().getY();
    obstacleInfo.rectangle.width = obstacle->getVisual().getSprite().getGlobalBounds().width;
    obstacleInfo.rectangle.height = obstacle->getVisual().getSprite().getGlobalBounds().height;

    RotatedRectangle playerRect = RotatedRectangle(sf::FloatRect(playerInfo.rectangle), player.getVisual().getRotation());
    RotatedRectangle obstacleRect = RotatedRectangle(sf::FloatRect(obstacleInfo.rectangle), obstacle->getVisual().getRotation());

    if (playerRect.intersects(obstacleRect))
        return CollisionType::INTERSECT;

    return CollisionType::NONE;
}

bool Game::touch(const sf::IntRect& s, const sf::IntRect& r) {
    bool left = s.left == r.left + r.width && s.left + s.width > r.left && s.top < r.top + r.height && s.top + s.height > r.top;
    bool right = s.left < r.left + r.width && s.left + s.width == r.left && s.top < r.top + r.height && s.top + s.height > r.top;
    bool down = s.left < r.left + r.width && s.left + s.width > r.left && s.top == r.top + r.height && s.top + s.height > r.top;
    bool up = s.left < r.left + r.width && s.left + s.width > r.left && s.top < r.top + r.height && s.top + s.height == r.top;

    return left || right || down || up;
}

bool Game::getOffRail(const Rail& rail) {
    int obstacleX = rail.getPosition().getX();
    int playerX = player.getPosition().getX();
    if (obstacleX < playerX && abs(playerX - obstacleX) >= ConstValues::RAIL_AND_BOBER_DIFFERENCE) {
        if (player.getPlayerState() == PlayerState::SLIDING) {
            player.setPlayerState(PlayerState::IDLE);
            player.getPosition().setY(ConstValues::IDLE_RIDE_Y);
            
            player.setVisual(Visual(TexturesManager::boberStand, ConstValues::BOBER_DEFAULT_WIDTH, ConstValues::BOBER_DEFAULT_HEIGHT));
        }
        player.getCollisionInfo().collisionType = CollisionType::NONE;
        
        return false;
    }
    return true;
}

void Game::generateObstacle() {
    obstacleFrame++;
    if (obstacleFrame % ConstValues::NUMBER_OF_FRAMES_TO_INCREMENT == 0) {
        obstacleSpawnRate = obstacleSpawnRate - obstacleSpawnRate / -currentObstacleSpeed;
        obstacleFrame = 1;
    }

    if (obstacleFrame % obstacleSpawnRate == 0) {
        int x = rand() % 1000;

        if (x < 333) {
            createBox();
            createScorePoint(270);
        }
        else if (x < 666) {
            createGrid();
            createScorePoint(500);
        }
        else {
            createRail();
            createScorePoint(500);
        }
    }
}

void Game::createGrid() {
    obstacles.emplace_back(std::make_unique<Grid>(Position(ConstValues::V_WIDTH, ConstValues::GRID_POSITION_Y), currentObstacleSpeed));
    obstacles.emplace_back(std::make_unique<GridStick>(Position(ConstValues::V_WIDTH, ConstValues::GRID_POSITION_Y), currentObstacleSpeed));
}

void Game::createRail() {
    obstacles.emplace_back(std::make_unique<Rail>(Position(ConstValues::V_WIDTH, ConstValues::RAIL_POSITION_Y), currentObstacleSpeed));
}

void Game::createBox() {
    obstacles.emplace_back(std::make_unique<Box>(Position(ConstValues::V_WIDTH, ConstValues::BOX_POSITION_Y), currentObstacleSpeed));
}

void Game::createScorePoint(int extra) {
    scorePoints.emplace_back(ScorePoint(Position(ConstValues::V_WIDTH + extra, ConstValues::SCORE_POINT_POSITION_Y), currentObstacleSpeed));
}

void Game::detectInput(long gameFrame) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        player.moveRight();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        player.moveLeft();
    }
}

void Game::clearObstacles() {
    if (obstacles.size() != 0 && obstacles.front()->getPosition().getX() < -500) {
        obstacles.erase(obstacles.begin());
    }
}

void Game::resizeView(sf::RenderWindow& window_, sf::View& view_) {
    float wx = float(window_.getSize().x);
    float wy = float(window_.getSize().y);
    float aspectRatio =  wx / wy;
    float originalRatio = float(ConstValues::V_WIDTH) / float(ConstValues::V_HEIGHT);

    if (aspectRatio > originalRatio) {
        float heightRatio = wy / float(ConstValues::V_HEIGHT);
        float expectedWidth = float(ConstValues::V_WIDTH) * heightRatio;
        float widthDiff = wx - expectedWidth;

        view_.setViewport(sf::FloatRect((widthDiff / 4.f) / wx, 0.f, (1.f - (widthDiff / 2.f) / wx), 1.f));
    }
    else if (aspectRatio < originalRatio) {
        float widthRatio = wx / float(ConstValues::V_WIDTH);
        float expectedHeight = float(ConstValues::V_HEIGHT) * widthRatio;
        float heightDiff = wy - expectedHeight;

        view_.setViewport(sf::FloatRect(0.f, (heightDiff / 4.f) / wy, 1.f, 1.f - (heightDiff / 2.f) / wy));
    }
}