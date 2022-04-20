#include "TexturesManager.h"

TexturesManager::TexturesManager() {
    background.loadFromFile("assets/background.jpg");
    start.loadFromFile("assets/start.jpg");
    gameOver.loadFromFile("assets/game-over.jpg");
    highScores.loadFromFile("assets/start.jpg");
    boberStand.loadFromFile("assets/bober-stand.png");
    boberCrouch.loadFromFile("assets/bober-luzny.png");
    boberJump.loadFromFile("assets/bober-jump.png");
    boberFlip.loadFromFile("assets/bober-flip.png");
    boberSlide.loadFromFile("assets/bober-rail.png");
    box.loadFromFile("assets/box.png");
    rail.loadFromFile("assets/rail.png");
    pipe.loadFromFile("assets/grubas.png");
    grid.loadFromFile("assets/grid.png");
    gridStick.loadFromFile("assets/grid-stick.png");
    heart.loadFromFile("assets/heart.png");
}
