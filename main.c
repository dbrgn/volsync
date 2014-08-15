#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"


#define _BV(bit)                           (1 << (bit))

#define bit_is_set(sfr, bit)               (_SFR_BYTE(sfr) & _BV(bit))
#define bit_is_clear(sfr, bit)             (!(_SFR_BYTE(sfr) & _BV(bit)))

#define loop_until_bit_is_set(sfr, bit)    do { } while (bit_is_clear(sfr, bit))
#define loop_until_bit_is_clear(sfr, bit)  do { } while (bit_is_set(sfr, bit))

#define LED_PORT PB7


static inline void init_ADC(void) {
    // Initialize ADC0
    ADMUX = _BV(REFS0); // Ref voltage AVcc, right adjust result, read ADC0
    ADCSRA |= _BV(ADPS0) | _BV(ADPS1); // ADC clock prescaler /8
    ADCSRA |= _BV(ADEN); // Enable ADC
    _delay_ms(1); // Settle time
}

static inline void delay_ms(uint16_t count) { 
  while (count--) { 
    _delay_ms(1); 

  } 
} 

static uint16_t read_ADC(void) {
    ADCSRA |= _BV(ADSC); // Start ADC conversion
    loop_until_bit_is_clear(ADCSRA, ADSC); // Wait until done
    //return ((ADC * (2000 - 100)) / 1023) + 100;  // Transform 0-255 range to 100-2000 range
    //return (ADC * 1.8572) + 100;  // Transform 0-255 range to 100-2000 range
    return ADC;
}

int main(void) {
    // Initialize variables
    uint16_t adc_val;

    // Set up I/O
    DDRB |= (1 << LED_PORT); // LED_PORT is output
    initUSART();
    printString("Hello world!\n");

    // Initialize ADC
    init_ADC();

    while (1) {
        // Read value from ADC 
        adc_val = read_ADC();
        printWord(adc_val);
        printString("\n");

        // Toggle LED_PORT
        PORTB ^= (1 << LED_PORT);

        delay_ms(200);
    }
}
