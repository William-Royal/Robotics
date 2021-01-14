
#include "Move.h"

#include "MoveThread.h"

void Move::moveMM(int mm, vex::motor leftDrive, vex::motor rightDrive)
{
  MoveThread threadL(leftDrive, (int)(mm * 1.13));
  MoveThread threadR(rightDrive, (int)(mm * 1.13));
  threadL.start();
  threadR.start();

  while (!threadL.done() || !threadR.done())
  {
    threadL.update();
    threadR.update();
    wait(15, vex::msec);
  }
}

void Move::moveDeg(int deg, vex::motor leftDrive, vex::motor rightDrive)
{
  MoveThread threadL(leftDrive, (int)(deg * 3.6));
  MoveThread threadR(rightDrive, -(int)(deg * 3.6));
  threadL.start();
  threadR.start();

  while (!threadL.done() || !threadR.done())
  {
    threadL.update();
    threadR.update();
    wait(15, vex::msec);
  }
}