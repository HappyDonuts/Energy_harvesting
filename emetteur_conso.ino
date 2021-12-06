#include <SPI.h>
#include <RF24.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LowPower.h>

#define pinCE   7             // On associe la broche "CE" du NRF24L01 à la sortie digitale D7 de l'arduino
#define pinCSN  8             // On associe la broche "CSN" du NRF24L01 à la sortie digitale D8 de l'arduino
#define tunnel  "PIPE3"       // On définit un "nom de tunnel" (5 caractères), pour pouvoir communiquer d'un NRF24 à l'autre

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2  

RF24 radio(pinCE, pinCSN);    // Instanciation du NRF24L01

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

const byte adresse[6] = tunnel;               // Mise au format "byte array" du nom du tunnel

void setup() {
  Serial.begin(9600);
  
  radio.begin();                      // Initialisation du module NRF24
  radio.openWritingPipe(adresse);     // Ouverture du tunnel en ÉCRITURE, avec le "nom" qu'on lui a donné
  radio.setPALevel(RF24_PA_MIN);      // Sélection d'un niveau "MINIMAL" pour communiquer (pas besoin d'une forte puissance, pour nos essais)
  radio.stopListening();              // Arrêt de l'écoute du NRF24 (signifiant qu'on va émettre, et non recevoir, ici)

  sensors.begin();
}

void loop() {
  char message[10];     // Message à transmettre à l'autre NRF24 (32 caractères maxi, avec cette librairie)
  
  sensors.requestTemperatures();
  int temperature = (sensors.getTempCByIndex(0))*10;
  
  sprintf(message, "%d", temperature); 
  Serial.println(message);
  radio.write(&message, sizeof(message));     // Envoi de notre message

  for (int i = 0; i< 2 ; i++)
  {
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  } 
  }
