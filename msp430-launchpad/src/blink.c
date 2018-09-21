#include <msp430.h>

int main(void) {
	WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
	P1DIR |= (1U << 0);
	P1DIR |= (1U << 6);
    P1OUT ^= (1U << 6);

	for (;;) {
		volatile unsigned int i;

		P1OUT ^= (1U << 0);
        P1OUT ^= (1U << 6);
		i = 60000;
		do i--;
		while(i != 0);
	}
	
	return 0;
}
