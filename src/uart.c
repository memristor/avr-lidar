#include "uart.h"
#include <avr/sfr_defs.h>
#include <avr/interrupt.h>
#if !defined(TXC0)
#if defined(TXC)
// Some chips like ATmega8 don't have UPE, only PE. The other bits are
// named as expected.
#if !defined(UPE) && defined(PE)
#define UPE PE
#endif
// On ATmega8, the uart and its bits are not numbered, so there is no TXC0 etc.
#define TXC0 TXC
#define RXEN0 RXEN
#define TXEN0 TXEN
#define RXCIE0 RXCIE
#define UDRIE0 UDRIE
#define U2X0 U2X
#define UPE0 UPE
#define UDRE0 UDRE
#elif defined(TXC1)
// Some devices have uart1 but no uart0
#define TXC0 TXC1
#define RXEN0 RXEN1
#define TXEN0 TXEN1
#define RXCIE0 RXCIE1
#define UDRIE0 UDRIE1
#define U2X0 U2X1
#define UPE0 UPE1
#define UDRE0 UDRE1
#elif defined(LINBRRH) 
  // ATmegaxxM1/C1
#define TXC0 LTXOK                         
#define RXEN0 LCMD1                   
#define TXEN0 LCMD0              
#define RXCIE0 LENRXOK                     
#define UDRIE0 LENTXOK                     
//!#define U2X0 zxcRU2X
#define UPE0 LPERR                         
#define UDRE0 LTXOK
#else
#error No UART found in HardwareSerial.cpp
#endif
#endif // !defined TXC0

typedef uint8_t tx_buffer_index_t;
typedef uint8_t rx_buffer_index_t;

volatile rx_buffer_index_t _rx_buffer_head;
volatile rx_buffer_index_t _rx_buffer_tail;
volatile tx_buffer_index_t _tx_buffer_head;
volatile tx_buffer_index_t _tx_buffer_tail;

volatile uint8_t * const _ubrrh = &LINBRRH;
volatile uint8_t * const _ubrrl = &LINBRRL;
volatile uint8_t * const _ucsra = &LINSIR;
volatile uint8_t * const _ucsrb = &LINENIR;
volatile uint8_t * const _ucsrc = &LINCR;
volatile uint8_t * const _udr = &LINDAT;

int _written = 0;
#define SERIAL_RX_BUFFER_SIZE 256
#define SERIAL_TX_BUFFER_SIZE 256

// HardwareSerial Serial(&LINBRRH, &LINBRRL, &LINSIR, &LINENIR, &LINCR, &LINDAT);

unsigned char _rx_buffer[SERIAL_RX_BUFFER_SIZE];
unsigned char _tx_buffer[SERIAL_TX_BUFFER_SIZE];

#define sbi(port, bit); port |= _BV(bit);
#define cbi(port, bit); port &= ~_BV(bit);
    
void uart_rx_complete_irq(void)
{
	// Rx AND Tx interrupts are handled together here for the LIN Module in UART mode.
    // So we need to figure out which one caused the IRQ and handle them both here..
    
    if (bit_is_set(LINSIR, LRXOK)) {							                    // Is there also an Rx character to handle? 
        unsigned char c = *_udr;
        rx_buffer_index_t i = (unsigned int)(_rx_buffer_head + 1) % SERIAL_RX_BUFFER_SIZE;

        // if we should be storing the received character into the location
        // just before the tail (meaning that the head would advance to the
        // current location of the tail), we're about to overflow the buffer
        // and so we don't write the character or advance the head.
        if (i != _rx_buffer_tail) {
			_rx_buffer[_rx_buffer_head] = c;
			_rx_buffer_head = i;
        }
    }
    
  	if (bit_is_set(LINSIR, LTXOK)) {                                            // Now, lets check to see if we arrived here because of a TX interrupt?
        if (_tx_buffer_head != _tx_buffer_tail) {                                // Yes we did, and there are some characters in the buffer to send out.
             // _tx_udr_empty_irq();                                               // Go send them.
        } else {
            cbi(*_ucsrb, UDRIE0);                                               // Buffer empty, so disable interrupts
            sbi(*_ucsra, TXC0);                                                 // And clear this Tx flag that brought us here
                                                                                // Need to do this check here, as _tx_udr_empty_irq() does not make the check before
                                                                                // trying to send another character out...
        }
    }

}


ISR(LIN_TC_vect) 
{
	uart_rx_complete_irq();
}



void uart_init(unsigned long baud, char config)
{
  #if defined(LINBRRH)
    // Disable re-sync; 8-time bit sampling mode
    LINBTR = 0x88;
    // Use LINBTR LBTR[5:0] of 8 to calcualte baud rate
    // NOTE: Baud rate is supposed to be very accurate
    // so no need for complex checking like with normal
    // mega USART
     uint16_t baud_setting = (F_CPU / (8 * baud)) - 1;
  #endif
  
  // assign the baud_setting, a.k.a. ubrr (USART Baud Rate Register)
  *_ubrrh = baud_setting >> 8;
  *_ubrrl = baud_setting;

  _written = false;

  //set the data bits, parity, and stop bits
	#if defined(__AVR_ATmega8__)
	  config |= 0x80; // select UCSRC register (shared with UBRRH)
	#endif

	#if defined(LINBRRH)
	  config |= ((1<<LCMD2) | (1<<LCMD1)| (1<<LCMD0) | (1<<LENA));              // Activate UART mode (instead of LIN mode) and turn Tx & Rx on.
	  LINSIR = 0x0F;						                            	    // Clear status and interrupt register bits
  #endif
  
  
  *_ucsrc = config;
  
  #if !defined(LINBRRH)
    sbi(*_ucsrb, RXEN0);                                                    // For LIN, this was handled with the config variable above.
    sbi(*_ucsrb, TXEN0);
  #endif
  
  sbi(*_ucsrb, RXCIE0);
  cbi(*_ucsrb, UDRIE0);
}


int uart_available(void)
{
  return ((unsigned int)(SERIAL_RX_BUFFER_SIZE + _rx_buffer_head - _rx_buffer_tail)) % SERIAL_RX_BUFFER_SIZE;
}

int uart_read(void)
{
  // if the head isn't ahead of the tail, we don't have any characters
  if (_rx_buffer_head == _rx_buffer_tail) {
    return -1;
  } else {
    unsigned char c = _rx_buffer[_rx_buffer_tail];
    _rx_buffer_tail = (rx_buffer_index_t)(_rx_buffer_tail + 1) % SERIAL_RX_BUFFER_SIZE;
    return c;
  }
}
