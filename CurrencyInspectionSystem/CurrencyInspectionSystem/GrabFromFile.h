#pragma once
#include "ImageGrabber.h"
class GrabFromFile :
	public ImageGrabber
{
	DECLARE_DYNCREATE(GrabFromFile)
public:
	GrabFromFile();
	~GrabFromFile();
	std::vector<ImageData> images;
#pragma region inline functions
	virtual bool SetImageSource(UINT _cameraID, string _configFileLocation);
	virtual bool RestartGrab();
	virtual BOOL InitInstance();
	virtual int Run();
#pragma endregion
};

