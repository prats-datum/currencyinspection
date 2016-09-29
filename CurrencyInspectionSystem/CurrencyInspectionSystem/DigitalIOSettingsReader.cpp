#include "stdafx.h"
#include "DigitalIOSettingsReader.h"


DigitalIOSettingsReader::DigitalIOSettingsReader()
{
}


DigitalIOSettingsReader::~DigitalIOSettingsReader()
{
}

char* DigitalIOSettingsReader::CONFIG_NAME = "DigitalIOSettings.ini";
char* DigitalIOSettingsReader::APP_NAME = "DigitalIOSettings";
char* DigitalIOSettingsReader::DIO_DEVICE_ID = "DIOCardDeviceID";
char* DigitalIOSettingsReader::DIO_DEVICE_DESCRIPTION = "DIOCardDescription";
char* DigitalIOSettingsReader::NUMBER_OF_DIO_SIGNAL = "NumberOfDIOSignal";
char* DigitalIOSettingsReader::SIGNAL = "Signal";
char* DigitalIOSettingsReader::SIGNAL_NAME = "SignalName";
char* DigitalIOSettingsReader::SIGNAL_DIRECTION = "SignalDirection";
char* DigitalIOSettingsReader::PIN_NUMBER = "PinNumber";
char* DigitalIOSettingsReader::PORT_NUMBER = "PortNumber";
char* DigitalIOSettingsReader::NUMBER_OF_CLOCKS = "NumberOfClocks";
char* DigitalIOSettingsReader::CLOCK = "Clock";
char* DigitalIOSettingsReader::CLOCK_NAME = "ClockName";
char* DigitalIOSettingsReader::CHANNEL = "Channel";
char* DigitalIOSettingsReader::NUMBER_OF_LIGHT_STICKS = "NumberOfLightSticks";
char* DigitalIOSettingsReader::LIGHT_STICK = "LightStick";
char* DigitalIOSettingsReader::LIGHT_STICK_DATA_WRITE_ENABLE = "LightStickDataWriteEnable";
char* DigitalIOSettingsReader::NUMBER_OF_DATA_WRITE_PINS = "NumberOfDataWritePins";
char* DigitalIOSettingsReader::NUMBER_OF_LIGHT_STICK_SELECTION_PINS = "NumberOfLightStickSelectionPins";
char* DigitalIOSettingsReader::DATA_WRITE_PIN = "DataWritePin";
char* DigitalIOSettingsReader::LIGHT_STICK_SELECTION_PIN = "LightStickSelectionPin";

std::map<SignalName, DIOSignal> DigitalIOSettingsReader::ReadDIOSignals()
{
	char configFileName[MAX_PATH_LENGTH];
	sprintf_s(configFileName, MAX_PATH_LENGTH, ".\\Configuration Files\\%s", CONFIG_NAME);
	// Device ID
	deviceID = GetPrivateProfileIntA(APP_NAME, DIO_DEVICE_ID, 0, configFileName);
	// Device Description
	char temp[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, DIO_DEVICE_DESCRIPTION, NULL, temp, MAX_PATH_LENGTH, configFileName);
	devDescription = std::string(temp);
	// Number Of Signal
	int numberOfDIOSignals = GetPrivateProfileIntA(APP_NAME, NUMBER_OF_DIO_SIGNAL, 0, configFileName);
	std::map<SignalName, DIOSignal> dioSignals;
	for (int signalIndex = 1; signalIndex <= numberOfDIOSignals; signalIndex++)
	{
		std::string signalAppName = std::string(SIGNAL) + std::to_string(signalIndex);
		// Signal Name
		SignalName tempSignalName = (SignalName)GetPrivateProfileIntA(signalAppName.c_str(), SIGNAL_NAME, 0, configFileName);
		// Signal Direction
		SignalDirection tempSignalDirection = (SignalDirection)GetPrivateProfileIntA(signalAppName.c_str(), SIGNAL_DIRECTION, 0, configFileName);
		// Pin Number
		int tempPinNumber = GetPrivateProfileIntA(signalAppName.c_str(), PIN_NUMBER, 0, configFileName);
		// Port Number
		int tempPortNumber = GetPrivateProfileIntA(signalAppName.c_str(), PORT_NUMBER, 0, configFileName);
		
		dioSignals[tempSignalName].Initialize(deviceID, devDescription, tempSignalName, tempSignalDirection, tempPortNumber, tempPinNumber);
	}
	return dioSignals;
}

std::map<ClockName, AdvantechClock> DigitalIOSettingsReader::ReadDIOClocks()
{
	char configFileName[MAX_PATH_LENGTH];
	sprintf_s(configFileName, MAX_PATH_LENGTH, ".\\Configuration Files\\%s", CONFIG_NAME);
	// Device ID
	deviceID = GetPrivateProfileIntA(APP_NAME, DIO_DEVICE_ID, 0, configFileName);
	// Device Description
	char temp[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, DIO_DEVICE_DESCRIPTION, NULL, temp, MAX_PATH_LENGTH, configFileName);
	devDescription = std::string(temp);

	// Number Of Clock
	int numberOfDIOClocks = GetPrivateProfileIntA(APP_NAME, NUMBER_OF_CLOCKS, 0, configFileName);
	std::map<ClockName, AdvantechClock> dioClocks;
	for (int clockIndex = 1; clockIndex <= numberOfDIOClocks; clockIndex++)
	{
		std::string clockAppName = std::string(CLOCK) + std::to_string(clockIndex);
		// Clock Name
		ClockName tempClockName = (ClockName)GetPrivateProfileIntA(clockAppName.c_str(), CLOCK_NAME, 0, configFileName);
		// Channel
		int tempClockChannel = GetPrivateProfileIntA(clockAppName.c_str(), CHANNEL, 0, configFileName);
		double tempCollectionPeriod = atof(temp);
		dioClocks[tempClockName].SetDetails(devDescription, tempClockChannel);
		dioClocks[tempClockName].Initialize();
		dioClocks[tempClockName].Start();
	}
	return dioClocks;
}


LightSticksControlSignals DigitalIOSettingsReader::ReadLightSticksControlSignals()
{
	LightSticksControlSignals tempLightStickCtrlSignals;
	char configFileName[MAX_PATH_LENGTH];
	sprintf_s(configFileName, MAX_PATH_LENGTH, ".\\Configuration Files\\%s", CONFIG_NAME);
	// Device ID
	deviceID = GetPrivateProfileIntA(APP_NAME, DIO_DEVICE_ID, 0, configFileName);
	// Device Description
	char temp[MAX_PATH_LENGTH];
	GetPrivateProfileStringA(APP_NAME, DIO_DEVICE_DESCRIPTION, NULL, temp, MAX_PATH_LENGTH, configFileName);
	devDescription = std::string(temp);
	
	// Number Of Light Sticks
	tempLightStickCtrlSignals.NumberOfLightSticks = GetPrivateProfileIntA(APP_NAME, NUMBER_OF_LIGHT_STICKS, 0, configFileName);
	// Light Sticks Selection IDs
	tempLightStickCtrlSignals.LightStickSelectionIDs.clear();
	for (int lightIndex = 1; lightIndex <= tempLightStickCtrlSignals.NumberOfLightSticks; lightIndex++)
	{
		std::string lightStickName = std::string(LIGHT_STICK) + std::to_string(lightIndex);
		int lightSelectionID = GetPrivateProfileIntA(APP_NAME, lightStickName.c_str(), 0, configFileName);
		tempLightStickCtrlSignals.LightStickSelectionIDs.push_back(lightSelectionID);
	}
	//LightStickDataWriteEnable
	// Signal Name
	SignalName tempSignalName = (SignalName)GetPrivateProfileIntA(LIGHT_STICK_DATA_WRITE_ENABLE, SIGNAL_NAME, 0, configFileName);
	// Signal Direction
	SignalDirection tempSignalDirection = (SignalDirection)GetPrivateProfileIntA(LIGHT_STICK_DATA_WRITE_ENABLE, SIGNAL_DIRECTION, 0, configFileName);
	// Pin Number
	int tempPinNumber = GetPrivateProfileIntA(LIGHT_STICK_DATA_WRITE_ENABLE, PIN_NUMBER, 0, configFileName);
	// Port Number
	int tempPortNumber = GetPrivateProfileIntA(LIGHT_STICK_DATA_WRITE_ENABLE, PORT_NUMBER, 0, configFileName);
	tempLightStickCtrlSignals.DataWriteEnable[0].Initialize(deviceID, devDescription, tempSignalName, tempSignalDirection, tempPortNumber, tempPinNumber);
	
	//NumberOfDataWritePins
	int NumberOfDataWritePins = GetPrivateProfileIntA(APP_NAME, NUMBER_OF_DATA_WRITE_PINS, 0, configFileName);
	tempLightStickCtrlSignals.DataWritePins.clear();
	for (int dataWritePinIndex = 1; dataWritePinIndex <= NumberOfDataWritePins; dataWritePinIndex++)
	{
		std::string dataWritePinAppName = std::string(DATA_WRITE_PIN) + std::to_string(dataWritePinIndex);
		// Signal Name
		SignalName tempSignalName = (SignalName)GetPrivateProfileIntA(dataWritePinAppName.c_str(), SIGNAL_NAME, 0, configFileName);
		// Signal Direction
		SignalDirection tempSignalDirection = (SignalDirection)GetPrivateProfileIntA(dataWritePinAppName.c_str(), SIGNAL_DIRECTION, 0, configFileName);
		// Pin Number
		int tempPinNumber = GetPrivateProfileIntA(dataWritePinAppName.c_str(), PIN_NUMBER, 0, configFileName);
		// Port Number
		int tempPortNumber = GetPrivateProfileIntA(dataWritePinAppName.c_str(), PORT_NUMBER, 0, configFileName);
		tempLightStickCtrlSignals.DataWritePins[dataWritePinIndex - 1].Initialize(deviceID, devDescription, tempSignalName, tempSignalDirection, tempPortNumber, tempPinNumber);
	}

	//NumberOfLightStickSelectionPins
	int NumberOfLightSticksSelectionPins = GetPrivateProfileIntA(APP_NAME, NUMBER_OF_LIGHT_STICK_SELECTION_PINS, 0, configFileName);
	tempLightStickCtrlSignals.LightSicksSelectionPins.clear();
	for (int lightStickSelectionPinIndex = 1; lightStickSelectionPinIndex <= NumberOfLightSticksSelectionPins; lightStickSelectionPinIndex++)
	{
		std::string lightStickSelectionPinAppName = std::string(LIGHT_STICK_SELECTION_PIN) + std::to_string(lightStickSelectionPinIndex);
		// Signal Name
		SignalName tempSignalName = (SignalName)GetPrivateProfileIntA(lightStickSelectionPinAppName.c_str(), SIGNAL_NAME, 0, configFileName);
		// Signal Direction
		SignalDirection tempSignalDirection = (SignalDirection)GetPrivateProfileIntA(lightStickSelectionPinAppName.c_str(), SIGNAL_DIRECTION, 0, configFileName);
		// Pin Number
		int tempPinNumber = GetPrivateProfileIntA(lightStickSelectionPinAppName.c_str(), PIN_NUMBER, 0, configFileName);
		// Port Number
		int tempPortNumber = GetPrivateProfileIntA(lightStickSelectionPinAppName.c_str(), PORT_NUMBER, 0, configFileName);

		tempLightStickCtrlSignals.LightSicksSelectionPins[lightStickSelectionPinIndex - 1].Initialize(deviceID, devDescription, tempSignalName, tempSignalDirection, tempPortNumber, tempPinNumber);
	}
	return tempLightStickCtrlSignals;
}