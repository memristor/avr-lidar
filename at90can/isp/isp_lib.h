//******************************************************************************
//! @file $RCSfile: isp_lib.h,v $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the prototypes and the macros of the
//!        ISP routines available for:
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
#ifndef _ISP_LIB_H_
#define _ISP_LIB_H_

//_____ I N C L U D E S ________________________________________________________

//_____ D E F I N I T I O N S __________________________________________________
#define      REGISTER_BYTE_AT   *(U8 volatile*)

//----------- Bootloader identification definition ----
// Boot Mem Def
//#define BOOT_VERSION    0x03 // Ver 03: JT-11.NOV.05
#define BOOT_VERSION    0x04 // Ver 04: JT-10.MAR.07
#define BOOT_ID1        0xD1
#define BOOT_ID2        0xD2

#define SECUR16 0xF0F0

#define BSB_DEFAULT     0xFF
#define SSB_DEFAULT     0xFF
#define EB_DEFAULT      0xFF
#define BTC1_DEFAULT    0xFF
#define BTC2_DEFAULT    0xFF
#define BTC3_DEFAULT    0xFF
#define NNB_DEFAULT     0xFF
#define CRIS_DEFAULT    0x00
#define SA_H_DEFAULT    0x00
#define SA_L_DEFAULT    0x00

#define BSB  ((U16) &boot_conf[0])
#define SSB  ((U16) &boot_conf[1])
#define EB   ((U16) &boot_conf[2])
#define BTC1 ((U16) &boot_conf[3])
#define BTC2 ((U16) &boot_conf[4])
#define BTC3 ((U16) &boot_conf[5])
#define NNB  ((U16) &boot_conf[6])
#define CRIS ((U16) &boot_conf[7])
#define SA_H ((U16) &boot_conf[8])
#define SA_L ((U16) &boot_conf[9])

#define BOOT_CONF_SIZE         10
#define SSB_INDEX            0x01
#define SSB_NO_SECURITY      0xFF
#define SSB_WR_PROTECTION    0xFE
#define SSB_RD_WR_PROTECTION 0xFC

//-------- Memory Definition -----------------
#define MEM_FLASH               0
#define MEM_EEPROM              1
#define MEM_SIGNATURE           2
#define MEM_BOOT_INF            3   // Boot Loader information
#define MEM_BOOT_CONF           4   // Boot Loader configuration
#define MEM_HW_REG              5
#define MEM_DEF_MAX             MEM_HW_REG
#define MEM_DEFAULT             MEM_FLASH

#define PAGE_DEFAULT            0x00
#define ADD_DEFAULT             0x0000
#define N_DEFAULT               0x0001

#define LOCAL_BUFFER_SIZE       0x100

//_____ M A C R O S ____________________________________________________________

//_____ D E C L A R A T I O N __________________________________________________


extern U8   __attribute__((section (".bootconf"))) boot_conf[];
extern U8   isp_select_memory;
extern U8   isp_select_page;
extern U16  isp_start_address;
extern U16  isp_number_of_bytes;
extern U16  isp_start_address_copy;
extern U16  isp_number_of_bytes_copy;
extern Bool isp_prog_on_going;

extern U8   local_buffer[LOCAL_BUFFER_SIZE];
extern U16  loc_buf_index;

//------------------------------------------------------------------------------
//  @fn isp_jump_to
//!
//! This function analyzes the "jump to" comming from ISP PROTOCOL.
//!
//! @warning none
//!
//! @param:  jump_addr  Addresse to jump to
//!
//! @return none
//!
extern void  isp_jump_to(U16 jump_addr);

//------------------------------------------------------------------------------
//  @fn isp_set_memory
//!
//! This function analyzes and set the memory code comming from ISP PROTOCOL.
//!
//! @warning none
//!
//! @param:  mem_code  Memory Code (from 0 to MEM_DEF_MAX)
//!
//! @return none
//!
extern void  isp_set_memory(U8 mem_code);

//------------------------------------------------------------------------------
//  @fn isp_set_page
//!
//! This function analyzes and set the page number comming from ISP PROTOCOL.
//!
//! @warning none
//!
//! @param:  page_nb  Page number
//!
//! @return none
//!
extern void  isp_set_page(U8 page_nb);

//------------------------------------------------------------------------------
//  @fn isp_address_range
//!
//! This function analyzes and set the "isp_start_address" inside 64K range
//! and the "isp_number_of_bytes" comming from ISP PROTOCOL.
//!
//! @warning: 1 - "isp_start_address" inside 64K range
//!           2 - "isp_number_of_bytes": 0x0001=1 byte up to 0xFFFF=65535
//!                bytes
//!
//! @param:  start_addr = start address byte inside 64K range
//!          end_addr   = end address byte inside 64K range
//!
//! @return none
//!
extern void  isp_address_range(U16 start_addr, U16 end_addr);

//------------------------------------------------------------------------------
//  @fn isp_memory_erase
//!
//! This function performes a full erase (if it is possible) of the memory
//! selected, code number comming from ISP PROTOCOL.
//!
//! @warning: 1 - Some of memories are "READ Only"
//!           2 - Erase controled by "SSB" (Software Security Byte)
//!           3 - Boot Loader Configuration erased with "Default Boot Loader
//!               Configuration"
//!
//! @param  none
//!
//! @return: 0 = Command available
//!          1 = Command failed or "READ Only" memory
//!
extern Bool  isp_memory_erase(void);

//------------------------------------------------------------------------------
//  @fn isp_read_block
//!
//! This function performes a read of "isp_number_of_bytes" of bytes, block
//! by block (size of buffer passed as parameter) on the selected memory
//! ("isp_select_memory") and in the selected page ("isp_select_page") from
//! "isp_start_address".
//!
//! @warning:  This function works on copies of "isp_start_address" and
//!            "isp_number_of_bytes" according with the size of the buffer
//!            passed as parameter. In fact, the calling function is in
//!            charge of manage copies for restoring initial values.
//!
//! @param: - isp_buffer = block for output data
//!         - size = size of isp_buffer
//!
//! @return: 0x00 - "isp_read_block()" block available and transfer
//!                  not finished
//!          0x01 - "isp_read_block()" last block, then "isp_number_of_bytes"
//!                  is equal to size of this last block.
//!          0xFF - Software Security Byte Set, read not available
//!
extern U8  isp_read_block(U8* isp_buffer, U16 size);

//------------------------------------------------------------------------------
//  @fn isp_blank_check
//!
//! This function performes a blank check of "isp_number_of_bytes" of bytes
//! on the selected memory ("isp_select_memory") and in the selected page
//! ("isp_select_page") from "isp_start_address".
//!
//! @warning  none
//!
//! @param  none
//!
//! @return: TRUE  (1) = no error, memory range blank.
//!          FALSE (0) = "isp_blank_check()" error, then "isp_start_address"
//!                       is equal to the address of the first byte not blank.
//!
extern Bool  isp_blank_check(void);

//------------------------------------------------------------------------------
//  @fn isp_prog_block
//!
//! This function performes a programmation of "isp_number_of_bytes" of bytes,
//! block by block (size of buffer passed as parameter) on the selected
//! memory ("isp_select_memory") and in the selected page ("isp_select_page")
//! from "isp_start_address".
//!
//! @warning:  This function works with "isp_start_address" and
//!            "isp_number_of_bytes" according with the size of the buffer
//!            passed as parameter. In fact, the calling function is in
//!            charge of manage copies for restoring initial values.
//!
//! @param: - isp_buffer = block for input data
//!         - size = size of isp_buffer
//!
//! @return: 0x00 = "isp_prog_block()" block programming completed and transfer
//!                  not finished.
//!          0x01 = "isp_prog_block()" last block, then "isp_number_of_bytes"
//!                  is equal to size of this last block.
//!          0xFF = Software Security Byte Set, write not available.
//!
extern U8  isp_prog_block(U8* isp_buffer, U16 size);

//------------------------------------------------------------------------------
//  @fn get_conf_byte
//!
//! This function gets a Bootloader Configuration Byte.
//!
//! @warning  none
//!
//! @param:  "Configuration_Byte" name
//!
//! @return: "Configuration_Byte" value.
//!
extern U8  get_conf_byte(U16 conf_byte);

//------------------------------------------------------------------------------
//  @fn put_conf_byte
//!
//! This function writess a Bootloader Configuration Byte.
//!
//! @warning  none
//!
//! @param:  "Configuration_Byte" address
//!
//! @return: "Configuration_Byte" value.
//!
void  put_conf_byte(U16 conf_byte, U8 value);

//------------------------------------------------------------------------------
//  @fn put_conf_block
//!
//! This function writes a Bootloader Configuration Block.
//!
//! @warning  none
//!
//! @param: - src      Source of (SRAM) buffer Address.
//!         - dest     "Configuration_Byte" first address.
//!         - byte_nb  Number of "Configuration_Bytes" to write.
//!
//! @return none
//!
void  put_conf_block(U8* src, U16 dest, U16 byte_nb);

//______________________________________________________________________________

#endif  // _ISP_LIB_H_
