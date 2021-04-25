#include <Arduino.h> //no need to include this if you are using arduino ide
int cpt = 0;         // initialise the encoder counter
// initialise the closed loop regulation variables
float previous_time = 0;
float consigne = 5;
float error = 0;
float previous_error = 0;
float sum_error = 0;
float kp = 400;
float kd = 800;
float ki = 10;
//the function that we call we never the pin 2 got interrupted with a rising edge
void increment()
{
  //check if the second channel is high or low Meaning which give us an information about the direction of the motor mouvemnet
  int SecondChannel = digitalRead(3);
  if (SecondChannel == HIGH)
  {
    cpt++;
  }
  else if (SecondChannel == LOW)
  {
    cpt--;
  }
}
void setup()
{
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  Serial.begin(9600);
  // declare the interruption pin and specifications
  attachInterrupt(digitalPinToInterrupt(2), increment, RISING);
}
void run(int s)
{
  analogWrite(9, s);
  digitalWrite(8, HIGH);
  digitalWrite(10, LOW);
}
void loop()
{
  float current_time = millis();
  // check whether we surpassed 10 ms since the last time we lunched the regulation
  if ((current_time - previous_time) >= 10)
  {
    float speed = (cpt / 4.8);
    error = consigne - speed;
    // Serial.println(error);
    // calculate the regulated commande
    int cmd = kp * error + kd * (error - previous_error) + ki * sum_error;
    // pad the commande to be uniforme with PWM signal
    if (cmd > 255)
    {
      cmd = 255;
    }
    else if (cmd < 0)
    {
      cmd = 0;
    }
    // Serial.println(cmd);
    previous_error = error;
    sum_error += error;
    previous_time = current_time;
    run(cmd);
    // Serial.println(cpt);
    Serial.println(speed);
    Serial.println("");
    cpt = 0;
  }
}
