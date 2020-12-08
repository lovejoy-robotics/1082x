using namespace vex;

extern brain Brain;

// VEXcode devices
extern optical O1;
extern drivetrain Drivetrain;
extern motor F1;
extern motor F2;
extern motor M1;
extern motor B1;
extern controller Controller1;
extern optical Op1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );