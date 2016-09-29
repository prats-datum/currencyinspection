#pragma once

#include "ApplicationSettingsReader.h"
#include "Halconcpp.h"
using namespace HalconCpp;
class GPUProvider
{
private:
public:
	HTuple DeviceIdentifier;
	HComputeDevice GPUHandle;
	GPUProvider();
	~GPUProvider();
	virtual int OpenGPU();
	virtual int InitAndActivateGPU();
	virtual int DeactivateGPU();
	virtual int CloseGPU();
};

