/*Codigo realizado por Diego Valladares Porras, carne: B77867 para el curso de IE-0624 Laboratorio de Microcontroladores
//Laboratorio 1: Introduccion a microcontroladores y manejo de GPIOS
//Instrucciones: Desarrollar un simulador de dado simplificado utilizando leds, un boton, el microcontrolador PIC12f675 o
PIC12f683 y cualquier otro componente que considere necesario. El objetivo de este laboratorio es introducir al
estudiante al manejo de GPIOs (General Purpose Input Outputs), generacion de numeros aleatorios y el flujo de
desarrollo que se pide para las practicas dirigidas. La cantidad de leds encendidos deben representar la cara del
dado con un numero al azar entre 1 y 6. Debe tener un boton de entrada con el que el usuario simula el lanzar
un dado de 6 caras, al presionarlo se deben encender los leds por un instante/periodo que representan la cara del
dado.
****************************************************************************************************************************/

#include <pic14/pic12f675.h>
typedef unsigned int word; //Se define el word para definir la configuracion del PIC
word __at 0x2007 __CONFIG = (_BODEN_OFF & _WDTE_OFF & _WDT_OFF & _MCLRE_OFF ); //Se definen BODEN (o BOREN, segun la TDS), WDTE, WDT OFF para evitar resets
																			//MCLRE=0 porque se utilizara el GP3 como input, entonces GP3=1
void delay (unsigned int tiempo); //Funcion para hacer los delays de los LEDs
	
void main(void) //Funcion principal
{

    TRISIO = 0b00000000; //Poner todos los pines como salidas menos GP3
    GPIO = 0x00; //Poner pines en bajo
	
	//Variables para inicializar la generacion de numeros aleatorios mediante el metodo de LFSR
    int lfsr=0b111; //Estado inicial del numero aleatorio
    int bit=0b000; //Valor inicial de bit=0, necesario para el cambio del valor de lfsr.
    unsigned int time = 100;

    //Loop forever
    while ( 1 )
    {
		//Generacion de numeros aleatorios del 1 al 6 utilizando el metodo "linear-feedback shift register" 
		bit=((lfsr >> 0) ^	 (lfsr >> 1)) & 1; 
		lfsr= (lfsr >> 1) | (bit << 2);
		if (GP3) //Si GP3=1
		{
			if (lfsr==0b001) // Si lfsr=1
			{	
				GPIO = 0b11000001;	//GP0=1 - Enciende 1 LEDs
				delay(time);
				GPIO = 0x00;
			}
			else if (lfsr==0b010) //  Si lfsr=2
			{
				GPIO = 0b11000010; // GP1=1 - Enciende 2 LEDs
				delay(time);
				GPIO = 0x00;
			}
			else if (lfsr==0b011) //  Si lfsr=3
			{
				GPIO = 0b11000100; // GP2=1 - Enciende 3 LEDs
				delay(time);
				GPIO = 0x00;
			}
			else if (lfsr==0b100) //  Si lfsr=4
			{
				GPIO = 0b11000101; //GP0=1,GP2=1 - Enciende 4 LEDs
				delay(time);
				GPIO = 0x00;
			}
			else if (lfsr==0b101) //  Si lfsr=5
			{
				GPIO = 0b11000110; //GP1=1,GP2=1 - Enciende 5 LEDs
				delay(time);
				GPIO = 0x00;
			}
			else if (lfsr==0b110) //  Si lfsr=6
			{
				GPIO = 0b11000111; //GP0=1, GP1=1,GP2=1 - Enciende 6 LEDs
				delay(time);
				GPIO = 0x00;
			}
				
		}
		
	}
    
}
void delay(unsigned int tiempo) 
{
	unsigned int i;
	unsigned int j;

	for(i=0;i<tiempo;i++)
	  for(j=0;j<1275;j++);
}
