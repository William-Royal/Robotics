
#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// LeftDrive            motor         1               
// RightDrive           motor         10              
// RightIntake          motor         8               
// LeftIntake           motor         5               
// RightLift            motor         9               
// LeftLift             motor         3               
// Vision6              vision        6               
// BarMotor             motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----
#include <cmath>

using namespace vex;
competition Competition;

int AmmonX;
int driveX;
int driveY;
int ldrive;
int rdrive;

void maxVal()
{
 if ((driveY + driveX) > 100)
 {
   driveY = (driveY / ((driveX + driveY) / 100));
 }
}

void SensorControl()
{
  if (driveX < 5 && driveX > -5)
  {
    if(Vision6.largestObject.centerX < 140 && Vision6.largestObject.centerX > 120)
    {
      driveX += -5;
    }
    else if (Vision6.largestObject.centerX <= 120 && Vision6.largestObject.centerX > 100)
    {
      driveX += -10;
    }
    else if(Vision6.largestObject.centerX > 160 && Vision6.largestObject.centerX < 180)
    {
      driveX += 5;
    }
    else if (Vision6.largestObject.centerX >= 180 && Vision6.largestObject.centerX < 200)
    {
      driveX += 10; 
    }
  }
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
  
 // dump preload into center goal
    RightDrive.spin(reverse, 100, pct);
    LeftDrive.spin(forward, 100, pct);
wait(140, msec);
    RightDrive.spin(reverse, 0, pct);
    LeftDrive.spin(forward, 0, pct);

    LeftIntake.spin(forward, 100, pct);
    RightIntake.spin(forward, 100, pct);
    LeftLift.spin(forward, 100, pct);
    RightLift.spin(forward, 100,pct);
wait(1000, msec);
    LeftIntake.spin(forward, 0, pct);
    RightIntake.spin(forward, 0, pct);
    LeftLift.spin(forward, 0, pct);
    RightLift.spin(forward, 0, pct);

//Turn
    LeftDrive.spin(forward, 80, pct);
    RightDrive.spin(reverse, 80, pct);
wait(350, msec);
//arc to corner
    RightDrive.spin(forward, 80, pct);
    LeftDrive.spin(forward, 45, pct);
    LeftIntake.spin(forward, 80, pct);
    RightIntake.spin(forward, 80, pct);
wait(1950, msec);
    LeftIntake.spin(forward, 80, pct);
    RightIntake.spin(forward, 80, pct);
    LeftLift.spin(forward, 80, pct);
    RightLift.spin(forward, 80, pct);
for(int i = 0; i< 50; i++)
{
  ldrive = 40;
  rdrive = 20;
  Vision6.takeSnapshot(Vision6__B_BALL);
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
    

//retrieve ball?
    RightIntake.spin(forward, 0, pct);
    LeftIntake.spin(forward, 0, pct);
    LeftLift.spin(forward, 0, pct);
    RightLift.spin(forward, 0, pct);

//back up and 180 turn
    LeftDrive.spin(reverse, 80, pct);
    RightDrive.spin(reverse, 80, pct);
wait(390, msec);
    LeftDrive.spin(forward, 80, pct);
    RightDrive.spin(reverse, 80, pct);
wait(750, msec);
    LeftDrive.spin(forward, 0, pct);
    RightDrive.spin(forward, 0, pct);
wait(100, msec);
    RightDrive.spin(reverse, 80, pct);
    LeftDrive.spin(reverse, 80, pct);
wait(700, msec);
    LeftDrive.spin(forward, 0, pct);
    RightDrive.spin(forward, 0, pct);

//dump ball into corner goal
    LeftIntake.spin(forward, 80, pct);
    RightIntake.spin(forward, 80, pct);
    LeftLift.spin(forward, 80, pct);
    RightLift.spin(forward, 80, pct);
wait(3100, msec);
    RightIntake.spin(forward, 0, pct);
    LeftIntake.spin(forward, 0, pct);
    LeftLift.spin(forward, 0, pct);
    RightLift.spin(forward, 0, pct);

//forward slightly
   RightDrive.spin(forward, 80, pct);
   LeftDrive.spin(forward, 80, pct);
wait(200, msec);
    LeftDrive.spin(forward, 0, pct);
    RightDrive.spin(forward, 0, pct);

   /*
 // Vision Example
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
    Vision6.takeSnapshot(Vision6__B_BALL);

    driveX = Controller1.Axis1.position();
    driveY = Controller1.Axis3.position();
    SensorControl();
    //maxVal();

    LeftDrive.spin(forward, driveY + driveX, pct);
    RightDrive.spin(forward, driveY - driveX, pct);

    chainControl();
    if(Controller1.ButtonA.pressing() or Controller1.ButtonB.pressing())
    {
      if(Controller1.Axis1.position() < 5 && Controller1.Axis1.position() >-5 && Controller1.Axis3.position() < 5 && Controller1.Axis3.position() >-5)
      {
        //Wheels lock
        
      }
    }
/*
    if(Controller1.ButtonRight.pressing())
    {
      while(!Controller1.ButtonLeft.pressing())
      {
        Vision6.takeSnapshot(Vision6__B_BALL);

        driveX = Controller1.Axis1.position();
        driveY = Controller1.Axis3.position();

        SensorControl();

        maxVal();
        LeftDrive.spin(forward, driveY + driveX, pct);
        RightDrive.spin(forward, driveY - driveX, pct);

        chainControl();
      }
    }
    else if(Controller1.ButtonLeft.pressing())
    {
      while(!Controller1.ButtonRight.pressing())
      {
      driveX = Controller1.Axis1.position();
      driveY = Controller1.Axis3.position();

      maxVal();
      LeftDrive.spin(forward, driveY + driveX, pct);
      RightDrive.spin(forward, driveY - driveX, pct);
      }
    }
    */
  }
}

// Main Function:
int main() 
{
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
}
