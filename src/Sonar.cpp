#include <Arduino.h>
#include <NewPing.h>

#define MAX_DISTANCE 400 
float current_time;
const int trigPinG = 5;
const int echoPinG = 5;
const int trigPinD = 6;
const int echoPinD= 6;
float error = 0;
float previous_time = 0;
float previous_error = 0;
float sum_error = 0;
float kp = 0.5;
float kd = 800;
float ki = 10;
int in1 = 13;
int in2 = 12;
int in3 = 11;
int in4 = 8;
int en1 = 9;
int en2 = 10;
int cmd = 0;

NewPing sensorL(trigPinG, echoPinG, MAX_DISTANCE);  
NewPing sensorR(trigPinD, echoPinD, MAX_DISTANCE);

long duration;
int distance;
void run(int s, int pin1 ,int pin2, int pin3)
{
 if (s > 0)
    {
       digitalWrite(pin1, HIGH);
       digitalWrite(pin2, LOW);
       analogWrite(pin3, s);
    }
}
void stay_in_the_fucking_line(int max_speed){
    error = (sensorL.ping_median(1)-sensorR.ping_median(1))/100;
    cmd = kp * error ;
    previous_error = error;
    sum_error += error;
    previous_time = current_time;
    if (cmd > max_speed)
    {
      cmd = max_speed;
    }
    else if (cmd < -max_speed)
    {
      cmd = -max_speed;
    }
    run(max_speed + cmd,in1,in2,en1);
    run(max_speed - cmd,in3,in4,en2);
}
void setup() {

 Serial.begin(9600);

}

void loop() {
  
  if ((current_time - previous_time) >= 10) stay_in_the_fucking_line(65);
  
}
