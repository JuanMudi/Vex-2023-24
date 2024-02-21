/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
/*
|0o|«l1     r1»|o0|
| o|           |o |
| o|           |o |
| o|           |o |
| o|           |o |
| o|«l3     r3»|o |
|0o|«l4     r4»|o0|
¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
*/

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

/*
Estructura definicion de motores
motor(PUERTO, REVERSA)
Si la flecha en el cuerpo del robot va en el sentido del movimiento del robot,
REVERSA = false, si va contrario al movimiento REVERSA = true
*/                                                                                                                                                                                                                          
motor motor_l1 = motor(PORT18, ratio18_1, false);
motor motor_l2 = motor(PORT9, ratio18_1, true);
motor motor_l3 = motor(PORT20, ratio18_1, false);

motor motor_r1 = motor(PORT13, ratio18_1, true);
motor motor_r2 = motor(PORT14, ratio18_1, false);
motor motor_r3 = motor(PORT2, ratio18_1, true);

motor garra = motor(PORT16, ratio36_1, false);

motor lateral_f = motor(PORT6, ratio18_1, false);
motor lateral_b = motor(PORT1, ratio18_1, true);

motor lanzador_l = motor(PORT8, ratio36_1, false);
motor lanzador_r = motor(PORT3, ratio36_1, true);

motor recogedor_l = motor(PORT12, ratio36_1, true);
motor recogedor_r = motor(PORT19, ratio36_1, false);

digital_out piston_r = digital_out(Brain.ThreeWirePort.A);
digital_out piston_l = digital_out(Brain.ThreeWirePort.B);

/*
Global Instance of the motors groups(Left and Right)
*/
motor_group m_group_left = motor_group(motor_l1, motor_l2, motor_l3);
motor_group m_group_right = motor_group(motor_r1, motor_r2, motor_r3);
motor_group lateral = motor_group(lateral_f, lateral_b);
motor_group lanzador = motor_group(lanzador_l, lanzador_r);
motor_group recogedor = motor_group(recogedor_l, recogedor_r);

drivetrain base = drivetrain(m_group_left, m_group_right, 260, 900, 130,
                             distanceUnits::mm, 1.0);

controller control = controller(primary);

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();


  base.setDriveVelocity(100, pct);

  garra.setVelocity(100, pct);

  lateral_f.setVelocity(100, pct);
  lateral_b.setVelocity(100, pct);

  lanzador_l.setVelocity(100, pct);
  lanzador_r.setVelocity(100, pct);


  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
 
 base.drive(reverse);
 wait(1300,msec);
 base.turn(right);
 wait(900,msec);
 piston_r.set(true);
 base.drive(reverse);
 wait(1400,msec);
 base.stop();
 wait(20,msec);

 base.turn(left);
 wait(800,msec);
 
 piston_r.set(false);
 base.drive(forward);
 wait(1600,msec);
 base.stop();
 lateral.spin(forward);
 wait(500, msec);
 lateral.stop();

 base.drive(reverse);
 wait(100,msec);
 base.stop();


 recogedor.spin(reverse);
 wait(1000,msec);
 recogedor.stop();



}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {

    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    base.arcade(control.Axis3.position(), control.Axis1.position());

    // Garra
    if (control.ButtonR1.pressing()) {
      garra.spin(forward);
    } else {
      if (control.ButtonL1.pressing()) {
        garra.spin(reverse);
      } else {
        garra.setBrake(hold);
        garra.stop();
      }
    }

    // Movimiento Lateral
    if (control.ButtonR2.pressing()) {
      lateral.spin(reverse);
    } else {
      if (control.ButtonL2.pressing()) {
        lateral.spin(forward);
      } else {
        lateral.stop();
      }
    }

    // Catapulta
    if (control.ButtonUp.pressing()) {
      lanzador.spin(forward);
    } else {
      if (control.ButtonDown.pressing()) {
        lanzador.spin(reverse);
      } else {
        lanzador.setStopping(hold);
        lanzador.stop();
      }
    }

    // Subir Garra
    if (control.ButtonX.pressing()) {
      recogedor.spin(forward);
    } else {
      if (control.ButtonB.pressing()) {
        recogedor.spin(reverse);
      } else {
        recogedor.setStopping(hold);
        recogedor.stop();
      }
    }

    // Pistones
    if (control.ButtonLeft.pressing()) {
      piston_l.set(true);
    }

    if (control.ButtonY.pressing()) {
      piston_l.set(false);
    }

    if (control.ButtonRight.pressing()) {
      piston_r.set(true);
    }
    if (control.ButtonA.pressing()) {
      piston_r.set(false);
    }

  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
