
#include <vex.h>

struct Move
{
  static void moveMM(int distance, vex::motor leftDrive1, vex::motor leftDrive2, vex::motor rightDrive1, vex::motor rightDrive2);
  static void moveDeg(int deg, vex::motor leftDrive1, vex::motor leftDrive2, vex::motor rightDrive1, vex::motor rightDrive2);
};