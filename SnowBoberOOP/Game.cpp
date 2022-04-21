#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "ConstValues.h"
#include <iostream>
#include <thread>
#include <chrono>

Game::Game() {
    window.create(sf::VideoMode(unsigned int(ConstValues::V_WIDTH), unsigned int(ConstValues::V_HEIGHT)), "SnowBober");
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
    int fps = 90;
    int timestep = 1000 / fps;

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
            
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Space:
                    player.jump(gameFrame);break;
                case sf::Keyboard::LControl:
                    player.crouch();break;
                case sf::Keyboard::Right:
                    player.moveRight();break;
                case sf::Keyboard::Left:
                    player.moveLeft();break;
                }break;
            }
        }


        window.clear();
        window.setView(view);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H) && (gameState == GameState::MAIN_MENU || gameState == GameState::GAME_OVER)) {
            gameState = GameState::HIGH_SCORES;
            drawHighScores();
        }
        else if (gameState == GameState::HIGH_SCORES) {
            drawHighScores();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                gameState = GameState::MAIN_MENU;
                createMainMenuWorld();
            }
        }
        else if (gameState == GameState::MAIN_MENU) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                //Gdx.input.getTextInput(this, "Podaj swój nick", "", "Player");
                playerName = "Bartek";
            }
            if (playerName != "") {
                gameState = GameState::GAMEPLAY;
                createGameWorld(playerName);
            }
            else {
                drawStart();
            }
        }
        else if (gameState == GameState::GAMEPLAY) {
            
            //detectInput(gameFrame);
            move(gameFrame);
            /*
            generateObstacle();

            detectCollisions();

            clearObstacles();

            if (player.getLives().size() == 0) {
                gameState = GameState::GAME_OVER;
                createGameOverWorld(player.getScore());
            }
            */
            drawGame();
        }
        else if (gameState == GameState::GAME_OVER) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                //                playerName = null;
                gameState = GameState::GAMEPLAY;
                //                createMainMenuWorld();
                createGameWorld(playerName);
            }
            drawEnd();
        }


        gameFrame++;


        //render part


        window.display();


        std::this_thread::sleep_for(std::chrono::milliseconds(timestep));
    }
}

void Game::createMainMenuWorld() {
    resetWorld();
    sf::Vector2u size = texturesManager.start.getSize();
    float skalaX = ConstValues::V_WIDTH / float(size.x);
    float skalaY = ConstValues::V_HEIGHT / float(size.y);

    Background background = Background(Position(0, 0), Visual(texturesManager.start, skalaX, skalaY), 0);
    backgrounds.push_back(background);
    playerName = "";
}

void Game::createGameWorld(std::string playerName_) {
    resetWorld();
    sf::Vector2u size = texturesManager.background.getSize();
    float skalaX = ConstValues::V_WIDTH / float(size.x);
    float skalaY = ConstValues::V_HEIGHT / float(size.y);

    Background background1 = Background(Position(0, 0), Visual(texturesManager.background, skalaX, skalaY), -2);
    Background background2 = Background(Position(ConstValues::V_WIDTH, 0), Visual(texturesManager.background, skalaX, skalaY), -2);
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

    for (Background& background : backgrounds) {
        background.render(window);
    }
}

void Game::drawEnd() {
    for (Background& background : backgrounds) {
        background.render(window);
    }
}

void Game::drawGame() {

    for (Background& background : backgrounds) {
        background.render(window);
    }

    /*for (Obstacle obstacle : obstacles) {
        if (obstacle.getZIndex() == 0) {
            obstacle.render(window);
        }
    }*/

    for (unsigned int i = 0; i < obstacles.size(); i++) {
        std::unique_ptr<Obstacle> obs_p(&obstacles.at(i));
        if (obs_p->getZIndex() == 0) {
            obs_p->render(window);
        }
    }

    player.render(window);
    //font.draw(batch, "Score: " + player.getScore(), ConstValues.SCORE_POSITION_X, ConstValues.SCORE_POSITION_Y);
    for (Life& life : player.getLives()) {
        life.render(window);
    }

    for (unsigned int i = 0; i < obstacles.size(); i++) {
        std::unique_ptr<Obstacle> obs_p(&obstacles.at(i));
        if (obs_p->getZIndex() == 1) {
            obs_p->render(window);
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
        moveEntity(obstacles.at(i), gameFrame);
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
    if (!player.isImmortal()) {
        for (unsigned int i = 0; i < obstacles.size(); i++) {
            std::unique_ptr<Obstacle> obs_p(&obstacles.at(i));
            CollisionType type = intersects(player, obs_p);
            if (type != CollisionType::NONE) {
                bool collisionFlag = true;
                if (obs_p->getObstacleType() == ObstacleType::RAIL) {
                    Rail* rail = (Rail*)(obs_p.get());
                    collisionFlag = getOffRail(*rail);
                }

                if (collisionFlag) player.collide(obs_p.get());
            }
        }
    }

    for (unsigned int i = 0; i < scorePoints.size(); i++) {
        std::unique_ptr<Obstacle> obs_p(&scorePoints.at(i));
        CollisionType type = intersects(player, obs_p);
        if (type != CollisionType::NONE) {
            player.collide(obs_p.get());
            scorePoints.erase(scorePoints.begin() + i);
        }
    }
}

CollisionType Game::intersects(Player player, std::unique_ptr<Obstacle> & obstacle) { 

    CollisionInfo playerInfo = player.getCollisionInfo();
    CollisionInfo obstacleInfo = obstacle->getCollisionInfo();

    playerInfo.rectangle.left = int(player.getPosition().getX());
    playerInfo.rectangle.top = int(player.getPosition().getY());

    obstacleInfo.rectangle.left = int(obstacle->getPosition().getX());
    obstacleInfo.rectangle.top = int(obstacle->getPosition().getY());

    if (touch(playerInfo.rectangle, obstacleInfo.rectangle)) {
        return CollisionType::TOUCH;
    }
    if (playerInfo.rectangle.intersects(obstacleInfo.rectangle)) {
        return CollisionType::INTERSECT;
    }

    return CollisionType::NONE;
}

bool Game::touch(const sf::IntRect& s, const sf::IntRect& r) {
    bool left = s.left == r.left + r.width && s.left + s.width > r.left && s.top < r.top + r.height && s.top + s.height > r.top;
    bool right = s.left < r.left + r.width && s.left + s.width == r.left && s.top < r.top + r.height && s.top + s.height > r.top;
    bool down = s.left < r.left + r.width && s.left + s.width > r.left && s.top == r.top + r.height && s.top + s.height > r.top;
    bool up = s.left < r.left + r.width && s.left + s.width > r.left && s.top < r.top + r.height && s.top + s.height == r.top;

    return left || right || down || up;
}

bool Game::getOffRail(const Rail& rail) { return false; }

void Game::generateObstacle() {}

void Game::createGrid() {}

void Game::createRail() {}

void Game::createBox() {}

void Game::createScorePoint(int extra) {}

void Game::detectInput(long gameFrame) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        player.jump(gameFrame);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) {
        player.crouch();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        player.moveRight();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        player.moveLeft();
    }
}

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

        view_.setViewport(sf::FloatRect((widthDiff / 4.f) / wx, 0.f, (1.f - (widthDiff / 2.f) / wx), 1.f));
    }
    else if (aspectRatio < originalRatio) {
        float widthRatio = wx / float(ConstValues::V_WIDTH);
        float expectedHeight = float(ConstValues::V_HEIGHT) * widthRatio;
        float heightDiff = wy - expectedHeight;

        view_.setViewport(sf::FloatRect(0.f, (heightDiff / 4.f) / wy, 1.f, 1.f - (heightDiff / 2.f) / wy));
    }

}