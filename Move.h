
#include <vex.h>

struct Move
{
  static void moveMM(int distance, vex::motor leftDrive, vex::motor rightDrive);
  static void moveDeg(int deg, vex::motor leftDrive, vex::motor rightDrive);
};