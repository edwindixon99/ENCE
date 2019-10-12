#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "outcome.h"
#include "button.h"


#define PACER_RATE 500
#define MESSAGE_RATE 2


void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}


int main (void)
{
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
    while (1)
    {
        pacer_wait ();
        navswitch_update ();

        if (!(playing != 0 && otherplayer_selected != 0)) {
        //if ((playing == 0)) {
            tinygl_update ();
            display_character (character);

            character = update_character (character);


            if (navswitch_push_event_p (NAVSWITCH_EAST)){
                playing = character;
                ir_uart_putc(playing);
            }
            if (ir_uart_read_ready_p ()) {
                otherplayer_selected = ir_uart_getc();
            }

        } else {
            tinygl_text(show_result(playing, otherplayer_selected));
            while (1) {
                pacer_wait ();
                tinygl_update ();
                if (button_pressed_p ()) {
                    playing = 0;
                    otherplayer_selected = 0;
                    break;
                }
            }
        }
    }

    return 0;
}
