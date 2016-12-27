//******************************************************************************
//! @file $RCSfile: flash_boot_lib.h,v $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the prototypes and the macros of the
//!        library of functions of:
//!             - Flash (code in "Boot Flash Section")
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

#ifndef _FLASH_BOOT_LIB_H_
#define _FLASH_BOOT_LIB_H_

//_____ I N C L U D E S ________________________________________________________

#include "config.h"
#include "flash_boot_drv.h"

//_____ M A C R O S ____________________________________________________________

//_____ D E F I N I T I O N S __________________________________________________

//_____ D E C L A R A T I O N S ________________________________________________

//------------------------------------------------------------------------------
//  @fn flash_rd_byte
//!
//! This function allows to read a byte in 64K bytes of Flash memory.
//!
//! @warning: The 64K page setting must be done before (ex: setting
//!           or clearing the RAMPZ register).
//!
//! @param: addr_byte   Address to read the byte in Flash memory.
//!
//! @return:     Value read in the Flash memory.
//!
extern U8 flash_rd_byte(U16 addr_byte);

//------------------------------------------------------------------------------
//  @fn flash_rd_word
//!
//! This function allows to read a word in 64K bytes of Flash memory.
//!
//! @warning: 1 - The address of the word is an even byte address.
//!           2 - The 64K page setting must be done before (ex: setting
//!               or clearing the RAMPZ register).
//!
//! @param: addr_word   Address to read the word in Flash memory.
//!
//! @return:    Value read in the Flash memory.
//!
extern U16 flash_rd_word(U16 addr_word);

 //-----------------------------------------------------------------------------
//  @fn flash_wr_byte
//!
//! This function allows to write a byte in 64K bytes of Flash memory.
//!
//! @warning: The 64K page setting must be done before (ex: setting
//!           or clearing the RAMPZ register).
//!
//! @param: addr_byte   Address to write the byte in Flash memory.
//!         value       Value to write in the Flash memory.
//!
//! @return none
//!
extern void flash_wr_byte(U16 addr_byte, U8 value);

//------------------------------------------------------------------------------
//  @fn flash_wr_block
//!
//! This function allows to write up to 65535 bytes (64K Bytes-1 byte) in
//! the Flash memory.
//! This function manages alignment issue (byte and page alignments).
//!
//!---------------------------------------------------------------------------..
//! CARE: Bytes to program must be in a different page that flash_wr_block()  ||
//!       function which is dedicated to program them.                        ||
//!       The cause is to program some bytes the following steps are needed:  ||
//!       - Fill_Temporary_Buffer (size=1 page length)                        ||
//!       - Erase_Page                                                        ||
//!       - Program_Page                                                      ||
//!       If the bytes to program are in the page of the function, the step:  ||
//!       Erase_Page --> Program_page is disturbed because blank words are    ||
//!       fetched in place of Program_Page !!!                                ||
//!---------------------------------------------------------------------------''
//!
//! @warning: 1 - This function isn't able to address the fully 64K bytes
//!               but we cannot find in the device a source buffer up to
//!               64K bytes.
//!           2 - The 64K page setting must be done before (ex: setting
//!               or clearing the RAMPZ register).
//!
//! @param: - src      Source of (SRAM) buffer Address.
//!         - dest     Destination, start address in Flash memory where data
//!                    must be written.
//!         - byte_nb  Number of byte to write.
//!
//! @return none
//!
extern void flash_wr_block(U8* src, U16 dest, U16 byte_nb);

//------------------------------------------------------------------------------
//  @fn flash_full_erase
//!
//! This function erases the whole Flash memory. It manages itself the RAMPZ.
//!
//! @warning none
//!
//! @param none
//!
//! @return none
//!
extern void flash_full_erase(void);

//------------------------------------------------------------------------------
//  @fn flash_page_blank_check
//!
//! This function blank checks a page of Flash memory.
//!
//! @warning: The 64K page setting must be done before (ex: setting or
//!           clearing the RAMPZ register).
//!
//! @param: page_addr   Address in the range page to blank check.
//!
//! @return: 1 - 0000 0000 0000 0000 binary = blank page
//!          2 - 1xxx xxxx xxxx xxxx binaty = first byte address not blank
//!                                           in the page (offset in the page)
//!
extern U16 flash_page_blank_check(U16 page_addr);

//______________________________________________________________________________

#endif  // _FLASH_BOOT_LIB_H_
