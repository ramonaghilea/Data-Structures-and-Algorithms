#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

int main(){
    testAll();
	testAllExtended();

	testFilter1();
	testFilter2();

    std::cout<<"Finished SMM Tests!"<<std::endl;
	system("pause");
}
