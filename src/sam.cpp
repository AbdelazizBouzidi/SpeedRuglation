#include <Arduino.h>

#define MAX_DISTANCE 400 
float current_time;
const int trigPinG = 4;
const int echoPinG = A2;
const int trigPinD = 3;
const int echoPinD= A1;
float error = 0;
float previous_time = 0;
float previous_error = 0;
float sum_error = 0;
float kp = 0.5;
float kd = 800;
float ki = 10;
int in1 = 11;
int in2 = 10;
int in3 = 9;
int in4 = 6;
int cmd = 0;
long duration;
int distance;

int read_sensor(int trigPin, int echoPin){
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
return distance;
}

void run(int s, int pin1 ,int pin2 )
{
 if (s > 0)
    {
       analogWrite(pin1, s);
       analogWrite(pin2, LOW);
       
    }
}

void stay_in_the_line(int max_speed){
    error = (read_sensor(trigPinG,echoPinG)-read_sensor(trigPinD,echoPinD));
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
    run(max_speed + cmd,in1,in2);
    run(max_speed - cmd,in3,in4);
}

void setup() {
  pinMode(trigPinG, OUTPUT); // Sets the trigPin as an Output
  pinMode(trigPinD, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinG, INPUT); // Sets the echoPin as an Input
  pinMode(echoPinD, INPUT); // Sets the echoPin as an Input
}

void loop() {
     if ((current_time - previous_time) >= 10) stay_in_the_line(65);

}
  
