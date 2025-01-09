# Small embedded system game

This project was made in October and November 2023 as a group project.

This game is inspired by the Bop It game. In the original game, the players have to do certain actions based on instructions given vocally. These actions include for example 
pressing buttons, flicking switches and pulling handles. Our game gives the instructions written on a screen instead of vocally. Our game also has two actions: pressing a button 
and rotating a rotation sensor. With more time, more actions could have been added.

The player has 3 seconds to do the correct action to continue playing. One point is given for each correct action. If the player does the wrong action or time runs out, the game 
ends. After losing, the screen will display the player's score and previous high score. The high score is stored in EEPROM, so that is stays on the device even if it is unplugged.

The system includes Arduino Nano, a screen, a button, a rotation sensor and a speaker. The speaker gives out different sounds for doing correct and false actions. 

### Picture and video

Picture of the final setup
![Image 9 1 2025 at 12 14](https://github.com/user-attachments/assets/b2c18a60-fd12-4eaf-a87c-0a6304d81e2d)

Video of gameplay can be found in the gameplay.mov file. It was filmed during final testing, so the game rules are sped up in the beginning.
