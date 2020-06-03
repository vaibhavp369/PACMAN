
/*
* animation.h
* Created:  22/03/2020 12:16:06
* Author: VAIBHAV PATIL
*/

#ifndef ANIMATION_H_
#define ANIMATION_H_

// This function is used to congigure buttons
void config_UI();

// This function used to send custom chractor data row wise

void upload_custom_char (unsigned char index, unsigned char *data);

//This function is used to create sine wave charactor
void creat_sine_char();

//This function is used to print sine wave

void print_sine_wave();

//This function is used to creat pacman charactor
void creat_pacman_char();

//This function is used to show demo of PACMAN
void play_pacman();

// This function show the demo of fire
void fire_demo();

#endif // ANIMATION_H_