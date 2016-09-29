#include "stdafx.h"
#include "GPUProvider.h"


GPUProvider::GPUProvider()
{
}

GPUProvider::~GPUProvider()
{
	//CloseGPU();
}

int GPUProvider::OpenGPU()
{
	int returnValue = 0;
#ifdef USE_GPU
	HTuple availableDeviceIdentifier, DeviceName;
	try
	{
		QueryAvailableComputeDevices(&availableDeviceIdentifier);
	}
	catch (HException &ex)
	{

	}
	char cCount[100];
	int iCount = availableDeviceIdentifier.Length();
	for (int index = 0; index < iCount; index++)
	{
		GetComputeDeviceInfo(availableDeviceIdentifier[index], "name", &DeviceName);
		if (ApplicationSettingsReader::GetInstance()->GPUNameStr.compare(DeviceName.S().Text()) == 0)
		{
			DeviceIdentifier = availableDeviceIdentifier[index];
			GPUHandle.OpenComputeDevice(DeviceIdentifier);
			GPUHandle.SetComputeDeviceParam("asynchronous_execution", "false");
			GPUHandle.SetComputeDeviceParam("alloc_pinned", "false");
			returnValue = 1;
			break;
		}
	}
#else
	returnValue = 1;
#endif // USE_GPU
	//AfxMessageBox(_T("Configured GPU was not found!!"));
	return returnValue;
}

int GPUProvider::CloseGPU()
{
	int returnValue = 0;

#ifdef USE_GPU
	if (GPUHandle.IsHandleValid())
	{
		DeactivateComputeDevice(GPUHandle);
		GPUHandle.ReleaseComputeDevice();
		returnValue = 1;
	}
	//GPUHandle.Clear();
#else
	returnValue = 1;
#endif // USE_GPU
	return returnValue;
}

int GPUProvider::InitAndActivateGPU()
{
	int returnValue = 0;

#ifdef USE_GPU
	if (GPUHandle.IsHandleValid())
	{
		////AfxMessageBox(_T("18"));
		GPUHandle.InitComputeDevice("affine_trans_image");
		//AfxMessageBox(_T("1"));
		GPUHandle.InitComputeDevice("trans_from_rgb");
		//AfxMessageBox(_T("2"));
		GPUHandle.InitComputeDevice("trans_to_rgb");
		//AfxMessageBox(_T("3"));
		GPUHandle.InitComputeDevice("zoom_image_factor");
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
		GPUHandle.ActivateComputeDevice();
		returnValue = 1;
	}
#else
	returnValue = 1;
#endif // USE_GPU
	return returnValue;
}

int GPUProvider::DeactivateGPU()
{
	int returnValue = 0;

#ifdef USE_GPU
	if (GPUHandle.IsHandleValid())
	{
		DeactivateComputeDevice(GPUHandle);
		returnValue = 1;
	}
#else
	returnValue = 1;
#endif // USE_GPU
	return returnValue;
}