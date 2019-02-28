#pragma once

#include <vector>
#include <string>
#include "Animal.h"
#include "Event.h"
#include "ReadWrite.h"


using std::vector;
using std::string;


class Model {
	string input, output;
	int N, D, DS, S, SS, F, FS, H, HS;
	int lowerBorder = 0;
	int upperBorder = 1000000;
	vector<Animal*> animals;
	vector<Event*> events;
	ReadWrite readWrite;



	void fillInTheFields() {
		readWrite.read(D, DS, S, SS, F, FS, H, HS, N, animals);
	}


	void displacement() {
		for (auto it = animals.begin(); it != animals.end(); ++it)
			(*it)->move();
	}

	
	void analysis(int const &i);


	void deleteAnimals();


	bool execution();


public:
	Model(string input, string output): readWrite(input, output) {
		N = D = DS = S = SS = F = FS = H = HS = 0;
	}
	
	void run();
};
