#include<iostream>
#include<vector>
#include "test.cpp"
#include "Syllogism.cpp"

using namespace std;

int main() {
	Syllogism syl;
	syl.put(make_pair("A", "B"));
	syl.print();
	syl.put(make_pair("B", "C"));
	syl.print();
	syl.put(make_pair("E", "F"));
	syl.print();
	syl.put(make_pair("D", "E"));
	syl.print();
	syl.qna("B");
	syl.put(make_pair("C", "D"));
	syl.print();
	syl.qna("B");

	Test test;
	test.test();

}

