#ifndef TETRIS_BLOCKS_H
#define TETRIS_BLOCKS_H
/* This library was created for hobby, assume that background color of tetris blocks is black
 * Created for: Damian Quiroz
 * Creation date: 2021-10-31
 * Email: damian.quiroz.13 at sansano.usm.cl
 * We need the library for ili9341 created for taburyak , all the rights are reserved for his creation
 * the dependences are located at: https://github.com/taburyak/STM32-ILI9341-320x240-FSMC-Library
 * */
#include "main.h"
#include "string.h"
#include "ili9341.h"

typedef enum {
	BLOCK_BOARD = 0,
	BLOCK_I = 1, 		/* ####*/

	BLOCK_J = 2, 		/*  #
	 	 	 	 			###*/

	BLOCK_L = 3, 		/*  #
	 	 	 	   	   	    ###*/

	BLOCK_O = 4,  		/*   ##
	 	 	 	 	 	 	 ##*/

	BLOCK_S = 5,  		/* ##
	 	 	 	   	   	    ##*/

	BLOCK_T = 6, 		/*  #
	 	 	 	  	  	  ### */

	BLOCK_Z = 7/*   ##
	 	 	 	 			##*/
}tetrisBlocksTypeDef;

const static uint16_t BLOCK_COLORS[8] =
{
	COLOR_GRAY_80,
	COLOR_DARKCYAN,
	COLOR_RED,
	COLOR_ORANGE,
	COLOR_PURPLE,
	COLOR_MAGENTA,
	COLOR_GREEN,
	COLOR_LIGHTGREY
};


typedef enum {
	BLOCK_SIZE_SMALL 	= 5,  	// every # of a block is made of 5x5 pixels
	BLOCK_SIZE_MEDIUM 	= 8,	// every # of a block is made of 8x8 pixels
	BLOCK_SIZE_HUGE 	= 12,	// every # of a block is made of 12x12 pixels
}tetrisBlockSizesTypeDef;
typedef enum {
	BLOCK_ORIENTATION_PORTRAIT 			= 0,
	BLOCK_ORIENTATION_LANDSCAPE 		= 1,
	BLOCK_ORIENTATION_PORTRAIT_MIRROR 	= 2,
	BLOCK_ORIENTATION_LANSCAPE_MIRROR 	= 3
}tetrisBlocksOrientationTypeDef;

typedef struct {
	uint8_t portrait[5][5];
	uint8_t landscape[5][5];
	uint8_t portrait_mirror[5][5];
	uint8_t landscape_mirror[5][5];

}tetrisBlocksShapesTemplateTypeDef;


typedef struct {
	uint8_t shape[5][5];

}tetrisBlocksShapeTypeDef;

static const tetrisBlocksShapesTemplateTypeDef I_BLOCK_SHAPES  =
{
	{{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,0,0,0}},
	{{0,0,0,0,0},
	{0,0,0,0,0},
	{1,1,1,1,0},
	{0,0,0,0,0},
	{0,0,0,0,0}},
	{{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,0,0,0}},
	{{0,0,0,0,0},
	{0,0,0,0,0},
	{1,1,1,1,0},
	{0,0,0,0,0},
	{0,0,0,0,0}}
};



static const tetrisBlocksShapesTemplateTypeDef J_BLOCK_SHAPES =
{
	{{0,0,0,0,0},
	{0,1,0,0,0},
	{0,1,1,1,0},
	{0,0,0,0,0},
	{0,0,0,0,0}},
	{{0,0,0,0,0},
	{0,0,1,1,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,0,0,0}},
	{{0,0,0,0,0},
	{0,0,0,0,0},
	{0,1,1,1,0},
	{0,0,0,1,0},
	{0,0,0,0,0}},
	{{0,0,0,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,1,1,0,0},
	{0,0,0,0,0}},
};

static const tetrisBlocksShapesTemplateTypeDef L_BLOCK_SHAPES =
{
	{{0,0,0,0,0},
	{0,0,0,1,0},
	{0,1,1,1,0},
	{0,0,0,0,0},
	{0,0,0,0,0}},
	{{0,0,0,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,1,1,0},
	{0,0,0,0,0}},
	{{0,0,0,0,0},
	{0,0,0,0,0},
	{0,1,1,1,0},
	{0,1,0,0,0},
	{0,0,0,0,0}},
	{{0,0,0,0,0},
	{0,1,1,0,0},
	{0,0,1,0,0},
	{0,0,1,0,0},
	{0,0,0,0,0}}
};
//
static const tetrisBlocksShapesTemplateTypeDef O_BLOCK_SHAPES  =
{
	{{0,0,0,0,0},
	{0,0,0,0,0},
	{0,1,1,0,0},
	{0,1,1,0,0},
	{0,0,0,0,0}},
	{{0,0,0,0,0},
	{0,0,0,0,0},
	{0,1,1,0,0},
	{0,1,1,0,0},
	{0,0,0,0,0}},
	{{0,0,0,0,0},
	{0,0,0,0,0},
	{0,1,1,0,0},
	{0,1,1,0,0},
	{0,0,0,0,0}},
	{{0,0,0,0,0},
	{0,0,0,0,0},
	{0,1,1,0,0},
	{0,1,1,0,0},
	{0,0,0,0,0}}
};

static const tetrisBlocksShapesTemplateTypeDef S_BLOCK_SHAPES =
{
	{{0,0,0,0,0},
	{0,0,1,1,0},
	{0,1,1,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0}},
	{{0,0,0,0,0},
	{0,0,1,0,0},
	{0,0,1,1,0},
	{0,0,0,1,0},
	{0,0,0,0,0}},
	{{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,1,1,0},
	{0,1,1,0,0},
	{0,0,0,0,0}},
	{{0,0,0,0,0},
	{0,0,1,0,0},
	{0,0,1,1,0},
	{0,0,0,1,0},
	{0,0,0,0,0}}
};

static const tetrisBlocksShapesTemplateTypeDef Z_BLOCK_SHAPES =
{
	{{0,0,0,0,0},
	{0,1,1,0,0},
	{0,0,1,1,0},
	{0,0,0,0,0},
	{0,0,0,0,0}},
	{{0,0,0,0,0},
	{0,0,1,0,0},
	{0,1,1,0,0},
	{0,1,0,0,0},
	{0,0,0,0,0}},
	{{0,0,0,0,0},
	{0,1,1,0,0},
	{0,0,1,1,0},
	{0,0,0,0,0},
	{0,0,0,0,0}},
	{{0,0,0,0,0},
	{0,0,1,0,0},
	{0,1,1,0,0},
	{0,1,0,0,0},
	{0,0,0,0,0}}
};

static const tetrisBlocksShapesTemplateTypeDef T_BLOCK_SHAPES =
{
	{{0,0,0,0,0},
	{0,0,1,0,0},
	{0,1,1,1,0},
	{0,0,0,0,0},
	{0,0,0,0,0}},
	{{0,0,0,0,0},
	{0,0,1,0,0},
	{0,0,1,1,0},
	{0,0,1,0,0},
	{0,0,0,0,0}},
	{{0,0,0,0,0},
	{0,0,0,0,0},
	{0,1,1,1,0},
	{0,0,1,0,0},
	{0,0,0,0,0}},
	{{0,0,0,0,0},
	{0,0,1,0,0},
	{0,1,1,0,0},
	{0,0,1,0,0},
	{0,0,0,0,0}}
};




typedef struct {
	uint16_t x;
	uint16_t y;
}tetrisBlocksPositions;

typedef struct{
	tetrisBlocksPositions up;
	tetrisBlocksPositions down;
	tetrisBlocksPositions left;
	tetrisBlocksPositions right;
}tetrisBlocksPositionLimits;


typedef struct {
	tetrisBlocksTypeDef blockType;
	tetrisBlocksOrientationTypeDef blockOrientation;
	uint16_t blockColor;
	tetrisBlocksPositions pos;
	tetrisBlockSizesTypeDef psize;
	tetrisBlocksShapeTypeDef shape;
	tetrisBlocksPositionLimits limits;
} tetrisBlockPropertiesTypeDef;

void drawBlock(tetrisBlockPropertiesTypeDef block);
void drawTetrisBlock(tetrisBlockPropertiesTypeDef block);
void drawBlockAt(int x, int y, tetrisBlockPropertiesTypeDef block);
void deleteBlock(tetrisBlockPropertiesTypeDef block);
void moveBlockDown(int step,tetrisBlockPropertiesTypeDef* block);
void rotateBlock(tetrisBlockPropertiesTypeDef* block);
void moveBlockRight(tetrisBlockPropertiesTypeDef* block);
void moveBlockLeft(tetrisBlockPropertiesTypeDef* block);
tetrisBlocksPositionLimits getBlockLimits(tetrisBlockPropertiesTypeDef block);
void copyBlockShape(uint8_t * shape[], tetrisBlockPropertiesTypeDef block);
tetrisBlocksShapeTypeDef getNextShape(tetrisBlockPropertiesTypeDef block);
tetrisBlocksOrientationTypeDef getNextOrientation(tetrisBlockPropertiesTypeDef block);
#endif
