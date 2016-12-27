//******************************************************************************
//! @file $RCSfile: spi_lib.c,v $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the library of functions of:
//!             - SPI
//!             - AT90CAN128/64/32
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//! This file has been validated with AVRStudio-413528/WinAVR-20070122.
//!
//! @version $Revision: 3.20 $ $Name: jtellier $
//!
//! @todo
//! @bug
//******************************************************************************

/*_____ I N C L U D E S ____________________________________________________*/
#include "config.h"
#include "spi_lib.h"

//_____ D E F I N I T I O N S __________________________________________________

//_____ F U N C T I O N S ______________________________________________________

//------------------------------------------------------------------------------
//  @fn spi_init
//!
//! This function configures the SPI controller:
//!     - MASTER or SLAVE
//!     - bit timing
//!     - enable the controller
//!
//! @warning When calling this function, 'config' input parameter must be
//!          built with OR operator with pre-defined values of 'spi_drv.h'.
//!          Example:
//!          spi_init(SPI_MASTER|SPI_MSB_FIRST|SPI_DATA_MODE_2|SPI_CLKIO_BY_32)
//!
//! @param  config:  c.f. pre-defined values in "spi_drv.h" 
//!
//! @return == TRUE:  (always)
//!
//------------------------------------------------------------------------------
Bool spi_init (U8 config)
{
    Spi_init_config(config);
    Spi_enable();
    return TRUE;
}

//------------------------------------------------------------------------------
//  @fn spi_test_hit
//!
//! This function checks if a byte has been received on the SPI.
//!
//! @warning none
//!
//! @param  none
//!
//! @return == TRUE:  byte received
//!         == FALSE: NO byte received
//!
//------------------------------------------------------------------------------
Bool spi_test_hit (void)
{
    return Spi_rx_ready();
}

//------------------------------------------------------------------------------
//  @fn spi_putchar
//!
//! This function sends a byte on the SPI.
//!
//! @warning none
//!
//! @param  ch:  character to send on the SPI.
//!
//! @return  character sent.
//!
//------------------------------------------------------------------------------
U8 spi_putchar (U8 ch)
{
    Spi_send_byte(ch);
    Spi_wait_spif();
    return ch;
}

//------------------------------------------------------------------------------
//  @fn spi_getchar
//!
//! This function reads a byte on the SPI.
//!
//! @warning none
//!
//! @param  none
//!
//! @return  character read.
//!
//------------------------------------------------------------------------------
U8 spi_getchar (void)
{
    U8 ch;

    Spi_wait_spif();
    ch = Spi_get_byte();
    return ch;
}

//------------------------------------------------------------------------------
//  @fn spi_transmit_master
//!
//! This function sends a byte on the SPI. Make the transmission possible.
//!
//! @warning See SPI section in datasheet.
//!
//! @param  ch:  character to send on the SPI.
//!
//! @return  none
//!
//------------------------------------------------------------------------------
void  spi_transmit_master(U8 ch)
{
    //-- Wait for transmission complete
    Spi_wait_eot();
    
    //-- Start new transmission
    Spi_send_byte(ch);
}



