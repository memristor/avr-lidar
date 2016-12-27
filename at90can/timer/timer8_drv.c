//******************************************************************************
//! @file $RCSfile: timer8_drv.c,v $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the low level functions (drivers) of:
//!             - 8-bit Timer(s)
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

//_____ I N C L U D E S ________________________________________________________
#include "config.h"
#include "timer8_drv.h"

//_____ D E F I N I T I O N S __________________________________________________

//_____ D E C L A R A T I O N S ________________________________________________

//_____ F U N C T I O N S ______________________________________________________

//------------------------------------------------------------------------------
//  @fn timer8_get_counter
//!
//! This function READ the 8-bit TIMER counter. "Call" compatible with
//!      16-bit Timers drivers. 
//!
//! @warning 
//!
//! @param  
//!
//! @return 8-bit counter value
//------------------------------------------------------------------------------
U8 timer8_get_counter(void)
{
    U8 u8_temp;
    
    u8_temp = Timer8_get_counter();
    
    return u8_temp;
}

