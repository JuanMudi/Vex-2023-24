#include "vex.h"

using namespace vex;


/*
|0o|«l1     r1»|o0|     
| o|           |o |
| o|«l2     r2»|o |
| o|           |o |
| o|«l3     r3»|o | 
| o|           |o |
|0o|«l4     r4»|o0|
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
*/

// A global instance of brain used for printing to the V5 brain screen
brain Brain;


/*
Estructura definicion de motores
motor(PUERTO, REVERSA)
Si la flecha en el cuerpo del robot va en el sentido del movimiento del robot, REVERSA = false, si va contrario al movimiento REVERSA = true
*/
motor motor_l1 = motor(PORT2, false);
motor motor_l2 = motor(PORT3,false);
motor motor_l3 = motor(PORT4,false);
motor motor_l4 = motor(PORT6,false);
motor motor_r1 = motor(PORT7,true);
motor motor_r2 = motor(PORT8,true);
motor motor_r3 = motor(PORT9,true);
motor motor_r4 = motor(PORT10,true);

/*
Global Instance of the motors groups(Left and Right)
*/
motor_group m_group_left = motor_group(motor_l1, motor_l2, motor_l3, motor_l4);
motor_group m_group_right = motor_group(motor_r1, motor_r2, motor_r3, motor_r4);

drivetrain base = drivetrain(m_group_left, m_group_right, 319.1764, 292.1, 130, distanceUnits::mm, 1.0);
controller control = controller(primary);
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
int base_control(){
  while(true){
     base.arcade(control.Axis3.position(), control.Axis1.position());
  }
}

void vexcodeInit(void) {
  task base(base_control); 
}