#pragma once

#include <string>
#include <list>
using namespace std;

//enum InterruptMode
//{
//	RisingEdge = 1,
//	FallingEdge = 2,
//	BothEdge = 3
//};
class InterruptHandler
{
public:
	virtual void OnInterruptReceived() {}
};

class DIOBase
{
public:
	string ID, Name, Description, DeviceNo;
	int PortID, PinNo;
	bool IsInitialized, IsRunning;

	DIOBase()
	{

	}

	DIOBase(string deviceDescription)
	{
		Description = deviceDescription;
	}

	DIOBase(string description, int portID, int pinNo)
	{
		Description = description;
		PortID = portID;
		PinNo = pinNo;
	}

	DIOBase(int deviceNo, string description, int portID, int pinNo)
	{
		Description = description;
		PortID = portID;
		DeviceNo = deviceNo;
		PinNo = pinNo;
	}

	DIOBase(int deviceNo, int portID, int pinNo)
	{
		DeviceNo = deviceNo;
		PortID = portID;
		PinNo = pinNo;
	}

	virtual bool InitDIO() { return false; }
	virtual bool ReleaseDIO() { return false; }
	virtual bool Initialize() { return false; }
	virtual bool Start() { return false; }
	virtual bool Stop() { return false; }

	list<InterruptHandler*> interruptHandler;
	void AddListener(InterruptHandler *_inputReciever) 
	{ 
		interruptHandler.push_back(_inputReciever); 
	}
};

class InputBase : public DIOBase
{
public:
	InputBase(string deviceDescription) : DIOBase(deviceDescription) {}
	InputBase(string description, int portID, int pinNo) : DIOBase(description, portID, pinNo) {}
	InputBase(int deviceNo, string description, int portID, int pinNo) : DIOBase(deviceNo, description, portID, pinNo) {}
	InputBase(int deviceNo, int portID, int pinNo) : DIOBase(deviceNo, portID, pinNo) {}

	bool ReadInputAsBinary(int portID, bool *pinData, char &data);
	bool ReadInputAsByte(int portID, char data);
	bool ReadInputAsByte(int portID, int startPin, int count, char &data);
	bool ReadPin(int portID, int pinID); 
	
	virtual bool InitDIO() { return false; }
	virtual bool ReleaseDIO() { return false; }
	virtual bool Initialize() { return false; }
	virtual bool Start() { return false; }
	virtual bool Stop() { return false; }
};

class OutputBase : public DIOBase
{
public:
	OutputBase(string deviceDescription) : DIOBase(deviceDescription) {}
	OutputBase(string description, int portID, int pinNo) : DIOBase(description, portID, pinNo) {}
	OutputBase(int deviceNo, string description, int portID, int pinNo) : DIOBase(deviceNo, description, portID, pinNo) {}
	OutputBase(int deviceNo, int portID, int pinNo) : DIOBase(deviceNo, portID, pinNo) {}
	bool SetOutput(int portID, char code);
	bool SetOutput(int portID, int pinID, bool value);

	virtual bool InitDIO() { return false; }
	virtual bool ReleaseDIO() { return false; }
	virtual bool Initialize() { return false; }
	virtual bool Start() { return false; }
	virtual bool Stop() { return false; }
};

class InterruptBase : public InputBase
{
public:
	InterruptBase(string deviceDescription) : InputBase(deviceDescription) {}
	InterruptBase(string description, int portID, int pinNo) : InputBase(description, portID, pinNo) {}
	InterruptBase(int deviceNo, string description, int portID, int pinNo) : InputBase(deviceNo, description, portID, pinNo) {}
	InterruptBase(int deviceNo, int portID, int pinNo) : InputBase(deviceNo, portID, pinNo) {}
		
	int SpuriousTriggerTime;
	int DebounceTime;
	bool DebounceSignal;
	virtual bool Initialize() { return false; }
	virtual bool Start() { return false; }
	virtual bool Stop() { return false; }
};

class ClockBase : public DIOBase
{
public:
	ClockBase() : DIOBase() {}
	ClockBase(string deviceDescription) : DIOBase(deviceDescription) {}
	ClockBase(string deviceDescription, int _channel) : DIOBase(deviceDescription) {}

	virtual long GetClockValue() { return 0; }
	virtual bool SetChannel(int _channel) { return false; }

	int channel;
	double lastReadClockValue;
	virtual bool Initialize() { return false; }
	virtual bool Start() { return false; }
	virtual bool Stop() { return false; }
};