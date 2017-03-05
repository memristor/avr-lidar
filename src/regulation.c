#include "regulation.h"
#include <can/can_wrapper.h>


static void set_speed(uint8_t);
static uint8_t duty = REGULATION_START_DUTY;
/*
 
    SET Kp IN FUNCTION regulation_update !!!
 
 */

void regulation_init() {
   /*
   TCCR0 - Timer Counter Control Register (TIMER0)
   -----------------------------------------------
   BITS DESCRIPTION
   

   NO:   NAME   DESCRIPTION
   --------------------------
   BIT 7 : FOC0   Force Output Compare [Not used in this example]
   BIT 6 : WGM00  Wave form generartion mode [SET to 1]
   BIT 5 : COM0A1  Compare Output Mode        [SET to 1]
   BIT 4 : COM00  Compare Output Mode        [SET to 0]

   BIT 3 : WGM01  Wave form generation mode [SET to 1]
   BIT 2 : CS02   Clock Select               [SET to 0]
   BIT 1 : CS01   Clock Select               [SET to 0]
   BIT 0 : CS00   Clock Select               [SET to 1]

   The above settings are for
   --------------------------

   Timer Clock = CPU Clock (No Prescalling)
   Mode        = Fast PWM
   PWM Output  = Non Inverted

   */

    TCCR0A|=(1<<WGM00)|(1<<WGM01)|(1<<COM0A1)|(1<<CS00);
   

   //Set OC0 PIN as output. It is  PB3 on ATmega16 ATmega32
    DDRB |= (1 << PB7);
    PORTB &= ~(1 << PB7);
   
    // Set initial speed
    update_speed();
}

/******************************************************************
Sets the duty cycle of output. 

Arguments
---------
duty: Between 0 - 255

0= 0%

255= 100%

The Function sets the duty cycle of pwm output generated on OC0 PIN
The average voltage on this output pin will be

         duty
 Vout=  ------ x 5v
         255 

This can be used to control the brightness of LED or Speed of Motor.
*********************************************************************/

void update_speed() {
    OCR0A = duty;
}



void regulation_update(uint16_t tmp_speed) {
    if(tmp_speed < REGULATION_SPEED - REGULATION_SPEED_TOLERANCE) {
        duty = (duty + 1 > 255) ? 255 : duty + 1;
    } else if (tmp_speed > REGULATION_SPEED + REGULATION_SPEED_TOLERANCE) {
        duty = (duty - 1 < REGULATION_MIN_DUTY) ? REGULATION_MIN_DUTY : duty - 1;
    }
    update_speed();
}
