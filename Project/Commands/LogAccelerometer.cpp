#include "LogAccelerometer.h"
//#include <fstream>

IMAQ_FUNC int Priv_SetWriteFileAllowed(UINT32 enable);

LogAccelerometer::LogAccelerometer(): CommandBase("LogAcclerometer") {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	//Requires(s_accelerometer);
	printf("Initializing LogAccelerometer command\n\r");
	m_logNumber = 1;
}

// Called just before this Command runs the first time
void LogAccelerometer::Initialize() {
	SetTimeout(5.0);
	printf("Enabling Logging\n\r");
	char* filename = new char[120];
	sprintf(filename, "/tmp/AccelerometerLog_%d.csv", m_logNumber);
	Priv_SetWriteFileAllowed(1);
	m_file.open(filename, fstream::out);
	if(!m_file.is_open()){printf("file failed to open\n\r");}
	s_accelerometer->EnableLogging();
	printf("Opened File %s\n\r", filename);
}

// Called repeatedly when this Command is scheduled to run
void LogAccelerometer::Execute() {
	s_accelerometer->Update((int)(1000*TimeSinceInitialized()));
}

// Make this return true when this Command no longer needs to run execute()
bool LogAccelerometer::IsFinished() {
	return IsTimedOut();
}

// Called once after isFinished returns true
void LogAccelerometer::End() {
	s_accelerometer->DisableLogging();
	s_accelerometer->WriteLog(m_file);
	printf("Written Log file\n\r");
	m_file.close();
	printf("Closed file");
	m_logNumber += 1;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LogAccelerometer::Interrupted() {
	printf("Accelerometer Logging has been interrupted.\nWriting log file early.\n");
	End();
}
