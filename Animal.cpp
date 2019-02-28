#include "Animal.h"

const vector<AnimalId> Animal::AnimalRation[4] = { {}, { DID, FID }, { DID }, { FID } };

void Animal::move() {
	if (!z && (vz < 0))
		toProjectSpeedVector();

	int x1 = x + vx;
	int y1 = y + vy;
	int z1 = z + vz;

	//under ground
	if (z1 < 0)
	{
		x1 = x - vx * z / vz;
		y1 = y - vy * z / vz;
		z1 = 0;
	}

	x = x1;
	y = y1;
	z = z1;
}


void Animal::changeDir(Animal& somebody) {
	double lambdaSqr = (double)speedModSqr / distanceSqr(somebody);
	double lambda = sqrt(lambdaSqr);

	if (victimFlag)
		lambda *= -1;

	vx = (int)trunc(lambda*(somebody.x - x));
	vy = (int)trunc(lambda*(somebody.y - y));
	vz = (int)trunc(lambda*(somebody.z - z));
	
	//z = 0 -> z != 0
	if ( (z == 0) && (vz != 0) )
		if ((id == FID) || (id == HID) || (((id == DID) || (id == SID)) && (vz < 0)))
			toProjectSpeedVector();
}
	