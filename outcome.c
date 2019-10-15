#include "outcome.h"
#include "navswitch.h"
#include "tinygl.h"
#include "pattern.h"
#include "led.h"

/** returns a string which is to be displayed on the users display based on the outcome of the game.
    @param  the character representing the pattern the user has recieved from other player.
    @param  the character representing the pattern the user has chosen.
    @return a string which is the outcome of the game.  */
char* show_result (char reciever, char sender)
{	
    char* outcome = "";

    // draw case. displays DRAW
    if (sender == reciever) {
        outcome = "DRAW";
        led_init();
        led_set(LED1, 0);

    // possible ways for user to win. displays WIN
    } else if ((sender == 'R' && reciever == 'P') || (sender == 'S' && reciever == 'R') || (sender == 'P' && reciever == 'S')) {
        outcome = "WIN";
        led_init();
        led_set(LED1, 1);

    // possible ways for user to lose. displays LOSE
    } else if ((sender == 'P' && reciever == 'R') || (sender == 'R' && reciever == 'S') || (sender == 'S' && reciever == 'P')) {
        outcome = "LOSE";
        led_init();
        led_set(LED1, 0);

    // unexpected character has been recieved
    } else {
        outcome = "ERROR1";
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
