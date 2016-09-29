#pragma once
#include "Halconcpp.h"
#include "ApplicationSettingsReader.h"
using namespace HalconCpp;

class GPUProviderSingleton
{
public:
	GPUProviderSingleton();
	~GPUProviderSingleton();
private:
	int OpenGPU();
	int CloseGPU();
public:

	HTuple DeviceIdentifier;
	HComputeDevice *GPUHandle;
	int InitAndActivateGPU();
	int DeActivateGPU();
	int ActivateGPU();

	//static HANDLE initializedEvent;
	static GPUProviderSingleton* thisInstance;
	static GPUProviderSingleton* GetGPU();
};

