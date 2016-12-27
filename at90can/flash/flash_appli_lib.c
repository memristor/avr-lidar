//******************************************************************************
//! @file $RCSfile: flash_appli_lib.c,v $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the library of functions of:
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

//_____ I N C L U D E S ________________________________________________________
#include "config.h"
#include "flash_appli_lib.h"
#include "flash_appli_drv.h"

//_____ D E F I N I T I O N S __________________________________________________

//_____ F U N C T I O N S ______________________________________________________

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
//------------------------------------------------------------------------------
U8 flash_rd_byte(U16 addr_byte)
{
#if defined(_RAMPZ_IS_USED_)
    U32  far_addr_byte;

    far_addr_byte = (((U32)(RAMPZ))<<16) | ((U32)(addr_byte));
    return (Farflash_rd_byte(far_addr_byte));

#else
    return (Stdflash_rd_byte(addr_byte));

#endif   //- If _RAMPZ_IS_USED_ ...

//    return (Flash_rd_byte(addr_word));
}

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
//------------------------------------------------------------------------------
U16 flash_rd_word(U16 addr_word)
{
#if defined(_RAMPZ_IS_USED_)
    U32  far_addr_word;

    far_addr_word = (((U32)(RAMPZ))<<16) | ((U32)(addr_word));
    return (Farflash_rd_word(far_addr_word));

#else
    return (Stdflash_rd_word(addr_word));

#endif   //- If _RAMPZ_IS_USED_ ...

//    return (Flash_rd_word(addr_word));
}

//------------------------------------------------------------------------------
//  @fn flash_appli_wr_byte
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
//------------------------------------------------------------------------------
void flash_appli_wr_byte(U16 addr_byte, U8 value)
{
    flash_appli_wr_block(&value, addr_byte, 1);
}

//------------------------------------------------------------------------------
//  @fn flash_appli_wr_block
//!
//! This application function calls flash_wr_block() function of the BootLoader
//!    if the application is runnning supervised by the BootLoader developped
//!    by ATMEL (see "can_bootloader_example" or "can_uart_bootloader_example").
//!
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
//------------------------------------------------------------------------------
void flash_appli_wr_block(U8* src, U16 dest, U16 byte_nb)
{
    Call_flash_appli_wr_block();
}
