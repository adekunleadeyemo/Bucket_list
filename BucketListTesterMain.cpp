#include <iostream>
#include "BucketListTester.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {

	for(int i=1; i<argc; i++) {
		switch (argv[i][0]) {
		case 'a': { BucketListTester t; t.testa(); } break;
		case 'b': { BucketListTester t; t.testb(); } break;
		case 'c': { BucketListTester t; t.testc(); } break;
		case 'd': { BucketListTester t; t.testd(); } break;
		case 'e': { BucketListTester t; t.teste(); } break;
		case 'f': { BucketListTester t; t.testf(); } break;
		case 'g': { BucketListTester t; t.testg(); } break;
		case 'h': { BucketListTester t; t.testh(); } break;
		case 'i': { BucketListTester t; t.testi(); } break;
		case 'j': { BucketListTester t; t.testj(); } break;
		case 'k': { BucketListTester t; t.testk(); } break;
		case 'l': { BucketListTester t; t.testl(); } break;
		case 'm': { BucketListTester t; t.testm(); } break;
		case 'n': { BucketListTester t; t.testn(); } break;
		case 'o': { BucketListTester t; t.testo(); } break;
		case 'p': { BucketListTester t; t.testp(); } break;
		case 'q': { BucketListTester t; t.testq(); } break;
		case 'r': { BucketListTester t; t.testr(); } break;
		case 's': { BucketListTester t; t.tests(); } break;
		case 't': { BucketListTester t; t.testt(); } break;
		case 'u': { BucketListTester t; t.testu(); } break;
		case 'v': { BucketListTester t; t.testv(); } break;
		case 'w': { BucketListTester t; t.testw(); } break;
		case 'x': { BucketListTester t; t.testx(); } break;
		case 'y': { BucketListTester t; t.testy(); } break;
		case 'z': { BucketListTester t; t.testz(); } break;
		default: { cout << "Options are a -- y." << endl; } break;
	       	}
	}
	return 0;
}

