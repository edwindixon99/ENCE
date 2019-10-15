/** @file   pattern.c
    @author Team 425 Edwin Dixon ejd83 & Jianqiao Guo jgu56
    @date    October 2019

        Header file for outcome.c
*/

#ifndef OUTCOME_H
#define OUTCOME_H


void game_init(void);

char* show_result (char sender, char reciever);

char update_character (char character);

void display_pattern (char character);

void end_screen(char playing);


#endif
