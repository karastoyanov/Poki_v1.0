#include<SoftwareSerial.h>
SoftwareSerial BTSerial(0,1); // assigning 10 as RX ans 11 as TX 
#define motor_left 6
#define motor_right 10
#define motor_right_dir 11
#define motor_left_dir 9
void setup() {
 pinMode(2,OUTPUT);
 pinMode(3,OUTPUT);
 pinMode(4,OUTPUT);
 pinMode(5,OUTPUT);
 while(!Serial){;} // waiting for serial communication to setup
 BTSerial.begin(9600); // beginning the bluetooth connection
}
void loop() {
 if(BTSerial.available()){
    Serial.write(BTSerial.read());
  }
  if(Serial.available()){
    BTSerial.write(Serial.read());
  }
 {
     char ch = BTSerial.read();  // reading one character at a time
     if(ch=='f'){          // action to be performed if input is 'f'
       digitalWrite(motor_left_dir,HIGH);
       digitalWrite(motor_right_dir,HIGH);
       analogWrite(motor_left,150);
       analogWrite(motor_right,120);
     }
     else if(ch == 'b'){       // action to be performed if input is 'b'
       digitalWrite(motor_left_dir,LOW);
       digitalWrite(motor_right_dir,LOW);
       analogWrite(motor_left,150);
       analogWrite(motor_right,150);
     }
     else if(ch == 'l'){       // action to be performed if input is 'l'
       digitalWrite(motor_left_dir,HIGH);
       digitalWrite(motor_right_dir,HIGH);
       analogWrite(motor_left,0);
       analogWrite(motor_right,120);
     }
     else if(ch == 'r'){     // action to be performed if input is 'r'
       digitalWrite(motor_left_dir,HIGH);
       digitalWrite(motor_right_dir,HIGH);
       analogWrite(motor_left,120);
       analogWrite(motor_right,0); 
     }
     else if(ch =='s'){  // action to be performed if input is 's'
       digitalWrite(motor_left_dir,HIGH);
       digitalWrite(motor_right_dir,HIGH);
       analogWrite(motor_left,0);
       analogWrite(motor_right,0); 
     }
 }
} 
