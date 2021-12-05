#include "tetris_game_rules.h"

void startGame()
{
	tetrisDrawStatus();
    tetrisDrawGameBoard();
	gameS.gameScore = 0;
	gameS.gameOverFlag = 0;
	gameS.gameOverDrawFlag = 0;
	gameS.clearRowsFlag = 0;
	gameTouchSignals.reset = 0;
	gameTouchSignals.start = 0;
	/* Game Board Initialization*/
	for(int i = 0; i < GAME_BOARD_BLOCKS_ROWS; i++)
	{
		for(int k = 0; k < GAME_BOARD_BLOCKS_COLS; k++){
			if((i < 2 || i >= (GAME_BOARD_BLOCKS_ROWS - 2)))
			{
				gameS.gameBoard[i][k] = 0x01;
			}else if(k < 2 || k >= (GAME_BOARD_BLOCKS_COLS - 2)){
				gameS.gameBoard[i][k] = 0x01;
			}else
			{
				gameS.gameBoard[i][k] = 0x00;
			}
		}
	}

	pickRandomBlock(&gameS.gameBlock,BLOCK_SIZE_HUGE);
	pickRandomBlock(&gameS.nextGameBlock,BLOCK_SIZE_MEDIUM);
	gameT.tetrisReactionTime = HAL_GetTick();
	gameT.tetrisCurrtenTimeStart = HAL_GetTick();
	gameT.tetrisCurrentTime = 0;
	gameT.tetrisFrequency = SPEED_FREQ;
	gameT.tetrisSpeed =  SPEED_NORMAL;
	calculateNextLevel();
	gameP = tetrisBlockPositionsToBoard(gameS.gameBlock);
	drawTetrisBlock(gameS.gameBlock);
	drawTetrisBlock(gameS.nextGameBlock);

}

/*
 * Run Tetris game
 */
void runGame()
{
	if(gameS.gameOverFlag == 0){


		gameP = tetrisBlockPositionsToBoard(gameS.gameBlock);
		uint8_t validationDown = nextRowPositionValid();
		uint8_t validationRight = nextRightPositionValid();
		uint8_t validationLeft = nextLeftPositionValid();
		calculateNextLevel();
		if(gameTouchSignals.down)
		{
			tetrisUpdateDownButton(DOWN_BUTTON_PRESSED_COLOR);
		}else
		{
			tetrisUpdateDownButton(DOWN_BUTTON_COLOR);
		}

		if(gameS.clearRowsFlag > 0)
		{
			calculateScore();
			drawGameBoard();
			gameS.clearRowsFlag = 0;
		}

		if(gameT.tetrisReactionTime + gameT.tetrisFrequency < HAL_GetTick())
		{
			if(gameSignals.swap == 1)
			{
				tetrisBlocksShapeTypeDef s = getNextShape(gameS.gameBlock);
				if(shapePositionValid(s,0,0) == 1){
					rotateBlock(&gameS.gameBlock);
				}
			}else if(gameSignals.left == 1 && validationLeft == 1){
				moveBlockLeft(&gameS.gameBlock);
			}else if(gameSignals.right == 1 && validationRight == 1){
				moveBlockRight(&gameS.gameBlock);
			}else if((gameSignals.down == 1 || gameTouchSignals.down) && validationDown == 1){
				moveBlockDown(GAME_BOARD_BLOCK_SIZE + 1,&gameS.gameBlock);
			}
			gameT.tetrisReactionTime = HAL_GetTick();

		}


		if(gameT.tetrisCurrentTime + gameT.tetrisSpeed  + gameT.tetrisCurrtenTimeStart < HAL_GetTick() || validationDown == 0 )
		{

			boardColor = gameS.gameBlock.blockColor;
			tetrisDrawGameBoard();

			if(validationDown == 1)
			{

				moveBlockDown(GAME_BOARD_BLOCK_SIZE + 1, &gameS.gameBlock);

			}else
			{
				updateGameBoard();
				updateGameBlock(&gameS.nextGameBlock,&gameS.gameBlock,1);
				pickRandomBlock(&gameS.nextGameBlock,BLOCK_SIZE_MEDIUM);
				drawTetrisBlock(gameS.gameBlock);
				drawTetrisBlock(gameS.nextGameBlock);
				gameS.clearRowsFlag = detectCompleteRows();
				if(gameP.row <= 3)
				{
					gameS.gameOverFlag = 1;
				}
			}
			gameT.tetrisCurrentTime = HAL_GetTick() - gameT.tetrisCurrtenTimeStart;
			tetrisUpdateTime(gameT.tetrisCurrentTime/1000);
		}



	}else{

		if(gameTouchSignals.reset)
		{
			tetrisUpdateStartButton(START_BUTTON_PRESSED_COLOR);
		}

		if(gameS.gameOverDrawFlag == 0){
			tetrisDrawGameOver();
			gameS.gameOverDrawFlag = 1;
		}else if(gameSignals.swap == 1)
		{
			lcdFillRect(GAME_BOARD_START_X,GAME_BOARD_START_Y,GAME_BOARD_WIDTH-1,GAME_BOARD_HEIGHT-1,COLOR_BLACK);
			startGame();
		}else if(gameTouchSignals.start == 1)
		{
			HAL_Delay(100);
			lcdFillRect(GAME_BOARD_START_X,GAME_BOARD_START_Y,GAME_BOARD_WIDTH-1,GAME_BOARD_HEIGHT-1,COLOR_BLACK);
			startGame();
		}

	}

}

void calculateScore()
{
	if(gameT.tetrisSpeed == SPEED_NORMAL)
	{
		gameS.gameScore+= 10*gameS.clearRowsFlag;
	}else if(gameT.tetrisSpeed == SPEED_MEDIUM){
		gameS.gameScore+= 10*(2*gameS.clearRowsFlag);
	}else if(gameT.tetrisSpeed == SPEED_HIGH){
		gameS.gameScore+= 10*(3*gameS.clearRowsFlag);
	}else{
		gameS.gameScore+= 10* (4*gameS.clearRowsFlag);
	}
	tetrisUpdateScore(gameS.gameScore);
}

void readSignals(uint8_t swap, uint8_t right,uint8_t left,uint8_t down)
{
	gameSignals.swap = swap;
	gameSignals.right = right;
	gameSignals.left = left;
	gameSignals.down = down;
}

void updateGameBoard() {
	int row = 0,col = 0;
	for(int i= gameP.row ; i < gameP.row + 5; i++)
	{
		col = 0;
		for(int j =  gameP.column; j < gameP.column  + 5; j++)
		{
			if( gameS.gameBlock.shape.shape[row][col] == 1)
			{
				gameS.gameBoard[i][j] = gameS.gameBlock.blockType;
			}
			col++;
		}

		row++;
	}
}


void drawGameBoard(){
	for(int i = GAME_BOARD_BLOCKS_ROWS_OFFSET; i < GAME_BOARD_BLOCKS_ROWS - GAME_BOARD_BLOCKS_ROWS_OFFSET;i++)
	{
		if(gameS.gameCompleteRows[i-GAME_BOARD_BLOCKS_ROWS_OFFSET] == 1)
		{
			for(int j = GAME_BOARD_BLOCKS_COLS_OFFSET; j < GAME_BOARD_BLOCKS_COLS - GAME_BOARD_BLOCKS_COLS_OFFSET;j++ ){
				gameS.gameBoard[i][j] = 0;
			}

			for(int r = i; r > GAME_BOARD_BLOCKS_ROWS_OFFSET; r--){
				for(int j = GAME_BOARD_BLOCKS_COLS_OFFSET; j < GAME_BOARD_BLOCKS_COLS - GAME_BOARD_BLOCKS_COLS_OFFSET;j++ ){
					gameS.gameBoard[r][j] = gameS.gameBoard[r-1][j];
				}
			}
		 gameS.gameCompleteRows[i-GAME_BOARD_BLOCKS_ROWS_OFFSET] = 0;
		}
	}

	lcdFillRect(GAME_BOARD_START_X,GAME_BOARD_START_Y,GAME_BOARD_WIDTH-1,GAME_BOARD_HEIGHT-1,COLOR_BLACK);
	tetrisBlockPropertiesTypeDef tb;
	tb.psize = GAME_BOARD_BLOCK_SIZE;
	for(int r = GAME_BOARD_BLOCKS_ROWS_OFFSET; r < GAME_BOARD_BLOCKS_ROWS - GAME_BOARD_BLOCKS_ROWS_OFFSET; r++)
	{
		for(int c = GAME_BOARD_BLOCKS_COLS_OFFSET; c < GAME_BOARD_BLOCKS_COLS - GAME_BOARD_BLOCKS_COLS_OFFSET;c++ )
		{
			if(gameS.gameBoard[r][c] > 0)
			{

				tb.blockColor = BLOCK_COLORS[gameS.gameBoard[r][c]];
				tb.pos.x = GAME_BOARD_START_X + (c-GAME_BOARD_BLOCKS_COLS_OFFSET)*(GAME_BOARD_BLOCK_SIZE + 1);
				tb.pos.y = GAME_BOARD_START_Y + (r-GAME_BOARD_BLOCKS_ROWS_OFFSET)*(GAME_BOARD_BLOCK_SIZE + 1);

				drawBlock(tb);
			}
		}
	}
	drawTetrisBlock(gameS.gameBlock);
}


uint8_t detectCompleteRows(){
	int row = 0;
	int sum = 0;
	uint8_t complete = 0;
	for(int i = GAME_BOARD_BLOCKS_ROWS_OFFSET; i < GAME_BOARD_BLOCKS_ROWS-GAME_BOARD_BLOCKS_ROWS_OFFSET; i++){
		sum = 0;
		for(int j = GAME_BOARD_BLOCKS_COLS_OFFSET; j < GAME_BOARD_BLOCKS_COLS - GAME_BOARD_BLOCKS_COLS_OFFSET;j++ ){
			if(gameS.gameBoard[i][j] > 0){
				sum++;
			}
		}

		if(sum == (GAME_BOARD_BLOCKS_COLS - 2*GAME_BOARD_BLOCKS_COLS_OFFSET))
		{
			gameS.gameCompleteRows[row] = 1;
			complete++;
		}
		row++;
	}
	return complete;
}

uint8_t shapePositionValid(tetrisBlocksShapeTypeDef shape, int xoffset, int yoffset){
	uint8_t valid = 1;
	int row = 0,col = 0;
	for(int i= gameP.row + yoffset; i < gameP.row + yoffset + 5; i++)
	{
		col = 0;
		for(int j =  gameP.column + xoffset; j < gameP.column + xoffset + 5; j++)
		{
			if(gameS.gameBoard[i][j] > 0 && shape.shape[row][col] == 1)
			{
				valid = 0;
			}
			col++;
		}

		row++;
	}
	return valid;
}

uint8_t positionValid(int xoffset, int yoffset)
{
	uint8_t valid = 1;
	int row = 0,col = 0;

	for(int i= gameP.row + yoffset; i < gameP.row + yoffset + 5; i++)
	{
		col = 0;
		if(xoffset < 0)
		{
			for(int j =  gameP.column - (-xoffset); j < gameP.column - (-xoffset) + 5; j++)
			{
				if(gameS.gameBoard[i][j] > 0 && gameS.gameBlock.shape.shape[row][col] == 1)
				{
					valid = 0;
				}
				col++;
			}
		}else{
			for(int j =  gameP.column + xoffset; j < gameP.column + xoffset + 5; j++)
			{
				if(gameS.gameBoard[i][j] > 0 && gameS.gameBlock.shape.shape[row][col] == 1)
				{
					valid = 0;
				}
				col++;
			}
		}

		row++;
	}
	return valid;
}

uint8_t nextRowPositionValid(){
	return positionValid(0,1);
}

uint8_t nextLeftPositionValid(){
	return positionValid(-1,0);
}

uint8_t nextRightPositionValid()
{
	return positionValid(1,0);
}

tetrisBoardPositionsTypeDef tetrisBlockPositionsToBoard(tetrisBlockPropertiesTypeDef block)
{
	tetrisBoardPositionsTypeDef pb;


	pb.column = GAME_BOARD_BLOCKS_COLS_OFFSET + (block.pos.x - GAME_BOARD_START_X )/(block.psize + 1);
	pb.row = GAME_BOARD_BLOCKS_ROWS_OFFSET + (block.pos.y - GAME_BOARD_START_Y )/(block.psize + 1) ;


	return pb;
}
tetrisBlocksPositions blockLimitPosition(tetrisBlockPropertiesTypeDef block){

}
uint8_t blockLimitPositionReached(tetrisBlockPropertiesTypeDef block){

}

void pickRandomBlock(tetrisBlockPropertiesTypeDef* block, tetrisBlockSizesTypeDef s){
	HAL_RNG_GenerateRandomNumber(&hrng,&randomNumberBlockType);
	uint32_t n = (randomNumberBlockType & 0x00FFFFFF)/2396745;

	block->blockType = (n == 0)? 1: n;
	block->blockOrientation = BLOCK_ORIENTATION_PORTRAIT;
	block->psize = s;
	block->blockColor = BLOCK_COLORS[block->blockType];
	copyBlockShape(&(block->shape.shape),*block);
	if(s == BLOCK_SIZE_HUGE)
	{
		block->pos.x = GAME_BOARD_START_X + GAME_BOARD_WIDTH/2 - 2*(GAME_BOARD_BLOCK_SIZE+1);
		block->pos.y  = GAME_BOARD_START_Y;
	}else if(s == BLOCK_SIZE_SMALL)
	{
		block->pos.x = NEXT_BLOCK_POS_X;
		block->pos.y = NEXT_BLOCK_POS_Y + 3;
	}else if(s == BLOCK_SIZE_MEDIUM)
	{
		block->pos.x = NEXT_BLOCK_POS_X;
		block->pos.y = NEXT_BLOCK_POS_Y + 3;
	}


}

void updateGameBlock(tetrisBlockPropertiesTypeDef* block, tetrisBlockPropertiesTypeDef* _block, uint8_t t){
	if(t == 0) // copy
	{
		deleteBlock(*block);
		_block->blockColor = block->blockColor;
		_block->blockOrientation = block->blockOrientation;
		_block->blockType = block->blockType;
		_block->shape = block->shape;
		_block->psize = block->psize;
		_block->pos.x = block->pos.x;
		_block->pos.y = block->pos.y;

	}else{ // copy and translate to board
		deleteBlock(*block);
		_block->blockColor = block->blockColor;
		_block->blockOrientation = block->blockOrientation;
		_block->blockType = block->blockType;
		_block->shape = block->shape;
		_block->psize = BLOCK_SIZE_HUGE;
		_block->pos.x = GAME_BOARD_START_X + GAME_BOARD_WIDTH/2 - 2*(GAME_BOARD_BLOCK_SIZE+1);
		_block->pos.y = GAME_BOARD_START_Y;
	}
}


void calculateNextLevel()
{
	if(gameT.tetrisCurrentTime >= ultraTimeLimit || gameS.gameScore >= ultraScoreLimit)
	{
		gameT.tetrisSpeed = SPEED_VERY_HIGH;

	}else if(gameT.tetrisCurrentTime >= highTimeLimit || gameS.gameScore >= highScoreLimit)
	{
		gameT.tetrisSpeed = SPEED_HIGH;
	}else if(gameT.tetrisCurrentTime >= mediumTimeLimit || gameS.gameScore >= mediumScoreLimit){
		gameT.tetrisSpeed = SPEED_MEDIUM;

	}else{
		gameT.tetrisSpeed = SPEED_NORMAL;
	}
}

void readTouch(uint16_t x, uint16_t y, uint8_t pressed)
{
	if(pressed)
	{
		if((x >= DOWN_BUTTON_X - DOWN_BUTTON_RADIUS) && x <= DOWN_BUTTON_X + DOWN_BUTTON_RADIUS)
		{
			if(y >= DOWN_BUTTON_Y-DOWN_BUTTON_RADIUS && y <= DOWN_BUTTON_Y + DOWN_BUTTON_RADIUS)
			{
				gameTouchSignals.down = 1;
			}
		}

		if(gameS.gameOverFlag == 1)
		{
			if(x >= START_BUTTON_X - START_BUTTON_RADIUS && x <= START_BUTTON_X + START_BUTTON_RADIUS)
			{
				if(y >= START_BUTTON_Y - START_BUTTON_RADIUS && y <= START_BUTTON_Y + START_BUTTON_RADIUS)
				{
					gameTouchSignals.reset = 1;
				}
			}
		}

	}else
	{
		if(gameTouchSignals.reset == 1)
		{
			gameTouchSignals.start = 1;
		}
		gameTouchSignals.down = 0;
		gameTouchSignals.reset = 0;
	}
}
