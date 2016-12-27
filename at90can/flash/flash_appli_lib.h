//******************************************************************************
//! @file $RCSfile: flash_appli_lib.h,v $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the prototypes and the macros of the
//!        library of functions of:
//!             - Flash (code in "Application Flash Section")
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

#ifndef _FLASH_APPPLI_LIB_H_
#define _FLASH_APPPLI_LIB_H_

//_____ I N C L U D E S ________________________________________________________

#include "config.h"
#include "flash_appli_drv.h"

//_____ M A C R O S ____________________________________________________________

//------------------------------------------------------------------------------
//  @fn MACRO-FUNCTION Call_flash_appli_wr_block
//!
//! Call to the "flash_api_wr_block()" function of the BootLoader
//!
//! @warning: none
//!
//! @param none
//!
//! @return none
//!
#define Call_flash_appli_wr_block() { asm ("call ((U16)((FLASHEND - (FLASH_API_WR_BLOCK_FUNCTION_SIZE -1))>>1))"::); }

//_____ D E F I N I T I O N S __________________________________________________
#define     FLASH_API_WR_BLOCK_FUNCTION_SIZE    0x06     // Size of "flash_api_wr_block()" of
                                                         // the BootLoader

//_____ D E C L A R A T I O N S ________________________________________________

//------------------------------------------------------------------------------
//  @fn flash_rd_byte
//!
//! This function allows to read a byte in 64K bytes of Flash memory.
//!
//! @warning: _RAMPZ_IS_USED must be defined in "config.h"
//! @warning: The 64K page setting must be done before (ex: setting
//!           or clearing the RAMPZ register).
//!
//! @param: addr_byte   Address to read the byte in Flash memory.
//!
//! @return:    Value read in the Flash memory.
//!
extern U8 flash_rd_byte(U16 addr_byte);

//------------------------------------------------------------------------------
//  @fn flash_rd_word
//!
//! This function allows to read a word in 64K bytes of Flash memory.
//!
//! @warning: _RAMPZ_IS_USED must be defined in "config.h"
//! @warning: 1 - The address of the word is an even byte address.
//!           2 - The 64K page setting must be done before (ex: setting
//!               or clearing the RAMPZ register).
//!
//! @param: addr_word   Address to read the word in Flash memory.
//!
//! @return:    Value read in the Flash memory.
//!
extern U16 flash_rd_word(U16 addr_word);

//------------------------------------------------------------------------------
//  @fn flash_appli_wr_byte
//!
//! This function allows to write a byte in 64K bytes of Flash memory.
//!
//! @warning: _RAMPZ_IS_USED must be defined in "config.h"
//! @warning: The 64K page setting must be done before (ex: setting
//!           or clearing the RAMPZ register).
//!
//! @param: addr_byte   Address to write the byte in Flash memory.
//!         value       Value to write in the Flash memory.
//!
//! @return none
//!
extern void flash_appli_wr_byte(U16 addr_byte, U8 value);

//------------------------------------------------------------------------------
//  @fn flash_appli_wr_block
//!
//! This application function calls flash_wr_block() function of the BootLoader
//!    if the application is runnning supervised by the BootLoader developped
//!    by ATMEL (see "can_bootloader_example" or "can_uart_bootloader_example").
//!
//! @warning: _RAMPZ_IS_USED must be defined in "config.h"
//! @warning: The 64K page setting must be done before (ex: setting
//!           or clearing the RAMPZ register).
//! @warning: See flash_wr_block() function in "flash_boot_lib.c".
//!
//! @param: - src      Source of (SRAM) buffer Address.
//!         - dest     Destination, start address in Flash memory where data
//!                    must be written.
//!         - byte_nb  Number of byte to write.
//!
//! @return none
//!
extern void flash_appli_wr_block(U8* src, U16 dest, U16 byte_nb);

//______________________________________________________________________________

#endif  // _FLASH_APPPLI_LIB_H_
