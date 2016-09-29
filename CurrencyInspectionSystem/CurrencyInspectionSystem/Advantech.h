#pragma once

#include "DigitalIO.h"
#include "bdaqctrl.h"
#define  deviceDescription  L"PCIE-1751,BID#0"

using namespace Automation::BDaq;

class AdvantechOutput : public OutputBase
{
public:
	DeviceInformation *devInfo;
	InstantDoCtrl *outputControl = AdxInstantDoCtrlCreate();

	AdvantechOutput(string description) : OutputBase(description) {}

	AdvantechOutput(int deviceNo, int portId, int pinNo) : OutputBase(deviceNo, portId, pinNo)
	{
		devInfo = new DeviceInformation(deviceNo);
	}
	AdvantechOutput(int deviceNo, string description, int portId, int pinNo) : OutputBase(deviceNo, description, portId, pinNo)
	{
		devInfo = new DeviceInformation(deviceNo, ModeWriteWithReset, 0);
	}
	~AdvantechOutput()
	{
		if (devInfo != NULL)
		{
			delete devInfo;
		}
	}

	virtual bool Initialize();
	virtual bool Start();
	virtual bool Stop();
	bool SetOutput(int portID, byte code);
	bool SetOutput(int portID, int startPin, int pinCount, byte code);
	bool SetOutput(int portID, int pinID, bool value);
	bool SetOutput(bool value);
};

class AdvantechInput : public InputBase
{
public:
	DeviceInformation *devInfo;
	InstantDiCtrl *inputControl = AdxInstantDiCtrlCreate();

	AdvantechInput(string description) : InputBase(description) {}

	/*AdvantechInput(int deviceNo, int portId, int pinNo) : InputBase(deviceNo, portId, pinNo)
	{
		devInfo = new DeviceInformation(deviceNo);
	}*/

	AdvantechInput(int deviceNo, string description, int portId, int pinNo) : InputBase(deviceNo, description, portId, pinNo)
	{		
		//devInfo = new DeviceInformation(description, ModeWriteWithReset, 0);
	}

	~AdvantechInput()
	{
		if (devInfo != NULL)
		{
			delete devInfo;
		}
	}

	virtual bool Initialize();
	virtual bool Start();
	virtual bool Stop();
	//bool ReadInputAsBinary(int portID, bool pinData[], byte data);
	bool ReadInputAsByte(int portID, byte data);
	bool ReadInputAsByte(int portID, int startPin, int count, byte data);
	bool ReadPin(int portID, int pinID);
	bool ReadPin();
};

class AdvantechInterrupt : public InterruptBase, public DiSnapEventListener
{
public:
	InstantDiCtrl *inputControl = AdxInstantDiCtrlCreate();
	DeviceInformation *devInfo;
	ActiveSignal interruptMode = FallingEdge;
	ICollection<DiintChannel>* interruptChans;
	int startPort = 0, portCount = 1;

	DiSnapEventListener *interrupt;

	AdvantechInterrupt(string description) : InterruptBase(description) {}

	AdvantechInterrupt(int deviceNo, int portId, int pinNo) : InterruptBase(deviceNo, portId, pinNo)
	{
		interrupt = this;
		//devInfo = new DeviceInformation(deviceNo);
		//inputControl->addInterruptListener(*interrupt);
	}

	AdvantechInterrupt(int deviceNo, string description, int portId, int pinNo) : InterruptBase(deviceNo, description, portId, pinNo)
	{
		interrupt = this;
		/*interrupt = &interruptHandler;
		devInfo = new DeviceInformation(deviceNo, ModeWriteWithReset, 0);
		inputControl->addInterruptListener(*interrupt);*/
	}


	~AdvantechInterrupt()
	{
		if (devInfo != NULL)
		{
			delete devInfo;
		}
	}

	virtual bool Initialize();
	virtual bool Start();
	virtual bool Stop();

	bool setInterruptMode(ActiveSignal _interruptMode);
	//bool ReadInputAsBinary(int portID, bool pinData[], byte data);
	bool ReadInputAsByte(int portID, byte data);
	bool ReadInputAsByte(int portID, int startPin, int count, byte data);
	bool ReadPin(int portID, int pinID);
	virtual void BDAQCALL DiSnapEvent(void * sender, DiSnapEventArgs * args)
	{
		//show snap data.
		//printf(" DI Interrupt channel is %d\n", args->SrcNum);
		//for (int32 i = startPort; i < startPort + portCount; ++i)
		//{
		//	printf(" DI port %d status:  0x%X\n\n", i, args->PortData[i - startPort]);
		//}
		for (auto &e : interruptHandler)
		{
			e->OnInterruptReceived();
		}
	}	
};

//class StatusChangeHandler : public DiSnapEventListener
//{
//public:
//	int startPort = 0, portCount = 8;
//	virtual void BDAQCALL DiSnapEvent(void * sender, DiSnapEventArgs * args)
//	{
//		unsigned char bufferForSnap[MAX_DIO_PORT_COUNT];
//		memcpy(bufferForSnap, args->PortData, MAX_DIO_PORT_COUNT);
//		signalValue = pinNo < 0 ? 255 : (byte)pow(2, 3);
//
//		//show snap data.
//		printf(" Status Change Interrupt port is %d\n", args->SrcNum);
//		for (int i = startPort; i < startPort + portCount; ++i)
//		{
//			printf(" DI port %d status is:  0x%X\n", i, bufferForSnap[i - startPort]);
//		}
//	}
//};

class AdvantechStatusChangeInterrupt : public InterruptBase, public DiSnapEventListener
{
public:
	DeviceInformation *devInfo;
	InstantDiCtrl *inputControl = AdxInstantDiCtrlCreate();

	bool isHigh;
	byte signalValue;
	ActiveSignal InterruptMode = ActiveSignal::BothEdge;
	bool IsInitialized;
	bool IsRunning;
	bool IsHigh;
	ICollection<DiCosintPort>* statusChangeChans;

	DiSnapEventListener *statusChange;

	AdvantechStatusChangeInterrupt(string description) : InterruptBase(description) { }
	
	AdvantechStatusChangeInterrupt(int deviceNo, string description, int portId, int pinNo)
		: InterruptBase(deviceNo, description, portId, pinNo)
	{
		statusChange = this;
	}
	~AdvantechStatusChangeInterrupt()
	{
		if (devInfo != NULL)
		{
			delete devInfo;
		}
	}

	virtual bool Initialize();
	virtual bool Start();
	virtual bool Stop();
		
	bool ReadInputAsByte(int portID, byte data);
	bool ReadInputAsByte(int portID, int startPin, int count, byte data);
	bool ReadPin(int portID, int pinID);
	bool ReadPin();

	int setPinNo(int _pinNo);
	bool setIsHighFlag(bool _ishigh);

	virtual void BDAQCALL DiSnapEvent(void * sender, DiSnapEventArgs * args)
	{
		//unsigned char bufferForSnap[MAX_DIO_PORT_COUNT];
		//memcpy(bufferForSnap, args->PortData, MAX_DIO_PORT_COUNT);
		//signalValue = (PinNo < 0) ? (255) : ((byte)pow(2, PinNo));
		//byte result = (byte)(bufferForSnap[PortID] & signalValue);
		//setIsHighFlag(result != 0);
		setIsHighFlag(ReadPin());
	}
};

class AdvantechClock : public ClockBase
{
public:
	EventCounterCtrl* eventCounterControl = AdxEventCounterCtrlCreate();
	DeviceInformation *devInfo;

	AdvantechClock() : ClockBase(){}
	AdvantechClock(string description) : ClockBase(description) {}
	AdvantechClock(string _description, int _channel) : ClockBase(_description, _channel) {}
	~AdvantechClock()
	{
		if (devInfo != NULL)
		{
			delete devInfo;
		}
	}
	void SetDetails(string _description, int _channel);
	virtual bool Initialize();
	virtual bool Start();
	virtual bool Stop();

	long GetClockValue();
	bool SetChannel(int _channel);
};