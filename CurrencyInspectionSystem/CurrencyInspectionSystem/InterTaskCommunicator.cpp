#include "stdafx.h"
#include "InterTaskCommunicator.h"


InterTaskCommunicator::InterTaskCommunicator()
{
	InitializeCriticalSection(&lcMutex);
	InitializeCriticalSection(&ldMutex);
	InitializeCriticalSection(&lmMutex);
	InitializeCriticalSection(&tpMutex);
	InitializeCriticalSection(&rtMutex);
}


InterTaskCommunicator::~InterTaskCommunicator()
{
	DeleteCriticalSection(&lcMutex);
	DeleteCriticalSection(&ldMutex);
	DeleteCriticalSection(&lmMutex);
	DeleteCriticalSection(&tpMutex);
	DeleteCriticalSection(&rtMutex);
}

void InterTaskCommunicator::UnRegisterAllEvents()
{
	layerDiffImageResultEvents.clear();
	maskResultEvents.clear();
	tiePointResultEvents.clear();
	resetTransferDataBufferNotificationReceiversList.clear();
}

#pragma region Layer CompositeImage Result communication methods
void InterTaskCommunicator::OnLayerCompositeImageResult(UINT _layerId, ULONG _imageNumber, int _inspectionResult, const HImage &_layerCompositeImageReult)
{
	for (std::list<LayerCompositeImageResultEventMap>::iterator iter = layerCompositeImageResultEvents.begin(); iter != layerCompositeImageResultEvents.end(); iter++)
	{
		if (iter->inspectionItemId == _layerId)
		{
			(iter->eventHandler)->OnLayerCompositeImageResult(_layerId, _imageNumber, _inspectionResult, _layerCompositeImageReult);
		}
	}
}

bool InterTaskCommunicator::RegisterForLayerCompositeImageResult(UINT _inspectionItemID, iLayerCompositeImageResultReceiver *_eventHandler)
{
	LayerCompositeImageResultEventMap eventMap(_inspectionItemID, _eventHandler);
	layerCompositeImageResultEvents.push_back(eventMap);
	return TRUE;
}

void InterTaskCommunicator::SendLayerCompositeImageResult(UINT _inspectionItemID, ULONG _imageNumber, int _inspectionResult, HImage &_layerCompositeImage)
{
	EnterCriticalSection(&lcMutex);
	OnLayerCompositeImageResult(_inspectionItemID, _imageNumber, _inspectionResult, _layerCompositeImage);
	LeaveCriticalSection(&lcMutex);
}
#pragma endregion

#pragma region Layer DiffImage Result communication methods
void InterTaskCommunicator::OnLayerDifferenceImageResult(UINT _layerId, ULONG _imageNumber, int _inspectionResult, const HImage &_layerDiffImageReult, const HRegion &_statisticsRegion, const HRegion &_layerRegion)
{
	for (std::list<LayerDifferenceImageResultEventMap>::iterator iter = layerDiffImageResultEvents.begin();	iter != layerDiffImageResultEvents.end(); iter++)
	{
		if (iter->inspectionItemId == _layerId)
		{
			(iter->eventHandler)->OnLayerDifferenceImageResult(_layerId, _imageNumber, _inspectionResult, _layerDiffImageReult, _statisticsRegion, _layerRegion);
		}
	}
}

bool InterTaskCommunicator::RegisterForLayerDiffImageResult(UINT _inspectionItemID, iLayerDifferenceImageResultReceiver *_eventHandler)
{
	LayerDifferenceImageResultEventMap eventMap(_inspectionItemID, _eventHandler);
	layerDiffImageResultEvents.push_back(eventMap);
	return TRUE;
}

void InterTaskCommunicator::SendLayerDiffImageResult(UINT _inspectionItemID, ULONG _imageNumber, int _inspectionResult, HImage &_layerDiffImage, HRegion &_statisticsRegion, HRegion &_layerRegion)
{
	EnterCriticalSection(&ldMutex);
	OnLayerDifferenceImageResult(_inspectionItemID, _imageNumber, _inspectionResult, _layerDiffImage, _statisticsRegion, _layerRegion);
	LeaveCriticalSection(&ldMutex);
}
#pragma endregion

#pragma region Mask Result communication methods
void InterTaskCommunicator::OnMaskReceived(UINT _layerId, ULONG _imageNumber, int _inspectionResult, const HRegion &_maskRegion)
{
	for (std::list<MaksEventMap>::iterator iter = maskResultEvents.begin(); iter != maskResultEvents.end(); iter++)
	{
		if (iter->inspectionItemId == _layerId)
		{
			(iter->eventHandler)->OnMaskReceived(_layerId, _imageNumber, _inspectionResult, _maskRegion);
		}
	}
}

bool InterTaskCommunicator::RegisterForMaskResult(UINT _inspectionItemID, iMaskReceiver *_eventHandler)
{
	MaksEventMap eventMap(_inspectionItemID, _eventHandler);
	maskResultEvents.push_back(eventMap);
	return TRUE;
}

void InterTaskCommunicator::SendMaskResult(UINT _layerId, ULONG _imageNumber, int _inspectionResult, HRegion &_maskRegion)
{
	EnterCriticalSection(&lmMutex);
	OnMaskReceived(_layerId, _imageNumber, _inspectionResult, _maskRegion);
	LeaveCriticalSection(&lmMutex);
}
#pragma endregion

#pragma region TiePoint Result communication methods
void InterTaskCommunicator::SendTiePointResult(UINT transferDataID, ULONG imageNumber, int inspectionResult, SearchType _searchType,
	HTuple rowPosition,	HTuple columnPosition, HTuple anglePosition)
{
	EnterCriticalSection(&tpMutex);
	OnTiePointResult(transferDataID, imageNumber, inspectionResult, _searchType,
		rowPosition, columnPosition, anglePosition);
	LeaveCriticalSection(&tpMutex);
}
bool InterTaskCommunicator::RegisterForTiePointResult(UINT _inspectionItemID, iTiePointResultReceiver *_eventHandler)
{
	TiePointResultEventMap eventMap(_inspectionItemID, _eventHandler);
	tiePointResultEvents.push_back(eventMap);
	return TRUE;
}
void InterTaskCommunicator::OnTiePointResult(UINT _transferDataID, ULONG _imageNumber, int _inspectionResult, SearchType _searchType,
	HTuple _rowPosition, HTuple _columnPosition, HTuple _anglePosition)
{
	for(auto &e:tiePointResultEvents)
	{
		if (e.inspectionItemId == _transferDataID)
		{
			(e.eventHandler)->OnTiePointResult(_transferDataID, _imageNumber, _inspectionResult, _searchType,
				_rowPosition, _columnPosition, _anglePosition);
		}
	}

}
#pragma endregion

#pragma region TiePoint Result communication methods
bool InterTaskCommunicator::RegisterForResetTransferDataBufferNotification(iResetTransferDataNotificationReceiver *_eventHandler)
{
	resetTransferDataBufferNotificationReceiversList.push_back(_eventHandler);
	return true;
}
void InterTaskCommunicator::SendResetTransferDataBufferNotification()
{
	EnterCriticalSection(&rtMutex);
	OnResetTransferDataBufferNotificationReceived();
	LeaveCriticalSection(&rtMutex);
}

void InterTaskCommunicator::OnResetTransferDataBufferNotificationReceived()
{
	for (std::list<iResetTransferDataNotificationReceiver *>::iterator iter = resetTransferDataBufferNotificationReceiversList.begin();
	iter != resetTransferDataBufferNotificationReceiversList.end();
		iter++)
	{
		(*iter)->OnResetTransferDataBufferNotificationReceived();
	}
}
#pragma endregion
