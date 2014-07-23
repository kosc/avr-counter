#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

const int digits[] = {0b1, 0b1001111, 0b10010, 0b110, 0b1001100, 0b100100, 0b100000, 0b1111, 0b0, 0b100};
volatile unsigned int counter = 0;

static void set_number(int number);
static void set_digit(int digit);
static void set_power(int pwr);

int main()
{
	DDRD = 0xff;
	DDRB = 0b0111; // PB3 - PCINT (pulse generator)
	PORTB |= 0b110; 
	PCMSK |= (1<<PCINT3);
	GIMSK |= (1<<PCIE);
	sei();
	while (1) {
		set_number(counter);
	}
	return 0;
}

static void set_number(int number) {
	char i;
	for (i=0; i<2; i++) {
		set_power(2-i);
		set_digit(number%10);
		number=number/10;
		_delay_ms(10);
	}
}

static void set_digit(int digit){
	PORTD = digits[digit];
}

static void set_power(int pwr){
	PORTB = pwr;
	PORTB |= 0b0100;
}

ISR(PCINT_vect) {
	if(!(PINB&_BV(PB3))) counter++;
}
