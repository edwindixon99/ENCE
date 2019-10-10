#include "system.h"
//#include "led.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10


void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}


int main (void)
{
    //led_init();
    //led_on();
    char playing = 0;
    char character = 'P';
    char otherplayer_selected = 0;

    system_init ();
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    navswitch_init ();

    /* TODO: Initialise IR driver.  */
    ir_uart_init ();

    pacer_init (PACER_RATE);
    while (1)
    {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();

        if (!(playing && otherplayer_selected)) {
            display_character (character);

            if (navswitch_push_event_p (NAVSWITCH_NORTH))
                character = 'R';

            if (navswitch_push_event_p (NAVSWITCH_WEST))
                character = 'S';

            if (navswitch_push_event_p (NAVSWITCH_SOUTH))
                character = 'P';

            /* TODO: Transmit the character over IR on a NAVSWITCH_PUSH
               event.  */
            if (navswitch_push_event_p (NAVSWITCH_EAST)){
                playing = character;
                ir_uart_putc(playing);
            }
            if (ir_uart_read_ready_p ()) {
                otherplayer_selected = ir_uart_getc();
            }

        } else {
            display_character (playing);
        }
    }

    return 0;
}
