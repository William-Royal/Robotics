
#include "vex.h"

#include "MoveThread.h"
#include "Move.h"

#define INVERT_TURNS -1 // 1 if left side, -1 if right
#define VISION_BALL Vision6__R_BALL // Vision6__R_BALL if red, Vision6__B_BALL if blue

#define ALL_MOTORS LeftDrive, FrontLeftDrive, RightDrive, FrontRightDrive

using namespace vex;
competition Competition;

unsigned int AmmonX = 0x0000;
int driveX;
int driveY;
int ldrive;
int rdrive;
int blueSize;
int redSize;

// Centers the detected object
void SensorControl()
{
 if(Vision6.largestObject.centerX > 100 && Vision6.largestObject.centerX < 200)
 {
   driveX += (Vision6.largestObject.centerX - 150) / 3;
   ldrive += driveX;
   rdrive -= driveX;
 }
}

// Senses for largest object, color independent
void multipleColor()
{
  Vision6.takeSnapshot(Vision6__B_BALL);
  blueSize = Vision6.largestObject.height * Vision6.largestObject.width;
  Vision6.takeSnapshot(Vision6__R_BALL);
  redSize =  Vision6.largestObject.height * Vision6.largestObject.width;
  if(blueSize > redSize)
  {
    Vision6.takeSnapshot(Vision6__B_BALL);
  }
}

void setIntakeSpeed(int speed)
{
  LeftIntake.spin(forward, speed, pct);
  RightIntake.spin(forward, speed, pct);
}

void setLiftSpeed(int speed)
{
  LeftLift.spin(forward, speed, pct);
  RightLift.spin(forward, speed,pct);
}

void chainControl()
{
  // Lift and Feed Controls
  if(Controller1.ButtonL1.pressing())
  {
    LeftIntake.spin(forward, 100, pct);
    LeftLift.spin(forward, 100, pct);
    RightIntake.spin(forward, 100, pct);
    RightLift.spin(forward, 100, pct);
  }
  else if(Controller1.ButtonL2.pressing())
  {
    LeftIntake.spin(reverse, 100, pct);
    LeftLift.spin(reverse, 100, pct);
    RightIntake.spin(reverse, 100, pct);
    RightLift.spin(reverse, 100, pct);
  }
  else if(Controller1.ButtonR1.pressing())
  {
    LeftIntake.spin(forward, 100, pct);
    LeftLift.spin(forward, 0, pct);
    RightIntake.spin(forward, 100, pct);
    RightLift.spin(forward, 0, pct);
  }
  else if(Controller1.ButtonR2.pressing())
  {
    LeftIntake.spin(reverse, 100, pct);
    LeftLift.spin(forward, 0, pct);
    RightIntake.spin(reverse, 100, pct);
    RightLift.spin(forward, 0, pct);
  }
  else
  {
    LeftIntake.spin(forward, 0, pct);
    LeftLift.spin(forward, 0, pct);
    RightIntake.spin(forward, 0, pct);
    RightLift.spin(forward, 0, pct);
  }

  // Flippery Guy
  if(Controller1.ButtonA.pressing())
  {
    BarMotor.spin(forward, 100, pct);
  }
  else if (Controller1.ButtonB.pressing())
  {
    BarMotor.spin(reverse, 100, pct);
  }
  else
  {
    BarMotor.spin(forward, 0, pct);
  }
}

// Beginning of match functions
void pre_auton(void)
{
  vexcodeInit();
}

  //Autonomous Function(s):
void autonomous(void)
{
  // 1. Turn
  Move::moveDeg(45 * INVERT_TURNS, ALL_MOTORS);

  // 2. Deposit preload
  setIntakeSpeed(100);
  setLiftSpeed(100);

  wait(1000, msec);

  setIntakeSpeed(0);
  setLiftSpeed(0);

  // 3. Move away from goal and turn to face other goal
  Move::moveMM(1300, ALL_MOTORS);
  Move::moveDeg(90 * INVERT_TURNS, ALL_MOTORS);

  // 4. Approach, correcting using active vision
  setIntakeSpeed(100);

  float endPosition = LeftDrive.rotation(deg) + 1200;
  while (LeftDrive.rotation(deg) < endPosition)
  {
    // Initial speed
    ldrive = 80;
    rdrive = 80;

    // Adjust speed to turn to face target
    SensorControl();

    // Update motor speeds
    LeftDrive.spin(fwd, ldrive, pct);
    FrontLeftDrive.spin(fwd, ldrive, pct);
    RightDrive.spin(fwd, rdrive, pct);
    FrontRightDrive.spin(fwd, rdrive, pct);
  }
  LeftDrive.spin(fwd, 0, pct);
  FrontLeftDrive.spin(fwd, 0, pct);
  RightDrive.spin(fwd, 0, pct);
  FrontRightDrive.spin(fwd, 0, pct);

  // 5. Reverse from goal, turn 180deg, reverse to goal
  Move::moveMM(-100, ALL_MOTORS);
  Move::moveDeg(180, ALL_MOTORS);
  Move::moveMM(-100, ALL_MOTORS);

  // 6. Eject payload
  setLiftSpeed(100);

  /*
 // dump preload into center goal

 
  // turn right
    RightDrive.spin(reverse, 100 * INVERT_TURNS, pct);
    LeftDrive.spin(forward, 100 * INVERT_TURNS, pct);
  
    wait(140, msec);

  // stop
    RightDrive.spin(reverse, 0, pct);
    LeftDrive.spin(forward, 0, pct);

  // start intakes
    LeftIntake.spin(forward, 100, pct);
    RightIntake.spin(forward, 100, pct);
    LeftLift.spin(forward, 100, pct);
    RightLift.spin(forward, 100,pct);

  wait(1000, msec);

  // stop intakes  
    LeftIntake.spin(forward, 0, pct);
    RightIntake.spin(forward, 0, pct);
    LeftLift.spin(forward, 0, pct);
    RightLift.spin(forward, 0, pct);

  // turn right 
    LeftDrive.spin(forward, 80 * INVERT_TURNS, pct);
    RightDrive.spin(reverse, 80 * INVERT_TURNS, pct);

    wait(400, msec);

  // arc to corner and engage intakes
  // RightDrive.spin(forward, 80 * INVERT_TURNS, pct);
  // LeftDrive.spin(forward, 45 * INVERT_TURNS, pct);
  RightDrive.spin(forward, 62.5 + (17.5 * INVERT_TURNS), pct);
  LeftDrive.spin(forward, 62.5 - (17.5 * INVERT_TURNS), pct);
  LeftIntake.spin(forward, 80, pct);
  RightIntake.spin(forward, 80, pct);

  wait(2100, msec);

  // engage intake and lift
  LeftIntake.spin(forward, 80, pct);
  RightIntake.spin(forward, 80, pct);
  LeftLift.spin(forward, 80, pct);
  RightLift.spin(forward, 80, pct);

  // vision sensor corrections
  for(int i = 0; i < 50; i++)
  {
    ldrive = 40;
    rdrive = 20;
    Vision6.takeSnapshot(VISION_BALL);
    if(Vision6.largestObject.centerX > 170)
    {
      ldrive += 15;
      rdrive -= 15;
    }
    else if(Vision6.largestObject.centerX < 140)
    {
      ldrive -= 15;
      rdrive += 15;
    }
      LeftDrive.spin(forward, ldrive, pct);
      RightDrive.spin(forward, rdrive, pct);
      wait(10, msec);
  }

  // lift and intake stop
  RightIntake.spin(forward, 0, pct);
  LeftIntake.spin(forward, 0, pct);
  LeftLift.spin(forward, 0, pct);
  RightLift.spin(forward, 0, pct);

  // reverse
  LeftDrive.spin(reverse, 80, pct);
  RightDrive.spin(reverse, 80, pct);

  wait(390, msec);

  // turn right
  LeftDrive.spin(forward, 80 * INVERT_TURNS, pct);
  RightDrive.spin(reverse, 80 * INVERT_TURNS, pct);

  wait(750, msec);

  // stop
  LeftDrive.spin(forward, 0, pct);
  RightDrive.spin(forward, 0, pct);

  wait(100, msec);
  
  // reverse
  RightDrive.spin(reverse, 80, pct);
  LeftDrive.spin(reverse, 80, pct);
  
  wait(700, msec);

  // stop
  LeftDrive.spin(forward, 0, pct);
  RightDrive.spin(forward, 0, pct);

  //dump ball into corner goal
  
  // engage intake and lift
  LeftIntake.spin(forward, 80, pct);
  RightIntake.spin(forward, 80, pct);
  LeftLift.spin(forward, 80, pct);
  RightLift.spin(forward, 80, pct);

  wait(3100, msec);
    
  // stop intake and lift
  RightIntake.spin(forward, 0, pct);
  LeftIntake.spin(forward, 0, pct);
  LeftLift.spin(forward, 0, pct);
  RightLift.spin(forward, 0, pct);

  // forward
  RightDrive.spin(forward, 80, pct);
  LeftDrive.spin(forward, 80, pct);

  wait(200, msec);

  // stop
  LeftDrive.spin(forward, 0, pct);
  RightDrive.spin(forward, 0, pct);
  */

   /*
  Vision Example
    for(int i = 0; i < 123; i++)
    {
      ldrive = 35;
      rdrive = 35;
      Vision6.takeSnapshot(Vision6__R_BALL);
      if(Vision6.largestObject.centerX < 140)
      {
        ldrive -= 5;
        rdrive += 5;
      }
      else if(Vision6.largestObject.centerX > 170)
      {
        ldrive += 5;
        rdrive -= 5;
      }
      LeftDrive.spin(forward, ldrive, pct);
      RightDrive.spin(forward, rdrive, pct);
      wait(10, msec);
    }
    */
    
}

//User Control Function(s):
void usercontrol(void)
{
  while(true)
  { 
    if(Controller1.ButtonDown.pressing())
    {
      for(int n = 0; n < 1; n++)
      {
         LeftDrive.spin(forward, 100, pct);
         RightDrive.spin(reverse, 100, pct);
         FrontLeftDrive.spin(forward, 100, pct);
         FrontRightDrive.spin(reverse, 100, pct);
         wait(750, msec);
         LeftDrive.setStopping(brake);
         RightDrive.setStopping(brake);
         FrontLeftDrive.setStopping(brake);
         FrontRightDrive.setStopping(brake);
         // Move::moveDeg(180, LeftDrive, FrontLeftDrive, RightDrive, FrontRightDrive);
      }
    }
    driveX = 0.60 * Controller1.Axis1.position();  // wow! 60% turn speed
    driveY = 0.85 * Controller1.Axis3.position();  // eh?  85% move speed

    //Vision6.takeSnapshot(VISION_BALL);
    if(Distance14.objectDistance(mm) > 250 or Distance14.objectDistance(mm) == 0)
    {
      multipleColor();
      SensorControl();
    }
    
    LeftDrive.spin(forward, driveY + driveX, pct);
    RightDrive.spin(forward, driveY - driveX, pct);
    FrontLeftDrive.spin(forward, driveY + driveX, pct);
    FrontRightDrive.spin(forward, driveY - driveX, pct);
    chainControl();
    Controller1.Screen.clearScreen();
    Controller1.Screen.print("Distance: ");
    Controller1.Screen.print(Distance14.objectDistance(mm));
    Controller1.Screen.newLine();

    wait(5, msec);
  }
}

// Main Function:
int main() 
{
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
}
