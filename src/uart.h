#ifndef USART_H_
#define USART_H_

// ------------------------------------------------------------------------
#include <stdio.h>

// ------------------------------------------------------------------------
#define BAUD			78200
#ifndef QUEUE_SIZE
#define QUEUE_SIZE		254
#endif
#if QUEUE_SIZE > 254
// We are using uint8_t pointers in the queue, no more than 255.
#error "QUEUE_SIZE uses uint8_t, cannot be bigger than 254."
#endif

#define IS_TX_FINISHED()  (bit_is_set(UCSR0A, TXC0) && bit_is_clear(UCSR0B,UDRIE0) && is_tx_queue_empty())

// ------------------------------------------------------------------------
void init_uart();

void add_byte_tx_queue(uint8_t dataByte);
int8_t get_byte_rx_queue();

// ------------------------------------------------------------------------

FILE UART_I_O;

#endif /* USART_H_ */
