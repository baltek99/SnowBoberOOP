#pragma once

class ConstValues {
public:
    static const int V_WIDTH = 964;
    static const int V_HEIGHT = 540;
    static const int JUMP_FROM_GROUND_Y = 120;
    static const int JUMP_FROM_RAIL_Y = 150;
    static const int IDLE_RIDE_Y = 70;
    static const int SLIDING_ON_RAIL_Y = 110;
    static const int BOBER_DEFAULT_POSITION_X = 100;
    static const int BOBER_DEFAULT_POSITION_Y = 70;
    static const int BOBER_CROUCH_POSITION_Y = 105;
    static const int RAIL_AND_BOBER_DIFFERENCE = 260;
    static const int BOBER_MIN_X = 0;
    static const int BOBER_MAX_X = V_WIDTH - 200;

    static const int NUMBER_OF_FRAMES_TO_INCREMENT = 1000;

    // TEXTURES REGION
    static const int BOBER_DEFAULT_WIDTH = 180;
    static const int BOBER_DEFAULT_HEIGHT = 215;
    static const int BOBER_ON_RAIL_WIDTH = 180;
    static const int BOBER_ON_RAIL_HEIGHT = 215;
    static const int BOBER_IN_JUMP_WIDTH = 180;
    static const int BOBER_IN_JUMP_HEIGHT = 160;
    static const int BOBER_CROUCH_WIDTH = 231;
    static const int BOBER_CROUCH_HEIGHT = 134;

    static const int BOX_WIDTH = 70;
    static const int BOX_HEIGHT = 70;
    static const int RAIL_WIDTH = 300;
    static const int RAIL_HEIGHT = 70;
    static const int GRID_WIDTH = 180;
    static const int GRID_HEIGHT = 280;
    static const int SCORE_WIDTH = 1;
    static const int SCORE_HEIGHT = V_HEIGHT;
    static const int HEART_WIDTH = 50;
    static const int HEART_HEIGHT = 50;

    static const int HEART_POSITION_Y = 450;
    static const int HEART_POSITION_X_1 = V_WIDTH - 250;
    static const int HEART_POSITION_X_2 = V_WIDTH - 180;
    static const int HEART_POSITION_X_3 = V_WIDTH - 110;

    static const int SCORE_POSITION_X = V_WIDTH - 200;
    static const int SCORE_POSITION_Y = 50;
};
