#include "stdafx.h"
#include "GPUProviderSingleton.h"

GPUProviderSingleton* GPUProviderSingleton::thisInstance = NULL;
//HANDLE GPUProvider::initializedEvent = CreateEventA(0, FALSE, FALSE, 0);

GPUProviderSingleton::GPUProviderSingleton()
{
	OpenGPU();
}

GPUProviderSingleton::~GPUProviderSingleton()
{
	CloseGPU();
}

int GPUProviderSingleton::OpenGPU()
{
	HTuple availableDeviceIdentifier, DeviceName;
	QueryAvailableComputeDevices(&availableDeviceIdentifier);
	char cCount[100];
	int iCount = availableDeviceIdentifier.Length();
	for (int index = 0; index < iCount; index++)
	{
		GetComputeDeviceInfo(availableDeviceIdentifier[index], "name", &DeviceName);
		if (ApplicationSettingsReader::GetInstance()->GPUNameStr.compare(DeviceName.S().Text()) == 0)
		{
			GPUProviderSingleton::DeviceIdentifier = availableDeviceIdentifier[index];
			GPUHandle = new HComputeDevice();
			GPUHandle->OpenComputeDevice(GPUProviderSingleton::DeviceIdentifier);
			GPUHandle->SetComputeDeviceParam("asynchronous_execution", "false");
			//GPUHandle->SetComputeDeviceParam("pinned_mem_cache_capacity", (50 * 1024 * 1024));
			//GPUHandle->SetComputeDeviceParam("alloc_pinned", "false");

			/*
			GPUHandle->SetComputeDeviceParam("image_cache_capacity", (2 * 1024 * 1024));
			GPUHandle->SetComputeDeviceParam("buffer_cache_capacity", (2 * 1024 * 1024 ));*/
			//GPUHandle->SetComputeDeviceParam("alloc_pinned", "false");
			//GPUHandle->
			//GPUHandle->SetComputeDeviceParam("asynchronous_execution", "false");
			return 1;
		}
	}
	return 0;
}

int GPUProviderSingleton::CloseGPU()
{
	if (GPUHandle != NULL)
	{
		if (GPUHandle->IsHandleValid())
		{
			GPUHandle->ReleaseComputeDevice();
		}
		GPUHandle->Clear();
		delete GPUHandle;
	}
	return 1;
}

int GPUProviderSingleton::InitAndActivateGPU()
{
	try
	{
		////AfxMessageBox(_T("18"));
		GPUHandle->InitComputeDevice("affine_trans_image");
		//AfxMessageBox(_T("1"));
		GPUHandle->InitComputeDevice("trans_from_rgb");
		//AfxMessageBox(_T("2"));
		GPUHandle->InitComputeDevice("trans_to_rgb");
		//AfxMessageBox(_T("3"));
		GPUHandle->InitComputeDevice("zoom_image_size");
		//AfxMessageBox(_T("5"));
		GPUHandle->InitComputeDevice("rgb1_to_gray");
		//AfxMessageBox(_T("6"));
		GPUHandle->InitComputeDevice("crop_domain");
		//AfxMessageBox(_T("7"));
		GPUHandle->InitComputeDevice("reduce_domain");
		//AfxMessageBox(_T("8"));
		GPUHandle->InitComputeDevice("sub_image");
		//AfxMessageBox(_T("9"));
		GPUHandle->InitComputeDevice("add_image");
		//AfxMessageBox(_T("10"));
		GPUHandle->InitComputeDevice("mult_image");
		//AfxMessageBox(_T("12"));
		GPUHandle->InitComputeDevice("max_image");
		//AfxMessageBox(_T("13"));
		GPUHandle->InitComputeDevice("min_image");
		//AfxMessageBox(_T("14"));
		GPUHandle->InitComputeDevice("convert_image_type");
		//AfxMessageBox(_T("15"));
		GPUHandle->InitComputeDevice("gray_erosion_rect");
		//AfxMessageBox(_T("16"));
		GPUHandle->InitComputeDevice("gray_dilation_rect");
		//AfxMessageBox(_T("17"));
		GPUHandle->InitComputeDevice("append_channel");
		//AfxMessageBox(_T("19"));
		GPUHandle->InitComputeDevice("abs_diff_image");
		//AfxMessageBox(_T("20"));
		GPUHandle->InitComputeDevice("decompose3");
		//AfxMessageBox(_T("21"));
		GPUHandle->InitComputeDevice("compose3");
		//GPUHandle->InitComputeDevice("find_ncc_model");
		//AfxMessageBox(_T("22"));
		GPUHandle->ActivateComputeDevice();
		return 1;
	}
	catch (HException &e)
	{
		return 0;
	}
	return 1;
}
int GPUProviderSingleton::DeActivateGPU()
{
	try
	{
		DeactivateComputeDevice(*GPUHandle);
		return 1;
	}
	catch (HException &e)
	{
		return 0;
	}
	return 0;
}


int GPUProviderSingleton::ActivateGPU()
{
	try
	{
		GPUHandle->ActivateComputeDevice();
		return 1;
	}
	catch (HException &e)
	{
		return 0;
	}
	return 0;
}


GPUProviderSingleton* GPUProviderSingleton::GetGPU()
{
	if (GPUProviderSingleton::thisInstance == NULL)
	{
		GPUProviderSingleton::thisInstance = new GPUProviderSingleton();
	}
	return GPUProviderSingleton::thisInstance;
}