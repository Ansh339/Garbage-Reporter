#include <WiFiNINA.h>
#include "secrets.h"
#include "ThingSpeak.h"
#define USUP_ECHO1 3
#define USUP_TRIG1 2
#define Led1 4
#define Led2 5


char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

void setup() {
  pinMode(Led2,OUTPUT);  
  pinMode(Led1,OUTPUT); 
  
  pinMode(USUP_ECHO1,INPUT);
  pinMode(USUP_TRIG1,OUTPUT); 

 
  if (WiFi.status() == WL_NO_MODULE) {
    //Serial.println("Communication with WiFi module failed!");
    while (true);
  }
  String fv = WiFi.firmwareVersion();
 if (fv != "1.0.0") {
    //Serial.println("Please upgrade the firmware");
  }
  ThingSpeak.begin(client); 
 
}

void loop() {
    long duration1,distance1;
     digitalWrite(USUP_TRIG1, LOW);  
     delayMicroseconds(2); 
     digitalWrite(USUP_TRIG1, HIGH);
     delayMicroseconds(10); 
     digitalWrite(USUP_TRIG1, LOW);
     duration1 = pulseIn(USUP_ECHO1, HIGH);
     distance1 = (duration1/2) / 29.1;
     if (distance1>35)
        {distance1=0;}
     else{distance1=map(distance1,0,35,100,0);}
     
     //Serial.print("L ");
     //Serial.print(distance1);
     
     Upload_data(distance1);
     
   if(distance1<5){
    digitalWrite(Led1,HIGH);
    digitalWrite(Led2,LOW);}
   else if(distance1>90){
        digitalWrite(Led1,LOW);
        digitalWrite(Led2,HIGH);
        } 
  delay(1000);      
}

void Upload_data(int L){
   if (WiFi.status() != WL_CONNECTED) {
    //Serial.print("Attempting to connect to SSID: ");
    //Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass);
      //Serial.print(".");
      delay(5000);
    }
    //Serial.println("\nConnected.");
  }  
  ThingSpeak.setField(1, L);
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if (x == 200) {
    //Serial.println("Channel update successful.");
  }   
}
