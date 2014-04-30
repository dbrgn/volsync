#include <avr/io.h>
#include <util/delay.h>


#define _BV(bit)                           (1 << (bit))

#define bit_is_set(sfr, bit)               (_SFR_BYTE(sfr) & _BV(bit))
#define bit_is_clear(sfr, bit)             (!(_SFR_BYTE(sfr) & _BV(bit)))

#define loop_until_bit_is_set(sfr, bit)    do { } while (bit_is_clear(sfr, bit))
#define loop_until_bit_is_clear(sfr, bit)  do { } while (bit_is_set(sfr, bit))


static inline void init_ADC1(void) {
    ADMUX = _BV(REFS0) | _BV(REFS1); // Reference voltage on VCC
    ADMUX |= _BV(MUX0); // Select ADC1
    ADCSRA |= _BV(ADPS0) | _BV(ADPS1); // ADC clock prescaler /8
    ADCSRA |= _BV(ADEN); // Enable ADC
    _delay_ms(1); // Settle time
}

static inline void delay_ms(uint16_t count) { 
  while (count--) { 
    _delay_ms(1); 

  } 
} 

static inline uint16_t read_ADC1(void) {
    ADCSRA |= _BV(ADSC); // Start ADC conversion
    loop_until_bit_is_clear(ADCSRA, ADSC); // Wait until done
    return 2048 - (8 * (ADC >> 2));
}

int main(void) {
    // Initialize variables
    uint16_t delay;

    // Set up I/O
    DDRB |= (1 << PB1); // PB1 is output

    // Initialize ADC
    init_ADC1();

    while (1) {
        // Read value from ADC 
        delay = read_ADC1();

        // Toggle PB1
        PORTB ^= (1 << PB1);
        delay_ms(delay);
    }
}
