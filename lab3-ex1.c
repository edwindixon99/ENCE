#include "system.h"
#include "button.h"
#include "pacer.h"
#include "pio.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "navswitch.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10
#define LOOP_TATE 500


typedef enum {STATE_INIT, STATE_PATTERN, STATE_TEXT} state_t;



//Paper pattern
static void Paper(void)
{
	tinygl_draw_line (tinygl_point(0,0), tinygl_point(0,6),7);
    tinygl_draw_line (tinygl_point(0,0), tinygl_point(4,0),5);
    tinygl_draw_line (tinygl_point(4,0), tinygl_point(4,6),7);
    tinygl_draw_line (tinygl_point(4,6), tinygl_point(0,6),5);
    
    tinygl_update();
};

//Rock pattern
static void Rock(void) 
{	        
	tinygl_draw_line (tinygl_point(0,1), tinygl_point(0,3),4);
	tinygl_draw_line (tinygl_point(1,0), tinygl_point(3,0),5);
	tinygl_draw_line (tinygl_point(4,1), tinygl_point(4,3),4);
	tinygl_draw_line (tinygl_point(1,4), tinygl_point(1,6),3);
	tinygl_draw_line (tinygl_point(3,4), tinygl_point(3,6),3);
    
	tinygl_update();
};

//Scissor pattern
static void Scissor(void)
{
	tinygl_draw_line (tinygl_point(0,0), tinygl_point(0,2),3);
	tinygl_draw_line (tinygl_point(0,2), tinygl_point(4,6),7);
	tinygl_draw_line (tinygl_point(4,0), tinygl_point(4,2),3);
	tinygl_draw_line (tinygl_point(4,2), tinygl_point(0,6),7);
    tinygl_draw_line (tinygl_point(0,0), tinygl_point(2,2),3);
    tinygl_draw_line (tinygl_point(4,0), tinygl_point(2,2),3);
    tinygl_draw_line (tinygl_point(1,2), tinygl_point(2,3),3);
    tinygl_draw_line (tinygl_point(2,3), tinygl_point(3,2),3);
    
    tinygl_update();
};





int main (void)
{
    system_init();
    button_init();
    
    //define LED matrix
    pio_config_set(LEDMAT_COL1_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_COL2_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_COL3_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_COL4_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_COL5_PIO, PIO_OUTPUT_HIGH);

    pio_config_set(LEDMAT_ROW1_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_ROW2_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_ROW3_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_ROW4_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_ROW5_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_ROW6_PIO, PIO_OUTPUT_HIGH);
    pio_config_set(LEDMAT_ROW7_PIO, PIO_OUTPUT_HIGH);
    
    //setup text and pattern
    tinygl_init(PACER_RATE);
    
    tinygl_font_set(&font5x7_1);
    
    tinygl_text_speed_set(MESSAGE_RATE);

    tinygl_text("Welcome");
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);

    

    pacer_init (PACER_RATE);

    while(1)
    {
        pacer_wait();
        button_update();
        
        //count the pattern show time
        uint64_t count1 = 10000;
        uint64_t count2 = 10000;
        uint64_t count3 = 10000;
        
        if(button_push_event_p(BUTTON1)) {
			//show 3 patterns
			while(count1 > 0) {
				tinygl_init(PACER_RATE);
				Rock();
				count1--;
			}
			
			while(count2 > 0) {
				tinygl_init(PACER_RATE);
				Paper();
				count2--;
			}
			
			while(count3 > 0) {
				tinygl_init(PACER_RATE);
				Scissor();
				count3--;
			}
				
			//explain how to play the game	
			tinygl_init(PACER_RATE);
			tinygl_text("Up is Rock, Down is paper, Left is Scissor, Right Confirm Your Choice, Press Button and Show Again");
			
		} else {
			tinygl_update();
		}			              
    }
    return 0;
}

