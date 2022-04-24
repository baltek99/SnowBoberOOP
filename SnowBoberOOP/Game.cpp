#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "ConstValues.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <cmath> 
#include "Grid.h"
#include "GridStick.h"
#include "Box.h"
#include <Windows.h>
#include <WinBase.h>

Game::Game() {
    window.create(sf::VideoMode(unsigned int(ConstValues::V_WIDTH), unsigned int(ConstValues::V_HEIGHT)), "SnowBober");
    view = sf::View(sf::Vector2f(window.getSize().x/2.f, window.getSize().y/2.f), sf::Vector2f(ConstValues::V_WIDTH, ConstValues::V_HEIGHT));
    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    font.loadFromFile("assets/cour.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);

    highScores.readHighScores();

    //for (int i = 0; i < highScores.getScores().size(); i++) {
    //    printf("%s \n", highScores.getScores().at(i).toString());
    //}

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
            
            case sf::Event::KeyPressed:
                if (gameState == GameState::GAMEPLAY) {
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Space:
                        player.jump(gameFrame);break;
                    case sf::Keyboard::LControl:
                        player.crouch();break;

                    }break;
                }
            }
        }


        window.clear();
        window.setView(view);

        //gameFrame++;

        std::chrono::milliseconds current_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

        if (current_ms > ms + timestep) {
            gameFrame++;
            updateWorld();
            ms = current_ms;
        }


        renderWorld();

        window.display();


        //std::this_thread::sleep_for(std::chrono::milliseconds(timestep));
    }
}


void Game::updateWorld() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H) && (gameState == GameState::MAIN_MENU || gameState == GameState::GAME_OVER)) {
        gameState = GameState::HIGH_SCORES;
        createHighScoreWorld();
    }
    else if (gameState == GameState::HIGH_SCORES) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)
            || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) {
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
            //                playerName = null;
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

    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

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

    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    highScores.addResult(playerName, result);

    highScores.writeHighScores();

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
    sf::Vector2u size = texturesManager.background.getSize();
    float skalaX = ConstValues::V_WIDTH / float(size.x);
    float skalaY = ConstValues::V_HEIGHT / float(size.y);

    Background background = Background(Position(0, 0), Visual(texturesManager.gameOver, skalaX, skalaY), 0);
    backgrounds.push_back(background);
}

void Game::createHighScoreWorld() {
    resetWorld();

    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
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

    
    for (unsigned int i = 0; i < obstacles.size(); i++) {
    
        if (player.isImmortal()) {
            player.updateImmortal();
            return;
        }

        /*
        sf::RectangleShape rsh;
        //rsh.setTextureRect(sf::IntRect(player.getVisual().getSprite().getGlobalBounds()));
        rsh.setOutlineColor(sf::Color::Red);
        rsh.setSize(sf::Vector2f(player.getVisual().getSprite().getLocalBounds().width * player.getVisual().getScaleX(),
            player.getVisual().getSprite().getLocalBounds().height * player.getVisual().getScaleY()));
        rsh.setOrigin(rsh.getSize().x / 2, rsh.getSize().y / 2);
        rsh.setRotation(player.getVisual().getRotation());
        rsh.setPosition(player.getPosition().getX() + rsh.getSize().x / 2, player.getPosition().getY() + rsh.getSize().y / 2);
        
       
        

        sf::RectangleShape rsh2;
        //rsh2.setTextureRect(sf::IntRect(obs_p->getVisual().getSprite().getGlobalBounds()));
        rsh2.setOutlineColor(sf::Color::Red);
        rsh2.setPosition(obs_p->getPosition().getX(), obs_p->getPosition().getY());
        rsh2.setSize(sf::Vector2f(obs_p->getVisual().getSprite().getGlobalBounds().width, obs_p->getVisual().getSprite().getGlobalBounds().height));
        
        
        window.draw(rsh);
        window.draw(rsh2);
*/ 
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
        /*if (obstacles.at(i)->getObstacleType() == ObstacleType::RAIL) {
            Rail* rail = (Rail*)(obs_p);
            collisionFlag = getOffRail(*rail);
        }*/

        
        if (collisionFlag) player.collide(obs_p);
    }
}

CollisionType Game::intersects(Player player, Obstacle* obstacle) { 

    CollisionInfo playerInfo = player.getCollisionInfo();
    CollisionInfo obstacleInfo = obstacle->getCollisionInfo();
    if (obstacle->getObstacleType() == ObstacleType::RAIL && obstacleInfo.rectangle.height < 1.f) {
        //printf("NONE &i", obstacleInfo.rectangle.height);
        return CollisionType::NONE;
    }
    //playerInfo.rectangle.left = player.getPosition().getX();
    //playerInfo.rectangle.top = player.getPosition().getY();
    //playerInfo.rectangle.width = player.getVisual().getSprite().getGlobalBounds().width;
   // playerInfo.rectangle.height = player.getVisual().getSprite().getGlobalBounds().height;   
    
    sf::RectangleShape rsh;
    rsh.setTextureRect(sf::IntRect(player.getVisual().getSprite().getGlobalBounds()));
    rsh.setOutlineColor(sf::Color::Red);
    rsh.setSize(sf::Vector2f(player.getVisual().getSprite().getLocalBounds().width * player.getVisual().getScaleX(),
        player.getVisual().getSprite().getLocalBounds().height * player.getVisual().getScaleY()));
    rsh.setOrigin(rsh.getSize().x / 2, rsh.getSize().y / 2);
    rsh.setRotation(player.getVisual().getRotation());
    rsh.setPosition(player.getPosition().getX() + rsh.getSize().x / 2, player.getPosition().getY() + rsh.getSize().y / 2);

    playerInfo.rectangle = sf::IntRect(rsh.getGlobalBounds());

    obstacleInfo.rectangle.left = obstacle->getPosition().getX();
    obstacleInfo.rectangle.top = obstacle->getPosition().getY() + 30;
    obstacleInfo.rectangle.width = obstacle->getVisual().getSprite().getGlobalBounds().width;
    obstacleInfo.rectangle.height = obstacle->getVisual().getSprite().getGlobalBounds().height;

    /*sf::RectangleShape rsh2;
    //rsh2.setTextureRect(sf::IntRect(obs_p->getVisual().getSprite().getGlobalBounds()));
    rsh2.setOutlineColor(sf::Color::Red);
    rsh2.setPosition(obstacle->getPosition().getX(), obstacle->getPosition().getY());
    rsh2.setSize(sf::Vector2f(obstacle->getVisual().getSprite().getGlobalBounds().width, obstacle->getVisual().getSprite().getGlobalBounds().height));

    obstacleInfo.rectangle = sf::IntRect(rsh2.getGlobalBounds());*/

    //intersects(rsh.getGlobalBounds(), rsh.getRotation(), rsh2.getGlobalBounds());

    if (touch(playerInfo.rectangle, obstacleInfo.rectangle)) {
        return CollisionType::TOUCH;
    }
    if (playerInfo.rectangle.intersects(obstacleInfo.rectangle)) {
        return CollisionType::INTERSECT;
    }

    return CollisionType::NONE;
}

bool Game::intersects(const sf::FloatRect& s, float rotation, const sf::FloatRect& r) {
    /*sf::FloatRect fr1 = sf::FloatRect(s);
    sf::FloatRect fr2 = sf::FloatRect(r);

    float matrix[3][3]{
        {cos(rotation), -sin(rotation), 0},
        {sin(rotation), cos(rotation), 0},
        {0, 0, 1}
    }; 
    

    float p1[3]{ s.left, s.top, 1 };
    float p2[3]{ s.left + s.width, s.top, 1 };

    float wektor[3][1] { p2[0] - p1[0], p2[1] - p1[1], 0 };

    float result[3][3]{ {0 ,0 ,0} , {0,0,0} , {0,0,0} };

    float matrix[2][2]{
        {cos(rotation), -sin(rotation)},
        {sin(rotation), cos(rotation)}
    };
    float p1[2]{ s.left + s.width/2, s.top };
    float p2[2]{ s.left + s.width, s.top };

    float wektor[2][1]{ p2[0] - p1[0], p2[1] - p1[1] };

    float result[2][2]{ {0 ,0 } , {0,0} };
    int r1 = 2;
    int c2 = 3;
    int c1 = 1;

    for (int i = 0; i < r1; ++i)
        for (int j = 0; j < c2; ++j)
            for (int k = 0; k < c1; ++k)
            {
                result[i][j] += wektor[i][k] * matrix[k][j];
            }

    printf("Pkt1 %f, %f \n", p1[0], p1[1]);
    printf("Pkt2 %f, %f \n", p2[0], p2[1]);
    printf("Macierz \n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%f ", result[i][j]);
        }
        printf("\n");
    }*/
    return true;
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