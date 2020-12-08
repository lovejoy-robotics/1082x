#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors

//Left 2 driveTrain motors
motor leftMotorA = motor(PORT5, ratio18_1, false);
motor leftMotorB = motor(PORT3, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);

//Right 2 driveTrain motors
motor rightMotorA = motor(PORT16, ratio18_1, true);
motor rightMotorB = motor(PORT12, ratio18_1, true);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);

//Front 2 intake motors
motor F1 = motor(PORT1, ratio18_1, false);
motor F2 = motor(PORT2, ratio18_1, true);

//top upper intake motor that controlls the top front, bottom front, and back bottom rollers 
//to always spin one direction
motor M1 = motor(PORT13, ratio36_1, false);

//top back roller motor that switches which way to spin so that it can either bring up 
//a ball to score or spit one out
motor B1 = motor(PORT6, ratio36_1, false);

//controller for the robot
controller Controller1 = controller(primary);

//front optical sensor to see the colors of the balls for automatic sorting of the balls
optical Op1 = optical(PORT10);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool Controller1LeftShoulderControlMotorsStopped = true;
bool Controller1RightShoulderControlMotorsStopped = true;
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3 + Axis1
      // right = Axis3 - Axis1
      int drivetrainLeftSideSpeed = Controller1.Axis3.position() + Controller1.Axis4.position();
      int drivetrainRightSideSpeed = Controller1.Axis3.position() - Controller1.Axis4.position();
      
      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftDriveSmart.stop();
          // tell the code that the left motor has been stopped
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor next time the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          // stop the right drive motor
          RightDriveSmart.stop();
          // tell the code that the right motor has been stopped
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }

      //this is the the sorting code that we have for the robot, this uses the hue of the ball
      //to automatically sort and spit out the ball that we dont want and to keep 
      //the ball we do want.
    
      //if the driver is holding down L1 then the sorting mechanism will start to sort through 
      //the balls that its intaking and will spit out the enemies balls and keep our teams balls
      if (Controller1.ButtonL1.pressing()) {
        M1.spin(forward);

        //if the ball is red then the optical sensor will see it being the hue of 10-25 or 320-360 
        //(it varies due to different lighting)
        if(Op1.hue() >= 10 & Op1.hue() <= 100 || Op1.hue() >= 320){
        B1.spin(reverse);  
        }

        //if the ball is blue then the optical sensor will see it being the hue of 100-300
        if(Op1.hue() >= 100 & Op1.hue() <= 300){
        B1.spin(forward);  
        }
        //if the sensor doesnt see anything then itll default to 100-150 meaning it wont spit out 
        //the ball but keep any balls inside going up to score

        Controller1LeftShoulderControlMotorsStopped = false;

        // check the ButtonL1/ButtonL2 status to control M1 and B1
        //brings the balls back down the upper intakes
        Controller1LeftShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonL2.pressing()) {
        M1.spin(reverse);
        B1.spin(reverse); 
        Controller1LeftShoulderControlMotorsStopped = false; 
      } else if (!Controller1LeftShoulderControlMotorsStopped) {
        M1.stop();
        B1.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1LeftShoulderControlMotorsStopped = true;
      }
      // check the ButtonR1/ButtonR2 status to control F1
      // ButtonR1/ButtonR2 control intake arms
      if (Controller1.ButtonR1.pressing()) {
        F1.spin(forward);
        F2.spin(forward);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonR2.pressing()) {
        F1.spin(reverse);
        F2.spin(reverse);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (!Controller1RightShoulderControlMotorsStopped) {
        F1.stop();
        F2.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1RightShoulderControlMotorsStopped = true;
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}