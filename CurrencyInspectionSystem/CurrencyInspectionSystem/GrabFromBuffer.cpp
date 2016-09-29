#include "stdafx.h"
#include "GrabFromBuffer.h"

IMPLEMENT_DYNCREATE(GrabFromBuffer, ImageGrabber)

GrabFromBuffer::GrabFromBuffer()
{
}


GrabFromBuffer::~GrabFromBuffer()
{
}

#pragma region inline functions
bool GrabFromBuffer::SetImageSource(UINT _cameraID, std::list<HImage> _buffer)
{
	return true;
}

bool GrabFromBuffer::RestartGrab()
{
	return true;
}

BOOL GrabFromBuffer::InitInstance()
{
	return TRUE;
}

int GrabFromBuffer::Run()
{
	return 1;
}
#pragma endregion