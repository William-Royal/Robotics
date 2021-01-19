
#include "Move.h"

#include "MoveThread.h"

void Move::moveMM(int mm, vex::motor leftDrive1, vex::motor leftDrive2, vex::motor rightDrive1, vex::motor rightDrive2)
{
  MoveThread threadL1(leftDrive1, (int)(mm * 1.13));
  MoveThread threadL2(leftDrive2, (int)(mm * 1.13));
  MoveThread threadR1(rightDrive1, (int)(mm * 1.13));
  MoveThread threadR2(rightDrive2, (int)(mm * 1.13));
  threadL1.start();
  threadL2.start();
  threadR1.start();
  threadR2.start();

  while (!threadL1.done() || !threadR1.done())
  {
    threadL1.update();
	  threadL2.update();
    threadR1.update();
	  threadR2.update();
    wait(15, vex::msec);
  }
}

void Move::moveDeg(int deg, vex::motor leftDrive1, vex::motor leftDrive2, vex::motor rightDrive1, vex::motor rightDrive2)
{
  MoveThread threadL1(leftDrive1, (int)(deg * 3.6));
  MoveThread threadL2(leftDrive2, (int)(deg * 3.6));
  MoveThread threadR1(rightDrive1, -(int)(deg * 3.6));
  MoveThread threadR2(rightDrive2, -(int)(deg * 3.6));
  threadL1.start();
  threadL2.start();
  threadR1.start();
  threadR2.start();

  while (!threadL1.done() || !threadR1.done())
  {
    threadL1.update();
	  threadL2.update();
    threadR1.update();
	  threadR2.update();
    wait(15, vex::msec);
  }
}