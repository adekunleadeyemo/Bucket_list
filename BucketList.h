#ifndef BUCKETLIST_H_
#define BUCKETLIST_H_

#include <string>
using std::string;

class Node {
	// Data members. Do not change them
	string s_; // string stored in this node
	Node* next_; // pointer to next node in the list
    

	// even constructors are private!
	// so only BucketList can access them
	Node();
	~Node();

	// You can add other member functions if you want

friend class BucketList; // allow BucketList to access private members
};

class BucketList {

public:
	// Constructor. Constructs an empty BucketList with initial capacity
	// INITIAL_CAP with no contents.
	BucketList();

	// Destructor. Deallocate all memory used.
	~BucketList();

	// Copy constructor.
	BucketList(const BucketList& other);

	// Copy assignment operator.
	BucketList& operator=(const BucketList& other);

	// Return true if the string s is in the BucketList, false otherwise.
	bool contains(const string& s) const;

	// Insert the string s into the BucketList.
	// If s is already in the BucketList, do not change anything.
	// If the bucket is going to contain more than one string
	// (i.e. the list has more than one node), they should be ordered
	// alphabetically (i.e. based on how C++ compares strings)
	// If the load factor is going to be exceeded after the insertion
	// (i.e. number of strings / capacity of container > MAX_LOAD_FACTOR),
	// double the capacity of the container first before the insertion.
	// See the assignment webpage for details on doubling.
	void insert(const string& s);

	// Remove the string s from the BucketList.
	// If s is not in the BucketList, do not change anything.
	void remove(const string& s);

	// Return a string representation of the BucketList, as described
	// in the assignment webpage.
	// Note that it does not actually print anything to the screen.
	// To pass the test cases you must make sure that even the
	// white spaces are correct. In particular,
	// there should be no space character after the number if no string is in 
	// that bucket; no space character after the last string of a bucket;
	// and no newline character after the last line.
	string toString() const;

	// The mash function that converts the string s to an integer.
	// This really shouldn't be public, but it is for the purpose of
	// testing.
	int h(const string& s) const;

	// Return the number of strings currently stored in the BucketList.
	int getSize() const;

	// Return the capacity (i.e. size of the array, or number of buckets)
	// of the BucketList.
	int getCap() const;
    
	// i introduced this function
	void reSize();
	// we didn't explain what static and constexpr are, but you can just
	// use them like normal constants in BucketList.cpp
	static constexpr int INITIAL_CAP = 10; // initial capacity
	static constexpr double MAX_LOAD_FACTOR = 0.7; // maximum load factor
	
	

private:

	Node** buckets_; // pointer to an array of Node*

	// You can add any other private member variables or functions
	// if you want
	int cap_; //this is created to hold the current capacity
	int size_; // this calculates the number of strings in the bucket list

};

#endif /* BUCKETLIST_H_ */
