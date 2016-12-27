//******************************************************************************
//! @file $RCSfile: adc_drv.h,v $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the prototypes and the macros of the
//!        low level functions (drivers) of:
//!             - ADC (Analog to Digital Convertor)
//!             - for AT90CAN128/64/32.
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//! This file has been validated with AVRStudio-413528/WinAVR-20070122.
//!
//! @version $Revision: 3.20 $ $Name: jtellier $
//!
//! @todo
//! @bug
//******************************************************************************

#ifndef _ADC_DRV_H_
#define _ADC_DRV_H_

//_____ I N C L U D E S ________________________________________________________

#include "config.h"

//_____ D E F I N I T I O N S __________________________________________________

#define EXTERNAL_AREF    0   
#define AVCC_AS_VREF     1
#define INTERNAL_VREF    3

#define LEFT_ADJUST      1   
#define NO_LEFT_ADJUST   0

#define ADC_FULL_RANGE       ((U16)(0x03FF))   // 10-bit ADC
#define INTERNAL_VREF_VALUE  ((U16)(   256))   // 2.56 Volts

#ifndef FOSC
        #error You must define FOSC in config.h
    #elif FOSC < 500
        #define ADC_PRESCALER 0x01
    #elif FOSC < 1000
        #define ADC_PRESCALER 0x02
    #elif FOSC < 2000
        #define ADC_PRESCALER 0x03
    #elif FOSC < 4000
        #define ADC_PRESCALER 0x04
    #elif FOSC < 8000
        #define ADC_PRESCALER 0x05
    #elif FOSC < 16000
        #define ADC_PRESCALER 0x06
    #elif FOSC < 20000
        #define ADC_PRESCALER 0x07
    #else
        #error Highest FOSC definition
#endif /* FOSC */

//_____ M A C R O S ____________________________________________________________

//------------------------------------------------------------------------------
//! Configure ADC Vref as external Aref (AREF pin).
//!
//! @param  none
//!
//------------------------------------------------------------------------------
#define Enable_external_aref() \
        ( ADMUX  &= ~((1<<REFS1)|(1<<REFS0)) )

//------------------------------------------------------------------------------
//! Configure ADC Vref as AVCC.
//!
//! @param  none
//!
//------------------------------------------------------------------------------
#define Enable_avcc_as_vref() \
         ( ADMUX  &= ~(1<<REFS1), ADMUX  |=  (1<<REFS0) ) 

//------------------------------------------------------------------------------
//! Configure ADC Vref as internal vref (2560 mV).
//!
//! @param  none
//!
//------------------------------------------------------------------------------
#define Enable_internal_vref()   ( ADMUX  |=  ((1<<REFS1)|(1<<REFS0)) )

//------------------------------------------------------------------------------
//! Get voltage reference setting.
//!
//! @param  none
//!
//! @return  voltage reference selection as it is in the ADC register
//!
//------------------------------------------------------------------------------
#define Get_vref()   ( ADMUX & ((1<<REFS1)|(1<<REFS0)) )

//------------------------------------------------------------------------------
//! ADC result = ADCH[1,0] / ACDL[7..0].
//!
//! @param  none
//!
//------------------------------------------------------------------------------
#define Clear_left_adjust()                  (ADMUX  &= ~(1<<ADLAR)) 

//------------------------------------------------------------------------------
//! ADC result = ADCH[7..0] / ACDL[7,6].
//!
//! @param  none
//!
//------------------------------------------------------------------------------
#define Set_left_adjust()                    (ADMUX  |=  (1<<ADLAR))

//------------------------------------------------------------------------------
//! Select ADC Channel.
//!
//! @param adc_channel   0 <= adc_channel <= 0x1F
//!
//------------------------------------------------------------------------------
#define Select_adc_channel(adc_channel)      (ADMUX  &= ~(0x1F<<MUX0), ADMUX |= (adc_channel<<MUX0))

//------------------------------------------------------------------------------
//! Configure Prescaler.
//!
//! @param adc_prescaler   0 <= adc_prescaler <= 7
//!
//------------------------------------------------------------------------------
#define Set_adc_prescaler(adc_prescaler)     (ADCSRA &= ~(0x07<<ADPS0), ADCSRA |= (adc_prescaler<<ADPS0)) 

//! Turn "ON" the ADC.
#define Enable_adc()                         (ADCSRA |=  (1<<ADEN))

//! Turn "OFF" the ADC.
#define Disable_adc()                        (ADCSRA &= ~(1<<ADEN))

//! Configure the High Speed Mode.
#define Set_adc_hsm()                        (ADCSRB |=  (1<<HSM))
#define Clear_adc_hsm()                      (ADCSRB &= ~(1<<HSM))

//! Start ADC conversion in single convertion mode.
#define Start_conv()                         (ADCSRA &= ~(1<<ADATE), ADCSRA |=  (1<<ADSC))

//! ADC conversion complete. If=0 then conversion running.
#define Conv_complete()                      (ADCSRA  &  (1<<ADIF))

//! Configure ADC interrupt.
#define Enable_adc_it()                      (ADCSRA |=  (1<<ADIE))
#define Disable_adc_it()                     (ADCSRA &= ~(1<<ADIE))
#define Clear_adc_it_flag()                  (ADCSRA |=  (1<<ADIF)) 

//_____ D E C L A R A T I O N S ________________________________________________

//_____ P R O T O T Y P E S ____________________________________________________

//------------------------------------------------------------------------------
//  @fn adc_init
//!
//! ADC channel initialization. Initialize the ADC with the selected
//! ADC_CHANNEL.
//!
//! @warning See ADC section in datasheet
//!
//! @param voltage_ref   Voltage reference source
//! @param left_adjust   Left adjust result
//! @param adc_channel   Analog channel selection
//!
//! @return range error.
//!          FALSE: Voltage reference source >3,
//!                 Left adjust result >2,
//!          TRUE:  In range
//!
U8   adc_init(U8 voltage_ref, Bool left_adjust, U8 adc_channel);

//------------------------------------------------------------------------------
//  @fn adc_single_conversion
//!
//! ADC channel single conversion. Perform an analog to digital single
//! conversion on the selected ADC_CHANNEL.
//!
//! @warning Perform a "adc_init()" before to choose the adc_channel
//!
//! @param adc_input_pin   ADC I/O pin selection
//!
//! @return Conversion value (U16).
//!
U16  adc_single_conversion(U8 adc_input_pin);

//______________________________________________________________________________

#endif  // _ADC_DRV_H_ 














