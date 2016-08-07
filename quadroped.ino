#include <Servo.h> 
#include <ALLBOT.h>

ALLBOT BOT(8);  //number of motors

enum MotorName {
  hipFrontLeft,
  hipFrontRight,
  hipRearLeft,
  hipRearRight,
  kneeFrontLeft,
  kneeFrontRight,
  kneeRearLeft,
  kneeRearRight
};

int sounderPin = 13;

void setup() {


/*
  BOT.attach(hipFrontLeft,   A1,  90, 0, 5);
  BOT.attach(hipFrontRight,  A0,  90, 1, 0);
  BOT.attach(hipRearLeft,    10,  90, 0,  -3);
  BOT.attach(hipRearRight,    4,  90, 0, 5);
 
  BOT.attach(kneeFrontLeft,  12,  90, 1, 37);
  BOT.attach(kneeFrontRight,  2,  90, 0, 40);
  BOT.attach(kneeRearLeft,   11,  90, 1, 37);
  BOT.attach(kneeRearRight,   3,  90, 0, 46);
*/





  //NAME.attach(motorname, pin, init-angle, flipped, offset-angle);
  BOT.attach(hipFrontLeft,   A1,  135, 0, 5);
  BOT.attach(hipFrontRight,  A0,  135, 1, 0);
  BOT.attach(hipRearLeft,    10,  135, 1,  3);
  BOT.attach(hipRearRight,    4,  135, 0, 5);
 
  BOT.attach(kneeFrontLeft,  12,  90, 1, 37);
  BOT.attach(kneeFrontRight,  2,  90, 0, 40);
  BOT.attach(kneeRearLeft,   11,  90, 1, 37);
  BOT.attach(kneeRearRight,   3,  90, 0, 46);
  
  //INIT sounder
  pinMode(sounderPin, OUTPUT);

  //wait for joints to be initialized
  delay(500);
  
  
  

}

void loop() {
  // put your main code here, to run repeatedly:
    static int speedms = 2;
  /*
    BOT.move(hipFrontRight, 90);
    BOT.move(hipRearRight, 90);
    BOT.animate(speedms);
    
    delay(speedms/2);
    
    BOT.move(hipFrontRight, 45);
    BOT.move(hipRearRight, 135);
    BOT.animate(speedms);
*/
  
  
  //BOT.animate(speedms);
  
  //delay(speedms/2);
  stepForward(1);
  
  
}

void stepForward(int steps) {
    
      static int stepSpeed = 100;
  
      //feet up
      BOT.move(kneeFrontRight,45 );
      BOT.move(kneeRearLeft,  45 );
      //move the hips forward   
      BOT.move(hipFrontRight, 135);
      BOT.move(hipRearLeft, 90);
      
      BOT.animate(stepSpeed);
      
      BOT.move(kneeFrontRight,90 );
      BOT.move(kneeRearLeft,  90 );
      
      BOT.animate(stepSpeed);
     // delay(stepSpeed);
      
      BOT.move(kneeRearRight,45 );
      BOT.move(kneeFrontLeft,  45 );
      
      BOT.move(hipFrontRight,90 );
      BOT.move(hipRearLeft,  135 );
      
      BOT.move(hipRearRight,90 );
      BOT.move(hipFrontLeft,  135 );
      BOT.animate(stepSpeed);
      
      BOT.move(kneeRearRight,90 );
      BOT.move(kneeFrontLeft,  90 );
      
      BOT.animate(stepSpeed);
 
     BOT.move(kneeFrontRight,45 );
      BOT.move(kneeRearLeft,  45 ); 
    BOT.move(hipRearRight,135 );
      BOT.move(hipFrontLeft,  90 );  
      
      BOT.animate(stepSpeed);
      
      BOT.move(kneeFrontLeft,90 );
      BOT.move(kneeRearRight,  90 ); 
    BOT.animate(stepSpeed);
}
