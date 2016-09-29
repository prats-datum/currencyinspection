#pragma once
#include "GoldenData.h"
#include "GrabFromFile.h"
#include "GrabFromCamera.h"
#include "Logger.h"
#include "CameraModelGenerator.h"


class GoldenGenerator : public iImageReceiver, public iModelBuildiingEventReceiver, public iExtendedTrainingSetReceiver
{
private:
	ImageGrabber *imgGrabber[MAX_NUM_OF_CAMERAS];
	HANDLE imgGrabberStopEvent;
	HANDLE imgGrabberExitEvent[MAX_NUM_OF_CAMERAS];
	HANDLE buildStopEvent;
	HANDLE cameraModelBuilderExitEvent[MAX_NUM_OF_CAMERAS];

	int imagesToGrab[MAX_NUM_OF_CAMERAS];

	iTrainingSetStatusReceiver *trainingSetStausReceiver;
	std::vector<GPUProvider> *gpuList;
public:
	std::map<UINT, CameraModelGenerator*> cameraModelGeneratorList;
	GoldenData *goldenData;
	GoldenGenerator();
	~GoldenGenerator();

	bool GrabTrainingSet(int _cameraID, ImageSourceType _sourceType, std::string _configFileName, int _imageCount, iImageReceiver *_receiver);
	void StopGrabbingTrainingSet(int _cameraID);
	virtual void OnImageReceived(ImageData &_imageData);
	void SetMasterSet(int _cameraID, HImage &_masterImage, HImage &_irMasterImage);


	virtual void OnModelBuidingExceptionReceived(UINT cameraID, UINT trainingSetNumber, UINT taskID, IPAException *exception);
	virtual void OnModelBuidingCompletedForImage(UINT cameraID, UINT trainingSetNumber, bool isSuccessfull);


	virtual void OnExtendedTrainingSetReceived(UINT cameraID, TrainingImageData _trainingSetData);
	void SetGPUList(std::vector<GPUProvider> &_gpuList)
	{
		gpuList = &_gpuList;
	}

	void SetTrainingSetStausReceiver(iTrainingSetStatusReceiver  *_trainingSetStatusReceiver);
	void ExtendGolden();
	bool EndGoldenExtension();
};

