#pragma once


// Number of cells on the X and Y axis
constexpr unsigned int NUM_OF_CELLS_X = 48;
constexpr unsigned int NUM_OF_CELLS_Y = 27;

// Size of the cell
constexpr unsigned int CELL_SIZE = 20;

// Movement speeds
constexpr unsigned int ARROW_SPEED = 3;
constexpr int TOWER_ROTATION_SPEED = 3;
constexpr unsigned int MIN_ENEMY_MOVE_TIME = 220;
constexpr unsigned int MAX_ENEMY_MOVE_TIME = 380;

// Font properties
static const char* DEFAULT_FONT_PATH = "res/fonts/arial.ttf";

// Time before next wave spawns
constexpr double WAVE_SPAWN_TIME = MAX_ENEMY_MOVE_TIME * 2.5;

// Time before tower can shoot again (ms)
constexpr double TOWER_SHOOT_COOLDOWN_TIME = 75;

// Characters that can't be in a filename
constexpr const char* NON_FILENAME_CHARACTERS = "[/\\\\:*?\"<>|.]";
