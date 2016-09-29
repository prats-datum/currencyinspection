#include "stdafx.h"
#include "ImagePreprocessor.h"


IMPLEMENT_DYNCREATE(ImagePreprocessor, CWinThread)
ImagePreprocessor::ImagePreprocessor()
{
	InitializeCriticalSection(&imageMutex);
	imageReceiversList.clear();
	newImageEvent = CreateEventW(NULL, FALSE, FALSE, NULL);
	ResetEvent(newImageEvent);
}


ImagePreprocessor::~ImagePreprocessor()
{
	DeleteCriticalSection(&imageMutex);
}
/*------------------------------------------------------------------------------------------------------------------
FUNCTION: SetStopEvent(HANDLE& _inspectionStopEvent,  HANDLE &_inspectionExitEvent))

PURPOSE:
Set stop event so that camera processor can stop inspection
PARAMETERS:
_inspectionStopEvent    - event to stop inspection
_inspectionExitEvent    - event raised by inspection thread on exit of run function
RETURN VALUE:
Returns void
------------------------------------------------------------------------------------------------------------------*/
void ImagePreprocessor::SetStopEvent(HANDLE& _inspectionStopEvent, HANDLE &_inspectionExitEvent)
{
	this->inspectionStopEvent = _inspectionStopEvent;
	this->inspectionExitEvent = _inspectionExitEvent;
}
/*------------------------------------------------------------------------------------------------------------------
FUNCTION: InitInstance(void)

PURPOSE:
on initialization of thread
PARAMETERS:
None
RETURN VALUE:
Returns true if successful. Otherwise, returns false.
------------------------------------------------------------------------------------------------------------------*/
BOOL ImagePreprocessor::InitInstance(void)
{
	return TRUE;
}


bool ImagePreprocessor::AddImageReceiver(iPreprocessedImageReceiver *imgReceiver)
{
	imageReceiversList.push_back(imgReceiver);
	return true;
}

void ImagePreprocessor::OnImageReceived(ImageData &_imageData)
{
	EnterCriticalSection(&imageMutex);
	int buffSize = imgDataList.size();
	LeaveCriticalSection(&imageMutex);

	if (buffSize < IMAGE_BUFFER_SIZE)
	{
		EnterCriticalSection(&imageMutex);
		imgDataList.push_back(_imageData);
		LeaveCriticalSection(&imageMutex);
	}
	else
	{
		EnterCriticalSection(&imageMutex);
		imgDataList.clear();
		imgDataList.push_back(_imageData);
		LeaveCriticalSection(&imageMutex);
		/*
		InspectionTaskException *exception;
		exception = new InspectionTaskException(inspectionItemID,inspectionType,_T("SetImage"),EX1012);
		throw exception;  */
		//CString Log;
		//Log.Format(_T("Image Buffer overloaded for Image Preprocessor"));
		LOGINFO(_T("Image Buffer overloaded for Image Preprocessor"));
		// ToDo raise exception buffer overloaded

	}
	SetEvent(newImageEvent);
	//CString Log;
	//Log.Format(_T("Image Buffer Size =  %d"), buffSize);
	//LOGDEBUG(Log);
}

/*------------------------------------------------------------------------------------------------------------------
FUNCTION: Run(void)

PURPOSE:
Thread function to process image as per inspection algo

PARAMETERS:
None

RETURN VALUE:
Returns 1 if successful. Otherwise, returns 0.
------------------------------------------------------------------------------------------------------------------*/
int ImagePreprocessor::Run(void)
{
	HANDLE          eventHandle[2];                                         // Event Handle array
	double          timeTaken;                                              // Total time taken for processing
	ImageData       _imageData;                                             // Image Data Structure
	double			t1, t2, t3, t4;											// Processing Time Stamps

	int             imageBufSize;
	int             result;                                                 // variable to hold inspection result
	TCHAR           errorMessage[MAX_ERROR_MESSAGE_LENGTH];
	LOGINFO(_T("Image Preprocessor Thread started"));

#ifdef SAVE_IMAGE_TO_HD
	HImage imageBuffer[MAX_IMAGE_BUFFER_SIZE];        // image buffer
	int tempCount = 0;
	int imageNo = 0;
	std::string imageFileName;
#endif


	eventHandle[0] = newImageEvent;                                         // event for new image
	eventHandle[1] = inspectionStopEvent;                                   // event to stop inspection
																			// more images are ther in buffer to process


	gpuList->at(0).InitAndActivateGPU();

	while (WAIT_OBJECT_0 == WaitForMultipleObjects(2, eventHandle, FALSE, INFINITE))
	{
		
			t1 = HSystem::CountSeconds();
			// pop images from image buffer               
			EnterCriticalSection(&imageMutex);
			if (imgDataList.size() > 0)
			{
				_imageData = imgDataList.front();
				imgDataList.pop_front();
			}
			else
			{
				LeaveCriticalSection(&imageMutex);
				continue;
			}
			LeaveCriticalSection(&imageMutex);
			t2 = HSystem::CountSeconds();
			// reset inspection results variables
#ifdef SAVE_IMAGE_TO_HD
			if (tempCount < MAX_IMAGE_BUFFER_SIZE)
			{
				imageBuffer[tempCount++] = _imageData.image;        // copy to image buffer
			}
#endif
			PreprocessedImageData preProcessedImageData(_imageData, inspectionWindow);
			t3 = HSystem::CountSeconds();
			for (auto &receiver : imageReceiversList)
			{
				receiver->OnPreprocessedImageReceived(preProcessedImageData);
			}
			// push result to result buffer and raise event
			t4 = HSystem::CountSeconds();
			timeTaken = (t4 - t1) * 1000;     // time taken in ms
											  // copy inspection results


#ifdef RESULTS_LOG_NEEDED

			std::string comma = ",";
			std::string mainLog = std::to_string(_imageData.imageNumber) + comma + std::to_string(t1) + comma + std::to_string(t4) + comma + std::to_string(timeTaken) +
				comma + std::to_string((t2 - t1) * 1000) + comma + std::to_string((t3 - t2) * 1000) + comma + std::to_string((t4 - t3) * 1000) + "\n";
			if (resultsLog.size() > MAX_RESULT_LOG_COUNT)
			{
				resultsLog.pop_front();
			}
			resultsLog.push_back(mainLog);

#endif
			//LOGDEBUG(_T("Processing Finished Image Preprocessor"));
			// check if more images are available to process
			EnterCriticalSection(&imageMutex);
			imageBufSize = imgDataList.size();
			LeaveCriticalSection(&imageMutex);
			if (imageBufSize > 0)
			{
				SetEvent(newImageEvent);
			}
			else
			{
				continue;
			}


	}

#ifdef SAVE_IMAGE_TO_HD
	// save images in buffer to hard disk
	for (register int i = 0; i<tempCount; i++)
	{
		sprintf_s(imageFileName, "./SavedImages/Image%d.bmp", i);
		try
		{
			imageBuffer[i].WriteImage("bmp", 0, imageFileName);
		}
		catch (HException &except)
		{


			LOGERROR(_T("Write image exception ") << except.message);


		}
	}
	CTextGraphics::PrintError(_T("Images Saved!      "));

#endif
#ifdef INSPECTION_DISPLAY_ON
	displayWindow.CloseWindow();
#endif
#ifdef RESULTS_LOG_NEEDED
	std::string fileName;
	fileName = std::string(IPA_LOGS_DIRECTORY) + "\\Online Processing Image Preprocessor Results.csv";
	FILE *fpProc = fopen(fileName.c_str(), "w");
	if (fpProc != NULL)
	{
		fprintf(fpProc, "ImageCnt,startTime,FinishTime,Overall Processing Time, Image Acquring Time, Processing Time, Result Publishing time\n");
		for (std::list<std::string>::iterator iter = this->resultsLog.begin(); iter != this->resultsLog.end(); iter++)
		{
			fprintf(fpProc, "%s", (*iter).c_str());
		}
		fclose(fpProc);
	}
	resultsLog.clear();
#endif
	gpuList->at(0).DeactivateGPU();

	SetEvent(inspectionExitEvent);
	::PostQuitMessage(0);
	return 1;

}
#pragma endregion
int ImagePreprocessor::OpenGPU()
{
	GPUProvider::OpenGPU();
	return 1;
}

int ImagePreprocessor::CloseGPU()
{
	GPUProvider::CloseGPU();
	return 1;
}

int ImagePreprocessor::InitAndActivateGPU()
{
	try
	{
		//GPUHandle.InitComputeDevice("trans_from_rgb");
		//GPUHandle.InitComputeDevice("rgb1_to_gray");
		//GPUHandle.InitComputeDevice("decompose3");
		//GPUHandle.InitComputeDevice("gray_erosion_rect");
		//GPUHandle.InitComputeDevice("gray_dilation_rect");
		//GPUHandle.InitComputeDevice("abs_diff_image");
		//GPUHandle.InitComputeDevice("invert_image");
		

		GPUHandle.InitComputeDevice("affine_trans_image");
		//AfxMessageBox(_T("1"));
		GPUHandle.InitComputeDevice("trans_from_rgb");
		//AfxMessageBox(_T("2"));
		GPUHandle.InitComputeDevice("trans_to_rgb");
		//AfxMessageBox(_T("3"));
		GPUHandle.InitComputeDevice("zoom_image_size");
		//AfxMessageBox(_T("5"));
		GPUHandle.InitComputeDevice("rgb1_to_gray");
		//AfxMessageBox(_T("6"));
		GPUHandle.InitComputeDevice("crop_domain");
		//AfxMessageBox(_T("7"));
		GPUHandle.InitComputeDevice("reduce_domain");
		//AfxMessageBox(_T("8"));
		GPUHandle.InitComputeDevice("sub_image");
		//AfxMessageBox(_T("9"));
		GPUHandle.InitComputeDevice("add_image");
		//AfxMessageBox(_T("10"));
		GPUHandle.InitComputeDevice("mult_image");
		//AfxMessageBox(_T("12"));
		GPUHandle.InitComputeDevice("max_image");
		//AfxMessageBox(_T("13"));
		GPUHandle.InitComputeDevice("min_image");
		//AfxMessageBox(_T("14"));
		GPUHandle.InitComputeDevice("convert_image_type");
		//AfxMessageBox(_T("15"));
		GPUHandle.InitComputeDevice("gray_erosion_rect");
		//AfxMessageBox(_T("16"));
		GPUHandle.InitComputeDevice("gray_dilation_rect");
		//AfxMessageBox(_T("17"));
		GPUHandle.InitComputeDevice("append_channel");
		//AfxMessageBox(_T("19"));
		GPUHandle.InitComputeDevice("abs_diff_image");
		//AfxMessageBox(_T("20"));
		GPUHandle.InitComputeDevice("decompose3");
		//AfxMessageBox(_T("21"));
		GPUHandle.InitComputeDevice("compose3");
		GPUHandle.InitComputeDevice("find_ncc_model");

		GPUHandle.ActivateComputeDevice();
		return 1;
	}
	catch (HException &e)
	{
		return 0;
	}
	return 1;
}