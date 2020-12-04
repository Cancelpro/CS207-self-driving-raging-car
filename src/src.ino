//Code Sources: 
//Sarvagnya Purohit: I borrowed their code and circuitry from: https://maker.pro/arduino/projects/arduino-audio-player
//Dejan: I used his guide for my DC motor controller and used some of his code provided here: https://howtomechatronics.com/tutorials/arduino/arduino-dc-motor-control-tutorial-l298n-pwm-h-bridge/
//Dejan: I used his sample code to get my Ultrasonic Sensor working: https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/
//Thanks to all of these sources, I couldn't of done it without them.

//Tait Larsen
//Student Number: 200380253

#include "SD.h"
#define SD_ChipSelectPin 4
#include "TMRpcm.h"
#include "SPI.h"

TMRpcm audio;
//Create variable rage counter.
//This variable will keep track of how many times our vehicle has collided with something.
int rageCounter = 0;

//Define the ports for our DC motor controller.
//Thank you Dejan for these
int enA = 10;
int in1 = 6;
int in2 = 7;
int in3 = 2;
int in4 = 3;
int enB = 0; 

//Create a timer with 500ms so our arduino will not start immediatelly.
int timer = 500;

//Setup our variable for our ultrasonic sensor
//Thank you Dejan for these.
const int hsEcho = 5;
const int hsTrig = 8;
int distance;
long duration;

//Check will turn true if we hit a wall.
bool hitWall = false;
void setup() {
  //Setup our DC motor pins as output and hsEcho as INPUT
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(hsTrig, OUTPUT);
  pinMode(hsEcho, INPUT);

  //Start Serial (I used this for debugging)
  Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:

  //This Code is borrowed from Dejan some modifications are my own:
  //use our ultrasonic sensor to send out sound.
  digitalWrite(hsTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(hsTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(hsTrig, LOW);

  //Now receive our sound with pulseIn and store it in duration
  duration = pulseIn(hsEcho, HIGH);

  //Big thanks to Dejan for this one: 
  //I used his formula to calculate distance :)
  distance = duration*0.034/2;
  Serial.println(rageCounter);

  //Check if the distance is lower than 20 and it hasn't hit a wall AND isn't actively raging:
  //We move our vehicle backwards and set hitWall to true, to avoid call this if statement too soon.
  
  if (distance <= 20 && !hitWall && rageCounter < 2){
    MoveBackwards(); //back the vehicle up
    //digitalWrite(12, HIGH);
    hitWall = true;
    timer = millis(); //Set timer to millis()
    rageCounter += 1; //increment rage counter
    
    
  } 

  //if our time is 1 second and we hit a wall.
  //Turn vehicle right
  //if our timer is > 1000 that means we have been backing up for 1 second and it's time to turn.
  else if(millis() - timer > 1000 && hitWall && rageCounter < 2){
    TurnRight(); //turns right
    hitWall = false; //Now we've dealt with the wall, hitWall = false.
    timer = millis(); //Start timer again.
  }

  //if our timer is > 500 that means we've been turning right for 500ms and it's time to move forward again.
  else if(millis() - timer > 500 && !hitWall && rageCounter < 2){
    MoveForward();
  } 

  //if our rageCounter is 2 Stop moving the vehicle and play our "noo" sound effect.
  else if(rageCounter == 2){
    
    StopMoving();
    PlaySound();

    timer = millis(); //reset timer
    rageCounter += 1;
    
    
  } 

  //if our rage counter is 3 and we've been play our "noo" sound for 2 seconds.
  else if(rageCounter == 3 && millis() - timer > 2000){
      rageCounter += 1; //increment rageCounter by 1
      timer = millis();
      
      audio.disable(); //disable the audio to free up ram (I kept running out.)
  } 

  
  else if (rageCounter >= 4){
    //if the timer was just reset move forward for 500ms
    if (millis() - timer <= 500){
      MoveForward();
    } 
    //if our timer is between 500 and 1000 ms Move backwards for 500ms
    else if (millis() - timer <= 1000 && millis() - timer > 500){
      MoveBackwards();
    } 

    //Once Rage for 4 times reset the counter to 0 to allow for us to drive normally again.
    else if (rageCounter == 8){
      rageCounter = 0; 
    }

    //if our timer is over 1000 ms increment rage by 1 and reset timer.
    else if (millis() - timer > 1000){
      rageCounter += 1;
      timer = millis();
    }
  }

PlaySound(){

  //Thanks Purohit for this code.
    //Sets up our audio speaker on pin 9.
    //this is done here because if I did it in setup like Purohit's tutorial I would run out of memory and crash the arduino
    audio.speakerPin = 9;

   //check if the sd can load
    if (!SD.begin(SD_ChipSelectPin)) {
      Serial.println("SD fail");
      return;
    }
   
    //set the volume and play "no.wav" 
    audio.setVolume(6);
    audio.play("no.wav");
}

}
void TurnRight(){
    //Turns off the right tire and forces our vehicle to turn left.
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    digitalWrite(enB, HIGH);
    digitalWrite(enA, LOW);
}

void MoveBackwards(){
    //reverses both tires and sets them both to max speed.
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    digitalWrite(enB, HIGH);
    digitalWrite(enA, HIGH);
}

void MoveForward(){
    //sets our tires to move forward at max speed.
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    digitalWrite(enB, HIGH);
    digitalWrite(enA, HIGH);
}

void StopMoving(){
    //Stops all tire movement.
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(enB, LOW);
    digitalWrite(enA, LOW);
}
