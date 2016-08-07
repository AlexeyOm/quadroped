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

String rawcommand;                        // Global variable that stores the raw received IR command
String command;                           // Global variable that stores part of the decoded IR command
int times;                                // Global variable that stores part the received IR command
int speedms;   

boolean IRreceive = true;                 // Set this to true if you want to use the IR remote
boolean receivelog = true;               // Set this to true if you want to see the serial messages for debugging the IR commands


void setup() {

  //NAME.attach(motorname, pin, init-angle, flipped, offset-angle);
  BOT.attach(hipFrontLeft,   A1,  120, 0, 5);
  BOT.attach(hipFrontRight,  A0,  120, 1, 0);
  BOT.attach(hipRearLeft,    10,  120, 1,  3);
  BOT.attach(hipRearRight,    4,  120, 0, 5);
 
  BOT.attach(kneeFrontLeft,  12,  110, 1, 37);
  BOT.attach(kneeFrontRight,  2,  110, 0, 40);
  BOT.attach(kneeRearLeft,   11,  110, 1, 37);
  BOT.attach(kneeRearRight,   3,  110, 0, 46);
 
  //INIT sounder
  pinMode(sounderPin, OUTPUT);

  //wait for joints to be initialized
  delay(500);
 
   if (IRreceive == true)                  // Check if required (when Serial is started servo1 connector will not work!)
    {
      Serial.begin(2400);
      Serial.setTimeout(100);
      Serial.println("serial communication started");
    }
 

}


 
  void loop() {
  if (IRreceive == true)                  // Choose between IR commands or random action
    {
      getcommand();                       // Listen for IR command
      executecommand();                   // Execute any receveid commands
    }
}
  
 
 










void getcommand (void)                   // This is the routine that listens and decodes any IR commands. Decodes commands end up in the global vars.
{ 
  int space1 = 0;
  int space2 = 0;
  
  if (Serial.available()) {
     rawcommand = Serial.readString();
     if (receivelog){
        Serial.println("START " +  rawcommand  + " END" + "Received string length = " + rawcommand.length() + "End character > at index = " + rawcommand.indexOf('>'));
     }
 
     //checking and deleting rubbish data at start of received command
     if ((rawcommand.indexOf('<') != 0) && (rawcommand.indexOf('<') != -1))
     {
        rawcommand = rawcommand.substring(0, rawcommand.indexOf('<'));
     }
     
     //check if received command is correct
     if ((rawcommand.charAt(0) == '<') && (rawcommand.indexOf('>') >= 8) )
     {
       if (receivelog){
         Serial.println("Command is VALID"); 
       }      
       //breakdown into chunks
       //command
       command = rawcommand.substring(1, 3);
       
       //finding the spaces to find the times and speedms
       for (int i=0; i <= rawcommand.length(); i++ )
       {
         if ((rawcommand.charAt(i) == ' ') && (space1 == 0))
         {
            space1 = i;
         }
         else if ((rawcommand.charAt(i) == ' ') && (space2 == 0))
         {
            space2 = i;
         }
       }
 
       //Setting the command variables and checking if they are indeed a number (toInt()).
       
       //times
       times = rawcommand.substring(space1 + 1, space2).toInt();
       
       //speedms
       speedms = rawcommand.substring(space2 + 1, rawcommand.indexOf('>')).toInt();
 
       if (receivelog){
         Serial.println("decoded commands are:");
         Serial.flush();
         Serial.println("command = " +  command);
         Serial.flush();
         Serial.println("times = " +  times);
         Serial.flush();
         Serial.println("speedms = " +  speedms);
       }
       
     }
     else
     {
       if (receivelog){
          Serial.println("Command is NOT valid");
       }
       resetserial();  
     }
  }
}
//--------------------------------------------------------------
void resetserial (void)                  // This clears any received IR commands that where received in the serial buffer while the robot was execution a command.
{
  //resetting all variables
  rawcommand = "";
  command = "";
  times = 0;
  speedms = 0;
  
  //flushing the serial buffer (64 byte) so there are no stored movements that need to be handled (annoying)...
  while (Serial.available()) {
    Serial.read();
  }
}
//--------------------------------------------------------------
void executecommand (void)                // Execute the commands that are stored in the global vars.
{ 
  if (command == "WF")
  {
    walkForward1(1,100);
    resetserial();
  }
  if (command == "TR")
  {
    turnRight(0,50);
    resetserial();
  }
  
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
      
      BOT.animate(stepSpeed/5);
      
      BOT.move(kneeFrontLeft,90 );
      BOT.move(kneeRearRight,  90 );
    BOT.animate(stepSpeed);
}


int turnRight(int angle, int turnSpeed) {
  
   
  BOT.move(hipFrontLeft,   120);
  BOT.move(hipFrontRight,  120);
  BOT.move(hipRearLeft,    120);
  BOT.move(hipRearRight,    120);
 
  BOT.move(kneeFrontLeft,  110);
  BOT.move(kneeFrontRight,  110);
  BOT.move(kneeRearLeft,   110);
  BOT.move(kneeRearRight,   110);
  
  BOT.animate(turnSpeed);
  
   
  BOT.move(kneeFrontLeft,80 );
  BOT.move(hipFrontLeft, 150);
  BOT.animate(turnSpeed);
  BOT.move(kneeFrontLeft, 110 );
  BOT.move(hipFrontLeft, 180);
  BOT.animate(turnSpeed);
  
  BOT.move(kneeFrontRight,80 );
  BOT.move(hipFrontRight, 100);
  BOT.animate(turnSpeed);
  BOT.move(kneeFrontRight, 110 );
  BOT.move(hipFrontRight, 80);
  BOT.animate(turnSpeed);

  BOT.move(kneeRearRight,80 );
  BOT.move(hipRearRight, 150);
  BOT.animate(turnSpeed);
  BOT.move(kneeRearRight, 110 );
  BOT.move(hipRearRight, 180);
  BOT.animate(turnSpeed);
  
  BOT.move(kneeRearLeft,80 );
  BOT.move(hipRearLeft, 100);
  BOT.animate(turnSpeed);
  BOT.move(kneeRearLeft, 110 );
  BOT.move(hipRearLeft, 80);
  BOT.animate(turnSpeed);
  
  BOT.move(hipFrontLeft,   120);
  BOT.move(hipFrontRight,  120);
  BOT.move(hipRearLeft,    120);
  BOT.move(hipRearRight,    120);
 
  BOT.move(kneeFrontLeft,  110);
  BOT.move(kneeFrontRight,  110);
  BOT.move(kneeRearLeft,   110);
  BOT.move(kneeRearRight,   110);
  
  BOT.animate(turnSpeed);
  
}

int walkForward1(int steps, int walkSpeed) {
  
  BOT.move(hipFrontLeft,   120);
  BOT.move(hipFrontRight,  120);
  BOT.move(hipRearLeft,    120);
  BOT.move(hipRearRight,    120);
  BOT.move(kneeFrontLeft,  110);
  BOT.move(kneeFrontRight,  110);
  BOT.move(kneeRearLeft,   110);
  BOT.move(kneeRearRight,   110);
  
  BOT.animate(walkSpeed);
  
  BOT.move(kneeFrontRight,  45);
  BOT.move(hipFrontRight,  130);
  BOT.move(kneeRearLeft,  45);
  BOT.move(hipRearLeft,  105);
  
  BOT.animate(walkSpeed);
  BOT.move(kneeFrontRight,  110);
  BOT.move(hipFrontRight,  140);
  BOT.move(kneeRearLeft,  110);
  BOT.move(hipRearLeft,  90);
  BOT.animate(walkSpeed);
  //other legs
  
  BOT.move(hipFrontRight,  130);
  BOT.move(hipRearLeft,  110);
  
  
  BOT.move(kneeFrontLeft,  45);
  BOT.move(hipFrontLeft,  130);
  BOT.move(kneeRearRight,  45);
  BOT.move(hipRearRight,  105);
  
  BOT.animate(walkSpeed);
  BOT.move(hipFrontRight,  120);
  BOT.move(hipRearLeft,  120);
  
  BOT.move(kneeFrontLeft,  110);
  BOT.move(hipFrontLeft,  140);
  BOT.move(kneeRearRight,  110);
  BOT.move(hipRearRight,  90);
  BOT.animate(walkSpeed);
  
}
