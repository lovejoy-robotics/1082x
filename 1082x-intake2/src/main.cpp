/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       kaylavigen                                                */
/*    Created:      Tue Dec 01 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// O1                   optical       1               
// Drivetrain           drivetrain    2, 3, 4, 5      
// F1                   motor         6               
// F2                   motor         7               
// M1                   motor         8               
// B1                   motor         9               
// Controller1          controller                    
// Op1                  optical       10              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  //this sets the velocity of the intakes and 2 upper intake motors to max for faster performance
 F1.setVelocity(100.0, percent);
 F2.setVelocity(100.0, percent);
 M1.setVelocity(100.0, percent);
 B1.setVelocity(100.0, percent);
 /*
 *since the optical sensor will be facing up and see the bottom of the ball then 
 *itll need some sort of light so it will stil see the color of the ball so 
 *we are turning the built in lights to max
 */
 Op1.setLightPower(100.0, percent);
 Op1.setLight(ledState :: on);
  
  /*
  *this is printing the hue that the optical sensor is seeing onto the brains screen so that we know 
  *what the hue is that its seeing
  */
 while(true){ 
   Brain.Screen.print(Op1.hue());
   wait(0.1, sec);
   Brain.Screen.clearLine();

   // 100-300 hue = blue 
   // 10-100 hue and 320-360 hue = red
   }
}