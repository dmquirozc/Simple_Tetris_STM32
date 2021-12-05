#include "tetris_blocks.h"


void drawBlock(tetrisBlockPropertiesTypeDef block)
{
	int x = block.pos.x ;
	int x1 =  x+block.psize;
	int y =  block.pos.y;
	int y1 =  block.pos.y + block.psize;

	lcdFillRect(x,block.pos.y,block.psize,block.psize,block.blockColor);
	lcdDrawHLine(x,x+block.psize,y,COLOR_WHITE);
	lcdDrawHLine(x,x+block.psize,y1,COLOR_WHITE);
	lcdDrawVLine(x,y,y1,COLOR_WHITE);
	lcdDrawVLine(x1,y,y1,COLOR_WHITE);
}

void drawBlockAt(int x, int y, tetrisBlockPropertiesTypeDef block)
{
	int x1 =  x+block.psize;
	int y1 =  block.pos.y + block.psize;
	lcdFillRect(x,block.pos.y,block.psize,block.psize,block.blockColor);
	lcdDrawHLine(x,x+block.psize,y,COLOR_WHITE);
	lcdDrawHLine(x,x+block.psize,y1,COLOR_WHITE);
	lcdDrawVLine(x,y,y1,COLOR_WHITE);
	lcdDrawVLine(x1,y,y1,COLOR_WHITE);
}


void drawTetrisBlock(tetrisBlockPropertiesTypeDef block){
	int x;
	int x1;
	int y;
	int y1;
	for(int r = 0; r < 5; r++)
	{
		for(int c = 0; c < 5; c++)
		{
			if(block.shape.shape[r][c] == 1)
			{

				x = block.pos.x + (c)*(block.psize + 1);
				x1 = x + block.psize;
				y =  block.pos.y + (r)*(block.psize + 1);
				y1 =  y + block.psize;
				lcdFillRect(x,y,block.psize,block.psize,block.blockColor);
				lcdDrawHLine(x,x1,y,COLOR_WHITE);
				lcdDrawHLine(x,x1,y1,COLOR_WHITE);
				lcdDrawVLine(x,y,y1,COLOR_WHITE);
				lcdDrawVLine(x1,y,y1,COLOR_WHITE);

			}
		}
	}
}

void deleteBlock(tetrisBlockPropertiesTypeDef block){
	int x;
	int y;

	for(int r = 0; r < 5; r++)
	{
		for(int c = 0; c < 5; c++)
		{
			if(block.shape.shape[r][c] == 1)
			{

				x = block.pos.x + (c)*(block.psize + 1);
				y =  block.pos.y + (r)*(block.psize + 1);
				lcdFillRect(x,y,block.psize,block.psize,COLOR_BLACK);
			}
		}
	}
}


void moveBlockDown(int step,tetrisBlockPropertiesTypeDef* block){
	deleteBlock(*block);

	if(block->pos.y + step > ILI9341_PIXEL_HEIGHT){
		block->pos.y = 0;
	}else{
		block->pos.y+= step;
	}


	drawTetrisBlock(*block);
}

tetrisBlocksPositionLimits getBlockLimits(tetrisBlockPropertiesTypeDef block){
	tetrisBlocksPositionLimits bl;
	uint8_t ul = 0,dl = 0,rl = 0,ll = 0;
	for(int r = 0; r < 5; r++)
	{

		for(int c = 0; c < 5; c++)
		{
			if(block.shape.shape[r][c] == 1)
			{
				if(ul == 0)
				{
					bl.up.x = block.pos.x + (c)*(block.psize + 1);
					bl.up.y = block.pos.y + (r)*(block.psize + 1);
					ul = 1;
 				}
			}
		}
	}

}

tetrisBlocksOrientationTypeDef getNextOrientation(tetrisBlockPropertiesTypeDef block){
	if(block.blockOrientation == BLOCK_ORIENTATION_PORTRAIT){
		return BLOCK_ORIENTATION_LANDSCAPE;
	}else if(block.blockOrientation == BLOCK_ORIENTATION_LANDSCAPE){
		return BLOCK_ORIENTATION_PORTRAIT_MIRROR;
	}else if(block.blockOrientation == BLOCK_ORIENTATION_PORTRAIT_MIRROR){
		return BLOCK_ORIENTATION_LANSCAPE_MIRROR;
	}else if(block.blockOrientation == BLOCK_ORIENTATION_LANSCAPE_MIRROR){
		return BLOCK_ORIENTATION_PORTRAIT;
	}
}
void rotateBlock(tetrisBlockPropertiesTypeDef* block){
	deleteBlock(*block);
	block->blockOrientation = getNextOrientation(*block);
	copyBlockShape(&block->shape.shape,*block);
	drawTetrisBlock(*block);
}

void moveBlockRight(tetrisBlockPropertiesTypeDef* block){
	deleteBlock(*block);
	block->pos.x+= block->psize+1;
	drawTetrisBlock(*block);
}
void moveBlockLeft(tetrisBlockPropertiesTypeDef* block){
	deleteBlock(*block);
	block->pos.x-= (block->psize+1);
	drawTetrisBlock(*block);
}
void copyBlockShape(uint8_t * shape[], tetrisBlockPropertiesTypeDef block){
	if(block.blockType == BLOCK_I)
	{
		if(block.blockOrientation == BLOCK_ORIENTATION_LANDSCAPE){
			memcpy(shape,I_BLOCK_SHAPES.landscape,25);
		}else if(block.blockOrientation == BLOCK_ORIENTATION_LANSCAPE_MIRROR){
			memcpy(shape, I_BLOCK_SHAPES.landscape_mirror,25);
		}else if(block.blockOrientation == BLOCK_ORIENTATION_PORTRAIT){
			memcpy(shape, I_BLOCK_SHAPES.portrait, 25);
		}else if(block.blockOrientation == BLOCK_ORIENTATION_PORTRAIT_MIRROR){
			memcpy(shape, I_BLOCK_SHAPES.portrait_mirror, 25);
		}
	}else if(block.blockType == BLOCK_J)
	{
		if(block.blockOrientation == BLOCK_ORIENTATION_LANDSCAPE){
			memcpy(shape, J_BLOCK_SHAPES.landscape,25);
		}else if(block.blockOrientation == BLOCK_ORIENTATION_LANSCAPE_MIRROR){
			memcpy(shape, J_BLOCK_SHAPES.landscape_mirror,25);
		}else if(block.blockOrientation == BLOCK_ORIENTATION_PORTRAIT){
			memcpy(shape, J_BLOCK_SHAPES.portrait, 25);
		}else if(block.blockOrientation == BLOCK_ORIENTATION_PORTRAIT_MIRROR){
			memcpy(shape, J_BLOCK_SHAPES.portrait_mirror, 25);
		}
	}else if(block.blockType == BLOCK_L)
	{
		if(block.blockOrientation == BLOCK_ORIENTATION_LANDSCAPE){
			memcpy(shape, L_BLOCK_SHAPES.landscape,25);
		}else if(block.blockOrientation == BLOCK_ORIENTATION_LANSCAPE_MIRROR){
			memcpy(shape, L_BLOCK_SHAPES.landscape_mirror,25);
		}else if(block.blockOrientation == BLOCK_ORIENTATION_PORTRAIT){
			memcpy(shape, L_BLOCK_SHAPES.portrait, 25);
		}else if(block.blockOrientation == BLOCK_ORIENTATION_PORTRAIT_MIRROR){
			memcpy(shape, L_BLOCK_SHAPES.portrait_mirror, 25);
		}
	}else if(block.blockType == BLOCK_O)
	{
		if(block.blockOrientation == BLOCK_ORIENTATION_LANDSCAPE){
			memcpy(shape, O_BLOCK_SHAPES.landscape,25);
		}else if(block.blockOrientation == BLOCK_ORIENTATION_LANSCAPE_MIRROR){
			memcpy(shape, O_BLOCK_SHAPES.landscape_mirror,25);
		}else if(block.blockOrientation == BLOCK_ORIENTATION_PORTRAIT){
			memcpy(shape, O_BLOCK_SHAPES.portrait, 25);
		}else if(block.blockOrientation == BLOCK_ORIENTATION_PORTRAIT_MIRROR){
			memcpy(shape, O_BLOCK_SHAPES.portrait_mirror, 25);
		}
	}else if(block.blockType == BLOCK_S)
	{
		if(block.blockOrientation == BLOCK_ORIENTATION_LANDSCAPE){
			memcpy(shape, S_BLOCK_SHAPES.landscape,25);
		}else if(block.blockOrientation == BLOCK_ORIENTATION_LANSCAPE_MIRROR){
			memcpy(shape, S_BLOCK_SHAPES.landscape_mirror,25);
		}else if(block.blockOrientation == BLOCK_ORIENTATION_PORTRAIT){
			memcpy(shape, S_BLOCK_SHAPES.portrait, 25);
		}else if(block.blockOrientation == BLOCK_ORIENTATION_PORTRAIT_MIRROR){
			memcpy(shape, S_BLOCK_SHAPES.portrait_mirror, 25);
		}
	}else if(block.blockType == BLOCK_Z)
	{
		if(block.blockOrientation == BLOCK_ORIENTATION_LANDSCAPE){
			memcpy(shape, Z_BLOCK_SHAPES.landscape,25);
		}else if(block.blockOrientation == BLOCK_ORIENTATION_LANSCAPE_MIRROR){
			memcpy(shape, Z_BLOCK_SHAPES.landscape_mirror,25);
		}else if(block.blockOrientation == BLOCK_ORIENTATION_PORTRAIT){
			memcpy(shape, Z_BLOCK_SHAPES.portrait, 25);
		}else if(block.blockOrientation == BLOCK_ORIENTATION_PORTRAIT_MIRROR){
			memcpy(shape, Z_BLOCK_SHAPES.portrait_mirror, 25);
		}
	}else if(block.blockType == BLOCK_T)
	{
		if(block.blockOrientation == BLOCK_ORIENTATION_LANDSCAPE){
			memcpy(shape, T_BLOCK_SHAPES.landscape,25);
		}else if(block.blockOrientation == BLOCK_ORIENTATION_LANSCAPE_MIRROR){
			memcpy(shape, T_BLOCK_SHAPES.landscape_mirror,25);
		}else if(block.blockOrientation == BLOCK_ORIENTATION_PORTRAIT){
			memcpy(shape, T_BLOCK_SHAPES.portrait, 25);
		}else if(block.blockOrientation == BLOCK_ORIENTATION_PORTRAIT_MIRROR){
			memcpy(shape, T_BLOCK_SHAPES.portrait_mirror, 25);
		}
	}
}

tetrisBlocksShapeTypeDef getNextShape(tetrisBlockPropertiesTypeDef block){
	tetrisBlocksShapeTypeDef s;
	tetrisBlockPropertiesTypeDef b;
	b.blockOrientation = getNextOrientation(block);
	b.blockType = block.blockType;
	copyBlockShape(s.shape,b);
	return s;
}
