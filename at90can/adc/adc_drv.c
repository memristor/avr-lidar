//******************************************************************************
//! @file $RCSfile: adc_drv.c,v $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the low level functions (drivers) of:
//!             - ADC (Analog to Digital Convertor)
//!             - for AT90CAN128/64/32
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//! This file has been validated with AVRStudio-413528/WinAVR-20070122.
//!
//! @version $Revision: 3.20 $ $Name: jtellier $
//!
//! @todo
//! @bug
//******************************************************************************

//_____  I N C L U D E S _______________________________________________________

#include "config.h"
#include "adc_drv.h"

//_____ M A C R O S ____________________________________________________________

//_____ D E F I N I T I O N S __________________________________________________

//_____ D E C L A R A T I O N S ________________________________________________

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
//------------------------------------------------------------------------------
U8 adc_init(U8 voltage_ref, Bool left_adjust, U8 adc_channel)
{
    U8 range_voltage_ref;
    U8 range_left_adjust;
        
    range_voltage_ref = TRUE;
    range_left_adjust = TRUE;
    
    // --- Enter in ADC
    Disable_adc();
    Disable_adc_it();
    Clear_adc_it_flag();
    
    // --- AVcc Voltage Reference
    switch (voltage_ref)
    {
        case EXTERNAL_AREF:            // Enable external AREF
            Enable_external_aref();
            break;
        case AVCC_AS_VREF:             // Enable AVCC as Vref
            Enable_avcc_as_vref();
            break;
        case INTERNAL_VREF:            // Enable internal Vref
            Enable_internal_vref();
            break;
        default:                       // Range error
            range_voltage_ref = FALSE;
           break;
    }
      
    // --- Left Adjust Result
    switch (left_adjust)
    {
        case LEFT_ADJUST:              // Enable left adjust result
            Set_left_adjust();
            break;
        case NO_LEFT_ADJUST:           // Disable left adjust result
            Clear_left_adjust();
            break;
        default:                       // Range error
            range_left_adjust = FALSE;
           break;
    }
      
    // --- Set Channel number
    Select_adc_channel(adc_channel);
         
    // --- Set ADC prescaler close to 125kHz
    Set_adc_prescaler(ADC_PRESCALER);    
     
    return (range_voltage_ref | range_left_adjust);     
}

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
//------------------------------------------------------------------------------
U16 adc_single_conversion(U8 adc_input_pin)
{
    U8  i;
    U16 j, adc_result;
    U16 accu_adc_result = 0;
    
    // --- To save power, the voltage over the ADC is turned off when not used.
    // --- This is done by controlling the voltage from the ADC I/O-pin.
    
    // Enable ADC I/O-pin
    ADC_PORT_OUT &= ~(1<<adc_input_pin);
    ADC_PORT_DIR &= ~(1<<adc_input_pin);
    ADC_DID_REG  |=  (1<<adc_input_pin);        

    // --- Enable the ADC
    Enable_adc();
    // --- This stabilizes INTERNAL_VREF rising level (if used) after enable ADC
    if ( Get_vref() == ((1<<REFS1)|(1<<REFS0)) )
    {
        for (j=0; j<(0x3FF<<(ADC_PRESCALER-1)); j++) {asm("nop");asm("nop");}
    }
    // --- Perform a dummy single conversion first
    Start_conv();                   // Do single conversion
    while(!Conv_complete());        // Wait for conversion done, ADIF flag active
    Clear_adc_it_flag();            // Clear ADIF flag      
        
    // --- Do the ADC conversion 16 times for better accuracy
    for(i=0; i<16; i++)             
    {
        // --- Perform a single conversion
        Start_conv();        
        // --- Wait for conversion done, ADIF flag active
        while(!Conv_complete());    
        // --- Read out ADCH/ADCL registers
        adc_result = ADC;
        // --- Accumulate result (32 samples) for later averaging
        accu_adc_result += adc_result;
        // --- Clear ADIF flag      
        Clear_adc_it_flag();
    }

    // --- Average the 16 samples
    adc_result = accu_adc_result >> 4;     
        
    // --- Disable the ADC
    Disable_adc();      

    return adc_result;
}
