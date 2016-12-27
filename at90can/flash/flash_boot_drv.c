//******************************************************************************
//! @file $RCSfile: flash_boot_drv.c,v $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the low level functions (drivers) of:
//!             - Flash (code in "Boot Flash Section")
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
#include "flash_boot_drv.h"

//_____ D E F I N I T I O N S __________________________________________________

//_____ F U N C T I O N S _________lashed i_____________________________________________

//------------------------------------------------------------------------------
//  @fn flash_fill_temp_buffer
//!
//! This function allows to load a word in the temporary Flash buffer..
//!
//! @warning This function must be fused in the NRWW Flash section.
//!
//! @param: addr    Address in Flash memory to write the 16-bit word.
//!         word    Word value to write in the Flash memory.
//!
//! @return none
//!
//------------------------------------------------------------------------------
void flash_fill_temp_buffer(U16 addr, U16 word)
{
      Flash_fill_temp_buffer(addr, word);
      //- Wait for SPMEN flag cleared
      Flash_prog_completed;
}

//------------------------------------------------------------------------------
//  @fn flash_page_write
//!
//! This function allows to write a Flash page with the temporary Flash
//! buffer content.
//!
//! @warning: 1 - This function must be fused in the NRWW Flash section.
//!           2 - The 64K page setting must be done before (ex: setting or
//!               clearing the RAMPZ register).
//!
//! @param: page_addr   Address in the range page to write (program).
//!
//! @return none
//!
//------------------------------------------------------------------------------
void flash_page_write(U16 page_addr)
{
      //- Verify if SPMEN flag is cleared
      Flash_prog_completed;
      Flash_page_write(page_addr);
      //- Wait for SPMEN flag cleared
      Flash_prog_completed;
}

//------------------------------------------------------------------------------
//  @fn flash_page_erase
//!
//! This function allows to erase a Flash page.
//!
//! @warning: 1 - This function must be fused in the NRWW Flash section.
//!           2 - The 64K page setting must be done before (ex: setting or
//!               clearing the RAMPZ register).
//!
//! @param: page_addr   Address in the range page to erase.
//!
//! @return none
//!
//------------------------------------------------------------------------------
void flash_page_erase(U16 page_addr)
{
      //- Verify if SPMEN flag is cleared
      Flash_prog_completed;
      Flash_page_erase(page_addr);
      //- Wait for SPMEN flag cleared
      Flash_prog_completed;
}

