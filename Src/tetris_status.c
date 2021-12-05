#include "tetris_status.h"
#include "stdio.h"
void tetrisDrawStatus()
{
	boardColor = COLOR_DARKGREY;
	downButtonColor = DOWN_BUTTON_COLOR;
	startButtonColor = START_BUTTON_COLOR;
	lcdSetTextColor(DEFAULT_TEXT_COLOR,DEFAULT_BACKGROUND_COLOR);
	lcdFillRect(0,0,ILI9341_PIXEL_WIDTH,ILI9341_PIXEL_HEIGHT,COLOR_BLACK);
	lcdDrawRoundRect(0,0,ILI9341_PIXEL_WIDTH,ILI9341_PIXEL_HEIGHT,10,COLOR_WHITE);
	//lcdDrawRoundRect(GAME_BOARD_START_X,GAME_BOARD_START_Y,GAME_BOARD_WIDTH,GAME_BOARD_HEIGHT,10,COLOR_WHITE);
	lcdSetCursor(GAME_TIME_TEXT_X,GAME_TIME_TEXT_Y);
	lcdPrintf("TIME:");
	lcdSetCursor(GAME_TIME_X,GAME_TIME_Y);
	lcdPrintf("0000");
	lcdSetCursor(SCORE_TEXT_X,SCORE_TEXT_Y);
	lcdPrintf("SCORE:");
	lcdSetCursor(SCORE_X,SCORE_Y);
	lcdPrintf("000000");
	lcdSetCursor(NEXT_BLOCK_TEXT_POS_X,NEXT_BLOCK_TEXT_POS_Y);
	lcdPrintf("NEXT:");
	lcdDrawRoundRect(NEXT_BLOCK_POS_X,NEXT_BLOCK_POS_Y,6*NEXT_BLOCK_SIZE,6*NEXT_BLOCK_SIZE,5,COLOR_WHITE);
	//lcdSetCursor(DOWN_BUTTON_POS_X_INIT,DOWN_BUTTON_POS_Y_INIT);
	tetrisDrawDownButton(DOWN_BUTTON_X, DOWN_BUTTON_Y, downButtonColor);
}

void tetrisDrawGameOver()
{

	lcdFillRect(GAME_OVER_X,GAME_OVER_Y,GAME_BOARD_WIDTH/2,GAME_BOARD_HEIGHT/2,COLOR_CYAN);
	lcdSetCursor(GAME_OVER_TEXT_X,GAME_OVER_TEXT_Y);
	lcdPrintf("GAME");
	lcdSetCursor(GAME_OVER_TEXT_X,GAME_OVER_TEXT_Y + 15);
	lcdPrintf("OVER");
	tetrisDrawStartButton(START_BUTTON_X,START_BUTTON_Y,startButtonColor);
}
/* GAME BOARDS OF 120 X 240*/
void tetrisDrawGameBoard()
{

	tetrisBlockPropertiesTypeDef tb;
	tb.blockColor = boardColor;
	tb.pos.x = GAME_BOARD_START_X - GAME_BOARD_BLOCK_SIZE  -1;
	tb.pos.y = GAME_BOARD_START_Y -  GAME_BOARD_BLOCK_SIZE -1;
	tb.psize = GAME_BOARD_BLOCK_SIZE;

	for(int i = 0; i < 12; i++)
	{
		drawBlock(tb);
		if(i != 11){
			tb.pos.x+=GAME_BOARD_BLOCK_SIZE +1;
		}else{
			tb.pos.y+=GAME_BOARD_BLOCK_SIZE +1;
		}

	}

	for(int i = 1; i < 22; i++)
	{
		drawBlock(tb);
		if(i != 21){
			tb.pos.y+=GAME_BOARD_BLOCK_SIZE+1;
		}else{
			tb.pos.x-=(GAME_BOARD_BLOCK_SIZE+1);
		}

	}

	for(int i = 1; i < 12; i++)
	{
		drawBlock(tb);
		if(i != 11){
			tb.pos.x-=(GAME_BOARD_BLOCK_SIZE+1);
		}else{
			tb.pos.y-=(GAME_BOARD_BLOCK_SIZE+1);

		}

	}

	for(int i = 1; i < 22; i++)
	{
		drawBlock(tb);
		if(i != 21){
			tb.pos.y-=(GAME_BOARD_BLOCK_SIZE+1);
		}

	}

}

void tetrisUpdateScore(int totalScore)
{
	char score[4];
	sprintf(score,"%06i",totalScore);
	lcdSetCursor(SCORE_X,SCORE_Y);
	lcdPrintf(score);
}

void tetrisUpdateTime(int time)
{
	char score[4];
	sprintf(score,"%04i",time);
	lcdSetCursor(GAME_TIME_X,GAME_TIME_Y);
	lcdPrintf(score);
}

void tetrisDrawDownButton(uint16_t x, uint16_t y, uint16_t color)
{

	lcdDrawCircle(x,y,DOWN_BUTTON_RADIUS-3,color);
	lcdDrawCircle(x,y,DOWN_BUTTON_RADIUS,color);
	lcdDrawTriangle(x-10,y-5,x+10,y-5,x,y+5,color);

}

void tetrisUpdateDownButton(uint16_t color)
{
	if(downButtonColor != color)
	{
		downButtonColor = color;
		tetrisDrawDownButton(DOWN_BUTTON_X,DOWN_BUTTON_Y,downButtonColor);
	}
}

void tetrisDrawStartButton(uint16_t x, uint16_t y, uint16_t color)
{

	lcdFillCircle(x,y,START_BUTTON_RADIUS,START_BUTTON_COLOR_BORDER);
	lcdFillCircle(x,y,START_BUTTON_RADIUS-2,color);
	lcdSetCursor(START_BUTTON_TEXT_X,START_BUTTON_TEXT_Y);
	lcdSetTextColor(START_BUTTON_TEXT_COLOR,color);
	lcdPrintf("START");
	lcdSetTextColor(DEFAULT_TEXT_COLOR,DEFAULT_BACKGROUND_COLOR);
}

void tetrisUpdateStartButton(uint16_t color)
{
	if(downButtonColor != color)
	{
		downButtonColor = color;
		tetrisDrawStartButton(START_BUTTON_X,START_BUTTON_Y,downButtonColor);
	}
}


