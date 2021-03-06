/*
* ADC functions for attiny13.
* Author: Guido Socher, Copyright: GPL 
* http://tuxgraphics.org/electronics/
*/
#include <avr/io.h>
#include <math.h>


void adcOn(void)
{
	// Set up the ADC and enable the interrupt.
   
	// Use the intenal vref of 2.56v and pin 7
    ADMUX = (1<<REFS1)|(1<<REFS0)|(1<<MUX0)|(1<<MUX1)|(1<<MUX2);  
	
  
	// Enable the A/D Converter, set the prescaler (125kHz), enable the interrupt.
    ADCSRA=(1<<ADEN)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADIE);


}

void adcOff(void)
{
	ADCSRA &= ~((1<<ADEN)|(1<<ADIE)); 
	// Shut off the ADC and disable the interrupt. 
	// This lowers the power consumption of the uC.
}

// convert adc reading to voltage (readout is multiplied by 10)
uint8_t analog2v(uint16_t aval)
{
		//double adcval = (double)aval;
		//            ADCout * Vref * Vdiv
        // Voltage = ---------------------- * Calibration Value
		//                     1024
		//
		return (uint8_t)(((double)aval * 0.17) - 5.29); // These numbers were generated by calibrating against two known voltage reads.
        //return((uint8_t)r);
}


// Start the ADC conversion. Results are handled by an interrupt in main.c.
void startConvert(void) 
{
	// Set channel
	//ADMUX &= ~0x03; // Clear out existing channel.
	//ADMUX |= (CHANNEL & 0x03); // Add in new channel.
	// This is unnecessary because channel 0 sets all mux vals to 0.
	
    //  start conversion 
	
	//if(bit_is_clear(ADCSRA,ADSC))
		ADCSRA |= (1<<ADSC); 
}


