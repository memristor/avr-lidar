//******************************************************************************
//! @file $RCSfile: can_boot_drv.h,v $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the prototypes and the macros of the
//!        low level functions (drivers) of:
//!             - EEPROM
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

#ifndef _EEPROM_DRV_H_
#define _EEPROM_DRV_H_

//_____ I N C L U D E S ________________________________________________________

//_____ D E F I N I T I O N S __________________________________________________
#define     E2_END               E2END
#define     _EEPROM_TYPE_        __attribute__((section(".eeprom")))
#define     EEPROM_BLANK_BYTE    0xFF

//_____ M A C R O S ____________________________________________________________

  //--- Eeprom basic functions
#define     Eeprom_prog_completed       { while (EECR & (1<<EEWE)); }

  //--- Eeprom functions
#define     Eeprom_rd_byte(addr)                    \
            ({                                      \
                U8 result;                          \
                asm                                 \
                (                                   \
                    "movw r30, %1"    "\n\t"        \
                    "out %2, r30"     "\n\t"        \
                    "out %3, r31"     "\n\t"        \
                    "sbi %4, %5"      "\n\t"        \
                    "in  %0, %6"      "\n\t"        \
                    : "=r" (result)                 \
                    : "r" ((U16)addr),              \
                      "I" (_SFR_IO_ADDR(EEARL)),    \
                      "I" (_SFR_IO_ADDR(EEARH)),    \
                      "I" (_SFR_IO_ADDR(EECR)),     \
                      "M" (EERE),                   \
                      "I" (_SFR_IO_ADDR(EEDR))      \
                    : "r30", "r31"                  \
                );                                  \
                result;                             \
            })

#define     Eeprom_wr_byte(addr, data)              \
            ({                                      \
                asm                                 \
                (                                   \
                    "movw r30, %0"    "\n\t"        \
                    "out %2, r30"     "\n\t"        \
                    "out %3, r31"     "\n\t"        \
                    "out %4, %1"      "\n\t"        \
                    "sbi %5, %6"      "\n\t"        \
                    "sbi %5, %7"      "\n\t"        \
                    :                               \
                    : "r" ((U16)addr),              \
                      "r" (data),                   \
                      "I" (_SFR_IO_ADDR(EEARL)),    \
                      "I" (_SFR_IO_ADDR(EEARH)),    \
                      "I" (_SFR_IO_ADDR(EEDR)),     \
                      "I" (_SFR_IO_ADDR(EECR)),     \
                      "M" (EEMWE),                  \
                      "M" (EEWE)                    \
                    : "r30", "r31"                  \
                );                                  \
            })



//_____ D E C L A R A T I O N S ________________________________________________

//______________________________________________________________________________

#endif // _EEPROM_DRV_H_

