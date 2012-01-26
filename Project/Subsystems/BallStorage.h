#ifndef BALLSTORAGE_H
#define BALLSTORAGE_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 * @brief This class contains all the methods
 * for interacting with the ball storage 
 * mechanism on the robot. At this point, it 
 * may not be necessary to have this class,
 * as the configuration for the ball handling
 * has not been decided.
 *
 * @author Arthur Lockman
 */
class BallStorage: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	BallStorage();
	int CountBalls();
	void Stop();
	void AdvanceBall(int position);
	void Clear();
	void InitDefaultCommand();
};

#endif
