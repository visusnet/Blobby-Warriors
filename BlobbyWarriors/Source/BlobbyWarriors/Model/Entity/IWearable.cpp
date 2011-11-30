#include "IWearable.h"

IWearable::IWearable()
{
}

void IWearable::setCarrierIsDucking(bool carrierIsDucking)
{
	this->carrierIsDucking = carrierIsDucking;
}

void IWearable::setCarrierViewingDirection(int setCarrierViewingDirection)
{
	this->carrierViewingDirection = setCarrierViewingDirection;
}