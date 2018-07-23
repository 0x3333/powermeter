#ifndef IO_H_
#define IO_H_

// ------------------------------------------------------------------------
#include <avr/io.h>

#define TRUE           1
#define FALSE          0
#define HIGH           TRUE
#define LOW            FALSE
#define OUTPUT         1
#define INPUT          0

// ------------------------------------------------------------------------

#define DIGITAL_READ(R, Pin) ((R & _BV(Pin)) != 0)
#define DIGITAL_WRITE(W,Pin,Value) if ((Value) == HIGH) { (W |= _BV(Pin)); } else { (W &= ~_BV(Pin)); }
#define PIN_MODE(D,Pin,Dir) if ((Dir) == OUTPUT) { (D |= _BV(Pin)); } else { (D &= ~_BV(Pin)); }
#define PULLUP_ON(D,Pin) DIGITAL_WRITE(D,Pin,HIGH)
#define PULLUP_OFF(D,Pin) DIGITAL_WRITE(D,Pin,LOW)
#define ANALOG_WRITE(Pin,Value) Pin = Value

// ------------------------------------------------------------------------

// Pin definitions
#define D0          0
#define D1          1
#define D2          2
#define D3          3
#define D4          4
#define D5          5
#define D6          6
#define D7          7
#define D8          0
#define D9          1
#define D10         2
#define D11         3
#define D12         4
#define D13         5
#define A0          0
#define A1          1
#define A2          2
#define A3          3
#define A4          4
#define A5          5

// Output Registers
#define D0_W        PORTD
#define D1_W        PORTD
#define D2_W        PORTD
#define D3_W        PORTD
#define D4_W        PORTD
#define D5_W        PORTD
#define D6_W        PORTD
#define D7_W        PORTD
#define D8_W        PORTB
#define D9_W        PORTB
#define D10_W       PORTB
#define D11_W       PORTB
#define D12_W       PORTB
#define D13_W       PORTB
#define A0_W        PORTC
#define A1_W        PORTC
#define A2_W        PORTC
#define A3_W        PORTC
#define A4_W        PORTC
#define A5_W        PORTC

// Input Registers
#define D0_R        PIND
#define D1_R        PIND
#define D2_R        PIND
#define D3_R        PIND
#define D4_R        PIND
#define D5_R        PIND
#define D6_R        PIND
#define D7_R        PIND
#define D8_R        PINB
#define D9_R        PINB
#define D10_R       PINB
#define D11_R       PINB
#define D12_R       PINB
#define D13_R       PINB
#define A0_R        PINC
#define A1_R        PINC
#define A2_R        PINC
#define A3_R        PINC
#define A4_R        PINC
#define A5_R        PINC

// Direction Registers
#define D0_D        DDRD
#define D1_D        DDRD
#define D2_D        DDRD
#define D3_D        DDRD
#define D4_D        DDRD
#define D5_D        DDRD
#define D6_D        DDRD
#define D7_D        DDRD
#define D8_D        DDRB
#define D9_D        DDRB
#define D10_D       DDRB
#define D11_D       DDRB
#define D12_D       DDRB
#define D13_D       DDRB
#define A0_D        DDRC
#define A1_D        DDRC
#define A2_D        DDRC
#define A3_D        DDRC
#define A4_D        DDRC
#define A5_D        DDRC

// ------------------------------------------------------------------------

#define RX1         D0
#define RX1_W       D0_W
#define RX1_R       D0_R
#define RX1_D       D0_D

#define TX1         D1
#define TX1_W       D1_W
#define TX1_R       D1_R
#define TX1_D       D1_D

#define LED0        D13
#define LED0_W      D13_W
#define LED0_R      D13_R
#define LED0_D      D13_D

// ------------------------------------------------------------------------

#define LED0_ON()       DIGITAL_WRITE(LED0_W, LED0, HIGH)
#define LED0_OFF()      DIGITAL_WRITE(LED0_W, LED0, LOW)
#define LED0_SET(S)     DIGITAL_WRITE(LED0_W, LED0, S)

#endif /* IO_H_ */
