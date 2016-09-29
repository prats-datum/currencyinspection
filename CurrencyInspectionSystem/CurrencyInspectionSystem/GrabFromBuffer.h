#pragma once
#include "ImageGrabber.h"
class GrabFromBuffer :
	public ImageGrabber
{
	DECLARE_DYNCREATE(GrabFromBuffer)
private:
	int cameraID;
	std::list<HImage> imgBuffer;

public:
	GrabFromBuffer();
	~GrabFromBuffer();

#pragma region inline functions
	virtual bool SetImageSource(UINT _cameraID, std::list<HImage> _buffer);
	virtual bool RestartGrab();
	virtual BOOL InitInstance();
	virtual int Run();
#pragma endregion
};

