#include <Servo.h> 
#include <SoftwareSerial.h>

SoftwareSerial teapot(10, 11);
Servo myservo;  

void setup() { 
  myservo.attach(5);  
  teapot.begin(4800);
} 
 
void loop(){    
   if(teapot.available()){
       teapot.read();
       vkl();
   }
} 

void vkl(){
    myservo.write(180);  
    delay(1000);  
    myservo.write(0); 
    delay(1000);
}
