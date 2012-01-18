This project is used for controlling the 2012 robot for The Northern Force.

 ------ Code Conventions ------

Variable Prefixes:
-----------------
	:example - "p_mySubsystem" would be a subsystem.
"p_" - indicates a robot subsystem
"c_" - indicates a command
"o_" - indicates an operator interface element
"k_" - indicates a constant value (defined in Robotmap.h with a #define command)
"l_" - indicates a local variable that would be instantiated within a class or method

Following these prefixes in your code will help to make this years code
much more readable by everyone else, not just yourself. Please 
stick to these prefixes when creating classes and objects! If your variables
do not have a prefix, they will have one added!

If there are any prefixes that you wish to add, please ask Arthur, Jay, Steve,
or one of the other mentors.

Commenting:
-----------------
Please make sure to comment the beginning of all of your methods that you might
create. Provide the author of the subclass, what the class does, what
it takes as parameters, and what the class returns.

Example:
/**
 * @brief This class does a, b, and c.
 *
 * @param x An int of some amount.
 * @param y A string of some value.
 * @param z A bool of some value.
 *
 * @return A boolean of fail or pass.
 *
 * @author John Smith
**/

Naming:
-----------------
All classes should be named with capital letters, in camel case.

Example: 
	class ExampleClass
	class ExampleClassExtensionThree
	
All methods should be named along the same parameters.

Example:
	void ExampleClass::ExampleMethod
	void ExampleClass::ExampleMethodNumberFour
	
Intentation:
-----------------
Please make sure that your code is properly indented. This makes it much easier
for everyone to read and make sense of.

Braces:
-----------------
Braces should be separated from the line that their method is on. It makes the
code much easier to read, especially with more complex class definitions.

Example:
void MyClass::MyMethod() 
{
	// Commands Here.
}

CommandBasedRobot(void):
	o_driveStick (1, 6, 10),
	o_driverStation (*DriverStation::GetInstance())
{
	CommandBase::init();
}


-----------------
If we all follow these code conventions this year, everyone will have a much 
easier time programming, and we can all work much more efficiently!