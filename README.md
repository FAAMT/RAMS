# "RAMS" - Obstacle Avoidance Robot
<br />
<p align="center">
<img src="https://user-images.githubusercontent.com/82693292/152702500-210ea833-a2d9-4a7c-b7a3-52329b781607.jpg" width=75%>
</p>
<br />

## About This Project

<p align="justified">
This project is on building a rudimentary obstacle avoidance system using a SparkFun Redboard and the Arduino IDE. The reason I started this project was my interest in unmanned ground vehicles (UGV). I wanted to get some experience in developing UGV systems and chose to build an obstacle avoidance robot. His name is RAMS... which doesn't stand for anything meaningful :sweat_smile:. My roommate coined the name and it just kind of stuck. Anyways, I'm making this repository public for two reasons: (1) To showcase my project (2) To assist others in their own projects. I hope that this repo can help others who share the same curiosity.
</p>

## RAMS Demo

<p align="center">
  <img src="https://user-images.githubusercontent.com/82693292/190885452-50586c44-ad33-47b3-81e9-90f1dbef93eb.gif" alt="animated" />
</p>



## List Of Components 

| Component     | Image           |
| ------------- |:-------------:|
| [SparkFun RedBoard Artemis x 1](https://www.sparkfun.com/products/15444) | <img src="https://user-images.githubusercontent.com/82693292/190883660-1c158871-7598-467a-b9d2-f20fc166e0ff.jpg" width=25%>
| [L289N x 1](https://www.amazon.com/Qunqi-Controller-Module-Stepper-Arduino/dp/B014KMHSW6/ref=asc_df_B014KMHSW6/?tag=hyprod-20&linkCode=df0&hvadid=167139094796&hvpos=&hvnetw=g&hvrand=13859763353518732303&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9016722&hvtargid=pla-306436938191&psc=1) | <img src="https://user-images.githubusercontent.com/82693292/190884224-5dc25f20-fb82-43d6-8225-5ec26fd470e7.jpg" width=25%>
| [MG995 x 1](https://www.amazon.com/180%C2%B0Metal-Waterproof-Airplane-Helicopter-Mechanical/dp/B09JWK2GB3/ref=asc_df_B09JWK2GB3/?tag=hyprod-20&linkCode=df0&hvadid=598270536205&hvpos=&hvnetw=g&hvrand=3355752210373419382&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9016722&hvtargid=pla-1675722646259&psc=1) | <img src="https://user-images.githubusercontent.com/82693292/190884318-726a7d4c-bb2b-44ad-af2b-8a74e481b7c4.jpg" width=25%>
| [Yellow Motors & Wheels x 2](https://www.googleadservices.com/pagead/aclk?sa=L&ai=DChcSEwicq9bgrJ36AhVEglsKHb7TD90YABAFGgJ5bQ&ae=2&ohost=www.google.com&cid=CAESbOD23aK1qJnD1RlMq7EP8oWNaj6HFGNsd4tho3Oor7yYtqiwzZJH3hPwdtShtObNoZNMUrGktXpEvQo30J-TriM10fUgiYuTiGzGVQXG23LbmDPa9BUKCBmCOBSTqBg1VsXoEifVo97OsJBBzw&sig=AOD64_3IQhMF9rh80WOnkZoXSJ8QIeS9AA&ctype=5&q=&ved=2ahUKEwikncvgrJ36AhV0jIkEHX7oBkAQ9aACKAB6BAgEECU&adurl=) | <img src="https://user-images.githubusercontent.com/82693292/190883796-67a8fa0b-7f35-4d6f-b26a-9222bdddec1d.jpg" width=25%>
| [GY-521 x 1](https://www.amazon.com/HiLetgo-MPU-6050-Accelerometer-Gyroscope-Converter/dp/B00LP25V1A/ref=asc_df_B00LP25V1A/?tag=hyprod-20&linkCode=df0&hvadid=247487538123&hvpos=&hvnetw=g&hvrand=9636067398850567305&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9016722&hvtargid=pla-407209664611&psc=1) | <img src="https://user-images.githubusercontent.com/82693292/190885707-3832a437-c79b-452b-a097-f51cdf761ea3.jpg" width=25%>



## System Diagrams

 

## Source Code


```c++
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
```


## Bibliography

