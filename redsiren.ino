#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

const int RXPin = 4, TXPin = 3;

const int button = 9;
const uint32_t GPSBaud = 9600; //Default baud of NEO-6M is 9600
float lt = 48.4652; // Random long starting point
float lg = 123.308; // Random lat starting point



bool buttonPressed = false;


TinyGPSPlus gps; // the TinyGPS++ object
SoftwareSerial ss(RXPin, TXPin); // the serial interface to the GPS device

SoftwareSerial btSerial(10, 11); // set serial RX & TX to pins 10 & 11 respectively
String bt_rx; //set up recieved string variable

void setup() {
  Serial.begin(9600);
  ss.begin(GPSBaud);
  btSerial.begin(9600);

  Serial.println(F("Arduino - GPS module"));
}

void loop() {
  //btSerial.println("Hudson is the best"); //Print message over terminal
  
  // read from button
  if(digitalRead(button)){
    buttonPressed = !buttonPressed;
    delay(1000);
  }

  // First checks if GPS is plif the button hasn't been pressed, then continue checking for button
  /*
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println(F("No GPS data received: check wiring"));
    
  }
  */
  if(buttonPressed){

    // If the GPS has valid longitude and latitude numbers, update them if possible
    // Else, print predetermined lat and long
    if(gps.location.isValid()){
      if((gps.location.lat() < (lt - 0.05)) || gps.location.lng() > (lg + 0.05)){
        printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
        printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
      }
    } else {

      btSerial.println ("Emergancy, Help Wanted at this Location");
      
      btSerial.print("Coordinates: ");
      btSerial.print(lt); //lat of UVIC
      btSerial.print(", ");
      btSerial.println(lg); //long of UVIC    
  
    }
    smartDelay(1000);
  }
