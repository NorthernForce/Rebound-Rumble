#include "LogAccelerometer.h"
#include <fstream>

LogAccelerometer::LogAccelerometer(): CommandBase("LogAcclerometer") {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(s_accelerometer);
	m_logNumber = 1;
}

// Called just before this Command runs the first time
void LogAccelerometer::Initialize() {
	SetTimeout(5.0); // Time to log Gyro data for
	s_accelerometer->EnableLogging(500); // <-- size of log?
	finished = false;
	char* filename;
	sprintf(filename, "AccelerometerLog_%d", m_logNumber);
	m_file.open(filename, fstream::in | fstream::out);
}

// Called repeatedly when this Command is scheduled to run
void LogAccelerometer::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool LogAccelerometer::IsFinished() {
	return IsTimedOut();
}

// Called once after isFinished returns true
void LogAccelerometer::End() {
	s_accelerometer->DisableLogging();
	s_accelerometer->WriteLog(m_file);
	m_file.close();
	m_logNumber += 1;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LogAccelerometer::Interrupted() {
	printf("Accelerometer Logging has been interrupted.\nWriting log file early.\n");
	End();
}
