#ifndef CAPTUREIMAGES_H
#define CAPTUREIMAGES_H

#include "../CommandBase.h"

/**
 *
 *
 * @author Joseph Martin
 */
class CaptureImages: public CommandBase {
public:
	CaptureImages();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
