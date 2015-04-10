/* 
 //contineous unless stop command
 w -> forward
 x -> reverse
 a -> left
 d -> right
 s -> stop
 1:9 -> speed
 
 */
#include <AFMotor.h>
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(51, 50); // RX, TX

AF_DCMotor motorFL(1);
AF_DCMotor motorFR(2);
AF_DCMotor motorRL(3);
AF_DCMotor motorRR(4);

char state;
int s_speed = 255;
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
  
  if (state == 's') {
    stopALL();
  }
  else if (state == 'w') {
    forward();
  }
  else if (state == 'x') {
    backward();
  }
  else if (state == 'a') {
    left();
  }
  else if (state == 'd') {
    right();
  }
  else if (state == '1') {
    set_speed(map(1, 1, 9, 0, 255));
  }
  else if (state == '2') {
    set_speed(map(2, 1, 9, 0, 255));
  }
  else if (state == '3') {
    set_speed(map(3, 1, 9, 0, 255));
  }
  else if (state == '4') {
    set_speed(map(4, 1, 9, 0, 255));
  }
  else if (state == '5') {
    set_speed(map(5, 1, 9, 0, 255));
  }
  else if (state == '6') {
    set_speed(map(6, 1, 9, 0, 255));
  }
  else if (state == '7') {
    set_speed(map(7, 1, 9, 0, 255));
  }
  else if (state == '8') {
    set_speed(map(8, 1, 9, 0, 255));
  }
  else if (state == '9') {
    set_speed(map(9, 1, 9, 0, 255));
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
