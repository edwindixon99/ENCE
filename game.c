#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "outcome.h"
#include "button.h"
#include "pattern.h"


#define PACER_RATE 500
#define MESSAGE_RATE 3


void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}


int main (void)
{
    int count;
    int start_game = 0;
    char playing = 0;
    char character = 'P';
    char otherplayer_selected = 0;

    system_init ();
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    button_init ();


    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    navswitch_init ();

    /* TODO: Initialise IR driver.  */
    ir_uart_init ();

    pacer_init (2000);

    tinygl_text("Welcome\0");

    while (1)
    {
        pacer_wait ();
        navswitch_update ();
        button_update();

        if (start_game == 0) {
            tinygl_update ();
            if (button_push_event_p (0)) {
                start_game = 1;
            }


        } else if (!(playing != 0 && otherplayer_selected != 0)) {
            tinygl_update ();
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
            tinygl_clear();
            tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);
            count = 0;
            tinygl_text("321\0");
            while (count < 6000) {
                count++;
                pacer_wait ();
                tinygl_update ();
            }
            tinygl_clear();
            count = 0;
            while (count < 5000) {
                pacer_wait ();
                count++;
                display_pattern (playing);
            }

            tinygl_init (PACER_RATE);
            tinygl_text_speed_set (MESSAGE_RATE);
            tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
            tinygl_text(show_result(playing, otherplayer_selected));
            while (1) {
                pacer_wait ();
                tinygl_update ();
                button_update();
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
