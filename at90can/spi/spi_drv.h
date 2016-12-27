//******************************************************************************
//! @file $RCSfile: spi_drv.h,v $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the prototypes and the macros of the
//!        low level functions (drivers) of:
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


#ifndef _SPI_DRV_H_
#define _SPI_DRV_H_

//_____ I N C L U D E S ________________________________________________________

#include "config.h"

//_____ D E F I N I T I O N S __________________________________________________

    // ---------- SPI Controller
    // ---------- Masks
#define MSK_SPI_MASTER            (1<<MSTR)
#define MSK_SPI_DATA_MODE         ((1<<CPOL)|(1<<CPHA))
#define MSK_SPI_CLOCK_RATE        ((1<<SPR1)|(1<<SPR0))
#define MSK_SPI_CONFIG            ((1<<DORD)|MSK_SPI_MASTER|MSK_SPI_DATA_MODE|MSK_SPI_CLOCK_RATE)

    // ---------- Pre-definitions for master/slave configuration
#define SPI_MASTER                (1<<MSTR)
#define SPI_SLAVE                 (0<<MSTR)

    // ---------- Pre-definitions for bit configuration
#define SPI_LSB_FIRST             (1<<DORD)
#define SPI_MSB_FIRST             (0<<DORD)

    // ---------- Pre-definitions for data (CPOL & CPHA) modes
#define SPI_DATA_MODE_0           ((0<<CPOL)|(0<<CPHA))
#define SPI_DATA_MODE_1           ((0<<CPOL)|(1<<CPHA))
#define SPI_DATA_MODE_2           ((1<<CPOL)|(0<<CPHA))
#define SPI_DATA_MODE_3           ((1<<CPOL)|(1<<CPHA))

    // ---------- Pre-definitions for relationship between SCK and CLKIO (16-bit)
    // ---------- (The 9th is the Double SPI Speed Bit: SPI2X of SPSR)
#define SPI_CLKIO_BY_2            ((1<<(SPI2X+8))|(0<<SPR1)|(0<<SPR0)) // -- 0x100
#define SPI_CLKIO_BY_4            ((0<<(SPI2X+8))|(0<<SPR1)|(0<<SPR0)) // -- 0x000
#define SPI_CLKIO_BY_8            ((1<<(SPI2X+8))|(0<<SPR1)|(1<<SPR0)) // -- 0x101
#define SPI_CLKIO_BY_16           ((0<<(SPI2X+8))|(0<<SPR1)|(1<<SPR0)) // -- 0x001
#define SPI_CLKIO_BY_32           ((1<<(SPI2X+8))|(1<<SPR1)|(0<<SPR0)) // -- 0x102
#define SPI_CLKIO_BY_64           ((0<<(SPI2X+8))|(1<<SPR1)|(0<<SPR0)) // -- 0x102
#define SPI_CLKIO_BY_128          ((0<<(SPI2X+8))|(1<<SPR1)|(1<<SPR0)) // -- 0x103

//_____ M A C R O S ____________________________________________________________

#define Spi_enable()              (SPCR |=  (1<<SPE))
#define Spi_disable()             (SPCR &= ~(1<<SPE))
#define Spi_enable_it()           (SPCR |=  (1<<SPIE))
#define Spi_disable_it()          (SPCR &= ~(1<<SPIE))
#define Spi_select_master_mode()  (SPCR |=  (1<<MSTR))
#define Spi_select_slave_mode()   (SPCR &= ~(1<<MSTR))

#define Spi_init_config(config)   { Spi_init_bus( ((U8)config) & MSK_SPI_MASTER ); \
                                    SPCR &= ~MSK_SPI_CONFIG;                       \
                                    SPCR |= (((U8)config) & MSK_SPI_CONFIG);       \
                                    SPSR |= (U8)(config >> 8);                     }

#define Spi_read_data()           (SPDR)
#define Spi_get_byte()            (SPDR)
#define Spi_write_data(ch)        (SPDR=ch)
#define Spi_send_byte(ch)         (SPDR=ch)

#define Spi_wait_spif()           { while (Spi_tx_ready() == 0); }  //-- For any SPI rate
#define Spi_wait_eor()            Spi_wait_spif()                   //-- Wait end of reception
#define Spi_wait_eot()            Spi_wait_spif()                   //-- Wait end of transmission
#define Spi_eor()                 ((SPSR & (1<<SPIF)) == (1<<SPIF))     //-- Check end of reception
#define Spi_eot()                 ((SPSR & (1<<SPIF)) == (1<<SPIF))     //-- Check end of transmission

#define Spi_get_colision_status() (SPSR & (1<<WCOL))
#define Spi_tx_ready()            (SPSR & (1<<SPIF))
#define Spi_rx_ready()            (Spi_tx_ready())

#define Spi_init_bus(master)      (                                            \
                                  (master==0) ?                                \
                                  (DDRB|=(1<<DDB3)) :                          \
                                  (Spi_init_ss(), DDRB|=(1<<DDB2)|(1<<DDB1))   \
                                  )

// -- MASTER usage ONLY
#define Spi_init_ss()             (DDRB  |=  (1<<DDB0))  // -- Can be user re-defined 
#define Spi_disable_ss()          (PORTB |=  (1<<PB0))   // -- Can be user re-defined 
#define Spi_enable_ss()           (PORTB &= ~(1<<DDB0))  // -- Can be user re-defined 
// -- 

#define Spi_write_dummy()         { (SPDR = 0x00); Spi_wait_spif(); }
#define Spi_read_dummy()          ({  asm                                 \
                                      (                                   \
                                          "in  r0, %0"      "\n\t"        \
                                          :                               \
                                          : "I" (_SFR_IO_ADDR(SPSR))      \
                                          : "r0"                          \
                                      );                                  })
#define Spi_ack_read()            Spi_read_dummy()                                  
#define Spi_ack_write()           Spi_read_dummy()                                  
#define Spi_ack_cmd()             Spi_read_dummy()
                    
//______________________________________________________________________________

#endif  /* _SPI_DRV_H_ */

