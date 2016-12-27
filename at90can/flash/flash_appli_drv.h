//******************************************************************************
//! @file $RCSfile: flash_appli_drv.h,v $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the prototypes and the macros of the
//!        low level functions (drivers) of:
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

#ifndef _FLASH_APPLI_DRV_H_
#define _FLASH_APPLI_DRV_H_

//_____ I N C L U D E S ________________________________________________________

//_____ D E F I N I T I O N S __________________________________________________
#define     _FLASH_TYPE_        __attribute__((section(".text")))

//_____ M A C R O S ____________________________________________________________

//--- intrinsic Flash functions in Application Flash section

    //--- for reading
    
#define     Stdflash_rd_byte(addr_byte)             \
            ({                                      \
                U16 addr = (U16)addr_byte;          \
                U8 result;                          \
                asm                                 \
                (                                   \
                    "lpm"             "\n\t"        \
                    "mov %0, r0"      "\n\t"        \
                    : "=r" (result)                 \
                    : "z" (addr)                    \
                    : "r0"                          \
                );                                  \
                result;                             \
            })


#define     Stdflash_rd_word(addr_word)             \
            ({                                      \
                U16 addr = (U16)addr_word;          \
                U16 result;                         \
                asm                                 \
                (                                   \
                    "lpm"             "\n\t"        \
                    "mov %A0, r0"     "\n\t"        \
                    "adiw r30, 1"     "\n\t"        \
                    "lpm"             "\n\t"        \
                    "mov %B0, r0"     "\n\t"        \
                    : "=r" (result), "=z" (addr)    \
                    : "1" (addr)                    \
                    : "r0"                          \
                );                                  \
                result;                             \
            })

#define     Farflash_rd_byte(addr_byte)             \
            ({                                      \
                U32 addr = (U32)addr_byte;          \
                U8 result;                          \
                asm                                 \
                (                                   \
                    "out %2, %C1"     "\n\t"        \
                    "mov r31, %B1"    "\n\t"        \
                    "mov r30, %A1"    "\n\t"        \
                    "elpm"            "\n\t"        \
                    "mov %0, r0"      "\n\t"        \
                    : "=r" (result)                 \
                    : "r" (addr),                   \
                      "I" (_SFR_IO_ADDR(RAMPZ))     \
                    : "r0", "r30", "r31"            \
                );                                  \
                result;                             \
            })

#define     Farflash_rd_word(addr_word)             \
            ({                                      \
                U32 addr = (U32)addr_word;          \
                U16 result;                         \
                asm                                 \
                (                                   \
                    "out %2, %C1"     "\n\t"        \
                    "mov r31, %B1"    "\n\t"        \
                    "mov r30, %A1"    "\n\t"        \
                    "elpm"            "\n\t"        \
                    "mov %A0, r0"     "\n\t"        \
                    "in r0, %2"       "\n\t"        \
                    "adiw r30, 1"     "\n\t"        \
                    "adc r0, __zero_reg__"  "\n\t"  \
                    "out %2, r0"      "\n\t"        \
                    "elpm"            "\n\t"        \
                    "mov %B0, r0"     "\n\t"        \
                    : "=r" (result)                 \
                    : "r" (addr),                   \
                      "I" (_SFR_IO_ADDR(RAMPZ))     \
                    : "r0", "r30", "r31"            \
                );                                  \
                result;                             \
            })

//______________________________________________________________________________

#endif // _FLASH_APPLI_DRV_H_

