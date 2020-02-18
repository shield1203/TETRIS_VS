#pragma once
enum GAME_STEP { STEP_MENU, STEP_SINGLE_PLAY, STEP_GAMEOVER, STEP_VERSUS_PLAY, STEP_VERSUS_GAMEOVER, STEP_EXIT };

enum COLOR : unsigned short { DARK, DARK_BLUE, DARK_GREEN, DARK_SKY, DARK_RED, DARK_PURPLE, DARK_YELLOW, DARK_WHITE, 
			GRAY, BLUE, GREEN, SKY, RED, PURPLE, YELLOW, WHITE };

enum KEY { UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, SPACE_BAR = 32, ENTER = 13 };

// SPRITES
enum MENU { TITLE_T1, TITLE_E, TITLE_T2, TITLE_R, TITLE_I, TITLE_S, SELECTOR, MODE_SINGLE_PLAY, MODE_VERSUS_PLAY, MODE_EXIT };

enum MAP { MAP_WIDTH = 10, MAP_HIGH = 24, OVER_LINE  = 2 };

// SOUND
enum SOUDN_BGM : unsigned int { MENU_BGM, GAME_BGM }; // 2

enum SOUND_EFFRCT : unsigned int { SOUND_BUTTON, SOUND_BLOCK, SOUND_DROP_BLOCK, SOUND_CLEAR_LINE, SOUND_GAMEOVER }; // 5