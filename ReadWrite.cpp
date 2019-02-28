#include "ReadWrite.h"

void ReadWrite::read(int& D, int& DS, int& S, int& SS, int& F, int& FS, int& H, int& HS, int& N, vector<Animal*> &animals) {
	ifstream fin;
	fin.open(inputfilename, ifstream::in);
	
	fin >> D >> DS >> S >> SS >> F >> FS >> H >> HS >> N;
	
	for (int i = 0; i < D; ++i)
	{
		int x, y, z, vx, vy, vz;
		fin >> x >> y >> z >> vx >> vy >> vz;
		animals.push_back(new Dragonfly(x, y, z, vx, vy, vz, DS));
	}
	
	for (int i = 0; i < S; ++i)
	{
		int x, y, z, vx, vy, vz;
		fin >> x >> y >> z >> vx >> vy >> vz;
		animals.push_back(new Stork(x, y, z, vx, vy, vz, SS));
	}
	
	for (int i = 0; i < F; ++i)
	{
		int x, y, vx, vy;
		fin >> x >> y >> vx >> vy;
		animals.push_back(new Frog(x, y, vx, vy, FS));
	}
	
	for (int i = 0; i < H; ++i)
	{
		int x, y, vx, vy;
		fin >> x >> y >> vx >> vy;
		animals.push_back(new Hedgehog(x, y, vx, vy, HS));
	}

	fin.close();
}



void ReadWrite::write(int const & D, int const & DS, int const & S, int const & SS, int const & F, int const & FS, int const & H, int const & HS, int const & N, vector<Animal*> const &animals) {
	ofstream fout;
	fout.open(outputfilename, ofstream::out);
	
	fout << D << " " << DS << " " << S << " " << SS << " " << F << " " << FS << " " << H << " " << HS << " " << N << endl;


	for (auto it = animals.begin(); it != (animals.begin() + D + S); ++it)
		fout << (*it)->x << " " << (*it)->y << " " << (*it)->z << " " << (*it)->vx << " " << (*it)->vy << " " << (*it)->vz << endl;
	
	
	for (auto it = (animals.begin() + D + S); it != animals.end(); ++it)
		fout << (*it)->x << " " << (*it)->y << " " << (*it)->vx << " " << (*it)->vy << endl;
	
	fout.close();
}
