#ifndef TETRIS_STATUS_H
#define TETRIS_STATUS_H
#include "ili9341.h"
#include "tetris_blocks.h"

#define GAME_BOARD_BLOCK_SIZE 			12
#define GAME_BOARD_WIDTH  				(GAME_BOARD_BLOCK_SIZE +1)*10
#define GAME_BOARD_HEIGHT 				(GAME_BOARD_BLOCK_SIZE +1)*20


#define GAME_BOARD_START_X				30
#define GAME_BOARD_START_Y 				40

#define SCORE_TEXT_X					120
#define SCORE_TEXT_Y					10
#define SCORE_X							180
#define SCORE_Y							10

#define GAME_TIME_X						60
#define GAME_TIME_Y 					10
#define GAME_TIME_TEXT_X				20
#define GAME_TIME_TEXT_Y				10

#define NEXT_BLOCK_TEXT_POS_X				180
#define NEXT_BLOCK_TEXT_POS_Y				100

#define NEXT_BLOCK_POS_X				180
#define NEXT_BLOCK_POS_Y				130

#define DOWN_BUTTON_X					205
#define DOWN_BUTTON_Y					270
#define DOWN_BUTTON_RADIUS				18
#define DOWN_BUTTON_COLOR				COLOR_GRAY_128
#define DOWN_BUTTON_PRESSED_COLOR		COLOR_GREENYELLOW

#define START_BUTTON_X					GAME_BOARD_START_X + GAME_BOARD_WIDTH/4 + 32
#define START_BUTTON_Y					GAME_BOARD_START_Y + GAME_BOARD_HEIGHT/4 + 80
#define START_BUTTON_TEXT_X				GAME_BOARD_START_X + GAME_BOARD_WIDTH/4 + 15
#define START_BUTTON_TEXT_Y				GAME_BOARD_START_Y + GAME_BOARD_HEIGHT/4 + 75
#define START_BUTTON_RADIUS				30
#define START_BUTTON_COLOR_BORDER		COLOR_WHITE
#define START_BUTTON_COLOR				COLOR_RED
#define START_BUTTON_PRESSED_COLOR		COLOR_GREEN

#define DEFAULT_TEXT_COLOR				COLOR_YELLOW
#define DEFAULT_BACKGROUND_COLOR		COLOR_BLACK
#define START_BUTTON_TEXT_COLOR			COLOR_BLACK
#define START_BUTTON_BACKGROUND_COLOR 	COLOR_GREEN
#define NEXT_BLOCK_SIZE					8

#define GAME_OVER_X 					GAME_BOARD_START_X + GAME_BOARD_WIDTH/4
#define GAME_OVER_Y						GAME_BOARD_START_Y + GAME_BOARD_HEIGHT/4
#define GAME_OVER_TEXT_X				GAME_BOARD_START_X + GAME_BOARD_WIDTH/4 + 20
#define GAME_OVER_TEXT_Y				GAME_BOARD_START_Y + GAME_BOARD_HEIGHT/4 + 20
uint16_t boardColor;
uint16_t downButtonColor;
uint16_t startButtonColor;
void tetrisDrawStatus();
void tetrisDrawGameBoard();
void tetrisUpdateScore();
void tetrisUpdateTime(int time);
void tetrisDrawGameOver();
void tetrisDrawNextBlock(tetrisBlockPropertiesTypeDef nb);
void tetrisDrawDownButton(uint16_t x, uint16_t y, uint16_t color);
void tetrisUpdateDownButton(uint16_t color);
void tetrisDrawStartButton(uint16_t x, uint16_t y, uint16_t color);
void tetrisUpdateStartButton(uint16_t color);

#endif
