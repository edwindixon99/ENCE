#include "outcome.h"
#include "navswitch.h"

char* show_result (char reciever, char sender)
{
    char* outcome = "";
    if (sender == reciever) {
        outcome = "DRAW";
    } else {
        if ((sender == 'R' && reciever == 'P') || (sender == 'S' && reciever == 'R') || (sender == 'P' && reciever == 'S')) {
            outcome = "WIN";
        } else {
            outcome = "LOSE";
        }
    }
    return outcome;
}

char update_character (char character)
{
    if (navswitch_push_event_p (NAVSWITCH_NORTH))
        character = 'R';

    if (navswitch_push_event_p (NAVSWITCH_WEST))
        character = 'S';

    if (navswitch_push_event_p (NAVSWITCH_SOUTH))
        character = 'P';

    return character;
}
