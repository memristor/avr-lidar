//******************************************************************************
//! @file $RCSfile: flash_boot_drv.h,v $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the prototypes and the macros of the
//!        low level functions (drivers) of:
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

#ifndef _FLASH_BOOT_DRV_H_
#define _FLASH_BOOT_DRV_H_

//_____ I N C L U D E S ________________________________________________________
//#include <intrinsics.h>

//_____ D E F I N I T I O N S __________________________________________________
#define     _FLASH_TYPE_        __attribute__((section(".text")))
#define     FLASH_BLANK_WORD    0xFFFF

//_____ M A C R O S ____________________________________________________________

//--- intrinsic Flash functions

    //--- for programming
    
#define     Flash_fill_temp_buffer(addr, w_value)   \
            ({                                      \
                asm                                 \
                (                                   \
                    "movw  r0, %0"    "\n\t"        \
                    "movw r30, %1"    "\n\t"        \
                    "ldi r16, %2"     "\n\t"        \
                    "out %3, r16"     "\n\t"        \
                    "spm"             "\n\t"        \
                    "clr  r1"         "\n\t"        \
                    :                               \
                    : "r" ((U16)w_value),           \
                      "r" ((U16)addr),              \
                      "M" ((U8)(1<<SPMEN)),         \
                      "I" (_SFR_IO_ADDR(SPMCSR))    \
                    : "r0", "r16", "r30", "r31"     \
                );                                  \
            })

#define     Flash_page_write(page_addr)             \
            ({                                      \
                asm                                 \
                (                                   \
                    "movw r30, %0"    "\n\t"        \
                    "ldi r16, %1"      "\n\t"       \
                    "out %2, r16"     "\n\t"        \
                    "spm"             "\n\t"        \
                    :                               \
                    : "r" ((U16)page_addr),         \
                      "M" ((U8)((1<<PGWRT)|(1<<SPMEN))),\
                      "I" (_SFR_IO_ADDR(SPMCSR))    \
                    : "r16", "r30", "r31"           \
                );                                  \
            })

#define     Flash_page_erase(page_addr)             \
            ({                                      \
                asm                                 \
                (                                   \
                    "movw r30, %0"    "\n\t"        \
                    "ldi r16, %1"     "\n\t"        \
                    "out %2, r16"     "\n\t"        \
                    "spm"             "\n\t"        \
                    :                               \
                    : "r" ((U16)page_addr),         \
                      "M" ((U8)((1<<PGERS)|(1<<SPMEN))),\
                      "I" (_SFR_IO_ADDR(SPMCSR))    \
                    : "r16", "r30", "r31"           \
                );                                  \
            })


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

    //--- others ...

#define     Flash_rww_section_enable                \
            ({                                      \
                asm                                 \
                (                                   \
                    "clr r0"          "\n\t"        \
                    "ldi r16, %0"     "\n\t"        \
                    "out %1, r16"     "\n\t"        \
                    "spm"             "\n\t"        \
                    :                               \
                    : "M" ((U8)((1<<RWWSRE)|(1<<SPMEN))),\
                      "I" (_SFR_IO_ADDR(SPMCSR))    \
                    : "r0", "r16"                   \
                );                                  \
            })

#define     Flash_prog_completed        { while (SPMCSR & (1<<SPMEN)); }


//_____ D E C L A R A T I O N S ________________________________________________

//------------------------------------------------------------------------------
//  @fn flash_fill_temp_buffer
//!
//! This function allows to load a word in the temporary Flash buffer..
//!
//! @warning none
//!
//! @param: addr    Address in Flash memory to write the 16-bit word.
//!         word    Word value to write in the Flash memory.
//!
//! @return none
//!
extern  void flash_fill_temp_buffer(U16 addr, U16 word);

//------------------------------------------------------------------------------
//  @fn flash_page_write
//!
//! This function allows to write a Flash page with the temporary Flash
//! buffer content.
//!
//! @warning: The 64K page setting must be done before (ex: setting or
//!           clearing the RAMPZ register).
//!
//! @param: page_addr   Address in the range page to write (program).
//!
//! @return none
//!
extern  void flash_page_write(U16 page_addr);

//------------------------------------------------------------------------------
//  @fn flash_page_erase
//!
//! This function allows to erase a Flash page.
//!
//! @warning: The 64K page setting must be done before (ex: setting or
//!           clearing the RAMPZ register).
//!
//! @param: page_addr   Address in the range page to erase.
//!
//! @return none
//!
extern  void flash_page_erase(U16 page_addr);

//______________________________________________________________________________

#endif // _FLASH_BOOT_DRV_H_

