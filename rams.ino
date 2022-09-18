////////////////////////////////////////////
// Created:     May-Aug 2021              //
// Author:      Fahad Tajiki              //
// Email:       ftajiki@purdue.edu        //
//                                        // 
//  This is the source code for RAMS      //
////////////////////////////////////////////
 
#include <HCSR04.h>
#include <Servo.h>
#include "Wire.h" // This library allows you to communicate with I2C devices.

Servo myservo;
 // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
const int MPU_ADDR = 0x68;
int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature; // variables for temperature data
char tmp_str[7]; // temporary variable used in convert function

//declarations of funtions
int sweep();
void forward();
void backward();
void lookright();


//declaration of variables
const int trig = 13; 
const int echo = 12;
const int enA = 10;
const int out1 = 3;
const int out2 = 4;
const int enB = 9;
const int out3 = 5;
const int out4 = 6;
long duration;
int distance;
int pos;
int dir;
int flag = 0;
int output = 0;
int offset = 45;
int AcXoff = 0;
int AcYoff = 0;
int AcZoff = 0;
int displacement = 0;
int oldaccX = 0;

char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  HCSR04.begin(trig, echo);

  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write((byte) 0x00); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  myservo.attach(11);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(enA, OUTPUT);
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(out3, OUTPUT);
  pinMode(out4, OUTPUT);
}

int sweep(){
  // Serial.println(pos);
   
   if(pos < 120 && flag == 0){
     pos += 30; //
    if(pos == 120){
    flag = 1;
    }
   }
  else if(pos > 0 && flag == 1){
    pos -= 30;
    if(pos < 5){
      flag = 0;
    }
   }           
    myservo.write(pos); //position setup
    return (pos < 90);
} 
  
void forward()
{
  
      analogWrite(enA, 255);
      analogWrite(enB, 255);
      digitalWrite(out1,LOW);
      digitalWrite(out2,HIGH);
      digitalWrite(out3,LOW);
      digitalWrite(out4,HIGH);

      delay(500);
      analogWrite(enA, 0);
      analogWrite(enB, 0);
      delay(1000);
}

void backward()
{
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  digitalWrite(out1, HIGH);
  digitalWrite(out2, LOW);
  digitalWrite(out3, HIGH);
  digitalWrite(out4, LOW);

    delay(500);
    analogWrite(enA, 0);
    analogWrite(enB, 0);
    delay(1000);
}    

void  lookright()
{
 analogWrite(enA, 255);
 analogWrite(enB, 255);
 digitalWrite(out1,HIGH);
 digitalWrite(out2,LOW);
 digitalWrite(out3,LOW);
 digitalWrite(out4,HIGH);

 delay(500);
 analogWrite(enA, 0);
 analogWrite(enB, 0);
 delay(1000);
}

void lookleft(){
 analogWrite(enA, 255);
 analogWrite(enB, 255);
 digitalWrite(out1,LOW);
 digitalWrite(out2,HIGH);
 digitalWrite(out3,HIGH);
 digitalWrite(out4,LOW);

 delay(500);
 analogWrite(enA, 0);
 analogWrite(enB, 0);
 delay(1000);
}

void loop() {
                //GY-521 Data Read
                 Wire.beginTransmission(MPU_ADDR);
                 Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
                 Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
                 Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
                 accelerometer_x = (Wire.read()<<8 | Wire.read()) + AcXoff;; // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
                 accelerometer_y = (Wire.read()<<8 | Wire.read()) + AcYoff; // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
                 accelerometer_z = (Wire.read()<<8 | Wire.read()) + AcZoff; // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
                 temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
                  Serial.print("aX = "); Serial.print(convert_int16_to_str(accelerometer_x));
                  Serial.print(" | aY = "); Serial.print(convert_int16_to_str(accelerometer_y));
                  Serial.print(" | aZ = "); Serial.print(convert_int16_to_str(accelerometer_z));
                  Serial.print(" | tmp = "); Serial.print(temperature/340.00+36.53);
                  Serial.print(" | dx = "); Serial.println(abs(accelerometer_x) - abs(oldaccX));
                  oldaccX = (accelerometer_x);
                  displacement = abs(accelerometer_x) - abs(oldaccX);
               //UR-S04 Data Read
               digitalWrite(trig, LOW);
               delay(2);
               digitalWrite(trig, HIGH);
               delay(10);
               digitalWrite(trig, LOW);
               duration = pulseIn(echo, HIGH);
               distance= duration*0.034/2; //calculate distance
                 Serial.print("Distance: ");
                 Serial.println(distance);
                 Serial.println(pos);
                 delay(100);
                
                if(accelerometer_z < 10000){
                   switch(dir){
                      case 0:
                        forward();
                        dir = 1;
                        delay(500);
                      case 1:
                        backward();
                        dir = 0;
                        delay(500);
                   }
                }
                else{
                  
                
                if(distance > 150){
                  forward();
                  delay(500);
                 
                }
                else if(distance > 35 && distance < 150){
                  if(pos  > (offset +  5)){
                    pos -= 5;
                    myservo.write(pos);
                    Serial.println(pos);
                    delay(75);
                  }
                  else if(pos < offset-5){
                    pos += 5;
                    myservo.write(pos);
                    Serial.println(pos);
                  delay(75);
                  }
                  else{
                   forward();
                  }
                 
                }
                else if(distance < 35){
                  sweep(); //invoke sweep();
                  delay(500);
                  lookright();
                  }
                  else{
                    backward();
                  }
                }
              }
