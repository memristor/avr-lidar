//******************************************************************************
//! @file $RCSfile: spi_lib.h,v $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the prototypes and the macros of the
//!        library of functions of:
//!             - SPI
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

#ifndef _SPI_LIB_H_
#define _SPI_LIB_H_

//_____ I N C L U D E S ________________________________________________________
#include "spi_drv.h"

//_____ D E F I N I T I O N S __________________________________________________

//_____ D E C L A R A T I O N S ________________________________________________

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
Bool spi_init (U8 config);

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
Bool spi_test_hit (void);

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
U8 spi_putchar (U8 ch);

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
U8 spi_getchar (void);

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
void  spi_transmit_master(U8 ch);

//______________________________________________________________________________

#endif /* _SPI_LIB_H_ */
