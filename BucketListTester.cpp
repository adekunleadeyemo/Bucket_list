#include <iostream>
#include "BucketListTester.h"
#include "BucketList.h"

using namespace std;

BucketListTester::BucketListTester() : error_(false), funcname_("") {}

// constructor, empty BL
void BucketListTester::testa() {
	funcname_ = "BucketListTester::testa";

	{
	BucketList t;
	if (t.getSize() != 0)
		errorOut_("Empty BL size reported as ", t.getSize(), 0);
	if (t.getCap() != BucketList::INITIAL_CAP)
		errorOut_("Initial BL cap reported as ", t.getCap(), 0);
	if (t.contains(""))
		errorOut_("Empty BL contains empty string?", 0);
	}

	passOut_();
}

// mash
void BucketListTester::testb() {
	funcname_ = "BucketListTester::testb";

	{
	BucketList t;
	if (t.h("a") != 97)
		errorOut_("h(a) reported as ", t.h("a"), 1);
	if (t.h("abc") != 689)
		errorOut_("h(abc) reported as ", t.h("abc"), 1);
	if (t.h("A") != 65)
		errorOut_("h(A) reported as ", t.h("A"), 1);

	if (t.h("689") != 394)
		errorOut_("h(689) reported as ", t.h("689"), 2);
	if (t.h("?!#$%") != 1149)
		errorOut_("h(?!#$%) reported as ", t.h("?!#$%"), 2);
	if (t.h("") != 0)
		errorOut_("h() of empty string reported as ", t.h(""), 2);

	}

	passOut_();
}

// insert: simplest, 1 string
void BucketListTester::testc() {
	funcname_ = "BucketListTester::testc";

	{
	BucketList t;
	t.insert("a");
	if (!t.contains("a")) errorOut_("a not found after insert", 0);
	if (t.getSize() != 1)
		errorOut_("size after insert reported as ", t.getSize(), 0);
	}

	passOut_();
}

// insert: several strings in diff buckets
void BucketListTester::testd() {
	funcname_ = "BucketListTester::testd";

	{
	BucketList t;
	t.insert("a"); t.insert("b"); t.insert("ab");
	if (!t.contains("a")) errorOut_("a not found", 1);
	if (!t.contains("b")) errorOut_("b not found", 1);
	if (!t.contains("ab")) errorOut_("ab not found", 1);

	if (t.getSize() != 3)
		errorOut_("size after 3 inserts reported as ", t.getSize(), 2);
	if (t.contains("ba")) errorOut_("found ba??", 2);
	if (t.contains("k")) errorOut_("found k??", 2);
	}

	passOut_();
}

// insert: multiple strings same bucket
void BucketListTester::teste() {
	funcname_ = "BucketListTester::teste";

	{
	BucketList t;
	t.insert("abc"); t.insert("cac");
	if (!t.contains("abc")) errorOut_("abc not found", 1);
	if (!t.contains("cac")) errorOut_("cac not found", 1);
	if (t.getSize() != 2)
		errorOut_("size after 2 inserts reported as ", t.getSize(), 1);

	// non alpha order (5th, 3rd, 1st, 2nd, 6th, 4th)
	BucketList u;
	string ss[] = {"_","K","7","A","i","U"};
	for(int i=0; i<6; i++) {
		u.insert(ss[i]);
		if (!u.contains(ss[i])) errorOut_(ss[i] + " not found", 2);
		if (u.getSize() != i+1)
			errorOut_("size after insert " + ss[i] + " reported as ", u.getSize(), 2);
	}

	for(string s : ss)
		if (!u.contains(s))
			errorOut_(s + " not found at the end", 2);

	}

	passOut_();
}

// insert: empty string; existing string; existing string in longer lists
void BucketListTester::testf() {
	funcname_ = "BucketListTester::testf";

	{
	BucketList t;
	t.insert("");
	if (!t.contains("")) errorOut_("empty string not found", 1);
	if (t.getSize() != 1)
		errorOut_("size after insert empty string reported as ", t.getSize(), 1);

	BucketList u;
	u.insert("a"); u.insert("a");
	if (!u.contains("a")) errorOut_("a not found after insert twice", 2);
	if (u.getSize() != 1)
		errorOut_("size after repeat insert a reported as ", u.getSize(), 2);

	BucketList v;
	v.insert("az"); v.insert("cy"); v.insert("ex");
	v.insert("cy");
	if (!v.contains("cy")) errorOut_("cy not found after insert twice", 2);
	if (v.getSize() != 3)
		errorOut_("size after repeat insert cy reported as ", v.getSize(), 2);

	}

	passOut_();
}

// toString empty BL
void BucketListTester::testg() {
	funcname_ = "BucketListTester::testg";

	{
	BucketList t;
	if (t.toString() != "0\n1\n2\n3\n4\n5\n6\n7\n8\n9")
		errorOut_("empty BL printed as\n", t.toString(), 0);
	}

	passOut_();
}

// toString: diff buckets
void BucketListTester::testh() {
	funcname_ = "BucketListTester::testh";

	{
	BucketList t;
	t.insert("a"); t.insert("b"); t.insert("c");
	if (t.toString() != "0\n1\n2\n3\n4\n5\n6\n7 a\n8 b\n9 c")
		errorOut_("BL with a,b,c printed as\n", t.toString(), 0);
	}

	passOut_();
}

// toString: collision, alpha order
void BucketListTester::testi() {
	funcname_ = "BucketListTester::testi";

	{
	BucketList t;
	t.insert("az"); t.insert("cy"); t.insert("ex"); t.insert("gw");
	if (t.toString() != "0\n1 az cy ex gw\n2\n3\n4\n5\n6\n7\n8\n9")
		errorOut_("t printed as\n", t.toString(), 1);

	BucketList u;
	u.insert("gw"); u.insert("ex"); u.insert("cy"); u.insert("az");
	if (u.toString() != "0\n1 az cy ex gw\n2\n3\n4\n5\n6\n7\n8\n9")
		errorOut_("u printed as\n", u.toString(), 2);

	BucketList v;
	v.insert("cy"); v.insert("gw"); v.insert("ex"); v.insert("az");
	if (v.toString() != "0\n1 az cy ex gw\n2\n3\n4\n5\n6\n7\n8\n9")
		errorOut_("v printed as\n", v.toString(), 2);
	}

	passOut_();
}

// mixed insert and toString
void BucketListTester::testj() {
	funcname_ = "BucketListTester::testj";

	{
	BucketList t;
	string ss[] = {"apple","banana","C++","F#","blue","abc","c"};

	for(int i = 0; i < 3; i++) t.insert(ss[i]);
	if (t.getSize() != 3)
		errorOut_("size after 3 inserts reported as ", t.getSize(), 1);
	for(int i = 0; i < 3; i++) {
		if (!t.contains(ss[i]))
			errorOut_(ss[i] + " not found", 1);
	}
	if (t.toString() != "0\n1\n2 banana\n3\n4\n5 C++\n6\n7\n8\n9 apple")
		errorOut_("after 3 inserts printed as\n", t.toString(), 1);

	for(int i = 3; i < 5; i++) t.insert(ss[i]);
	if (t.getSize() != 5)
		errorOut_("size after 5 inserts reported as ", t.getSize(), 2);
	for(int i = 3; i < 5; i++) {
		if (!t.contains(ss[i]))
			errorOut_(ss[i] + " not found", 2);
	}
	if (t.toString() != "0 F# blue\n1\n2 banana\n3\n4\n5 C++\n6\n7\n8\n9 apple")
		errorOut_("after 5 inserts printed as\n", t.toString(), 2);

	for(int i = 5; i < 7; i++) t.insert(ss[i]);
	if (t.getSize() != 7)
		errorOut_("size after 7 inserts reported as ", t.getSize(), 2);
	for(int i = 5; i < 7; i++) {
		if (!t.contains(ss[i]))
			errorOut_(ss[i] + " not found", 2);
	}
	if (t.toString() != "0 F# blue\n1\n2 banana\n3\n4\n5 C++\n6\n7\n8\n9 abc apple c")
		errorOut_("after 7 inserts printed as\n", t.toString(), 2);

	}

	passOut_();
}

// simplest remove
void BucketListTester::testk() {
	funcname_ = "BucketListTester::testk";

	{
	BucketList t;
	t.insert("a");
	t.remove("a");

	if (t.contains("a")) errorOut_("a not removed", 1);
	if (t.getSize() != 0)
		errorOut_("size after remove reported as ", t.getSize(), 1);
	}

	passOut_();
}

// remove from empty BL; remove non-existent entry
void BucketListTester::testl() {
	funcname_ = "BucketListTester::testl";

	{
	BucketList t;
	t.remove("a");
	if (t.contains("a")) errorOut_("remove from empty BL incorrect", 1);
	if (t.getSize() != 0)
		errorOut_("size after remove from empty BL reported as ", t.getSize(), 1);

	BucketList u;
	u.insert("a");
	u.remove("b");
	if (!u.contains("a")) errorOut_("u incorrectly removed a", 2);
	if (u.contains("b")) errorOut_("u did not remove b", 2);
	if (u.getSize() != 1) errorOut_("u size after remove reported as ", u.getSize(), 2);
	}

	passOut_();
}

// remove from diff buckets
void BucketListTester::testm() {
	funcname_ = "BucketListTester::testm";

	{
	BucketList t;
	t.insert("a"); t.insert("b"); t.insert("c");

	t.remove("b");
	if (t.contains("b")) errorOut_("b not removed", 1);
	if (t.getSize() != 2) errorOut_("size after remove b reported as ", t.getSize(), 1);

	t.remove("a");
	if (t.contains("a")) errorOut_("a not removed", 2);
	if (t.getSize() != 1) errorOut_("size after remove a reported as ", t.getSize(), 2);

	t.remove("c");
	if (t.contains("c")) errorOut_("c not removed", 2);
	if (t.getSize() != 0) errorOut_("size after remove c reported as ", t.getSize(), 2);
	}

	passOut_();
}

// remove from bucket with multiple items
void BucketListTester::testn() {
	funcname_ = "BucketListTester::testn";

	{
	string ss[] = {"K","A","_","7","U"};
	BucketList t;
	for(string s : ss) t.insert(s);

	// 3rd, 2nd, 5th, 1st, 4th
	for(int i=0; i<5; i++) {
		t.remove(ss[i]);
		if (t.contains(ss[i])) errorOut_(ss[i] + "not removed", 1);
		if (t.getSize() != 4-i)
			errorOut_("size after remove " + ss[i] + " reported as ", t.getSize(), 2);
	}

	}

	passOut_();
}

// remove + toString
void BucketListTester::testo() {
	funcname_ = "BucketListTester::testo";

	{
	BucketList t;
	t.insert("ay");
	t.insert("az"); t.insert("cy"); t.insert("ex"); t.insert("gw");
	if (t.toString() != "0\n1 az cy ex gw\n2\n3\n4\n5\n6\n7\n8\n9 ay")
		errorOut_("after 5 inserts printed as\n", t.toString(), 1);

	// singleton
	t.remove("ay");
	if (t.toString() != "0\n1 az cy ex gw\n2\n3\n4\n5\n6\n7\n8\n9")
		errorOut_("after remove ay printed as\n", t.toString(), 1);
	// middle
	t.remove("ex");
	if (t.toString() != "0\n1 az cy gw\n2\n3\n4\n5\n6\n7\n8\n9")
		errorOut_("after remove ex printed as\n", t.toString(), 1);
	// non-existent
	t.remove("a");
	if (t.toString() != "0\n1 az cy gw\n2\n3\n4\n5\n6\n7\n8\n9")
		errorOut_("after remove a printed as\n", t.toString(), 2);
	// head
	t.remove("az");
	if (t.toString() != "0\n1 cy gw\n2\n3\n4\n5\n6\n7\n8\n9")
		errorOut_("after remove az printed as\n", t.toString(), 2);
	// tail
	t.remove("gw");
	if (t.toString() != "0\n1 cy\n2\n3\n4\n5\n6\n7\n8\n9")
		errorOut_("after remove gw printed as\n", t.toString(), 2);
	// last
	t.remove("cy");
	if (t.toString() != "0\n1\n2\n3\n4\n5\n6\n7\n8\n9")
		errorOut_("after remove cy printed as\n", t.toString(), 2);
	// from empty
	t.remove("cy");
	if (t.toString() != "0\n1\n2\n3\n4\n5\n6\n7\n8\n9")
		errorOut_("after remove from empty printed as\n", t.toString(), 2);

	}

	passOut_();
}

// basic copy con
void BucketListTester::testp() {
	funcname_ = "BucketListTester::testp";

	{
	BucketList t1;
	t1.insert("a");
	string s1 = t1.toString();

	BucketList t2(t1);
	if (!t2.contains("a")) errorOut_("copy does not have a", 1);
	if (t2.getSize() != 1)
		errorOut_("copy wrong size: ", t2.getSize(), 1);
	if (t2.getCap() != BucketList::INITIAL_CAP)
		errorOut_("copy wrong cap: ", t2.getCap(), 1);
	if (t2.toString() != s1)
		errorOut_("copy printed differently:\n", t2.toString(), 1);

	// damaged org?
	if (!t1.contains("a")) errorOut_("org no longer have a", 2);
	if (t1.getSize() != 1)
		errorOut_("org wrong size: ", t1.getSize(), 2);
	if (t1.getCap() != BucketList::INITIAL_CAP)
		errorOut_("org wrong cap: ", t1.getCap(), 2);
	if (t1.toString() != s1)
		errorOut_("org printed differently:\n", t1.toString(), 1);

	// sticky?
	t1.insert("b");
	t2.insert("c");
	if (t2.contains("b"))
		errorOut_("sticky copy con: old affected new", 2);
	if (t1.contains("c"))
		errorOut_("sticky copy con: new affected old", 2);
	}

	passOut_();
}

// copy con empty BL; bigger BL
void BucketListTester::testq() {
	funcname_ = "BucketListTester::testq";

	{
	// empty
	BucketList t1;
	string s1 = t1.toString();
	BucketList t2(t1);
	if (t2.getSize() != 0)
		errorOut_("empty copy wrong size: ", t2.getSize(), 1);
	if (t2.getCap() != BucketList::INITIAL_CAP)
		errorOut_("empty copy wrong cap: ", t2.getCap(), 1);
	if (t2.toString() != s1)
		errorOut_("empty copy printed differently:\n", t2.toString(), 1);
	if (t1.getSize() != 0)
		errorOut_("empty org wrong size: ", t1.getSize(), 1);
	if (t1.getCap() != BucketList::INITIAL_CAP)
		errorOut_("empty org wrong cap: ", t1.getCap(), 1);
	if (t1.toString() != s1)
		errorOut_("empty org printed differently:\n", t1.toString(), 1);

	// bigger
	BucketList u1;
	string ss[] = {"a","b","c","d","k","l","u"};
	for(string s : ss) u1.insert(s);
	s1 = u1.toString();
	BucketList u2(u1);
	if (u2.getSize() != 7)
		errorOut_("copy wrong size: ", u2.getSize(), 2);
	if (u2.getCap() != BucketList::INITIAL_CAP)
		errorOut_("copy wrong cap: ", u2.getCap(), 2);
	if (u2.toString() != s1)
		errorOut_("copy printed differently:\n", u2.toString(), 2);
	for(string s : ss)
		if (!u2.contains(s))
			errorOut_("copy missing string ", s, 2);

	// damaged org?
	if (u1.getSize() != 7)
		errorOut_("org wrong size: ", u1.getSize(), 2);
	if (u1.getCap() != BucketList::INITIAL_CAP)
		errorOut_("org wrong cap: ", u1.getCap(), 2);
	if (u1.toString() != s1)
		errorOut_("org printed differently:\n", u1.toString(), 2);
	for(string s : ss)
		if (!u1.contains(s))
			errorOut_("org missing string ", s, 2);

	// sticky? (w/ remove)
	u1.remove("a");
	u2.remove("b");
	if (!u1.contains("b"))
		errorOut_("sticky copy con: new affected old", 2);
	if (!u2.contains("a"))
		errorOut_("sticky copy con: old affected new", 2);

	}

	passOut_();
}

// basic copy asg
void BucketListTester::testr() {
	funcname_ = "BucketListTester::testr";

	{
	BucketList t1;
	BucketList t2;
	t1.insert("a");
	string s1 = t1.toString();
	t2.insert("b");

	t2 = t1;
	if (!t2.contains("a")) errorOut_("a not copied", 1);
	if (t2.getSize() != 1)
		errorOut_("copy wrong size: ", t2.getSize(), 1);
	if (t2.getCap() != BucketList::INITIAL_CAP)
		errorOut_("copy wrong cap: ", t2.getCap(), 1);
	if (t2.toString() != s1)
		errorOut_("copy printed differently:\n", t2.toString(), 1);

	// old contents still there?
	if (t2.contains("b")) errorOut_("b still there after copy?", 1);

	// damaged org?
	if (!t1.contains("a")) errorOut_("a no longer in org?", 2);
	if (t1.getSize() != 1)
		errorOut_("copy wrong size: ", t1.getSize(), 2);
	if (t1.getCap() != BucketList::INITIAL_CAP)
		errorOut_("copy wrong cap: ", t1.getCap(), 2);
	if (t1.toString() != s1)
		errorOut_("org printed differently:\n", t1.toString(), 2);

	// sticky?
	t1.insert("c");
	t2.insert("d");
	if (t1.contains("d")) errorOut_("sticky: new affected old", 2);
	if (t2.contains("c")) errorOut_("sticky: old affected new", 2);
	}

	passOut_();
}

// copy asg bigger
void BucketListTester::tests() {
	funcname_ = "BucketListTester::tests";

	{
	BucketList t1;
	BucketList t2;
	string s1[] = {"a","b","c","d","k","l","u"};
	for(string s : s1) t1.insert(s);
	string res = t1.toString();
	string s2[] = {"A","B","K"};
	for(string s : s2) t2.insert(s);

	t2 = t1;
	if (t2.getSize() != 7)
		errorOut_("copy wrong size: ", t2.getSize(), 1);
	if (t2.getCap() != BucketList::INITIAL_CAP)
		errorOut_("copy wrong cap: ", t2.getCap(), 1);
	if (t2.toString() != res)
		errorOut_("copy printed differently:\n", t2.toString(), 1);
	for(string s : s1)
		if (!t2.contains(s))
			errorOut_("copy missing string ", s, 1);

	// old contents still there?
	for(string s : s2)
		if (t2.contains(s))
			errorOut_("copy still contain string ", s, 1);

	// damaged org?
	if (t1.getSize() != 7)
		errorOut_("org wrong size: ", t1.getSize(), 1);
	if (t1.getCap() != BucketList::INITIAL_CAP)
		errorOut_("org wrong cap: ", t1.getCap(), 1);
	if (t1.toString() != res)
		errorOut_("org printed differently:\n", t2.toString(), 1);
	for(string s : s1)
		if (!t1.contains(s))
			errorOut_("org missing string ", s, 1);

	// sticky? (w/ remove)
	t1.remove("a");
	t2.remove("b");
	if (!t1.contains("b")) errorOut_("sticky: new affected old", 2);
	if (!t2.contains("a")) errorOut_("sticky: old affected new", 2);

	}

	passOut_();
}

// copy asg self-asg
void BucketListTester::testt() {
	funcname_ = "BucketListTester::testt";

	{
	BucketList u;
	u.insert("a"); u.insert("b"); u.insert("k");
	u = u;
	if (!u.contains("a")) errorOut_("self-assign not contain a", 1);
	if (!u.contains("b")) errorOut_("self-assign not contain b", 1);
	if (!u.contains("k")) errorOut_("self-assign not contain k", 1);
	if (u.getSize() != 3) errorOut_("self-assign wrong size: ", u.getSize(), 1);

	u.remove("b"); u.remove("k"); u.insert("c");
	if (u.contains("b")) errorOut_("self-assign b not removed", 2);
	if (u.contains("k")) errorOut_("self-assign k not removed", 2);
	if (!u.contains("c")) errorOut_("self-assign c not inserted", 2);
	if (u.getSize() != 2) errorOut_("self-assign after updates wrong size:", u.getSize(), 2);

	}

	passOut_();
}

// resize: simplest
void BucketListTester::testu() {
	funcname_ = "BucketListTester::testu";

	{
	BucketList t;
	t.insert("a");
	t.insert("b");
	t.insert("c");
	t.insert("d");
	t.insert("e");
	t.insert("k");
	t.insert("l");
	if (t.getCap() != BucketList::INITIAL_CAP)
		errorOut_("7 strings wrong capacity: ", t.getCap(), 0);
	t.insert("f");
	if (t.getCap() != 2*BucketList::INITIAL_CAP)
		errorOut_("8 strings wrong capacity: ", t.getCap(), 0);
	t.insert("u");
	if (t.getCap() != 2*BucketList::INITIAL_CAP)
		errorOut_("9 strings wrong capacity: ", t.getCap(), 0);
	}

	passOut_();
}

// bigger resize size/cap check and with remove
void BucketListTester::testv() {
	funcname_ = "BucketListTester::testv";

	{
	BucketList t;
	int c = BucketList::INITIAL_CAP;
	for(int i=1; i<=100; i++) {
		t.insert(std::to_string(i));
		if (i > c*BucketList::MAX_LOAD_FACTOR) c *= 2;
		if (t.getSize() != i)
			errorOut_("ins "+std::to_string(i)+" size "+std::to_string(t.getSize()), 1);
		if (t.getCap() != c)
			errorOut_("ins "+std::to_string(i)+" cap "+std::to_string(t.getCap()), 1);
	}

	// remove should not shrink
	for(int i=1; i<=100; i++) {
		t.remove(std::to_string(i));
		if (t.getSize() != 100-i)
			errorOut_("del"+std::to_string(i)+" size"+std::to_string(t.getSize()), 2);
		if (t.getCap() != c)
			errorOut_("del"+std::to_string(i)+" cap"+std::to_string(t.getCap()), 2);
	}

	}

	passOut_();
}

// resize check contains and toString
void BucketListTester::testw() {
	funcname_ = "BucketListTester::testw";

	{
	BucketList t;
	string ss[] = {"apple","C++","c","F#","blue","abc","banana","red"};
	for(string s : ss) t.insert(s);
	for(string s : ss) {
		if (!t.contains(s))
			errorOut_(s + " not found", 1);
	}
	if (t.toString() != "0 F#\n1\n2\n3\n4\n5 C++\n6\n7\n8\n9 abc apple\n10 blue\n11\n12 banana\n13\n14\n15\n16 red\n17\n18\n19 c")
		errorOut_("after resize printed as\n", t.toString(), 2);

	}

	passOut_();
}

// bigger ins + del + toString w/ resize
void BucketListTester::testx() {
	funcname_ = "BucketListTester::testx";

	{
	BucketList t;
	string res = "0\n1\n2\n3\n4\n5\n6\n7\n8\n9";

	string c, h;
	for(int i=6; i>=0; i--) {
		c = string(1,i+'a');
		t.insert(c);
		h = std::to_string(t.h(c) % t.getCap());
		res.insert(res.find(h) + h.length(), " "+c);
		if (res != t.toString())
			errorOut_("insert string " + c + " wrong", 1);
	}

	res = "0 d\n1 e\n2 f\n3 g\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17 a\n18 b\n19 c";

	string ss[] = {"MG","KH","II","GJ","EK","CL","AM"};
	for(string s : ss) {
		t.insert(s);
		h = std::to_string(t.h(s) % t.getCap());
		res.insert(res.find(h) + h.length(), " "+s);
		if (res != t.toString())
			errorOut_("insert string " + s + " wrong", 1);
	}

	for(int i=0; i<7; i++) {
		c = string(1,i+'a');
		t.remove(c);
		res.replace(res.find(" "+c), 2, "");
		if (res != t.toString())
			errorOut_("remove string " + c + " wrong", 2);

	}

	for(string s : ss) {
		t.remove(s);
		res.replace(res.find(" "+s), 3, "");
		if (t.toString() != res)
			errorOut_("remove string " + s + " wrong", 2);
	}

	}

	passOut_();
}

// resize w/ copy
void BucketListTester::testy() {
	funcname_ = "BucketListTester::testy";

	{
	// "overgrown" should be copied as is, not shrank
	BucketList t1;
	for(int i=1; i<=5; i++)
		t1.insert(std::to_string(i));
	BucketList t2;
	for(int i=1; i<=10; i++)
		t2.insert(std::to_string(i));
	for(int i=6; i<=10; i++)
		t2.remove(std::to_string(i));
	BucketList t3(t2);
	if (t1.toString() == t2.toString())
		errorOut_("t1 t2 toString should not be same!", 1);
	if (t1.toString() == t3.toString())
		errorOut_("t1 t3 toString should not be same!", 1);
	if (t2.toString() != t3.toString())
		errorOut_("t2 t3 toString should be same!", 1);

	BucketList u1;
	for(int i=1; i<=20; i++)
		u1.insert(std::to_string(i));
	BucketList u2(u1);
	if (u1.toString() != u2.toString())
		errorOut_("u1 u2 toString not same after 20 inserts", 2);
	for(int i=21; i<=100; i++) {
		u1.insert(std::to_string(i));
		u2.insert(std::to_string(i));
	}
	if (u1.toString() != u2.toString())
		errorOut_("u1 u2 toString not same after 100 inserts", 2);

	for(int i=79; i>=60; i--)
		u1.remove(std::to_string(i));
	u2 = u1;
	if (u1.toString() != u2.toString())
		errorOut_("u1 u2 toString not same after 20 removes", 2);
	for(int i=59; i>=30; i--) {
		u1.remove(std::to_string(i));
		u2.remove(std::to_string(i));
	}
	if (u1.toString() != u2.toString())
		errorOut_("u1 u2 toString not same after 50 removes", 2);

	}

	passOut_();
}

// reserved for new test cases
void BucketListTester::testz() {
	funcname_ = "BucketListTester::testz";

}

void BucketListTester::errorOut_(const string& errMsg, unsigned int errBit) {

	cerr << funcname_ << ":" << " fail" << errBit << ": ";
	cerr << errMsg << endl;
	error_ |= (1<<errBit);
	cerr << std::flush;
}

void BucketListTester::errorOut_(const string& errMsg, const string& errResult, unsigned int errBit) {

	cerr << funcname_ << ":" << " fail" << errBit << ": ";
	cerr << errMsg << errResult << endl;
	error_ |= (1<<errBit);
	cerr << std::flush;
}

void BucketListTester::errorOut_(const string& errMsg, int errResult, unsigned int errBit) {

	cerr << funcname_ << ":" << " fail" << errBit << ": ";
	cerr << errMsg << std::to_string(errResult) << endl;
	error_ |= (1<<errBit);
	cerr << std::flush;
}

void BucketListTester::passOut_() {

	if (!error_) {
		cerr << funcname_ << ":" << " pass" << endl;
	}
	cerr << std::flush;
}

