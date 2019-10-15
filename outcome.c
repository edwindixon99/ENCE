/** @file   outcome.c
    @author Team 425 Edwin Dixon ejd83 & Jianqiao Guo jgu56
    @date    October 2019

        Helper functions used throughout the game.
*/


#include "system.h"
#include "outcome.h"
#include "navswitch.h"
#include "tinygl.h"
#include "pattern.h"
#include "led.h"
#include "pacer.h"
#include "button.h"
#include "../fonts/font5x7_1.h"
#include "ir_uart.h"


#define TINYGL_RATE 500
#define PACER_RATE 2000
#define MESSAGE_RATE 3


/** initialize and configure drivers and utilities used for the game.    */
void game_init(void)
{
    system_init ();

    tinygl_init (TINYGL_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_speed_set (MESSAGE_RATE);

    button_init ();

    navswitch_init ();

    ir_uart_init ();

    pacer_init (PACER_RATE);
}








/** returns a string which is to be displayed on the users display based on the outcome of the game.
    @param  the character representing the pattern the user has recieved from other player.
    @param  the character representing the pattern the user has chosen.
    @return a string which is the outcome of the game.  */
char* show_result (char reciever, char sender)
{
    char* outcome = "";
    led_init();
    led_set(LED1, 0);


    if (sender == reciever) {               // draw case. displays DRAW
        outcome = "DRAW";
        led_set(LED1, 0);


    } else if ((sender == 'R' && reciever == 'P') || (sender == 'S' && reciever == 'R') || (sender == 'P' && reciever == 'S')) {        // possible ways for user to win. displays WIN
        outcome = "WIN";
        led_set(LED1, 1);


    } else if ((sender == 'P' && reciever == 'R') || (sender == 'R' && reciever == 'S') || (sender == 'S' && reciever == 'P')) {        // possible ways for user to lose. displays LOSE
        outcome = "LOSE";
        led_set(LED1, 0);


    } else {                                        // unexpected character has been recieved through mistake or interference
        outcome = "ERROR1";
        led_set(LED1, 0);
    }
    return outcome;
}


/** Updates the users choice of what pattern to display.
    @param  the character representing the pattern currently being displayed.
    @return the character representing the pattern the user has chosen.  */
char update_character (char character)
{
    // clear the previous pattern on display
    tinygl_clear();

    // selects Rock when navswitch pushed North
    if (navswitch_push_event_p (NAVSWITCH_NORTH))
        character = 'R';

    // selects Scissors when navswitch pushed West
    if (navswitch_push_event_p (NAVSWITCH_WEST))
        character = 'S';

    // selects Paper when navswitch pushed South
    if (navswitch_push_event_p (NAVSWITCH_SOUTH))
        character = 'P';

    return character;
}


/** displays the a pattern of either Rock, Paper or Scisscors.
    @param  the character representing the pattern wanting to be displayed.   */
void display_pattern (char character)
{
    if (character == 'R') {
        Rock();
    } else if (character == 'P') {
        Paper();
    } else if (character == 'S') {
        Scissor();
    }
}


/** displays a countdown followed by the pattern that the user played.
    @param  the character representing the pattern that was chosen to be played   */
void end_screen(char playing)
{
    tinygl_clear();
    tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);
    int count = 0;

    tinygl_text("321\0");
    while (count < 6000) {          //displays countdown from 3
        count++;
        pacer_wait ();
        tinygl_update ();
    }

    tinygl_clear();
    count = 0;
    while (count < 5000) {          //displays pattern that was played
        pacer_wait ();
        count++;
        display_pattern (playing);
    }
    tinygl_clear ();
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
}




