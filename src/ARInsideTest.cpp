#include "ARInsideTest.h"
#include <iostream>

char* argv_0;

int main(int argc, char* argv[])
{
	// safe it, so we can use it in tests
	argv_0 = argv[0];

	testing::InitGoogleTest(&argc, argv); 
	return RUN_ALL_TESTS();
}
