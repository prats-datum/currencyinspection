#pragma once
#include "ImageGrabber.h"
#include "SiSoImageAcquisition.h"

class GrabFromCamera :
	public ImageGrabber
{
	DECLARE_DYNCREATE(GrabFromCamera)
	SiSoImageAcquisition sisoImgAcquisition;
	FILE* fp;
	void LogIAEvents(std::string iaLog);
	std::list<std::string> imagesLog;
public:
	GrabFromCamera();
	~GrabFromCamera();
#pragma region inline functions
	virtual bool SetImageSource(UINT _cameraID, string _configFileLocation);
	virtual bool RestartGrab();
	virtual BOOL InitInstance();
	virtual int Run();
#pragma endregion
};

