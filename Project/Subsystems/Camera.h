#ifndef CAMERA_H
#define CAMERA_H
#include <WPILib.h>

/**
 * @brief Controls the camera and does the tracking
 * and vision analysis.
 *
 * @author Arthur Lockman
 */
class Camera: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	void InitCamera();
public:
	Camera();
	void InitDefaultCommand();
	void Search();
	float GetDistanceToTarget();
	float GetAngleToTarget();
	void SaveImageToFTP();
	
private:
	//! Main image processing function
	void ProcessImages();

	//! Static function called to run the image processing task
	static void ImageProcessingTask(Camera& camera);

	//! The axis camera instance
	AxisCamera& m_cam;

	//! The current camera image
	HSLImage m_image;
	
	//! The task object used to process camera images
	Task m_imageProcessingTask;
};

#endif
