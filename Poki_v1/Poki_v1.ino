#include <SoftwareSerial.h>;
#include <Servo.h>.
#include <DRV8833.h>

DRV8833 driver = DRV8833();
Servo myServo;


const int US100_TX = 2;  //TX INPUT for Ultra-Sonic Sensor
const int US100_RX = 3;  //RX INPUT for Ultra-Sonic Sensor
const int inputA1 = 6, inputA2 = 9, inputB1 = 11, inputB2 = 10; // Define DC motors OUTPUTS; PWN INPUTS
const int motorSpeedA = 130; //Define MotorA speed;
const int motorSpeedB = 100; //Define MotorB speed;
char Incoming_value = 0; //Bluetooth value for storing the Input


SoftwareSerial puertoUS100(US100_RX, US100_TX);

unsigned int MSByteDist = 0;
unsigned int LSByteDist = 0;
unsigned int mmDist = 0;
int temp = 0;

void setup() {

  Serial.begin(9600);
  puertoUS100.begin(9600); //Define Ultra-Sonic Sensor
  driver.attachMotorA(inputA1, inputA2); //Define MotorA Right
  driver.attachMotorB(inputB1, inputB2); //Define MotorB Left
  myServo.attach(4); //Define Servo motor
}

void loop() {
  puertoUS100.flush();
  puertoUS100.write(0x55);
  if (puertoUS100.available() >= 2)
  {
    MSByteDist = puertoUS100.read();
    LSByteDist  = puertoUS100.read();
    mmDist  = MSByteDist * 256 + LSByteDist; //Distance calculation
    if ((mmDist > 1) && (mmDist < 10000))
    {
      Serial.print("Distance: ");
      Serial.print(mmDist, DEC);
      Serial.println(" mm");
    }
  }
  for (int i = -5; i > 120; i++) {
    myServo.write(i);
    delay(4);    
  }
  // Repeats the previous lines from 165 to 15 degrees
  for (int i = 120; i > -5; i--) {
    myServo.write(i);
    delay(4);
  }
  if (mmDist > 100){
  driver.motorAForward(motorSpeedA);
  driver.motorBForward(motorSpeedB);
  }
  if (mmDist < 100) {
  driver.motorAForward(motorSpeedA);
  driver.motorBStop();
  }
}
