#include "main.h"

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
	std::shared_ptr<OdomChassisController> drive =
		ChassisControllerBuilder()
				.withMotors(
						-11,  // Top left
						20, // Top right (reversed)
						19, // Bottom right (reversed)
						-12   // Bottom left
				)
				/*.withGains(
					{0.054, 0.043, 0.42}, // Distance controller gains
					{0.001, 0, 0.0001}, // Turn controller gains
					{0.001, 0, 0.0001}  // Angle controller gains (helps drive straight)
			)*/
			//Tune here
			//double kP = 0.054;
			//double kI = 0.043;
			//double kD = 0.42;
				// Green gearset, 3.5 inch wheel diameter, 10 inch wheelbase
			.withDimensions(AbstractMotor::gearset::green,  {{3.25_in, 12.5_in}, imev5GreenTPR * (3.0/5.0)})
			.withOdometry()
			.buildOdometry();

			drive->setMaxVelocity(30);
			drive->setState({0_in, 0_in, 0_deg});
			drive->driveToPoint({2_ft, 0_ft});

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
		Controller controller;
		ADIButton rollerLimitSwitch('D');
		//Motor rightLift(3);
		Motor fork (4);
		//Motor leftLift(8);
		//const int LEFT_LIFT_MOTOR_PORT = 8;
		//const int RIGHT_LIFT_MOTOR_PORT = 3;
		//MotorGroup group1({8, -3});
		Motor rightLift (-3);
		ControllerButton armUpButton(ControllerDigital::L1);
		ControllerButton armDownButton(ControllerDigital::L2);
		ControllerButton forkUpButton(ControllerDigital::R1);
		ControllerButton forkDownButton(ControllerDigital::R2);

		std::shared_ptr<ChassisController> drive =
			ChassisControllerBuilder()
					.withMotors(
							{20,
							9},
							{-11,
							-1}
					)
					//.withGains(
					//	{0.001, 0, 0.0001}, // Distance controller gains
					//	{0.001, 0, 0.0001}, // Turn controller gains
					//	{0.001, 0, 0.0001}  // Angle controller gains (helps drive straight)
					//)
					//Tune here
					//double kP = 0.054;
					//double kI = 0.043;
					//double kD = 0.42;
					// Green gearset, 3.25 inch wheel diameter, 10 inch wheelbase
					.withDimensions(AbstractMotor::gearset::green, {{4_in, 18_in}, imev5GreenTPR})

				.build();

				//std::shared_ptr<AsyncPositionController<double, double>> liftControl =
  			//AsyncPosControllerBuilder().withMotor(group1).build();

				std::shared_ptr<AsyncPositionController<double, double>> forkControl =
  			AsyncPosControllerBuilder().withMotor(fork).build();

				//liftControl->setMaxVelocity(100);
				forkControl->setMaxVelocity(100);


				rightLift.setBrakeMode(AbstractMotor::brakeMode::hold);


				//auto driveModel = std::dynamic_pointer_cast<TankDriveModel>(drive->getModel());

				while(true){
					//XDrive go here
				/*	xModel->xArcade(controller.getAnalog(ControllerAnalog::leftX),
                        controller.getAnalog(ControllerAnalog::leftY),
												controller.getAnalog(ControllerAnalog::rightX));*/
												drive->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY),
                            controller.getAnalog(ControllerAnalog::leftX));


							rightLift.moveVelocity(controller.getAnalog(ControllerAnalog::rightY)*-100);


				/*	if (armUpButton.changedToPressed()) {
      liftControl->setTarget(-2600);
    } else if (armDownButton.changedToPressed()) {
      liftControl->setTarget(2);
    }*/

				if(forkDownButton.changedToPressed()){
					forkControl->setTarget(-1000);
				}
				else if(forkUpButton.changedToPressed()){
					forkControl->setTarget(2);
				}








				pros::delay(50);



			}




}
