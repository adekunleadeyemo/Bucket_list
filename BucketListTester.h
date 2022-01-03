#ifndef BUCKETLISTTESTER_H_
#define BUCKETLISTTESTER_H_

#include <string>
#include "BucketList.h"

class BucketListTester {
public:
	BucketListTester();

	// getsize and getcap req'd throughout

	// ctor
	void testa();

	// mash
	void testb();

	// insert
	void testc();
	void testd();
	void teste();
	void testf();

	// toString
	void testg();
	void testh();
	void testi();
	void testj();

	// remove
	void testk();
	void testl();
	void testm();
	void testn();
	void testo();

	// copy con, asg
	void testp();
	void testq();
	void testr();
	void tests();
	void testt();

	// resize
	void testu();
	void testv();
	void testw();
	void testx();
	void testy();

	// unused
	void testz();

private:

	// three overloaded versions
	void errorOut_(const std::string& errMsg, unsigned int errBit);
	void errorOut_(const std::string& errMsg, const std::string& errRes, unsigned int errBit);
	void errorOut_(const std::string& errMsg, int errRes, unsigned int errBit);
	void passOut_();

	char error_;
	std::string funcname_;
};

#endif /* BUCKETLISTTESTER_H_ */
