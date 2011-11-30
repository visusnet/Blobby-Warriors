#ifndef IWEARABLE_H
#define IWEARABLE_H

class IWearable
{
	public:
	IWearable();
	void setCarrierIsDucking(bool carrierIsDucking);
	void setCarrierViewingDirection(int carrierViewingDirection);

	protected:
	bool carrierIsDucking;
	int carrierViewingDirection;
};

#endif