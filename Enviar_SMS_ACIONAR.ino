 /*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 * autor : Renato Silva de Lira
 * co-autor: Matias Gonçalves
 */
#include <SoftwareSerial.h> //Incluimos a livraria SoftwareSerial
#include "DHT.h"
#define DHTPIN A1 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11 
#include<IRremote.h>


SoftwareSerial SIM800L(8, 9);
// Conecte o SIM800L TX ao pino 8 RX do Arduino. 
// Conecte o SIM800L RX ao pino 9 do Arduino TX.
SoftwareSerial mySerial(8, 9);//Declaramos os pinos RX(8) e TX(9) que vamos usar
SoftwareSerial gsm(8,9);
DHT dht(DHTPIN, DHTTYPE);
IRsend irsend;

String Comando; //Declaramos uma variavel de tipo String para armazenar o texto do SMS recebido
int LED1 = 5; //Definimos o pino onde esta conectado o LED (Digital 2)
int LED = 3; //Definimos o pino onde esta conectado o LED (Digital 3)


void setup(){
Serial.begin(9600); //Iniciamos a comunicação serie
SIM800L.begin(9600); //Iniciamos una instância da livraria SoftwareSerial
SIM800L.println("AT+CMGF=1"); //Configuramos o módulo para trabalhar com os SMS em modo texto
delay(1000); //Pausa de 1 segundo

SIM800L.println("AT+CNMI=1,2,0,0,0"); //Configuramos o módulo para que nos mostre os SMS recebidos por comunicação serie

pinMode(LED1, OUTPUT); //Definimos o pino onde esta ligado o LED como saida

pinMode(LED, OUTPUT); //Definimos o pino onde esta ligado o LED como saida


 
}

void loop()
{
  if (SIM800L.available()){ //Se há dados disponiveis
Comando = SIM800L.readString(); //Armazenamo-los na variavel Comandos
Serial.println("NOVO SMS ENTRADA: " + Comando); //Obtemo-los por comunicação série
}

if(Comando.indexOf("T1")>=0){ //Se a variável Comando contem a palavra T1
mySerial.begin(9600);
delay(1000);
mySerial.println("AT");
delay(500);
mySerial.println("AT+CMGF=1");
delay(500);
mySerial.println("AT+CMGS=\"+5592992672693\"\r");
delay(500);
 
  mySerial.print("DHT Analisando temperatura!\n");
  delay(500);
  dht.begin();
  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(t) || isnan(h)) 
  {
    Serial.println("Falha ao ler do DHT");
  } 
  else
  {
   mySerial.print("Umidade: ");
    mySerial.print(h);
    mySerial.print(" %t\n");
    mySerial.print("Temperatura: ");
    mySerial.print(t);
    mySerial.print(" *C\n\n");
mySerial.print("ACIONAR O SISTESMA DE VENTILACAO ?");     
delay(500);
mySerial.write(26);
Comando = ""; //Esvaziamos a variavel    
  }
  
Serial.begin(9600); //Iniciamos a comunicação serie
SIM800L.begin(9600); //Iniciamos una instância da livraria SoftwareSerial
SIM800L.println("AT+CMGF=1"); //Configuramos o módulo para trabalhar com os SMS em modo texto
delay(1000); //Pausa de 1 segundo

SIM800L.println("AT+CNMI=1,2,0,0,0"); //Configuramos o módulo para que nos mostre os SMS recebidos por comunicação serie

pinMode(LED1, OUTPUT); //Definimos o pino onde esta ligado o LED como saida


}


if (SIM800L.available()>0){
Comando = SIM800L.readString();
Serial.println("NOVO SMS ENTRADA: " + Comando); 
}

if(Comando.indexOf("Sim")>=0){ //Se a variável Comando contem a palavra ON
Serial.println("Acender o LED"); //Avisamos por comunicação serie
digitalWrite(LED1, HIGH); //Activamos o LED
Comando = ""; //Esvaziamos a variavel
}

if(Comando.indexOf("Off")>=0){ //Se a variavel Comando contem a palavra OFF
Serial.println("Apagar o LED"); //Avisamos por comunicação serie
digitalWrite(LED1, LOW); //Desactivamos o LED
Comando = ""; //Esvaziamos a variavel
}

if (SIM800L.available()>0){
Comando = SIM800L.readString();
Serial.println("NOVO SMS ENTRADA: " + Comando); 
}

if(Comando.indexOf("T2")>=0){ //Se a variável Comando contem a palavra T1
mySerial.begin(9600);
delay(1000);
mySerial.println("AT");
delay(500);
mySerial.println("AT+CMGF=1");
delay(500);
mySerial.println("AT+CMGS=\"+5592992672693\"\r");
delay(500);
mySerial.print("ACIONAR TV ?");     
delay(500);
mySerial.write(26);
Comando = ""; //Esvaziamos a variavel 

Serial.begin(9600); //Iniciamos a comunicação serie
SIM800L.begin(9600); //Iniciamos una instância da livraria SoftwareSerial
SIM800L.println("AT+CMGF=1"); //Configuramos o módulo para trabalhar com os SMS em modo texto
delay(1000); //Pausa de 1 segundo

SIM800L.println("AT+CNMI=1,2,0,0,0"); //Configuramos o módulo para que nos mostre os SMS recebidos por comunicação serie

pinMode(LED, OUTPUT); //Definimos o pino onde esta ligado o LED como saida
}

 
if(Comando.indexOf("Des")>=0){ //Se a variável Comando contem a palavra Sim
irsend.sendRC5(0x80C, 12); //Envia o sinal   
Serial.println("\\\\desligando tv");  
Comando = ""; //Esvaziamos a variavel
}

if(Comando.indexOf("Lig")>=0){ //Se a variavel Comando contem a palavra Off
irsend.sendRC5(0xC, 12); //Envia o sinal   
Serial.println("ligando tv");
Comando = ""; //Esvaziamos a variavel
}

}
 
