/* 
 //contineous unless stop command
 1 -> forward
 2 -> reverse
 3 -> left
 4 -> right
 0 -> stop
 
 //once set
 5 -> fast speed
 6 -> slow speed
 
 */
#include <AFMotor.h>
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(51, 50); // RX, TX

AF_DCMotor motorFL(1);
AF_DCMotor motorFR(2);
AF_DCMotor motorRL(3);
AF_DCMotor motorRR(4);

char state;
int s_speed = 240;
int iteration = 0;

void setup() {
  BTSerial.begin(9600);
  //Serial.begin(9600);
  BTSerial.print("start!");
  //Serial.print("start!");
  set_speed(s_speed);  
}

void loop() {
  iteration++;
  if(iteration > 150 && state != '0'){
   iteration = 0;
   state = '0';
  }
  //state = '0';

  //if(Serial.available() > 0){     
  //  state = Serial.read();
  //  BTSerial.print(state);
  //}
  if(BTSerial.available() > 0){     
    state = BTSerial.read();
    //Serial.print(state);
    iteration = 0;
  }  
  
  if (state == '0') {
    stopALL();
  }
  else if (state == '1') {
    forward();
  }
  else if (state == '2') {
    backward();
  }
  else if (state == '3') {
    left();
  }
  else if (state == '4') {
    right();
  }

}

void forward(){
  set_speed(s_speed);
  motorFL.run(FORWARD);
  motorFR.run(FORWARD);
  motorRL.run(FORWARD);
  motorRR.run(FORWARD);   
  //stopALL();
}    

void backward(){
  set_speed(s_speed);
  motorFL.run(BACKWARD);
  motorFR.run(BACKWARD);
  motorRL.run(BACKWARD);
  motorRR.run(BACKWARD);   
  //stopALL();
}    

void left(){
  set_speed(s_speed);
  motorFL.run(FORWARD);
  motorFR.run(BACKWARD);
  motorRL.run(FORWARD);
  motorRR.run(BACKWARD);   
  //stopALL();
}    

void right(){
  set_speed(s_speed);
  motorFL.run(BACKWARD);
  motorFR.run(FORWARD);
  motorRL.run(BACKWARD);
  motorRR.run(FORWARD);   
  //stopALL();
}    

void stopALL(){
  set_speed(0);  
}

void set_speed(int s){  
  motorFL.setSpeed(s);
  motorFR.setSpeed(s);
  motorRL.setSpeed(s);
  motorRR.setSpeed(s);
}   
