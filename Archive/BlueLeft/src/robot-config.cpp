#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LeftDrive = motor(PORT1, ratio18_1, false);
motor RightDrive = motor(PORT10, ratio18_1, true);
motor RightIntake = motor(PORT8, ratio18_1, true);
motor LeftIntake = motor(PORT2, ratio18_1, false);
motor RightLift = motor(PORT9, ratio18_1, true);
motor LeftLift = motor(PORT3, ratio18_1, false);
/*vex-vision-config:begin*/
signature Vision6__B_BALL = signature (1, -1947, -1057, -1502, 7537, 9709, 8623, 4, 0);
signature Vision6__R_BALL = signature (2, 2729, 8973, 5852, -463, 337, -62, 1.6, 0);
vision Vision6 = vision (PORT6, 50, Vision6__B_BALL, Vision6__R_BALL);
/*vex-vision-config:end*/
motor BarMotor = motor(PORT4, ratio18_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}