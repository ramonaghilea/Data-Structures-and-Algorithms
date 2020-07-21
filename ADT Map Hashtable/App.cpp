#include "ExtendedTest.h"
#include "ShortTest.h"

#include "Map.h"


#include <iostream>
using namespace std;


int main() {

	testIteratorPrev();
	testIteratorPrev2();
	testAll();
	testAllExtended();

	cout << "That's all!" << endl;
	system("pause");
	return 0;
}


