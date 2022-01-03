#include <iostream>
#include "BucketList.h"

using namespace std;

int main() {

	BucketList t;
	t.insert("a");
	t.insert("cac");
	t.insert("abc");

	cout << t.contains("a") << endl;
	cout << t.contains("abc") << endl;
	cout << t.contains("cac") << endl;
	cout << t.contains("d") << endl << endl;

	cout << t.toString() << endl << endl;

	t.remove("a");
	cout << t.toString() << endl << endl;

	t.remove("abc");
	cout << t.toString() << endl << endl;

	BucketList t2;
	t2 = t;
	cout << t2.toString() << endl;

}

