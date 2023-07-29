/*
 * Timer.c
 *
 * Created: 8/6/2022 8:19:02 PM
 *  Author: MSI
 */ 
#include "Timer.h"

void Timer0_CTC_mode_init()
{
	//set timer clock
	SET_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS02);
	//enable ctc mode
	SET_BIT(TCCR0,WGM01);
	// enable interrupt of ctc mode
	SET_BIT(TIMSK,OCIE0);
	sei();
	//enable interrupt every 10 ms
	OCR0=80;
	
}
void Timer0_generate_signal_non_PWM()
{
	SET_BIT(DDRB,3);
	//set timer clock
	SET_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS02);
	//enable ctc mode
	SET_BIT(TCCR0,WGM01);
	// identify the frequancy of signal generated
	OCR0=64;
	// generate tog signal on pb3 every compare match
	SET_BIT(TCCR0,COM00);
}
void Timer0_generate_signal_FAST_PWM()
{
	SET_BIT(DDRB,3);
	//set timer clock
	SET_BIT(TCCR0,CS00);
	SET_BIT(TCCR0,CS02);
	// enable fast PWM mode
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
	// identify the frequancy of signal generated
	OCR0=64;
	//generate set on compare match and clear on bottom(inverting mode)
	SET_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
	//generate clear on compare match and set on bottom(non-inverting mode)
	//SET_BIT(TCCR0,COM01);
	
	
}
void Timer0_generate_signal_phase_correct_PWM()
{
		SET_BIT(DDRB,3);
		//set timer clock
		SET_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS02);
		// enable phase correct mode PWM mode
		SET_BIT(TCCR0,WGM00);
		// identify the frequancy of signal generated
		OCR0=64;
		//generate set on compare match when counting up and clear on  compare match when down counting 
		SET_BIT(TCCR0,COM00);
		SET_BIT(TCCR0,COM01);
		//generate clear on compare match when counting up and set on compare match when down counting
		
		//SET_BIT(TCCR0,COM01);
	
}
void Timer2_RTC_interrupt()
{
	//set external clock
	SET_BIT(ASSR,AS2);
	//set prescaller to 128
	SET_BIT(TCCR2,CS22);
	SET_BIT(TCCR2,CS20);
	//enable overflow interrupt
	SET_BIT(TIMSK,TOIE2);
	sei();
	
	
}
void watch_dog_enable()
{
	SET_BIT(WDTCR,WDE);
	//set number of cycles to 32k before reset MCU
	SET_BIT(WDTCR,WDP0);
	
}
void watch_dog_disable()
{
	SET_BIT(WDTCR,WDE);
	SET_BIT(WDTCR,WDTOE);
	CLR_BIT(WDTCR,WDE);
}
void Timer2_fastPWM_generate1(double degree)
{
	float f=0;
	// set oc1a to be output bit
	SET_BIT(DDRD,5);
	//set clock with 8 prescaller
	SET_BIT(TCCR1B,CS11);
	//set mode to fast pwm 
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM13);
	// clear on compare match set at bottom(ICR1)(non inverting mode)
    SET_BIT(TCCR1A,COM1A1);
	//duty cycle of signal
	if (degree>=0&&degree<45)
	{
		f=(degree*0.0055555555555555555556)+1500;
	}
	else if (degree>=45&&degree<=90)
	{
		f=2000-(degree*0.0055555555555555555556);
	}
	else if (degree<0&&degree>=-45)
	{
		degree*=-1.0;
		f=1500-(degree*0.0055555555555555555556);
	}
	else if (degree>=-90&&degree<-45)
	{
		degree*=-1.0;
		f=(degree*0.0055555555555555555556)+1000;
	}
	OCR1A=f;
	//period of cycle
	ICR1=19999;
	
	
}
void Timer2_fastPWM_generate2(double degree)
{
	float f=0;
	// set oc1a to be output bit
	SET_BIT(DDRD,4);
	//set clock with 8 prescaller
	SET_BIT(TCCR1B,CS11);
	//set mode to fast pwm
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	// clear on compare match set at bottom(ICR1)(non inverting mode)
	SET_BIT(TCCR1A,COM1B1);
	//duty cycle of signal
	if (degree>=0&&degree<45)
	{
		f=(degree*0.0055555555555555555556)+1500;
	}
	else if (degree>=45&&degree<=90)
	{
		f=2000-(degree*0.0055555555555555555556);
	}
	else if (degree<0&&degree>=-45)
	{
		degree*=-1.0;
		f=1500-(degree*0.0055555555555555555556);
	}
	else if (degree>=-90&&degree<-45)
	{
		degree*=-1.0;
		f=(degree*0.0055555555555555555556)+1000;
	}
	OCR1B=f;
	//period of cycle
	ICR1=19999;
	
	
}