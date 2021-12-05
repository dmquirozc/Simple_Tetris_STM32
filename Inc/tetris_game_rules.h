#ifndef TETRIS_GAME_RULES_H
#define TETRIS_GAME_RULES_H

#include "main.h"
#include "tetris_status.h"

#define GAME_BOARD_LIMIT_DOWN   GAME_BOARD_START_Y + GAME_BOARD_HEIGHT
#define GAME_BOARD_LIMIT_RIGHT  GAME_BOARD_START_X + GAME_BOARD_WIDTH
#define GAME_BOARD_LIMIT_LEFT	GAME_BOARD_START_X
#define GAME_BOARD_BLOCKS_ROWS	24
#define GAME_BOARD_BLOCKS_COLS  14

#define GAME_BOARD_BLOCKS_ROWS_OFFSET 2
#define GAME_BOARD_BLOCKS_COLS_OFFSET 2

typedef struct{
	uint8_t gameBoard[GAME_BOARD_BLOCKS_ROWS][GAME_BOARD_BLOCKS_COLS];
	uint8_t gameCompleteRows[20];
	uint16_t gameScore;
	tetrisBlockPropertiesTypeDef gameBlock;
	tetrisBlockPropertiesTypeDef nextGameBlock;
	uint8_t gameOverFlag;
	uint8_t gameOverDrawFlag;
	uint8_t clearRowsFlag;
}tetrisGameSettings;

typedef enum {
	normalScoreLimit = 100,
	mediumScoreLimit = 300,
	highScoreLimit = 900,
	ultraScoreLimit = 3600
}tetrisScoreLimits;

typedef enum {
	normalTimeLimit = 60000,
	mediumTimeLimit = 120000,
	highTimeLimit = 270000,
	ultraTimeLimit = 500000
}tetrisTimeLimits;

typedef struct{
	uint32_t tetrisCurrtenTimeStart;
	uint32_t tetrisCurrentTime;
	uint32_t tetrisReactionTime;
	uint32_t tetrisSpeed;
	uint32_t tetrisFrequency;
}tetrisTimingParametersTypeDef;

typedef struct
{
	uint16_t row;
	uint16_t column;
}tetrisBoardPositionsTypeDef;

typedef struct{
	uint8_t swap;
	uint8_t right;
	uint8_t left;
	uint8_t down;
}tetrisGameSignals;

typedef struct
{
	uint8_t down;
	uint8_t reset;
	uint8_t start;
}tetrisGameTouchSignals;
typedef enum {
	SPEED_NORMAL = 1000,
	SPEED_MEDIUM = 750,
	SPEED_HIGH = 500,
	SPEED_VERY_HIGH = 250,
	SPEED_FREQ = 150
}tetrisSpeedRangesTypeDef;

tetrisGameSettings gameS;
tetrisTimingParametersTypeDef gameT;
tetrisBoardPositionsTypeDef gameP;
uint32_t randomNumberBlockType;
RNG_HandleTypeDef hrng;
tetrisGameSignals gameSignals;
tetrisGameTouchSignals gameTouchSignals;
void startGame();
void runGame();
void readSignals(uint8_t swap, uint8_t right,uint8_t left,uint8_t down);
void readTouch(uint16_t x, uint16_t y, uint8_t pressed);
void updateGameBoard();
void updateGameBlock(tetrisBlockPropertiesTypeDef* block, tetrisBlockPropertiesTypeDef* _block, uint8_t t);
void drawGameBoard();
uint8_t detectCompleteRows();
uint8_t shapePositionValid(tetrisBlocksShapeTypeDef shape, int xoffset, int yoffset);
uint8_t positionValid(int xoffset, int yoffset);
uint8_t nextRowPositionValid();
uint8_t nextLeftPositionValid();
uint8_t nextRightPositionValid();
tetrisBoardPositionsTypeDef tetrisBlockPositionsToBoard(tetrisBlockPropertiesTypeDef block);
tetrisBlocksPositions blockLimitPosition(tetrisBlockPropertiesTypeDef block);
uint8_t blockLimitPositionReached(tetrisBlockPropertiesTypeDef block);
void pickRandomBlock(tetrisBlockPropertiesTypeDef* block, tetrisBlockSizesTypeDef s);
void calculateScore();
void calculateNextLevel();
#endif
