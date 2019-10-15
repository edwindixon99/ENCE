/** @file   game.c
    @author Team 425 Edwin Dixon ejd83 & Jianqiao Guo jgu56
    @date    October 2019

    Rock, Paper, Scissors. Main game module.
*/


#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "outcome.h"
#include "button.h"
#include "pattern.h"


#define TINYGL_RATE 500
#define PACER_RATE 2000
#define MESSAGE_RATE 3



int main (void)
{
    int start_game = 0;
    char playing = 0;
    char character = 'P';
    char otherplayer_selected = 0;
    char* result = "";


    game_init();

    tinygl_text("Welcome\0");

    while (1)
    {
        pacer_wait ();
        button_update();
        navswitch_update ();

        if (start_game == 0) {
            tinygl_update ();
            if (button_push_event_p (0)) {
                start_game = 1;
            }

        } else if (!(playing != 0 && otherplayer_selected != 0)) {

            display_pattern (character);

            character = update_character (character);

            if (navswitch_push_event_p (NAVSWITCH_EAST)){
                playing = character;
                ir_uart_putc(playing);
            }
            if (ir_uart_read_ready_p ()) {
                otherplayer_selected = ir_uart_getc();
            }

        } else {

            end_screen(playing);
            result = show_result(playing, otherplayer_selected);
            tinygl_text(result);

            while (1) {

                pacer_wait ();
                button_update();
                tinygl_update ();

                if (button_push_event_p (0)) {
                    playing = 0;
                    otherplayer_selected = 0;
                    break;
                }
            }
        }
    }

    return 0;
}
