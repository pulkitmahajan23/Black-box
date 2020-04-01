#include <WiFi.h>                                                    // esp8266 library
#include <FirebaseESP32.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <MQ135.h>

#define FIREBASE_HOST "***********.firebaseio.com"                          // the project name address from firebase id
#define FIREBASE_AUTH "***************************************"            // the secret key generated from firebase

#define WIFI_SSID "**********"                                             // input your home or public wifi name 
#define WIFI_PASSWORD "**************"                                    //password of wifi ssid                     

MPU6050 mpu6050(Wire);
FirebaseData firebase;

const int lm35=36;
const int mq135=39;
MQ135 gassensor=MQ135(mq135);

float temp;
float emission;
void setup() {
  Serial.begin(9600);
  pinMode(lm35,INPUT);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.println("Connecting to Wifi...");
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }
  Serial.println("\nWifi Connected with local IP: ");
  Serial.print(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  mpu6050.update();
  Firebase.setFloat(firebase,"/GyroOffSet/X",mpu6050.getGyroX());
  Firebase.setFloat(firebase,"/GyroOffSet/Y",mpu6050.getGyroY());
  Firebase.setFloat(firebase,"/GyroOffSet/Z",mpu6050.getGyroZ());
  Firebase.setFloat(firebase,"/Accel/X",mpu6050.getAccX());
  Firebase.setFloat(firebase,"/Accel/Y",mpu6050.getAccY());
  Firebase.setFloat(firebase,"/Accel/Z",mpu6050.getAccZ());
  temp=analogRead(lm35);
  temp=(temp*330)/1024.0;
  Firebase.setFloat(firebase,"/Engine_Temperature",temp);
  emission=gassensor.getPPM();
  Firebase.setFloat(firebase,"/Emission_Value",emission);
}

void loop()
{
  temp=analogRead(lm35);
  mpu6050.update();
  temp=(temp*330)/1024.0;
  Firebase.pushInt(firebase,"/Engine_Temperature",temp);
  Firebase.pushFloat(firebase,"/Accel/X",mpu6050.getGyroX());
  Firebase.pushFloat(firebase,"/GyroOffSet/Y",mpu6050.getGyroY());
  Firebase.pushFloat(firebase,"/GyroOffSet/Z",mpu6050.getGyroZ());
  Firebase.pushFloat(firebase,"/Accel/X",mpu6050.getAccX());
  Firebase.pushFloat(firebase,"/Accel/Y",mpu6050.getAccY());
  Firebase.pushFloat(firebase,"/Accel/Z",mpu6050.getAccZ());
  emission=gassensor.getPPM();
  Firebase.pushFloat(firebase,"/Emission_Value",emission);
  delay(1000);
}
