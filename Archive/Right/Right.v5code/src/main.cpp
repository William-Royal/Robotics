/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\ohowes                                           */
/*    Created:      Mon Dec 14 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// lift1                motor         9               
// backright            motor         10              
// intake1              motor         8               
// intake2              motor         3               
// lift2                motor         5               
// backleft             motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "time.h"
// Allows for easier use of the VEX Library
using namespace vex;
int ldrive;
int rdrive;
competition Competition;

float myVariable;

// "when autonomous" hat block
int onauton_autonomous_0() {
 
 // angle
    backright.spin(forward, 100, pct);
    backleft.spin(reverse, 100, pct);
wait(200, msec);
    backright.spin(reverse, 0, pct);
    backleft.spin(forward, 0, pct);

//ditch ball into center
    intake1.spin(forward, 100, pct);
    intake2.spin(forward, 100, pct);
    lift1.spin(forward, 100, pct);
    lift2.spin(forward, 100,pct);
wait(1200, msec);
    intake1.spin(forward, 0, pct);
    intake2.spin(forward, 0, pct);
    lift1.spin(forward, 0, pct);
    lift2.spin(forward, 0, pct);

//onward!
    backleft.spin(forward, 80, pct);
    backright.spin(forward, 80, pct);
wait(500, msec);
    backleft.spin(forward, 0, pct);
    backright.spin(forward, 0, pct);

//forward, pick up??
    backleft.spin(forward, 80, pct);
    backright.spin(forward, 80,pct);
    intake1.spin(forward, 80, pct);
    intake2.spin(forward, 80, pct);
wait(500, msec);
    backleft.spin(forward, 0, pct);
    backright.spin(forward, 0, pct);
    intake1.spin(forward, 0, pct);
    intake2.spin(forward, 0, pct);

//
    backleft.spin(forward, 80, pct);
    backright.spin(reverse, 80, pct);
    intake1.spin(forward, 80, pct);
    intake2.spin(forward, 80, pct);
wait(750, msec);
    backleft.spin(forward, 0, pct);
    backright.spin(reverse, 0, pct);
    intake1.spin(forward, 0, pct);
    intake2.spin(forward, 0, pct);

//
    lift1.spin(forward, 80, pct);
    lift2.spin(forward, 80, pct);
wait(400, msec);
    lift1.spin(forward, 0, pct);
    lift2.spin(forward, 0, pct);






  return 0;
}

void VEXcode_driver_task() {
  // Start the driver control tasks....

  while(Competition.isDriverControl() && Competition.isEnabled()) {this_thread::sleep_for(10);}



  return;
}

void VEXcode_auton_task() {
  // Start the auton control tasks....
  vex::task auto0(onauton_autonomous_0);
  while(Competition.isAutonomous() && Competition.isEnabled()) {this_thread::sleep_for(10);}
  auto0.stop();
  return;
}



int main() {
  vex::competition::bStopTasksBetweenModes = false;
  Competition.autonomous(VEXcode_auton_task);
  Competition.drivercontrol(VEXcode_driver_task);

  // post event registration

  // wait for rotation sensor to fully initialize
  wait(30, msec);

}



