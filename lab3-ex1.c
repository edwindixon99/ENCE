#include "system.h"
#include "button.h"
#include "pacer.h"
#include "pio.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "navswitch.h"
#include "timer.h"


#define PACER_RATE 500
#define MESSAGE_RATE 10
#define LOOP_TATE 500

typedef enum {STATE_INIT, STATE_PATTERN, STATE_TEXT} state_t;


/** Define PIO pins driving LED matrix rows.  */
static const pio_t rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO,
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};

static const uint8_t Rock[] =
{
    0b0001110,
    0b1110001,
    0b0000001,
    0b1110001,
    0b0001110,
};

static const uint8_t Paper[] =
{
    0b1000111,
    0b0101010,
    0b0010100,
    0b0101010,
    0b1000111,
};


/** Define PIO pins driving LED matrix columns.  */
static const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};


static void display_column (uint8_t row_pattern, uint8_t current_column)
{
    static uint8_t prevcolumn = 0;
    pio_output_high(cols[prevcolumn]);
    for (int i =0; i<7; i++) {
        if ((row_pattern >> i) &1) {
            pio_output_low(rows[i]);
        } else {
            pio_output_high(rows[i]);
        }
    }
    pio_output_low(cols[current_column]);
    prevcolumn = current_column;
}


static void display()
{
	tinygl_clear();
	uint8_t Rock_column = 0;
	while(Rock_column <= 6) {
		display_column (Rock[Rock_column], Rock_column);

		Rock_column++;

		if(Rock_column > (LEDMAT_COLS_NUM - 1))
		{
			Rock_column = 0;
		}
	}
}


static state_t state = STATE_INIT;

int main (void)
{
    system_init();
    button_init();
    uint8_t Rock_column = 0;
    uint8_t Scissor_column = 0;
    uint8_t pattern = 0;
    uint8_t Scissor = 0;
    
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
    
    
    tinygl_init(PACER_RATE);
    
    tinygl_font_set(&font5x7_1);
    
    tinygl_text_speed_set(MESSAGE_RATE);

    /* TODO: Initialise tinygl. */
    tinygl_text("Welcome");
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);

    /* TODO: Set the message using tinygl_text().  */
    

    pacer_init (PACER_RATE);

    while(1)
    {
        pacer_wait();
        button_update();
        navswitch_init();
        navswitch_update ();

        
        if(navswitch_push_event_p(NAVSWITCH_NORTH)) {
			switch(state) 
			{
			case STATE_INIT:
				state = STATE_TEXT;
				break;
				
			case STATE_TEXT:
				tinygl_text("Up is Rock");
				tinygl_update();
				state = STATE_PATTERN;
				break;
				
			case STATE_PATTERN:
				break;
				
			default:
				break;
			}
		} else {
			tinygl_update();
		}
		
		if(navswitch_push_event_p(NAVSWITCH_NORTH)) {
			switch(state) 
			{
				case STATE_INIT:
					break;
				case STATE_TEXT:
					break;
				case STATE_PATTERN:
					display();
					break;
				default:
					break;
				}
			} else {
				tinygl_update();
			}
		
					
					
		
		
		
		/*if(navswitch_push_event_p(NAVSWITCH_SOUTH)) {
			Scissor = 1;
			pattern = 0;
		}

			
		if(Scissor == 1) {
			
			display_column (Paper[Scissor_column], Scissor_column);
			Scissor_column++;
		
			if (Scissor_column > (LEDMAT_COLS_NUM - 1))
			{
				Scissor_column = 0;
			}
		}*/
			
		
        /* TODO: Call the tinygl update function. */
        
    }
    return 0;
}

