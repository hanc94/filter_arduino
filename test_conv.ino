//Archivos de cabecera
#include "coefs_filter.h"
#include "myPWM.h"

//Pin de entrada analogico
#define AI0 A0

//Memoria del filtro
short xd[P];

//Funcion que efectua la suma de convolucion
short conv(short *x,double *h,int p){
 double acc;
 int k;
 
 acc=0.0;
 //Suma de convolucion
 for(k=p-1;k>=0;k--){
 acc+=h[k]*(double)x[k];
 //Movimiento de datos
 x[k]=x[k-1];
 } 
 return (short)acc;
}

void setup(){
  //Inicia puerto serial
  Serial.begin(9600);
  //Inicia PWM para emulacion de DAC
  initPWM();
}

void loop(){
  
  short xn,yn;
  static int cnt=0;
  unsigned long runTime;

  
  //Lee voltaje de entrada  
  xn=analogRead(AI0);
  
  //Muestra actual en linea de retardos
  xd[0]=xn;
  
  //Para medir tiempo de ejecucion de la convolucion
   runTime=micros();
  //Suma de convolucion
  yn=conv(xd,h,P);
  runTime=micros()-runTime;
  
  //Escribe voltaje de salida
  myAnalogWrite(yn);
  
  //Muestra informacion cada segundo
  if((cnt%FS)==0){
  Serial.print("Entrada: ");
  Serial.println(xn);
  Serial.print("Salida: ");
  Serial.println(yn);
  Serial.print("Tiempo de ejecucion de la convolucion: ");
  Serial.print(runTime);
  Serial.println(" us");
}
  //Incrementa contador que se usa en la visualizacion
  cnt++;
  
  //Retardo de un periodo de muestreo, considera el tiempo tomado por la convolucion
  delay((unsigned long)(1000.0/(double)FS)-(double)runTime/1000.0);
}

