//******************************************************************************
//! @file $RCSfile: can_isp_protocol.h,v $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the prototypes and the macros of the
//!        library of functions of:
//!             - CAN ISP PROTOCOL
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

#ifndef _CAN_ISP_PROTOCOL_H_
#define _CAN_ISP_PROTOCOL_H_

//_____ I N C L U D E S ________________________________________________________

#include "reduced_can_lib.h"

//_____ D E F I N I T I O N S __________________________________________________

//------ IAP data
#define MAX_BASE_ISP_IAP_ID         0x7F0
#define MIN_BASE_ISP_IAP_ID         0x000

//------ Protocol commands

#define CAN_ID_SELECT_NODE          0x00

#define CAN_ID_PROG_START           0x01
#   define  CAN_INIT_PROG           0x00
#   define  CAN_FULL_ERASE_1        0x80
#   define  CAN_FULL_ERASE_2        0xFF
#   define  CAN_FULL_ERASE_3        0xFF

#define CAN_ID_PROG_DATA            0x02

#define CAN_ID_DISPLAY_DATA         0x03
#   define  CAN_READ_DATA           0x00
#   define  CAN_BLANK_CHECK         0x80

#define CAN_ID_START_APPLI          0x04
#   define  CAN_START_APPLI         0x03
#   define  CAN_RESET_APPLI         0x00
#   define  CAN_JUMP_APPLI          0x01

#define CAN_ID_SELECT_MEM_PAGE      0x06
#   define  CAN_NO_ACTION           0x00
#   define  CAN_SEL_MEM             0x01
#   define  CAN_SEL_PAGE            0x02
#   define  CAN_SEL_MEM_N_PAGE      0x03

#define CAN_ID_ERROR                0x06

#define COMMAND_OK                  0x00
#define OK_END_OF_DATA              0x00
#define OK_NEW_DATA                 0x02

//_____ D E C L A R A T I O N __________________________________________________

extern void can_isp_protocol_init(void);
extern Bool can_isp_protocol_task(void);
extern void can_isp_send_frame(void);
extern void can_isp_send_error_frame(void);

extern U16          base_isp_id;
extern U8           can_isp_rx_buffer[8];
extern st_cmd_t     can_isp_rx_msg;
extern U8           can_isp_tx_buffer[8];
extern st_cmd_t     can_isp_tx_msg;

extern Bool         can_communication_opened;
extern U8           isp_select_memory;
extern U8           isp_select_page;
extern U16          isp_start_address;
extern U16          isp_number_of_bytes;
extern Bool         isp_prog_on_going;

//______________________________________________________________________________

#endif  /* _CAN_ISP_PROTOCOL_H_ */

