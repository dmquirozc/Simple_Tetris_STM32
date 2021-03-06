# Simple_Tetris_STM32
This project shows a simple tetris game using the STM32F4407VET6 Black Board and the ILI9341 Touch Screen.
## Limitations 
This project was created on STM32F407VET6 Black Boards using FSMC driver to handle the ILI9341 draws on screen. This idea was take from  Andriy Honcharenko 
STM32-ILI9341-320x240-FSMC-Library repository, without that this project wouldn't have been possible (https://github.com/taburyak/STM32-ILI9341-320x240-FSMC-Library) 
## Logic
The logic of the game was inspired on 
https://inventwithpython.com/pygame/chapter7.html
Thanks to their project I was able to make this little game.
## TouchScreen
The touch driver was made for me, you can find it on https://github.com/dmquirozc/XPT2046_driver_STM32.
## How to Play
To play the game just put the program on your board with the ILI9341 Screen and the game will start.
To move Right and Left use the buttons K0 (Left) and K1 (Right). 
To rotate the tetris block use the button K_Up.
This three signals are read using the lines of code above:
```c
uint8_t swap = HAL_GPIO_ReadPin(SWAP_BUTTON_GPIO_Port,SWAP_BUTTON_Pin);
uint8_t right = !HAL_GPIO_ReadPin(RIGHT_BUTTON_GPIO_Port,RIGHT_BUTTON_Pin);
uint8_t left = !HAL_GPIO_ReadPin(LEFT_BUTTON_GPIO_Port,LEFT_BUTTON_Pin);
readSignals(swap,right,left,0);
```
The readSignals adn readTouch functions collect the external signals necessary to move around and play.
```c
void readSignals(uint8_t swap, uint8_t right,uint8_t left,uint8_t down);
void readTouch(uint16_t x, uint16_t y, uint8_t pressed);
```


The readTouch function was configured to read the "down" button of the screen and the start button to reset the game when it's ends.

<img src="https://user-images.githubusercontent.com/32380955/144747292-55185dbb-133b-4660-84bd-c5c8c5317fcb.jpg" alt="down_button" width="300px"/>
<img src="https://user-images.githubusercontent.com/32380955/144747363-e0b21dce-d6bf-4b6f-9299-ebc3ecb65d4d.jpg" alt="end_game" width="300px"/>

<img src="https://user-images.githubusercontent.com/32380955/144747365-8ba1ecfe-cecc-424c-b37a-840372de61f8.jpg" alt="start_button" width="300px"/>

## Demo
### Playing
https://user-images.githubusercontent.com/32380955/144747461-c923bc27-56b8-4869-8c75-91651a21d1a8.mp4

### Restart Game

https://user-images.githubusercontent.com/32380955/144747468-24466002-d23d-471c-96c0-d54223977545.mp4

