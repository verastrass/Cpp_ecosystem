#pragma once

#include <fstream>
#include <vector>
#include <string>
#include "Animal.h"

using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::endl;


class ReadWrite {
	string inputfilename;
	string outputfilename;

public:
	ReadWrite() {}
	ReadWrite(string inputfilename, string outputfilename): inputfilename(inputfilename), outputfilename(outputfilename) {}
	
	void read(int& D, int& DS, int& S, int& SS, int& F, int& FS, int& H, int& HS, int& N, vector<Animal*> &animals);
	
	
	void write(int const & D, int const & DS, int const & S, int const & SS, int const & F, int const & FS, int const & H, int const & HS, int const & N, vector<Animal*> const &animals);
};
