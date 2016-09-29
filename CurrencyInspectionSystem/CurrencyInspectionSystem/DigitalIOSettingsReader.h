#pragma once
#include "Advantech.h"
#include "Globals.h"

enum InterfaceName
{
	SisoTriggerCard = 0,
	KomoriPLC,
	DIO,
	TowerLamp,
	DAC
};

enum SignalDirection
{
	InputSignal = 0,
	InterruptSignal = 1,
	StatusChangeSignal = 2,
	OutputSignal = 3
};

enum SignalName
{
	DebouncedImageTrigger = 1,
	MachineStateSignal = 2,
	PreparationCompletedSignal = 3,
	InspectionAvailableSignal = 4,
	StartInspectionSignal = 5,
	EjectorSensorEvent = 6,
	InspectionResultSignal = 7,
	InspectionSystemAbnormalSignal = 8,
	TowerLampRed = 9,
	TowerLampYellow = 10,
	TowerLampBlue = 11,
	LightStickControlSignals=12
};

enum ClockName
{
	EncoderClock = 1
};

class DIONotificationReceiver
{
public:
	virtual void OnDIONotificationReceived(SignalName dioSignalName) = 0;
};

class DIOSignal : public InterruptHandler
{
public:
	int portNo;
	int pinNo;
	SignalDirection signalDirection;
	SignalName signalName;
	DIOBase *dio;
	std::list<DIONotificationReceiver *> dioNotificationReceiverList;

	DIOSignal()
	{

	}
	
	void Initialize(int _deviceID, std::string _devDescription, SignalName _signalName, SignalDirection _signalDirection, int _portNo, int _pinNo)
	{
		signalName = _signalName;
		signalDirection = _signalDirection;
		portNo = _portNo;
		pinNo = _pinNo;
		dioNotificationReceiverList.clear();
		switch (_signalDirection)
		{
		case InputSignal: 
			dio = new AdvantechInput(_deviceID, _devDescription, portNo, pinNo);
			break;
		case InterruptSignal: 
			dio = new AdvantechInterrupt(_deviceID, _devDescription, portNo, pinNo);
			dio->AddListener(this);
			break;
		case StatusChangeSignal: 
			dio = new AdvantechStatusChangeInterrupt(_deviceID, _devDescription, portNo, pinNo);
			dio->AddListener(this);
			break;
		case OutputSignal: dio = new AdvantechOutput(_deviceID, _devDescription, portNo, pinNo);
			break;
		}
		dio->Initialize();
		dio->Start();
	}

	void AddListener(DIONotificationReceiver *_notificationReciever)
	{
		dioNotificationReceiverList.push_back(_notificationReciever);
	}
	~DIOSignal()
	{
		dio->interruptHandler.clear();
		delete dio;
	}

	virtual void OnInterruptReceived()
	{
		for (auto &e : dioNotificationReceiverList)
		{
			e->OnDIONotificationReceived(signalName);
		}
	}
};

class LightSticksControlSignals
{
public:
	int NumberOfLightSticks;
	vector<int> LightStickSelectionIDs;
	map<int, DIOSignal> DataWriteEnable;
	map<int, DIOSignal> DataWritePins;
	map<int, DIOSignal> LightSicksSelectionPins;
};


class DigitalIOSettingsReader
{
	static char *CONFIG_NAME, *APP_NAME, *DIO_DEVICE_ID, *DIO_DEVICE_DESCRIPTION, *NUMBER_OF_DIO_SIGNAL, *SIGNAL, *SIGNAL_NAME, *SIGNAL_DIRECTION, *PIN_NUMBER,
		*PORT_NUMBER, *NUMBER_OF_CLOCKS, *CLOCK, *CLOCK_NAME, *CHANNEL, *NUMBER_OF_LIGHT_STICKS, *LIGHT_STICK, *LIGHT_STICK_DATA_WRITE_ENABLE,
		*NUMBER_OF_DATA_WRITE_PINS, *NUMBER_OF_LIGHT_STICK_SELECTION_PINS, *DATA_WRITE_PIN, *LIGHT_STICK_SELECTION_PIN;
	int deviceID;
	std::string devDescription;
public:
	DigitalIOSettingsReader();
	~DigitalIOSettingsReader();

	std::map<SignalName, DIOSignal> ReadDIOSignals();

	std::map<ClockName, AdvantechClock> ReadDIOClocks();

	LightSticksControlSignals ReadLightSticksControlSignals();

};

