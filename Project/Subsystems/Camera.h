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
	~Camera();

	void InitDefaultCommand();
	void Search();
	float GetDistanceToTarget();
	float GetAngleToTarget();
	void SaveImageToFTP();
	bool HasTarget() const;

	//! Sets the directory within which to save the images
	void SetDirectory (const char* directory, unsigned nextImage = 1);

	//! Captures the next n images
	void CaptureImages (unsigned count);

private:
	//! Main image processing function
	void ProcessImages();

	//! Static function called to run the image processing task
	static void ImageProcessingTask(Camera& camera);

	//! Saves the image
	void SaveImage(ImageBase& image, const char* name);

	//! The axis camera instance
	AxisCamera& m_cam;

	//! The current camera image
	HSLImage m_image;

	//! The task object used to process camera images
	Task m_imageProcessingTask;

	//! A semaphore to provide mutual exclusion to the camera data members
	const SEM_ID m_cameraSemaphore;

	//! The visible particles, protected by m_particleSemaphore
	vector<ParticleAnalysisReport> m_particles;

	//! The directory the images are stored in
	char m_directory[32];

	//! The unique image number used to generate the image file name
	unsigned m_imageNo;

	//! The last image number to capture
	unsigned m_lastImageNo;

	//! Controls the saving of the source images
	bool m_saveSourceImage;

	//! Controls the saving of the processed images
	bool m_saveProcessedImages;
};

#endif
