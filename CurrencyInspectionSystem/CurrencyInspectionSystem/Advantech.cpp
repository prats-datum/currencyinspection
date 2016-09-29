#include "stdafx.h"
#include "Advantech.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool AdvantechOutput::Initialize()
{
	try
	{
		if (!IsInitialized)
		{
			wchar_t text_wchar[30];
			size_t length;
			mbstowcs_s(&length, text_wchar, Description.c_str(), Description.length());

			devInfo = new DeviceInformation(text_wchar);
			ErrorCode ret = outputControl->setSelectedDevice(*devInfo);
			IsInitialized = outputControl->getInitialized();
		}
	}
	catch (exception &e)
	{
		//OnErrorOccured(new MessageEventArgs(1, "Initialize Output Error", e));
		return false;
	}
	return true;
}

bool AdvantechOutput::Start()
{
	IsRunning = true;
	return IsInitialized;
}

bool AdvantechOutput::Stop()
{
	IsRunning = false;
	return IsInitialized;
}

bool AdvantechOutput::SetOutput(int portID, byte code)
{
	if (!IsInitialized) if (!Initialize()) return false;
	try
	{
		ErrorCode error = outputControl->Write(portID, code);
	}
	catch (exception &e)
	{
		return false;
	}
	return true;
}

bool AdvantechOutput::SetOutput(int portID, int startPin, int pinCount, byte code)
{
	if (startPin + pinCount > 8) pinCount = 8 - startPin;
	code = (byte)(code << (startPin));
	code = (byte)(code >> (8 - pinCount));
	return SetOutput(portID, code);
}

bool AdvantechOutput::SetOutput(int portID, int pinID, bool value)
{
	if (!IsInitialized) if (!Initialize()) return false;
	try
	{
		ErrorCode error = outputControl->WriteBit(portID, pinID, (byte)(value ? 0x01 : 0x00));
		if (error == Success) 
			return true;
	}
	catch (exception &e)
	{
		return false;
	}
	return false;
}


bool AdvantechOutput::SetOutput(bool value)
{
	return SetOutput(PortID, PinNo, value);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool AdvantechInput::Initialize()
{
	try
	{
		if (!IsInitialized)
		{
			wchar_t text_wchar[30];
			size_t length;
			mbstowcs_s(&length, text_wchar, Description.c_str(), Description.length());

			devInfo = new DeviceInformation(text_wchar);
			inputControl->setSelectedDevice(*devInfo);
			IsInitialized = inputControl->getInitialized();
		}
	}
	catch (exception &e)
	{
		return false;
	}
	return true;
}

bool AdvantechInput::Start()
{
	IsRunning = true;
	return IsInitialized;
}

bool AdvantechInput::Stop()
{
	IsRunning = false;
	return IsInitialized;
}

//bool AdvantechInput::ReadInputAsBinary(int portID, bool pinData[], byte data)
//{
//	if (!IsInitialized)
//	{
//		if (!Initialize())
//		{
//			return false;
//		}
//	}
//	try
//	{
//		ErrorCode error = inputControl->Read(portID, data);
//		if (error == Success)
//		{
//			//pinData = Convert.ToString(data, 2).PadLeft(8, '0').Select(c = > c == '1').ToArray();
//			return true;
//		}
//	}
//	catch (exception &e)
//	{
//		return false;
//	}
//	return false;
//}

bool AdvantechInput::ReadInputAsByte(int portID, byte data)
{
	if (!IsInitialized)
	{
		if (!Initialize())
		{
			return false;
		}
	}
	try
	{
		ErrorCode error = inputControl->Read(portID, data);
		if (error == Success) return true;
	}
	catch (exception &e)
	{
		return false;
	}
	return false;
}

bool AdvantechInput::ReadInputAsByte(int portID, int startPin, int count, byte data)
{
	if (!IsInitialized)
	{
		if (!Initialize())
		{
			return false;
		}
	}
	try
	{
		ErrorCode error = inputControl->Read(portID, data);
		if (error == Success)
		{
			if (startPin + count > 8) count = 8 - startPin;
			data = (byte)(data << (startPin));
			data = (byte)(data >> (8 - count));
			return true;
		}
	}
	catch (exception &e)
	{
		return false;
	}
	return false;
}

bool AdvantechInput::ReadPin(int portID, int pinID)
{
	if (!IsInitialized) if (!Initialize()) return false;

	try
	{
		byte data;
		ErrorCode error = inputControl->ReadBit(portID, pinID, &data);
		if (error == Success) return data == 1;
	}
	catch (exception &e)
	{
		return false;
	}
	return false;
}

bool AdvantechInput::ReadPin()
{
	return ReadPin(PortID, PinNo);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool AdvantechInterrupt::Initialize()
{
	try
	{
		if (!IsInitialized)
		{
			wchar_t text_wchar[30];
			size_t length;
			mbstowcs_s(&length, text_wchar, Description.c_str(), Description.length());

			devInfo = new DeviceInformation(text_wchar);
			inputControl->setSelectedDevice(*devInfo);
			inputControl->addInterruptListener(*interrupt);
			interruptChans = inputControl->getDiintChannels();
			if (interruptChans == NULL)
			{
				//"Interrupt functionality not availablle in the card"
				return 0;
			}
			interruptChans->getItem(PortID).setEnabled(true);
			interruptChans->getItem(PortID).setTrigEdge((ActiveSignal)interruptMode);
			IsInitialized = true;
		}
	}
	catch (exception &e)
	{
		return false;
	}
	return true;
}

bool AdvantechInterrupt::setInterruptMode(ActiveSignal _interruptMode)
{
	if (IsInitialized)
	{
		interruptChans->getItem(PortID).setTrigEdge((ActiveSignal)_interruptMode);
		interruptMode = _interruptMode;
		return true;
	}
	return false;
}

bool AdvantechInterrupt::Start()
{
	if (!IsInitialized)
		if (!Initialize())
			return false;
	IsRunning = false;
	if (inputControl->getInitialized())
	{
		try
		{
			ErrorCode status = inputControl->SnapStart();
			if (status == Success)
			{
				IsRunning = true;
				return IsRunning;
			}
			return IsRunning;
		}
		catch (exception &e)
		{
			return IsRunning;
		}
	}
	return IsRunning;
}

bool AdvantechInterrupt::Stop()
{
	if (IsInitialized && inputControl->getInitialized())
	{
		try
		{
			IsRunning = false;
			ErrorCode status = inputControl->SnapStop();
			if (status == Success)
			{
				return true;
			}
			return false;
		}
		catch (exception &e)
		{
			return false;
		}
	}
	return false;
}

//bool AdvantechInterrupt::ReadInputAsBinary(int portID, bool pinData[], byte data)
//{
//	if (!IsInitialized)
//	{
//		if (!Initialize())
//		{
//			return false;
//		}
//	}
//	try
//	{
//		ErrorCode error = inputControl->Read(portID, data);
//		if (error == Success)
//		{
//			//pinData = Convert.ToString(data, 2).PadLeft(8, '0').Select(c = > c == '1').ToArray();
//			return true;
//		}
//		//OnErrorOccured(new MessageEventArgs(4, "Input Read Error", error.ToString(), MessageType.Error));
//	}
//	catch (exception &e)
//	{
//		//OnErrorOccured(new MessageEventArgs(4, "Input Read Error", e));
//		//data = new byte();
//		return false;
//	}
//	return false;
//}

bool AdvantechInterrupt::ReadInputAsByte(int portID, byte data)
{
	if (!IsInitialized)
	{
		if (!Initialize())
		{
			return false;
		}
	}
	try
	{
		ErrorCode error = inputControl->Read(portID, data);
		if (error == Success) return true;
	}
	catch (exception &e)
	{
		return false;
	}
	return false;
}

bool AdvantechInterrupt::ReadInputAsByte(int portID, int startPin, int count, byte data)
{
	if (!IsInitialized)
	{
		if (!Initialize())
		{
			return false;
		}
	}
	try
	{
		ErrorCode error = inputControl->Read(portID, data);
		if (error == Success)
		{
			if (startPin + count > 8) count = 8 - startPin;
			data = (byte)(data << (startPin));
			data = (byte)(data >> (8 - count));
			return true;
		}
	}
	catch (exception &e)
	{
		return false;
	}
	return false;
}

bool AdvantechInterrupt::ReadPin(int portID, int pinID)
{
	if (!IsInitialized) if (!Initialize()) return false;

	try
	{
		byte data;
		ErrorCode error = inputControl->ReadBit(portID, pinID, &data);
		if (error == Success) return data == 1;
	}
	catch (exception &e)
	{
		return false;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void AdvantechClock::SetDetails(string _description, int _channel)
{
	Description = _description;
	channel = _channel;
}


bool AdvantechClock::Initialize()
{
	try
	{
		if (!IsInitialized)
		{

			wchar_t text_wchar[30];
			size_t length;
			mbstowcs_s(&length, text_wchar, Description.c_str(), Description.length());

			devInfo = new DeviceInformation(text_wchar);
			eventCounterControl->setSelectedDevice(*devInfo);

			SetChannel(channel);
			IsInitialized = true;
		}
	}
	catch (exception &e)
	{
		return false;
	}
	return true;
}

bool AdvantechClock::Start()
{
	eventCounterControl->setEnabled(true);
	IsRunning = true;
	return IsRunning;
}

bool AdvantechClock::Stop()
{
	eventCounterControl->setEnabled(false);
	IsRunning = false;
	return IsRunning;
}

long AdvantechClock::GetClockValue()
{
	if (!IsInitialized)
	{
		if (!Initialize())
		{
			return -1;
		}
	}
	try
	{
		return eventCounterControl->getValue();
	}
	catch (exception &e)
	{
		return -1;
	}
	return -1;
}


bool AdvantechClock::SetChannel(int _channel)
{
	channel = _channel;
	eventCounterControl->setChannel(channel);
	return 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool AdvantechStatusChangeInterrupt::Initialize()
{
	try
	{
		if (!IsInitialized)
		{
			wchar_t text_wchar[30];
			size_t length;
			mbstowcs_s(&length, text_wchar, Description.c_str(), Description.length());

			devInfo = new DeviceInformation(text_wchar);
			inputControl->setSelectedDevice(*devInfo);
			statusChangeChans = inputControl->getDiCosintPorts();
			if (statusChangeChans == NULL)
			{
				//"Status Change functionality not availablle in the card"
				return false;
			}			
			statusChangeChans->getItem(PortID).setMask(0xFF);
			IsInitialized = true;

			inputControl->addChangeOfStateListener(*statusChange);
		}
	}
	catch (exception *e)
	{
		return false;
	}
	return true;
}

bool AdvantechStatusChangeInterrupt::ReadInputAsByte(int portID, byte data)
{
	if (!IsInitialized)
	{
		if (!Initialize())
		{
			return false;
		}
	}
	try
	{
		ErrorCode error = inputControl->Read(portID, data);
		if (error == Success) return true;
	}
	catch (exception *e)
	{
		return false;
	}
	return false;
}

bool AdvantechStatusChangeInterrupt::ReadInputAsByte(int portID, int startPin, int count, byte data)
{
	if (!IsInitialized)
	{
		if (!Initialize())
		{
			return false;
		}
	}
	try
	{
		ErrorCode error = inputControl->Read(portID, data);
		if (error == Success)
		{
			if (startPin + count > 8) count = 8 - startPin;
			data = (byte)(data << (startPin));
			data = (byte)(data >> (8 - count));
			return true;
		}
	}
	catch (exception *e)
	{
		return false;
	}
	return false;
}

bool AdvantechStatusChangeInterrupt::ReadPin(int portID, int pinID)
{
	if (!IsInitialized) if (!Initialize()) return false;

	try
	{
		byte data;
		ErrorCode error = inputControl->ReadBit(portID, pinID, &data);
		if (error == Success) return data == 1;
	}
	catch (exception *e)
	{
		return false;
	}
	return false;
}


bool AdvantechStatusChangeInterrupt::ReadPin()
{
	return ReadPin(PortID, PinNo);
}

bool AdvantechStatusChangeInterrupt::Start()
{
	if (!IsInitialized) if (!Initialize()) return false;
	if (inputControl->getInitialized())
	{
		try
		{
			ErrorCode error = inputControl->SnapStart();
			if (error == Success)
			{
				try { isHigh = ReadPin(PortID, PinNo); }
				catch(exception *e)
				{
					//ignored
				}
				IsRunning = true;
				return true;
			}
			return false;
		}
		catch (exception *e)
		{
			return false;
		}
	}
	return false;
}

bool AdvantechStatusChangeInterrupt::Stop()
{
	if (IsInitialized && inputControl->getInitialized())
	{
		try
		{
			IsRunning = false;
			ErrorCode error = inputControl->SnapStop();
			if (error == Success) return true;
			return false;
		}
		catch (exception e)
		{
			return false;
		}
	}
	return false;
}

//void AdvantechStatusChangeInterrupt::InputControlOnInterrupt(void *sender, DiSnapEventArgs diSnapEventArgs)
//{
//	byte b = diSnapEventArgs.PortData[PortID];
//	byte result = (byte)(b & signalValue);
//	setIsHighFlag(result != 0);
//}

int AdvantechStatusChangeInterrupt::setPinNo(int _pinNo)
{
	signalValue = _pinNo < 0 ? 255 : (byte)pow(2, _pinNo);
	PinNo = _pinNo;
	return true;
}

bool AdvantechStatusChangeInterrupt::setIsHighFlag(bool _ishigh)
{
	if (isHigh == _ishigh) return true;
	isHigh = _ishigh;
	if (((InterruptMode == RisingEdge || InterruptMode == BothEdge)
		&& isHigh) || ((InterruptMode == FallingEdge || InterruptMode == BothEdge)
			&& !isHigh))
	{
		for (auto &e : interruptHandler)
		{
			e->OnInterruptReceived();
		}
	}
	return true;
}
