#include "main.h"
#define DIGITAL_SENSOR_PORT 'A'
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	printf("hello");
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User test!");

	pros::lcd::register_btn1_cb(on_center_button);

	pros::ADIDigitalOut clamp (DIGITAL_SENSOR_PORT);

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	//Motor fork (9);
	//Motor rightLift (-3);

std::shared_ptr<AsyncPositionController<double, double>> rightLift =
  AsyncPosControllerBuilder()
    .withMotor(3) // lift motor port 3
    .build();
		std::shared_ptr<AsyncPositionController<double, double>> leftLift =
		  AsyncPosControllerBuilder()
		    .withMotor(-8) // lift motor port 3
		    .build();
	std::shared_ptr<AsyncPositionController<double, double>> fork =
		AsyncPosControllerBuilder()
	    .withMotor(8)
	    .build();
	Motor intake(12);
		Motor arm(20);
	std::shared_ptr<ChassisController> drive =
		ChassisControllerBuilder()
				.withMotors(
					{2,
					10},
					{-6,
					-7}

				)
				/*.withGains(
        {0.001, 0, 0.00004}, // Distance controller gains
        {0.002, 0, 0.00008}, // Turn controller gains
        {0.001, 0, 0.00004}  // Angle controller gains (helps drive straight)
    )*/
				// Green gearset, 3.5 inch wheel diameter, 10 inch wheelbase
			.withDimensions(AbstractMotor::gearset::green,  {{4_in, 17.5_in}, imev5GreenTPR})
			.build();

			pros::ADIDigitalOut clamp(DIGITAL_SENSOR_PORT);

			//skills with odom





			/*clamp.set_value(true);
			pros::delay(1000);
			clamp.set_value(false);*/



 //skills
 			/*rightLift->setTarget(0);
			leftLift->setTarget(0);
			drive->setMaxVelocity(60);
			drive->moveDistance(2_ft);
			clamp.set_value(true);
			rightLift->setTarget(2200);
			leftLift->setTarget(2200);
			drive->moveDistance(0.2_ft);
			drive->turnAngle(-90_deg);
			drive->moveDistance(-0.5_ft);
			drive->moveDistance(0.5_ft);
			drive->setMaxVelocity(80);
			drive->moveDistance(2_ft);
			drive->setMaxVelocity(60);
			drive->turnAngle(88_deg);
			drive->moveDistance(5_ft);
			drive->moveDistance(-0.6_ft);
			drive->turnAngle(-85_deg);
			drive->moveDistance(-1.74_ft);
			drive->moveDistance(6.75_ft);
			drive->moveDistance(-1.8_ft);
			drive->turnAngle(70_deg);
			drive->moveDistance(-4_ft);
			drive->moveDistance(5.8_ft);
			//drive->moveDistance(2.85_ft);
			rightLift->setTarget(1450);
			leftLift->setTarget(1450);
			rightLift->waitUntilSettled();
			clamp.set_value(false);
			rightLift->setTarget(2200);
			leftLift->setTarget(2200);
			drive->moveDistance(-0.4_ft);
			drive->turnAngle(-86_deg);
			drive->moveDistance(4_ft);*/

			//Actual skills
			rightLift->setTarget(0);
			leftLift->setTarget(0);
			drive->setMaxVelocity(100);
			drive->moveDistance(7_ft);
			clamp.set_value(false);
			drive->moveDistance(-1_ft);
			drive->setMaxVelocity(85);
			drive->turnAngle(-65_deg);
			drive->setMaxVelocity(100);
			drive->moveDistance(1.4_ft);
			drive->setMaxVelocity(85);
			drive->turnAngle(-78_deg);
			drive->setMaxVelocity(100);
			drive->moveDistance(3.5_ft);
			drive->setMaxVelocity(85);
			drive->turnAngle(72_deg);
			drive->setMaxVelocity(100);
			drive->moveDistance(2_ft);
			drive->setMaxVelocity(85);
			drive->turnAngle(61_deg);
			drive->setMaxVelocity(100);
			drive->moveDistance(2.5_ft);
			drive->moveDistance(-0.5_ft);
			drive->setMaxVelocity(85);
			drive->turnAngle(-50_deg);
			drive->setMaxVelocity(100);
			drive->moveDistance(3.2_ft);
			drive->setMaxVelocity(85);
			drive->turnAngle(-95_deg);
			drive->setMaxVelocity(100);
			drive->moveDistance(-4.2_ft);
			rightLift->setTarget(0);
			leftLift->setTarget(0);
			drive->moveDistance(2.5_ft);
			drive->setMaxVelocity(85);
			drive->turnAngle(77_deg);
			drive->setMaxVelocity(100);
			drive->moveDistance(2_ft);
			clamp.set_value(true);
			rightLift->setTarget(400);
			leftLift->setTarget(400);
			rightLift->waitUntilSettled();
			drive->moveDistance(-2.5_ft);
			rightLift->setTarget(2200);
			leftLift->setTarget(2200);
			rightLift->waitUntilSettled();
			drive->moveDistance(0.8_ft);
			drive->setMaxVelocity(85);
			drive->turnAngle(-75_deg);
			drive->setMaxVelocity(100);
			drive->moveDistance(4_ft);
			drive->moveDistance(-1_ft);
			drive->setMaxVelocity(85);
			drive->turnAngle(-73_deg);
			drive->setMaxVelocity(100);
			drive->moveDistance(3_ft);
			drive->setMaxVelocity(85);
			drive->turnAngle(67_deg);
			drive->setMaxVelocity(100);
			drive->moveDistance(3.4_ft);
			rightLift->setTarget(1450);
			leftLift->setTarget(1450);
			rightLift->waitUntilSettled();
			clamp.set_value(false);
			rightLift->setTarget(2200);
			leftLift->setTarget(2200);
			drive->setMaxVelocity(150);
			drive->moveDistance(-0.4_ft);
			drive->moveDistance(-2_ft);
			drive->turnAngle(60_deg);
			rightLift->setTarget(80);
			leftLift->setTarget(80);
			drive->moveDistance(3_ft);
			drive->turnAngle(-65_deg);
			drive->setMaxVelocity(200);
			drive->moveDistance(2.5_ft);
			clamp.set_value(true);
			drive->moveDistance(-6_ft);

			//Skills with pid
			/*drive->setMaxVelocity(180);
			rightLift->setTarget(100);
				leftLift->setTarget(100);
				drive->moveDistance(8_ft);
				drive->moveDistance(-1_ft);
				drive->turnAngle(-85_deg);
				drive->moveDistance(2.4_ft);
				drive->turnAngle(-85_deg);
				drive->moveDistance(3.5_ft);
				drive->turnAngle(90_deg);
				drive->moveDistance(2.8_ft);
				drive->turnAngle(100_deg);
				drive->moveDistance(2.5_ft);
				drive->moveDistance(-0.5_ft);
				drive->turnAngle(-45_deg);
				drive->moveDistance(3.9_ft);
				drive->turnAngle(-110_deg);
				drive->moveDistance(-4_ft);
				drive->setMaxVelocity(140);
				rightLift->setTarget(0);
				leftLift->setTarget(0);
				drive->moveDistance(2.5_ft);
				drive->turnAngle(92_deg);
				drive->moveDistance(1.5_ft);
				clamp.set_value(true);
				rightLift->setTarget(400);
				leftLift->setTarget(400);
				rightLift->waitUntilSettled();
				drive->moveDistance(-2.5_ft);
				rightLift->setTarget(2200);
				leftLift->setTarget(2200);
				rightLift->waitUntilSettled();
				drive->moveDistance(0.8_ft);
				drive->turnAngle(-90_deg);
				drive->moveDistance(6_ft);
				drive->moveDistance(-1_ft);
				drive->turnAngle(-90_deg);
				drive->moveDistance(3_ft);
				drive->turnAngle(90_deg);
				drive->moveDistance(1_ft);
				rightLift->setTarget(1450);
				leftLift->setTarget(1450);
				rightLift->waitUntilSettled();
				clamp.set_value(false);
				rightLift->setTarget(2200);
				leftLift->setTarget(2200);
				drive->moveDistance(-0.4_ft);*/

				/*drive->setMaxVelocity(140);
				clamp.set_value(false);
				drive->moveDistance(5_ft);
				drive->turnAngle(-90_deg);
				drive->moveDistance(2_ft);
				drive->turnAngle(-90_deg);
				drive->moveDistance(2_ft);*/




}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
		static bool buttonPressed = false;
		bool hasRisenOnce = false;
		Controller controller;
		ADIButton rollerLimitSwitch('D');
		//Motor rightLift(3);
		Motor leftLift(8);
		//Motor leftLift(8);
		//const int LEFT_LIFT_MOTOR_PORT = 8;
		//const int RIGHT_LIFT_MOTOR_PORT = 3;
		//MotorGroup group1({8, -3});
		Motor rightLift (3);
		Motor intake(12);
		Motor arm(20);
		ControllerButton armUpButton(ControllerDigital::L1);
		ControllerButton armDownButton(ControllerDigital::L2);
		ControllerButton intakeButton(ControllerDigital::A);
		ControllerButton pneumaticsTrue(ControllerDigital::R2);
		ControllerButton pneumaticsFalse(ControllerDigital::R1);
		ControllerButton hardStop(ControllerDigital::B);
		pros::ADIDigitalOut clamp(DIGITAL_SENSOR_PORT);
		clamp.set_value(false);

		std::shared_ptr<ChassisController> drive =
			ChassisControllerBuilder()
					.withMotors(
							{2,
							10},
							{-6,
							-7}
					)
					// Green gearset, 3.25 inch wheel diameter, 10 inch wheelbase
					.withDimensions(AbstractMotor::gearset::green, {{4_in, 17.5_in}, imev5GreenTPR})

				.build();

				//std::shared_ptr<AsyncPositionController<double, double>> liftControl =
  			//AsyncPosControllerBuilder().withMotor(group1).build();

				//std::shared_ptr<AsyncPositionController<double, double>> forkControl =
  			//AsyncPosControllerBuilder().withMotor(fork).build();

				//liftControl->setMaxVelocity(100);
				//forkControl->setMaxVelocity(100);




				rightLift.setBrakeMode(AbstractMotor::brakeMode::hold);
				leftLift.setBrakeMode(AbstractMotor::brakeMode::hold);
				arm.setBrakeMode(AbstractMotor::brakeMode::hold);


				//auto driveModel = std::dynamic_pointer_cast<TankDriveModel>(drive->getModel());

				while(true){
					//XDrive go here
				/*	xModel->xArcade(controller.getAnalog(ControllerAnalog::leftX),
                        controller.getAnalog(ControllerAnalog::leftY),
												controller.getAnalog(ControllerAnalog::rightX));*/
												if(rightLift.getPosition() > 20){
													hasRisenOnce = true;
												}

												drive->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY),
                            controller.getAnalog(ControllerAnalog::leftX));


							if(!buttonPressed && hasRisenOnce && rightLift.getPosition() < 120 && controller.getAnalog(ControllerAnalog::rightY) < 0){
								rightLift.moveVelocity(0);
								leftLift.moveVelocity(0);
							}
							else if(!buttonPressed && hasRisenOnce && rightLift.getPosition() > 2000 && controller.getAnalog(ControllerAnalog::rightY) > 0){
								rightLift.moveVelocity(0);
								leftLift.moveVelocity(0);
							}
							else{
							rightLift.moveVelocity(controller.getAnalog(ControllerAnalog::rightY)*650);
							leftLift.moveVelocity(controller.getAnalog(ControllerAnalog::rightY)*-650);
						}

						if(hardStop.isPressed()){
							buttonPressed = true;
						}


				/*	if (armUpButton.changedToPressed()) {
      liftControl->setTarget(-2600);
    } else if (armDownButton.changedToPressed()) {
      liftControl->setTarget(2);
    }*/

				if(intakeButton.isPressed()){
					intake.moveVelocity(-100);
				}
				else{
					intake.moveVelocity(0);
				}

				if(armDownButton.isPressed()){
					arm.moveVelocity(-100);
				}
				else if(armUpButton.isPressed()){
					arm.moveVelocity(100);
				}
				else{
					arm.moveVelocity(0);
				}

				if(pneumaticsTrue.isPressed()){
					clamp.set_value(true);
				}
				else if(pneumaticsFalse.isPressed()){
					clamp.set_value(false);
				}








				pros::delay(50);



			}




}
