// Sample Code for 3DOF robot by Dr. Duong Van Lac (c) lac.duongvan@hust.edu.vn
// Kỹ thuật lập trình trong Cơ điện tử

int  dataValue[4]; 
int  q1= 0,q2= 52,q3= -125,q4;
//  q_1 = dataValue[0], 
//  q_2 = dataValue[1], 
//  q_3 = dataValue[2], 
//  q_4 = dataValue[3], 

#include <Servo.h>

Servo servo_1, servo_2, servo_3, servo_4;  // create servo object to control a servo

char buffer[4]; // char array
int  cnt = 0;
int  index = 0;
// Format message: >q_1:q_2:q_3:q_4' '
// Eg. >30:55:99:10\n

void setup() {
  // put your setup code here, to run once:
    Serial.setTimeout(5);
    Serial.begin(9600);
    servo_1.attach(3); 
    servo_2.attach(5); 
    servo_3.attach(6); 
    servo_4.attach(9); 
}

void loop() {
  // put your main code here, to run repeatedly:
 if(Serial.available())
 {
  char c = Serial.read();
  switch(c)
  {
    case '>':        // new message   
          cnt = 0;  
          index = 0;  
          break; 
    case ':':       // next data  
          dataValue[index] =  atoi(buffer);
          index ++;
          buffer[0] ='\0';  buffer[1] ='\0'; 
          buffer[2] ='\0';  buffer[3] ='\0'; 
          cnt = 0; 
          break; 
    case ' ':       // finish      
          dataValue[index] =  atoi(buffer);
          buffer[0] ='\0';  buffer[1] ='\0'; 
          buffer[2] ='\0';  buffer[3] ='\0'; 
          cnt = 0;
          index = 0;
          break; 
    default:
    buffer[cnt++] = c;
  }
 }

q1 = dataValue[0];
q2 = dataValue[1];
q3 = dataValue[2];
if(dataValue[3]==0)
{
q4 = 17;
}
else
{ 
  q4=0;
}
servo_1.write(q1);   
servo_2.write(-(q2-53));   
servo_3.write(q3+120);   
servo_4.write(q4);   

// Serial.print("q_1 = ");
// Serial.print(q1);
// Serial.print("|q_2 = ");
// Serial.print(q2);
// Serial.print("|q_3 = ");
// Serial.print(q3);
// Serial.print("|q_3 = ");
// Serial.println(q4);

}
