#include "Model.h"

const string inputFileName = "input.txt";
const string outputFileName = "output.txt";

int main() {
	Model m(inputFileName, outputFileName);
	m.run();
	return EXIT_SUCCESS;
}