//******************************************************************************
//! @file $RCSfile: timer8_drv.h,v $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the prototypes and the macros of the
//!        low level functions (drivers) of:
//!             - 8-bit timer(s)
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

#ifndef _TIMER8_DRV_H_
#define _TIMER8_DRV_H_

//_____ I N C L U D E S ________________________________________________________

#include "config.h"

//_____ G E N E R A L    D E F I N I T I O N S _________________________________

#ifndef FOSC
#  error  You must define FOSC in "config.h" file
#endif
    // ----------
#ifndef TIMER8_0             // 8-bit TIMER 0 Defintion
#define TIMER8_0        0x00
#endif
#ifndef TIMER8_2             // 8-bit TIMER 2 Defintion
#define TIMER8_2        0x02
#endif
#ifndef BOTH_TIMER8          // Both the 8-bit TIMERs Defintion
#define BOTH_TIMER8     0xFF
#endif

//_____ M A C R O S ____________________________________________________________

    // ---------- Two ways to have a look on the things
#define Timer8_set_pwm_a(value)    ( Timer8_set_compare_a(value) )
#define Timer8_set_pwm(value)      ( Timer8_set_pwm_a(value) )
#define Timer8_get_pwm_a()         ( Timer8_get_compare_a() )
#define Timer8_get_pwm()           ( Timer8_get_pwm_a() )
    // ---------- If no clock, the timer is off !
#define Timer8_off()                 Timer8_set_clock(TIMER8_NO_CLOCK)

    
#ifndef USE_TIMER8
#       error You must define USE_TIMER8 to TIMER8_0 or TIMER8_2 or BOTH_TIMER8 in "config.h" file

#   elif (USE_TIMER8 == TIMER8_0)        //!< 8-bit TIMER 0 used
    //!< =================================
    //!< ------ Only TIMER8_0 used ------
    //!< =================================
#       define Timer8_select(timer8_num)        // Empty !
    // ---------- Macros
#       define Timer8_clear()                  { TCCR0A=0; TCNT0=0; OCR0A=0; }
        // ----------
#       define Timer8_set_counter(value)       ( TCNT0 = value )
#       define Timer8_get_counter()            ( TCNT0 )
        // ----------
#       define Timer8_set_compare_a(value)     ( OCR0A = value )
#       define Timer8_set_compare(value)       ( Timer8_set_compare_a(value) )          // No index specified
#       define Timer8_get_compare_a()          ( OCR0A )
#       define Timer8_get_compare()            ( Timer8_get_compare_a() )               // No index specified
        // ----------
#       define Timer8_set_mode_output_a(conf)  ( TCCR0A = (TCCR0A & (~TIMER8_COMP_MODE_MASK_A)) | (conf << COM0A0) )
#       define Timer8_set_mode_output(conf)    ( Timer8_set_mode_output_a(conf) )       // No index specified
#       define Timer8_get_mode_output_a()      ((TCCR0A & TIMER8_COMP_MODE_MASK_A) >> COM0A0 )
#       define Timer8_get_mode_output()        ( Timer8_get_mode_output_a() )           // No index specified
        // ----------
#       define Timer8_set_waveform_mode(conf)  ( TCCR0A = (TCCR0A & (~TIMER8_WGM_RA_MASK)) |  \
                                               ( (((conf & 0x02) >> 1) << WGM01) | ((conf & 0x1) << WGM00) ) )
#       define Timer8_get_waveform_mode()      ( ((TCCR0A & (1<<WGM00)) >> WGM00) |  \
                                               ( ((TCCR0A & (1<<WGM01)) >> WGM01) << 0x1) )
        // ----------
#       define Timer8_set_clock(value)         ( TCCR0A = (TCCR0A & (~TIMER8_CLK_MASK)) | (value << CS00) )
#       define Timer8_get_clock()              ((TCCR0A & TIMER8_CLK_MASK) >> CS00 )
        // ----------
#       define Timer8_overflow_it_enable()    ( TIMSK0 |=  (1<<TOIE0)  )
#       define Timer8_overflow_it_disable()   ( TIMSK0 &= ~(1<<TOIE0)  )
#       define Timer8_compare_a_it_enable()   ( TIMSK0 |=  (1<<OCIE0A) )
#       define Timer8_compare_a_it_disable()  ( TIMSK0 &= ~(1<<OCIE0A) )
#       define Timer8_compare_it_enable()     ( Timer8_compare_a_it_enable()  )
#       define Timer8_compare_it_disable()    ( Timer8_compare_a_it_disable() )

#       define Timer8_get_overflow_it_mask()  ((TIMSK0  &  (1<<TOIE0) ) >> TOIE0  )
#       define Timer8_get_compare_a_it_mask() ((TIMSK0  &  (1<<OCIE0A)) >> OCIE0A )
#       define Timer8_get_compare_it_mask()   ( Timer8_get_compare_a_it_mask() )
        // ----------
#       define Timer8_clear_overflow_it()     ( TIFR0 |=  (1<<TOV0)  )
#       define Timer8_clear_compare_a_it()    ( TIFR0 |=  (1<<OCF0A) )
#       define Timer8_clear_compare_it()      ( Timer8_clear_compare_a_it() )
#       define Timer8_get_overflow_it()       ((TIFR0  &  (1<<TOV0) ) >> TOV0  )
#       define Timer8_get_compare_a_it()      ((TIFR0  &  (1<<OCF0A)) >> OCF0A )
#       define Timer8_get_compare_it()        ( Timer8_get_compare_a_it() )

#   elif USE_TIMER8 == TIMER8_2          //!< 8-bit TIMER 2 used
    //!< =================================
    //!< ------ Only TIMER8_2 used ------
    //!< =================================
#       define Timer8_select(timer8_num)        // Empty !
    // ---------- Macros
#       define Timer8_clear()                  { TCCR2A=0; TCNT2=0; OCR2A=0; }
        // ----------
#       define Timer8_set_counter(value)       ( TCNT2 = value )
#       define Timer8_get_counter()            ( TCNT2 )
        // ----------
#       define Timer8_set_compare_a(value)     ( OCR2A = value )
#       define Timer8_set_compare(value)       ( Timer8_set_compare_a(value) )          // No index specified
#       define Timer8_get_compare_a()          ( OCR2A )
#       define Timer8_get_compare()            ( Timer8_get_compare_a() )               // No index specified
        // ----------
#       define Timer8_set_mode_output_a(conf)  ( TCCR2A = (TCCR2A & (~TIMER8_COMP_MODE_MASK_A)) | (conf << COM2A0) )
#       define Timer8_set_mode_output(conf)    ( Timer8_set_mode_output_a(conf) )       // No index specified
#       define Timer8_get_mode_output_a()      ((TCCR2A & TIMER8_COMP_MODE_MASK_A) >> COM2A0 )
#       define Timer8_get_mode_output()        ( Timer8_get_mode_output_a() )           // No index specified
        // ----------
#       define Timer8_set_waveform_mode(conf)  ( TCCR2A = (TCCR2A & (~TIMER8_WGM_RA_MASK)) |  \
                                               ( (((conf & 0x02) >> 1) << WGM21) | ((conf & 0x1) << WGM20) ) )
#       define Timer8_get_waveform_mode()      ( ((TCCR2A & (1<<WGM20)) >> WGM20)          |  \
                                               ( ((TCCR2A & (1<<WGM21)) >> WGM21) << 0x1) )
        // ----------
#       define Timer8_set_clock(value)         ( TCCR2A = (TCCR2A & (~TIMER8_CLK_MASK)) | (value << CS20) )
#       define Timer8_get_clock()              ((TCCR2A & TIMER8_CLK_MASK) >> CS20 )
        // ----------
#       define Timer8_overflow_it_enable()    ( TIMSK2 |=  (1<<TOIE2)  )
#       define Timer8_overflow_it_disable()   ( TIMSK2 &= ~(1<<TOIE2)  )
#       define Timer8_compare_a_it_enable()   ( TIMSK2 |=  (1<<OCIE2A) )
#       define Timer8_compare_a_it_disable()  ( TIMSK2 &= ~(1<<OCIE2A) )
#       define Timer8_compare_it_enable()     ( Timer8_compare_a_it_enable()  )
#       define Timer8_compare_it_disable()    ( Timer8_compare_a_it_disable() )

#       define Timer8_get_overflow_it_mask()  ((TIMSK2  &  (1<<TOIE2) ) >> TOIE2  )
#       define Timer8_get_compare_a_it_mask() ((TIMSK2  &  (1<<OCIE2A)) >> OCIE2A )
#       define Timer8_get_compare_it_mask()   ( Timer8_get_compare_a_it_mask() )
        // ----------
#       define Timer8_clear_overflow_it()     ( TIFR2 |=  (1<<TOV2)  )
#       define Timer8_clear_compare_a_it()    ( TIFR2 |=  (1<<OCF2A) )
#       define Timer8_clear_compare_it()      ( Timer8_clear_compare_a_it() )
#       define Timer8_get_overflow_it()       ((TIFR2  &  (1<<TOV2) ) >> TOV2  )
#       define Timer8_get_compare_a_it()      ((TIFR2  &  (1<<OCF2A)) >> OCF2A )
#       define Timer8_get_compare_it()        ( Timer8_get_compare_a_it() )

#   elif USE_TIMER8 == BOTH_TIMER8   //!< Both the 8-bit TIMERs
    //!< =========================================
    //!< ------ Both TIMER8_0 & 2 are used ------
    //!< =========================================
        extern U8 timer8_selected;         // $$$-- EXTERNAL DECLARATION --$$$
#       define Timer8_select(timer8_num)      (timer8_selected=timer8_num)
    // ---------- Macros
#       define Timer8_clear()                 ((timer8_selected==TIMER8_0)? \
                                                  (TCCR0A=0, TCNT0=0, OCR0A=0 ) \
                                                  : \
                                                  (TCCR2A=0, TCNT2=0, OCR2A=0 ) )
        // ----------
#       define Timer8_set_counter(value)      ((timer8_selected==TIMER8_0)? (TCNT0 = value) : (TCNT2 = value) )
#       define Timer8_get_counter()           ((timer8_selected==TIMER8_0)? (TCNT0) : (TCNT2) )
        // ----------
#       define Timer8_set_compare_a(value)    ((timer8_selected==TIMER8_0)? (OCR0A = value) : (OCR2A = value) )
#       define Timer8_set_compare(value)      ( Timer8_set_compare_a(value) )
#       define Timer8_get_compare_a()         ((timer8_selected==TIMER8_0)? (OCR0A) : (OCR2A) )
#       define Timer8_get_compare()           ( Timer8_get_compare_a() )
        // ----------
#       define Timer8_set_mode_output_a(conf) ((timer8_selected==TIMER8_0)? \
                                                  (TCCR0A = (TCCR0A & (~TIMER8_COMP_MODE_MASK_A)) | (conf << COM0A0)) \
                                                  : \
                                                  (TCCR2A = (TCCR2A & (~TIMER8_COMP_MODE_MASK_A)) | (conf << COM2A0)) )
#       define Timer8_set_mode_output(conf)   ( Timer8_set_mode_output_a(conf) )
#       define Timer8_get_mode_output_a()     ((timer8_selected==TIMER8_0)? \
                                                  ((TCCR0A & TIMER8_COMP_MODE_MASK_A) >> COM0A0) \
                                                  : \
                                                  ((TCCR2A & TIMER8_COMP_MODE_MASK_A) >> COM2A0) )
#       define Timer8_get_mode_output()       ( Timer8_get_mode_output_a() )
        // ----------
#       define Timer8_set_waveform_mode(conf) ((timer8_selected==TIMER8_0)? \
                                                  (TCCR0A = (TCCR0A & (~WGM8_RA_MASK)) |  \
                                                  ((((conf & 0x02) >> 1) << WGM01) | ((conf & 0x1) << WGM00) ) )  \
                                                  : \
                                                  (TCCR2A = (TCCR2A & (~WGM8_RA_MASK)) |  \
                                                  ((((conf & 0x02) >> 1) << WGM21) | ((conf & 0x1) << WGM20) ) )  )
#       define Timer8_get_waveform_mode()     ((timer8_selected==TIMER8_0)? \
                                                  (((TCCR0A & (1<<WGM00)) >> WGM00) | (((TCCR0A & (1<<WGM01)) >> WGM01) << 0x1)) \
                                                  : \
                                                  (((TCCR2A & (1<<WGM20)) >> WGM20) | (((TCCR2A & (1<<WGM21)) >> WGM21) << 0x1)) )
        // ----------
#       define Timer8_set_clock(value)        ((timer8_selected==TIMER8_0)? \
                                                  (TCCR0A = (TCCR0A & (~TIMER8_CLK_MASK)) | (value << CS00)) \
                                                  : \
                                                  (TCCR2A = (TCCR2A & (~TIMER8_CLK_MASK)) | (value << CS20)) )

#       define Timer8_get_clock()             ((timer8_selected==TIMER8_0)? \
                                                  (((TCCR0A & TIMER8_CLK_MASK) >> CS00)) : (((TCCR2A & TIMER8_CLK_MASK) >> CS20)) )
        // ----------
#       define Timer8_overflow_it_enable()    ((timer8_selected==TIMER8_0)? \
                                                  (TIMSK0 |=  (1<<TOIE0)) : (TIMSK2 |=  (1<<TOIE2)) )
#       define Timer8_overflow_it_disable()   ((timer8_selected==TIMER8_0)? \
                                                  (TIMSK0 &= ~(1<<TOIE0)) : (TIMSK2 &= ~(1<<TOIE2)) )
#       define Timer8_compare_a_it_enable()   ((timer8_selected==TIMER8_0)? \
                                                  (TIMSK0 |= (1<<OCIE0A)) : (TIMSK2 |= (1<<OCIE2A)) )
#       define Timer8_compare_a_it_disable()  ((timer8_selected==TIMER8_0)? \
                                                  (TIMSK0 &= ~(1<<OCIE0A)) : (TIMSK2 &= ~(1<<OCIE2A)) )
#       define Timer8_compare_it_enable()     ( Timer8_compare_a_it_enable()  )
#       define Timer8_compare_it_disable()    ( Timer8_compare_a_it_disable() )

#       define Timer8_get_overflow_it_mask()  ((timer8_selected==TIMER8_0)? \
                                                  ((TIMSK0 & (1<<TOIE0)) >> TOIE0) : ((TIMSK2 & (1<<TOIE2)) >> TOIE2) )
#       define Timer8_get_compare_a_it_mask() ((timer8_selected==TIMER8_0)? \
                                                  ((TIMSK0 & (1<<OCIE0A)) >> OCIE0A) : ((TIMSK2 & (1<<OCIE2A)) >> OCIE2A) )
#       define Timer8_get_compare_it_mask()   ( Timer8_get_compare_a_it_mask() )
        // ----------
#       define Timer8_clear_overflow_it()     ((timer8_selected==TIMER8_0)? \
                                                  (TIFR0 |= (1<<TOV0)) : (TIFR2 |= (1<<TOV2)) )
#       define Timer8_clear_compare_a_it()    ((timer8_selected==TIMER8_0)? \
                                                  (TIFR0 |= (1<<OCF0A)) : (TIFR2 |= (1<<OCF2A)) )
#       define Timer8_clear_compare_it()      ( Timer8_clear_compare_a_it() )
#       define Timer8_get_overflow_it()       ((timer8_selected==TIMER8_0)? \
                                                  ((TIFR0 & (1<<TOV0)) >> TOV0) : ((TIFR2 & (1<<TOV2)) >> TOV2) )
#       define Timer8_get_compare_a_it()      ((timer8_selected==TIMER8_0)? \
                                                  ((TIFR0 & (1<<OCF0A)) >> OCF0A) : ((TIFR2 & (1<<OCF2A)) >> OCF2A) )
#       define Timer8_get_compare_it()        ( Timer8_get_compare_a_it() )

    #else
        #error USE_TIMER8 definition is not referenced in "timer8_drv.h" file
#endif


    //!< =========================================
    //!< ------ ONLY when TIMER8_2 is used -------
    //!< =========================================
        // ---------- CLK SOURCE for TIMER 2 
#       define Timer8_2_system_clk()          ( ASSR &= ~((1<<EXCLK)|(1<<AS2)) )
#       define Timer8_2_external_osc()        ( ASSR  =  (ASSR & ~(1<<EXCLK)) | (1<<AS2) )
#       define Timer8_2_external_clk()        ( ASSR |=  ((1<<EXCLK)|(1<<AS2)) )
        // ---------- UPDATE in ASYNCHRONOUS OPERATION 
#       define Timer8_2_update_busy()         ( ASSR & ( (1<<TCN2UB) | (1<<OCR2UB) | (1<<TCR2UB) ) )


//_____ T I M E R   D E F I N I T I O N S ______________________________________

    // ---------- Pre-definitions for "conf" field for Timer8_set(get)_mode_output_x(conf) macros
#define TIMER8_COMP_MODE_NORMAL    (0)
#define TIMER8_COMP_MODE_TOGGLE    (1)
#define TIMER8_COMP_MODE_CLEAR_OC  (2)
#define TIMER8_COMP_MODE_SET_OC    (3)
#define TIMER8_COMP_MODE_MASK_A    (3<<COM0A0)
    // ---------- Pre-definitions for "conf" field for Timer8_set_waveform_mode(conf) macro
#define TIMER8_WGM_NORMAL          (0)
#define TIMER8_WGM_PWM_PC8         (1)
#define TIMER8_WGM_CTC_OCR         (2)
#define TIMER8_WGM_FAST_PWM8       (3)
#define TIMER8_WGM_RA_MASK         ( (1<<WGM00) | (1<<WGM01) )
    // ---------- Pre-definitions for "value" field for Timer8_set_clock(value) macro
#define TIMER8_NO_CLOCK                   (0)
#define TIMER8_CLKIO_BY_1                 (1)
#define TIMER8_CLK_MASK                   (7<<CS00)
        // ---------- and especally for TIMER 0
#define TIMER8_0_NO_CLOCK                 (0)
#define TIMER8_0_CLKIO_BY_1               (1)
#define TIMER8_0_CLKIO_BY_8               (2)
#define TIMER8_0_CLKIO_BY_64              (3)
#define TIMER8_0_CLKIO_BY_256             (4)
#define TIMER8_0_CLKIO_BY_1024            (5)
#define TIMER8_0_EXT_CLOCK_FALLING_EDGE   (6)
#define TIMER8_0_EXT_CLOCK_RISING_EDGE    (7)
        // ---------- and especally for TIMER 2
#define TIMER8_2_NO_CLOCK                 (0)
#define TIMER8_2_CLKIO_BY_1               (1)
#define TIMER8_2_CLKIO_BY_8               (2)
#define TIMER8_2_CLKIO_BY_32              (3)
#define TIMER8_2_CLKIO_BY_64              (4)
#define TIMER8_2_CLKIO_BY_128             (5)
#define TIMER8_2_CLKIO_BY_256             (6)
#define TIMER8_2_CLKIO_BY_1024            (7)


//_____ D E C L A R A T I O N S ________________________________________________

//------------------------------------------------------------------------------
//  @fn timer8_get_counter
//!
//! This function READ the 8-bit TIMER counter.
//!
//! @warning 
//!
//! @param  
//!
//! @return 8-bit counter value
//!
extern  U8 timer8_get_counter(void);

//______________________________________________________________________________

#endif  // _TIMER8_DRV_H_

















