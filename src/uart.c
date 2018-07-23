/*
 ==============================================================================
 Author:   Tercio Gaudencio Filho
 Company:  EPIC Consultoria em TI
 Revision: 1.0
 Date:     13/09/2013
 ==============================================================================
 For use with avr-gcc (GCC) 4.7.2
 ==============================================================================
 */

// -------------------------------------------------------------------------
// Includes:
#include "uart.h"

#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/setbaud.h>
#include <string.h>

#include "io.h"

// -------------------------------------------------------------------------
struct Queue
{
	uint8_t start;
	uint8_t end;
	uint8_t length;
	int buffer[QUEUE_SIZE];
};

static struct Queue queueTx;
static struct Queue queueRx;
static inline int16_t uart_putc(char c, FILE *stream);
static inline int16_t uart_getc(FILE *stream);
FILE UART_I_O = FDEV_SETUP_STREAM(uart_putc, uart_getc, _FDEV_SETUP_RW);

// -------------------------------------------------------------------------
// Queue:
static inline void reset_queue(struct Queue *queue)
{
	queue->start = 0;
	queue->end = 0;
	queue->length = 0;
}

/**
 * This function are not safe against override, caller must check if they have bytes available.
 */
static inline void add_byte_queue(struct Queue *queue, uint8_t data)
{
	queue->buffer[queue->end++] = data;
	if (queue->end == QUEUE_SIZE)
	{
		queue->end = 0;
	}
	queue->length++;
}

/**
 * This function are not safe against override, caller must check if they have bytes available.
 */
static inline int8_t get_byte_queue(struct Queue *queue)
{
	uint8_t data = queue->buffer[queue->start++];
	if (queue->start == QUEUE_SIZE)
	{
		queue->start = 0;
	}
	queue->length--;
	return data;
}

static inline int8_t is_queue_empty(struct Queue *queue)
{
	return queue->length == 0;
}

static inline int8_t is_queue_full(struct Queue *queue)
{
	return queue->length == QUEUE_SIZE;
}

// -------------------------------------------------------------------------

void init_uart()
{
	// Reset queues
	reset_queue(&queueTx);
	reset_queue(&queueRx);

	// Define IO mode
	PIN_MODE(TX1_D, TX1, OUTPUT); // TX
	PIN_MODE(RX1_D, RX1, INPUT);  // RX

	// Baud rate
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

	//8-bit data
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
	//Enable RX and TX
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);

	// IO configuration
	stdin = stdout = &UART_I_O;
}

// -------------------------------------------------------------------------
// Enable/Disable:

static inline void uart_enable_tx()
{
	UCSR0B |= _BV(UDRIE0);
}

static inline void uart_disable_tx()
{
	UCSR0B &= ~_BV(UDRIE0);
}

// -------------------------------------------------------------------------
// putc/getc:

static inline int16_t uart_putc(char c, FILE *stream)
{
	if (is_queue_full(&queueTx))
	{
		return EOF;
	}
	else
	{
		add_byte_tx_queue(c);
		uart_enable_tx();
		return c;
	}
}
static inline int16_t uart_getc(FILE *stream)
{
	if (is_queue_empty(&queueTx))
	{
		return EOF;
	}
	else
	{
		return get_byte_rx_queue();
	}
}

// -------------------------------------------------------------------------
// TX Queue:

void add_byte_tx_queue(uint8_t dataByte)
{
	add_byte_queue(&queueTx, dataByte);
}
static inline int8_t get_byte_tx_queue()
{
	return get_byte_queue(&queueTx);
}

// -------------------------------------------------------------------------
// RX Queue:

static inline void add_byte_rx_queue(uint8_t dataByte)
{
	add_byte_queue(&queueRx, dataByte);
}
int8_t get_byte_rx_queue()
{
	return get_byte_queue(&queueRx);
}

// -------------------------------------------------------------------------
// ISR:

// USART Rx Complete
ISR(USART_RX_vect)
{
	uint8_t temp = UDR0;
	if (!is_queue_full(&queueRx)) // If queue is full, drop byte
	{
		add_byte_rx_queue(temp);
	}
}

// USART, Data Register Empty
ISR(USART_UDRE_vect)
{
	if (is_queue_empty(&queueTx))
	{
		uart_disable_tx();
	}
	else
	{
		UDR0 = get_byte_tx_queue();
	}
}

// USART Tx Complete
ISR(USART_TX_vect)
{
}
