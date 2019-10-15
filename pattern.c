#include "avr/io.h"
#include "pattern.h"
#include "tinygl.h"

//Paper pattern
void Paper(void)
{
	tinygl_draw_line (tinygl_point(0,0), tinygl_point(0,6),7);
    tinygl_draw_line (tinygl_point(0,0), tinygl_point(4,0),5);
    tinygl_draw_line (tinygl_point(4,0), tinygl_point(4,6),7);
    tinygl_draw_line (tinygl_point(4,6), tinygl_point(0,6),5);
    
    tinygl_update();
};

//Rock pattern
void Rock(void) 
{	        
	tinygl_draw_line (tinygl_point(0,1), tinygl_point(0,3),4);
	tinygl_draw_line (tinygl_point(1,0), tinygl_point(3,0),5);
	tinygl_draw_line (tinygl_point(4,1), tinygl_point(4,3),4);
	tinygl_draw_line (tinygl_point(1,4), tinygl_point(1,6),3);
	tinygl_draw_line (tinygl_point(3,4), tinygl_point(3,6),3);
    
	tinygl_update();
};

//Scissor pattern
void Scissor(void)
{
	tinygl_draw_line (tinygl_point(0,0), tinygl_point(0,2),3);
	tinygl_draw_line (tinygl_point(0,2), tinygl_point(4,6),7);
	tinygl_draw_line (tinygl_point(4,0), tinygl_point(4,2),3);
	tinygl_draw_line (tinygl_point(4,2), tinygl_point(0,6),7);
    tinygl_draw_line (tinygl_point(0,0), tinygl_point(2,2),3);
    tinygl_draw_line (tinygl_point(4,0), tinygl_point(2,2),3);
    
    tinygl_update();
};
