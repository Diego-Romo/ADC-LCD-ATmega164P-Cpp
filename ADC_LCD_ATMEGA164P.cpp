
#include <avr/io.h>
#include <stdio.h>   // para sprintf
#include "lcd.h"
#define F_CPU 8000000UL    // Frecuencia a la que está trabajando el microcontrolador
#include <util/delay.h>

void config_conversor_adc(void);

int main(void)
{
      lcd_init(LCD_DISP_ON);  // inicia el lcd
      lcd_clrscr();
	  
	  config_conversor_adc();
	  
	  lcd_gotoxy(0,0); lcd_puts(" Conversor ADC");
	  lcd_gotoxy(5,1); lcd_puts("LCD 16x2");
	  _delay_ms(500);
	  lcd_clrscr();
	  
	  int valorBruto = 0;
	  double valorTratado = 0;
	  char display[15];
	  
      
    while (1) 
    {

			ADMUX &= 0b11110001;
			

			ADCSRA |= (1<<ADSC);			//Inicia conversion
			// REVISAR LA CONFIGURACION DE LOS REGISTROS EN EL MANUAL DE MICROCONTROLADOR.
			while (ADCSRA & (1<<ADSC))  // espera a que la conversion este lista
			{
			}
			valorBruto = (int)ADCW;
			
			lcd_gotoxy(0,0); lcd_puts("Valor bruto:");
			lcd_gotoxy(12,0);lcd_write_value(valorBruto,4);
			
			valorTratado = (double)valorBruto;
			valorTratado = 5*(valorTratado/1023);
			sprintf(display,"Volts: %.3f V", valorTratado);
			lcd_gotoxy(0,1);lcd_puts(display);
			
		
    }
}



void config_conversor_adc(void)
{
	// REVISAR LA CONFIGURACION DE LOS REGISTROS EN EL MANUAL DE MICROCONTROLADOR.
	DDRA = 0;
	ADMUX  |= (1<<REFS0);
	ADCSRA |= (1<<ADEN)|(1<<ADPS1);
}

