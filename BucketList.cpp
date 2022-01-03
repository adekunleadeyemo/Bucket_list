#include "BucketList.h"

Node::Node() {
	// IMPLEMENT ME
	// initializing Node Constructor

	s_ = "";
	next_ = nullptr;	
}

Node::~Node() {
	// IMPLEMENT ME

}

BucketList::BucketList() {
	// IMPLEMENT ME
	//initialize BucketList Constructor
	
	cap_ = INITIAL_CAP;
	size_ = 0;
	buckets_ = new Node* [cap_]();
}

BucketList::~BucketList() {
	// IMPLEMENT ME
		for(int i = 0; i < cap_; i++){
		Node* temp = buckets_[i];
		while(temp != nullptr){
			Node* tempNext = temp->next_;
			delete temp; 					
			temp = tempNext;
		} 
	}
	delete [] buckets_;
}
		    
BucketList::BucketList(const BucketList& other) {
	// IMPLEMENT ME
	//Create a memory new bucket for buckets 
	
	buckets_ = new Node*[other.getCap()]();
	
	//initialize copy previous copy constructor primitive type values
	cap_ = other.getCap();
	size_ = 0;
	
	//loop through previous bucketlist and insert strings in new bucket list
	for(int i = 0; i<cap_; i++){
		Node* temp = other.buckets_[i];
		while(temp != nullptr){
			insert(temp->s_);
			temp = temp->next_;
		} 
	}
}
	
BucketList& BucketList::operator=(const BucketList& other) {
	// IMPLEMENT ME
	//check if previous bucket is the same as the new bucket
	if(&other != this){
	
		//delete all nodes in previous bucket list	
		for(int i = 0; i<cap_; i++){
			Node* temp = other.buckets_[i];
			while(temp != nullptr){
				remove(temp->s_);
				temp = temp->next_;
			} 
		}	
		
		//copy strings in  previous bucketlist to new bucketlist	
		buckets_ = new Node*[other.getCap()]();
		cap_ = other.getCap();
		size_ = 0;
		for(int i = 0; i<cap_; i++){
			Node* temp = other.buckets_[i];
			while(temp != nullptr){
				insert(temp->s_);
				temp = temp->next_;
			} 
		}
	}
	return *this;
}

void BucketList::reSize(){
	//create new temp to store the address of previous bucketlist 
	Node** temp_bucket = buckets_;
	
	//create new bucket with double cap of previous bucket	
	buckets_ = new Node*[cap_*2]();
	
	//set cap and intialize size to get ready for insert	
	size_ = 0;
	cap_ = cap_ * 2;
	
	//insert string according to new mash value in new bucketlist	
	for(int i = 0; i < cap_/2; i++){
		Node* temp2 = temp_bucket[i];
		while(temp2 != nullptr){
			insert(temp2->s_);
			temp2 = temp2->next_;
		} 
	}
	
	//delete all strings in previous bucket		
	for(int i = 0; i < cap_/2; i++){
		Node* temp = temp_bucket[i];
		while(temp != nullptr){
			Node* tempNext = temp->next_;
			delete temp; 					
			temp = tempNext;
		} 
	}
}

bool BucketList::contains(const string& s) const {

	// THIS IS DONE FOR YOU AS AN EXAMPLE
	// but you need to change something...

	int hc = h(s) % getCap(); // ...here.
	Node* temp = buckets_[hc];
	while (temp != nullptr) {
		if (temp->s_ == s) return true;
		temp = temp->next_;
	}
	return false;
}

void BucketList::insert(const string& s) {
	// IMPLEMENT ME
	//check if the buckList needs resizing
  	if( (getSize() + 1 )> (MAX_LOAD_FACTOR * cap_)) reSize();
  	
	//calculate mash value of incoming string	
	int mash = h(s)%cap_;
	
	// do nothing  if string is already contained in the bucketlist	
	if(contains(s)){
		return;
	}	
	
	//create a new bucket node to store  incoming string 	
	Node* newBucket = new Node;
	newBucket->s_ = s;
	
	//check if bucket is empty, to insert at the head
	if(buckets_[mash] == nullptr){
		buckets_[mash] = newBucket ;
		size_++;
		return;
	}

	//check if incoming string is smaller, to insert at the head	
	if(buckets_[mash]->s_ > s){
		Node* temp = buckets_[mash];
		newBucket->next_ = temp;
		buckets_[mash] = newBucket;	
		size_++;
		return;
	}
	
	// create pointer to store current and previous location in bucket 	
	Node* temp = buckets_[mash];
	Node* tempPrev = nullptr;	

	//loop through bucket and search for bigger strings and insert after
	while(temp != nullptr){		
		if(temp->s_ > s){
			newBucket->next_= temp;
			tempPrev->next_ = newBucket;
			size_++;			
			return;		
		}
	
	//	if loop gets to the extreme, insert after
		if(temp->next_== nullptr){
			temp->next_ = newBucket;		
			size_++;
			return;			
		}

		tempPrev = temp;
		temp = temp->next_;	
	}
}

void BucketList::remove(const string& s) {
	// IMPLEMENT ME
	//do nothing if string is not in the bucketlist
	if(!contains(s)){
		return;
	}
	
	//compute mash and set pointers to current and previous location
	int mash = h(s)%cap_;
	Node* temp = buckets_[mash];
	Node* tempPrev = nullptr;
	
	//Delete string if found at the head position
	if(temp->s_ == s){		
		buckets_[mash] =  temp->next_;
		delete temp;
		temp = nullptr;
		size_ --;
		return;
	}

	//search for string elsewhere, if found delete
	while(temp != nullptr){
		if(temp->s_ == s){	
			tempPrev->next_ = temp->next_;
			delete temp;
			temp = nullptr;
			size_ --;
			return;
		}
        tempPrev = temp;
		temp = temp->next_;
	}
}

string BucketList::toString() const {
	// IMPLEMENT ME
	// create a bucketlist to hold all the strings
	string bucket_list;
	
	//loop through bucket, and store in bucket_list
	for(int i = 0; i<cap_; i++){
		bucket_list += std::to_string(i);
		Node* temp =  buckets_[i];
       while(temp!=nullptr){
			bucket_list += " " + temp->s_;
			temp = temp->next_;
	    }  
	   if(i < cap_ -1) {
		   bucket_list += "\n";
	    }
    }
	return bucket_list;
}

int BucketList::h(const string& s) const {
	// IMPLEMENT ME
	//initialize the mash function arithmetic variable
	int h_mash = 0; 
	int s_size = s.length(); 
	
	//declare array to hold powers of 2
	int arrPw2[s_size];
	arrPw2[0] = 1;
	
	// looping through and append terms to array of powers 2
	for(int i=1; i<s_size; i++) arrPw2[i] = 2*arrPw2[i-1];
    
	// declare an array to hold ascii values of string
	int s_intArr[s_size];
	
	//multiply corresponding terms of array arrPw2 and s_intArr cummulatively
	for(int i=0; i<s_size; i++){
		s_intArr[i] = s[i];
		h_mash += s_intArr[i]*arrPw2[i];
	}
	return h_mash;
}

int BucketList::getSize() const {
	// IMPLEMENT ME
	return size_;
}

int BucketList::getCap() const {
	// IMPLEMENT ME
	return cap_;
}
