/* 
This circuit and code has created a ultrasonic range finder with LCD Screen Layout.
The program also includes a green LED to show that the range finder is on.
Ultrasonic wave is sent out of the triggerPin and returned through echoPin. 
The echoPin measures the time to return the wave, and the resulting time is translated to inches/cm.
The inches / cm calculation is then read out on the LCD screen for user.
*/

#include <LiquidCrystal.h> //Initializes the LCD Screen.
LiquidCrystal lcd( 12,11,5,4,3,2); // These are the pin numbers for the LCD screen.
int triggerPin = 8; //Trigger pin set to port 8 of Arduino.
int echoPin = 9; //Echo pin set to port 9 of Arduino.
int inches = 0; //variable "inches" created to track inches from distance sensor.
int centimeter = 0; //variable "cm" created to track cm's from distance sensor.
int greenLED = 13; //variable greenLED created for greenLED. Set to port 13 of Arduino.
int slideSwitch = 7; //variable slideSwitch created for slideSwitch. Set to port 7 of Arduino.

 
int checkDistance(int triggerPin, int echoPin){
  /*
  Function creation which returns distance. Parameters are triggerPin(OUTPUT) and echoPin(INPUT).
  I learned from, and included suggestions from instructables circuits in order to properly initialize this sensor.
  (https://www.instructables.com/id/Ultrasonic-Distance-Sensor-Arduino-Tinkercad/).
  */
  
  pinMode(triggerPin, OUTPUT); //triggerPin set as OUTPUT from port 8.
  pinMode(echoPin, INPUT); //echoPin set as INPUT to port 9.
  digitalWrite(triggerPin, LOW); //triggerPin off. 
  delayMicroseconds(5); //wait 5 microseconds.
  digitalWrite(triggerPin, HIGH); //triggerPin set to on.
  delayMicroseconds(10); // wait 10 microseconds.
  digitalWrite(triggerPin, LOW); //triggerPin off.
  return pulseIn(echoPin, HIGH); //reads echoPin and returns the soundwave travel time. Recorded in microsseconds. 
}


void setup(){
  pinMode(7, OUTPUT);//Output initialized from port 7. (slideSwitch).
  pinMode(8, OUTPUT); //Output initialized from 8. (triggerPin).
  pinMode(9, INPUT);//Input initialized from port 9. (echoPin).
  pinMode(13, OUTPUT); //Output initialized from port 13 (greenLED).
  lcd.begin (16,2); //Initializes the LCD Screen. 
}



void loop(){
  
  
  if(digitalRead(slideSwitch)){ //IF slide switch is on, then complete the following.
  
  centimeter = checkDistance(triggerPin , echoPin) * 0.01723; //rough calculation to convert microseconds to CM.
  inches = centimeter * 0.395;//rough calculation to convert cm to inches.
  digitalWrite(greenLED, HIGH);//turn on greenLED.
  delay(500);//500ms delay.
  lcd.setCursor(0,0);//set LCD cursor to position 0,0 (row 0, column 0).
  lcd.print(centimeter);//print value of centimeter on LCD.
  lcd.print(" centimeter");//print "centimeter" after value of centimeter.
  delay(500);//500ms delay.
  lcd.setCursor(0,1);//set LCD cursor to position 0,1 (row 1, column 0).
  lcd.print(inches); //print value of inches to LCD.
  lcd.print(" inches");//print "inches" after value of inches. 
  delay(500);//500ms delay.
    
  } else { //OTHERWISE, clear screen and turn off greenLED.
    
    lcd.clear(); //clear LCD screen.
    digitalWrite(greenLED, LOW);//turn off greenLED. 
    
  }
  
  
 
}