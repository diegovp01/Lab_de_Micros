#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

//Biblioteca para utilizar pantalla LCD

Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);


/*******************************/
//Variables para leer signo y magnitud de tension
float vcc1 = 0.0;
float vcc2 =0.0;
float vcc3 = 0.0;
float vcc4 =0.0;
float sign =0.0;
float sign2 =0.0;
float sign3 =0.0;
float sign4 =0.0;

/**********************************/
//Tensi[on resultante a reportar en la pantalla
float VCC = 0;
float VCC2 = 0;
float VCC3 = 0;
float VCC4 = 0;

void setup()   {
  
//Comunicacion serie 
  Serial.begin(9600);
// Comunicaci[on de la pantalla
  display.begin();

//Pines de alerta a exceso de tension
  
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(8, OUTPUT);
  
//Configuracion pantalla
  display.setContrast(50);

  delay(100);
  display.clearDisplay();   
}
void loop()
{
  //Lectura de los pines
  sign4 = digitalRead(19);
  sign3 = digitalRead(18);
  sign2 = digitalRead(12);
  sign = digitalRead(13);
  vcc1 = analogRead(A0);
  vcc2 = analogRead(A1);
  vcc3 = analogRead(A2);
  vcc4 = analogRead(A3);


//Formula para definir tension post-ADC

  VCC =  ((vcc1*2.0+0.5)/1023)*5;
  VCC2 = ((vcc2*2.0+0.5)/1023)*7.5;
  VCC3 = ((vcc3*2.0+0.5)/1023)*11;
  VCC4 = ((vcc4*2.0+0.5)/1023)*11;

if(sign4){
  VCC4 = VCC4*(-1.1);
}

if(sign3){
  VCC3 = VCC3*(-1.1);
}  

if(sign2){
  VCC2 = VCC2*(-1.1);
}  

if(sign){
  VCC = VCC*(-1.1);
}  

 // Funcionamiento de la pantalla primer pin
 
  display.clearDisplay();
  //Letra
  display.setTextSize(1);
  //Posicion
  display.setCursor(0,0);
  //Impresion
  display.print("V1=");
  display.println(VCC,1);


  // Alarma con respecto al led
  
  if(VCC>20||VCC<-20){
  digitalWrite(8, HIGH);
  delay(50);
  digitalWrite(8, LOW);
  delay(50);
  
  }
  display.setTextSize(1);
  display.setCursor(0,10);
  display.print("V2=");
  display.println(VCC2,1);    
    if(VCC2>20||VCC2<-20){
  digitalWrite(9, HIGH);
  delay(50);
  digitalWrite(9, LOW);
  delay(50);
 
  }

  

  display.setTextSize(1);
  display.setCursor(0,20);
  display.print("V3=");
  display.println(VCC3,1);
    if(VCC3>20||VCC3<-20){
  digitalWrite(10, HIGH);
  delay(50);
  digitalWrite(10, LOW);
  delay(50);
  
  }

  display.setTextSize(1);
  display.setCursor(0,30);
  display.print("V4=");
  display.println(VCC4,1);
    if(VCC4>20||VCC4<-20){
  digitalWrite(11, HIGH);
  delay(50);
  digitalWrite(11, LOW);
  delay(50);
  
  }

Serial.print("V1:");
 Serial.println(VCC);
Serial.print("V2:");
 Serial.println(VCC2);
Serial.print("V3:");
 Serial.println(VCC3);
Serial.print("V4:");
 Serial.println(VCC4);

  display.display();
  delay(1);  
 
}