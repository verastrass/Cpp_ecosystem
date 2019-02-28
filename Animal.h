#pragma once

#include <cmath>
#include <vector>
#include <algorithm>

using std::sqrt;
using std::trunc;
using std::vector;
using std::min_element;

enum AnimalVoracity {DVOR = 0, SVOR = 1, FVOR = 3, HVOR = 1}; 
enum AnimalId {DID, SID, FID, HID};


class ReadWrite;

class Animal {
	int x, y, z;
	int vx, vy, vz;
	int sensitivity;
	AnimalVoracity voracity;
	friend ReadWrite;
	long long speedModSqr;
	static const vector<AnimalId> AnimalRation[4];
	

	bool cmpDistSqr(Animal& a, Animal& b) {
		return (distanceSqr(a) < distanceSqr(b));
	}
	

	void toProjectSpeedVector() {
		double lambdaSqr = speedModSqr / (double)(vx*vx + vy*vy);
		double lambda = sqrt(lambdaSqr);
		vx = (int)trunc(lambda*vx);
		vy = (int)trunc(lambda*vy);
		vz = 0;
	}

	
public:
	vector<Animal*>::iterator victim;
	AnimalId id;
	bool deleteFlag = false;
	bool victimFlag = false;
	bool predatorFlag = false;
	
	
	Animal(int x, int y, int z, int vx, int vy, int vz, int sensitivity, AnimalVoracity voracity, AnimalId id) :
		x(x), y(y), z(z), vx(vx), vy(vy), vz(vz), sensitivity(sensitivity), voracity(voracity), id(id), speedModSqr(vx*vx + vy*vy + vz*vz) {}
	
	
	bool isOutsideTheSimulation(int const & lBorder, int const & uBorder) {
		return ((x < lBorder) || (y < lBorder) || (z < lBorder) || (x > uBorder) || (y > uBorder) || (z > uBorder));
	}
	
	
	long long distanceSqr(Animal& somebody) {
		long long xx = x - somebody.x;
		long long yy = y - somebody.y;
		long long zz = z - somebody.z;
		return (xx*xx + yy*yy + zz*zz);
	}


	bool isInVoracityZone(Animal& somebody) {
		return (distanceSqr(somebody) <= (long long)voracity*voracity);
	}


	bool canEat(Animal& somebody) {
		for (auto it = AnimalRation[(int)id].begin(); it != AnimalRation[(int)id].end(); ++it)
			if (*it == somebody.id)
				return true;
		return false;
	}


	bool hasInSight(Animal& somebody) {
		return ( (distanceSqr(somebody) > 0) && (distanceSqr(somebody) <= (long long)sensitivity*sensitivity) );
	}
	
	
	vector<vector<Animal*>::iterator>::iterator whoIsCloser(vector<vector<Animal*>::iterator> &animals) {
		auto it = min_element(animals.begin(), animals.end(), [this](vector<Animal*>::iterator a, vector<Animal*>::iterator b){ return this->cmpDistSqr(**a, **b); });
		return it;
	}


	void move();


	void changeDir(Animal& somebody);
};



class Dragonfly:public Animal {
public:
	Dragonfly(int x, int y, int z, int vx, int vy, int vz, int sensitivity) :
		Animal(x, y, z, vx, vy, vz, sensitivity, DVOR, DID) {}
};


class Stork:public Animal {
public:
	Stork(int x, int y, int z, int vx, int vy, int vz, int sensitivity) : 
		Animal(x, y, z, vx, vy, vz, sensitivity, SVOR, SID) {}
};


class Frog:public Animal {
public:
	Frog(int x, int y, int vx, int vy, int sensitivity) :
		Animal(x, y, 0, vx, vy, 0, sensitivity, FVOR, FID) {}
};


class Hedgehog:public Animal {
public:
	Hedgehog(int x, int y, int vx, int vy, int sensitivity) :
		Animal(x, y, 0, vx, vy, 0, sensitivity, HVOR, HID) {}
};