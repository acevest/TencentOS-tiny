#include "tos.h"
//#include <avr/pgmspace.h>
//#include <avr/interrupt.h>

int main(void)
{
	tos_knl_init();
	tos_knl_start();
	

    /* Replace with your application code */
    while (1) 
    {
    }
}

