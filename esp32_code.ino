#include <Arduino.h>
#include <WiFi.h>
#include "ThingSpeak.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

const char* ssid = "XXXXXXXX";   // your network SSID (name) 
const char* password = "XXXX0000";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = "00000000";
const char * myWriteAPIKey = "X0X0X0XOX0";

unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

void setup() {
  Serial.begin(115200); // Initialize the hardware serial port
  
  WiFi.status();
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}
void loop()
{
  if(mySerial.available()){
  String rxString = "";
  String strArr[3]; //Set the size of the array to equal the number of values you will be receiveing.
  //Keep looping until there is something in the buffer.
  while (mySerial.available()) {
    //Delay to allow byte to arrive in input buffer.
    delay(2);
    //Read a single character from the buffer.
    char ch = mySerial.read();
    //Append that single character to a string.
    rxString+= ch;
  }
  int stringStart = 0;
  int arrayIndex = 0;
  for (int i=0; i < rxString.length(); i++){
    //Get character and check if it's our "special" character.
    if(rxString.charAt(i) == ','){
      //Clear previous values from array.
      strArr[arrayIndex] = "";
      //Save substring into array.
      strArr[arrayIndex] = rxString.substring(stringStart, i);
      //Set new string starting point.
      stringStart = (i+1);
      arrayIndex++;
    }
  }
  //Put values from the array into the variables.
  String value1 = strArr[0];
  String value2 = strArr[1];
  String value3 = strArr[2];


  if ((millis() - lastTime) > timerDelay) {
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }

    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int x = ThingSpeak.writeField(myChannelNumber, 1,value1, myWriteAPIKey);
    int y = ThingSpeak.writeField(myChannelNumber, 2,value2, myWriteAPIKey);
    int z = ThingSpeak.writeField(myChannelNumber, 3,value3, myWriteAPIKey);

    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
    if(y == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(y));
    }
    lastTime = millis();
    if(z == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(z));
    }
    lastTime = millis();
  }
}

}
