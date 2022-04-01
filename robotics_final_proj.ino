#include <Servo.h>
Servo myservo;
int enA = A5;
int in1 = A4;
int in2 = A3;
int enB = A0;
int in3 = A2;
int in4 = A1;
int trig =11;
int echo = 12;
int buzzer = 8;
int gas_sensor = 5;
int flame_sensor = 2;
int blue_led = 4;
int red_led = 3;
int gasstate;
int flamestate;
int feedback;
int distance;
int left_distance;
int right_distance;
int limit = 25;
int command;
  void setup () {
            Serial.begin(9600);
            myservo.attach(9);
            myservo.write(90);
            pinMode(enA,OUTPUT);
            pinMode(in1, OUTPUT);
            pinMode(in2, OUTPUT);
            pinMode(enB,OUTPUT);
            pinMode(in3, OUTPUT);
            pinMode(in4, OUTPUT);
            pinMode(trig,OUTPUT);
            pinMode(echo,INPUT);
            pinMode(gas_sensor, INPUT);
            pinMode(flame_sensor,INPUT);
            pinMode(red_led, OUTPUT);
            pinMode(blue_led, OUTPUT);
            pinMode(buzzer, OUTPUT);
        }
void loop () {
            Serial.println(distance_value());
            sensor_readings();
    if (Serial.available()>0) {
        command = Serial.read();
          switch(command) {
            case 'X':
            Auto_mode();
            break;
            default:
            Bluetooth_mode();
         }
     }
 }
void Bluetooth_mode () {
        switch(command) {
          case 'B':
          forward ();
          break;
          case'F':
          backward ();
          break;
          case'R':
          left ();
          break;
          case'L':
          right ();
          break;
          default:
          stoprobot();
      }
  }
  
void sensor_readings(){
    gasstate=digitalRead(gas_sensor);
    flamestate=digitalRead(flame_sensor);
    if (gasstate==LOW) {
  
    stoprobot();
      for (int x=0; x<3; x++) {
          digitalWrite(buzzer,HIGH);
          digitalWrite(blue_led,HIGH);
          delay (500);
          digitalWrite(buzzer,LOW);
          digitalWrite(blue_led,LOW);
          delay (500);
      }
   }
   
   if (flamestate==HIGH) {
    stoprobot();
      for (int x=0; x<5; x++) {
          digitalWrite(buzzer,HIGH);
          digitalWrite(red_led,HIGH);
          delay (500);
          digitalWrite(buzzer,LOW);
          digitalWrite(red_led,LOW);
          delay (500);
         }
      }
  }
  
void backward () {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        digitalWrite(enA, HIGH);
        digitalWrite(enB, HIGH);
    }
void right (){
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        digitalWrite(enA, HIGH);
        digitalWrite(enB, HIGH);
    }
void left () {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        digitalWrite(enA, HIGH);
        digitalWrite(enB, HIGH);
    }
void forward (){
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        digitalWrite(enA, HIGH);
        digitalWrite(enB, HIGH);
    }
void stoprobot(){
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
        digitalWrite(enA, LOW);
        digitalWrite(enB, LOW);
    }
void Auto_mode(){
        char sentIn_variable;
        while (sentIn_variable != 'x'){
        sensor_readings();
        backward ();
        compare_distance();
        if (Serial.available()>0){
        sentIn_variable = Serial.read();
      }
    }
  stoprobot();
}
      int distance_value(){
      digitalWrite(trig,LOW);
      delayMicroseconds(2);
      digitalWrite(trig,HIGH);
      delayMicroseconds(10);
      digitalWrite(trig, LOW);//sets the trigger pin off
      feedback = pulseIn(echo, HIGH);// echo pin reads the signal and stores it in feedback variable
      distance = (feedback * 0.034) / 2;// converts it to cm and stores it in the distance variable
      
      //Serial.println(distance);
 return distance;
  }
void check_way(){
      stoprobot();
      myservo.write(180);
      delay (500);
      left_distance = distance_value();
      myservo.write(0);
      delay (500);
      right_distance = distance_value();
      myservo.write(90);
      if (right_distance > limit) {
      right ();
      delay (500);
      forward ();
  }
else if (left_distance > limit) {
      left ();
      delay (500);
      forward ();
    }
  }
void compare_distance(){
      Serial.println(distance_value());
      if(distance_value () < limit){
      check_way();
    }
  }
