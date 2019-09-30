// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!
#include <ArduinoJson.h>
#include <AFMotor.h>

AF_DCMotor motor(1);
AF_DCMotor motor4(4);

StaticJsonBuffer<200> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();

JsonArray& sensores = root.createNestedArray("sensors");
//JsonArray& pasos = root.createNestedArray("pasos");

int speedV = 200;
String val;
void stopMotors(){
  
  motor.run(RELEASE);
  motor4.run(RELEASE);
  
}

void froward(){
  
  motor.run(FORWARD);
  motor4.run(FORWARD);
  
}

void backward(){

  motor.run(BACKWARD);
  motor4.run(BACKWARD);
  
}

void setup() {
  Serial.begin(9600);

  sensores.add("motores");
  sensores.add("putos");

  // turn on motor
  motor.setSpeed(200);
  motor4.setSpeed(200);
 
  motor.run(RELEASE);
  motor4.run(RELEASE);
  
  root.printTo(Serial);
  Serial.println("");

}

void loop() {
  
  if (Serial.available() > 0) {
    
    speedV = (Serial.readString()).toInt();
    //speedV = atoi(val);
    //Serial.println("set speed: "+ speedV);
    //Serial.println("");
  }
  
  motor.setSpeed(speedV);
  motor4.setSpeed(speedV);

/*  
  froward();
  delay(2000);

  backward();
  delay(2000);

  stopMotors();
  delay(1000);
*/

}
