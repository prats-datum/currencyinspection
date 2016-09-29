#pragma once
#include "afxwin.h"
#include "ImageGrabber.h"
#include "GPUProvider.h"
#include "GPUProviderSingleton.h"

class iPreprocessedImageReceiver
{
public:
	virtual void OnPreprocessedImageReceived(PreprocessedImageData &imageData)
	{}
};


class ImagePreprocessor :
	public CWinThread, public iImageReceiver, public GPUProvider
{
	DECLARE_DYNCREATE(ImagePreprocessor)

private:
	std::list<std::string> resultsLog;
	std::vector<GPUProvider> *gpuList;
public:
	ImagePreprocessor();
	~ImagePreprocessor();
	// to set processing stop event
	void SetStopEvent(HANDLE &_inspectionStopEvent, HANDLE &_inspectionExitEvent);
	int							cameraID;                                   // Camera ID
	std::list<iPreprocessedImageReceiver*>	imageReceiversList;             // List to hold preprocessed ImageReceivers objects
	HANDLE                           inspectionStopEvent;                   // event to stop processing  
	HANDLE                           inspectionExitEvent;                   // event raised by inspection thread on e
	HANDLE                           newImageEvent;                         // event from image acquisition
	CRITICAL_SECTION                 imageMutex;                            // critical section to access image data
	std::list<ImageData>             imgDataList;                          // image list
	HRegion							 inspectionWindow;
#pragma endregion
	// virtual function override from base class
	virtual BOOL InitInstance(void);
	// virtual function override from base class
	virtual int Run(void);
#pragma region inline functions
	bool AddImageReceiver(iPreprocessedImageReceiver *imgReceiver);
	virtual void OnImageReceived(ImageData &_imageData);

	virtual int OpenGPU();
	virtual int InitAndActivateGPU();
	virtual int CloseGPU();

	void SetGPUList(std::vector<GPUProvider> &_gpuList)
	{
		gpuList = &_gpuList;
	}
};

