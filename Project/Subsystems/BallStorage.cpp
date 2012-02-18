#include "BallStorage.h"
#include "../Robotmap.h"
#include "../CommandBase.h"
#include "../Commands/BallController.h"

/**
 * @brief The constructor for the Ball Storage system.
 */
BallStorage::BallStorage() try :
    Subsystem("BallStorage"),
    m_storageMotor((printf("Initializing pickup motor jaguar. \n"), k_storageMotorJaguar)),
    m_ballCount(0)
{
	m_storageMotor.ChangeControlMode(CANJaguar::kPosition);
	m_storageMotor.ConfigMaxOutputVoltage(k_storageMaxOutputVoltage);
	m_storageMotor.EnableControl();
    //!TODO: Ramp this jaguar

	printf("Pickup motor jaguar successfully created. \n");
} catch (exception e)
{
    printf("Error creating pickup motor jaguar");
    printf(e.what());
}
   
/**
 * @brief Sets up the default command for the robot.
 */
void BallStorage::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
    SetDefaultCommand(new BallController());
}

/**
 * @brief Gets the number of balls currently in the
 * robot.
 * 
 * @return An int, the number of balls.
 */
int BallStorage::CountBalls()
{
    return m_ballCount;
}

void BallStorage::GetBallFromPickup()
{
    CommandBase::s_ballPickup->AdvanceBall();
}

/**
 * @brief Stops the storage mechanism from moving.
 * Used to stop ball flow once a ball is collected.
 */
void BallStorage::Stop()
{
	m_storageMotor.Set(0.0);
}

/**
 * @brief Enables the jaguar if it has been disabled.
 */
void BallStorage::Enable()
{
    m_storageMotor.EnableControl();
}

/**
 * @brief Disables jaguar control in this subsystem
 */
void BallStorage::Disable()
{
    m_storageMotor.DisableControl();
}

/**
 * @brief Advances balls in the storage mechanism
 * the number of times specified.
 *
 * @param times The number of times that the balls should be advanced.
 */
void BallStorage::AdvanceBall(int times)
{
	m_storageMotor.Set(0.0);
}

/**
 * @brief Clears all the balls out of the storage mechanism.
 */
void BallStorage::Clear()
{
	
}
