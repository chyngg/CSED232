#include <iostream>
#include "MultiHeadList.h"

using namespace std;
class Test {
public:
	void test() {
		MultiHeadList<int> mhList;
		mhList.push_back(1);
		cout << "push_back(1)" << endl;
		print(mhList);
		mhList.push_back(2, 0);
		cout << "push_back(2, 0)" << endl;
		print(mhList);
		mhList.push_back(3, 1);
		cout << "push_back(3, 1)" << endl;
		print(mhList);
		mhList.push_back(4);
		cout << "push_back(4)" << endl;
		print(mhList);
		mhList.push_back(5, 1);
		cout << "push_back(5,1)" << endl;
		print(mhList);
		mhList.push_front(6, 2);
		cout << "push_front(6, 2)" << endl;
		print(mhList);

		mhList.pop_back(1);
		cout << "pop_back(1)" << endl;
		print(mhList);
		mhList.pop_back(1);
		cout << "pop_back(1)" << endl;
		print(mhList);

		mhList.pop_back(2);
		cout << "pop_back(2)" << endl;
		print(mhList);
		mhList.pop_front(2);
		cout << "pop_front(2)" << endl;
		print(mhList);
		mhList.push_front(7);
		cout << "push_front(7)" << endl;
		print(mhList);
		mhList.merge(2, 1);
		cout << "merge(2,1)" << endl;
		print(mhList);
		mhList.erase(7, 0);
		cout << "erase(7,0)" << endl;
		print(mhList);
		mhList.erase(7, 1);
		cout << "erase(7,1)" << endl;
		print(mhList);
		mhList.insert(mhList.begin(1), 8);
		cout << "insert(mhList.begin(1), 8)" << endl;
		print(mhList);
		mhList.insert(++mhList.begin(1), 9);
		cout << "insert(++mhList.begin(1), 9)" << endl;
		print(mhList);
		mhList.erase(mhList.begin(1) + 2);
		cout << "erase(mhList.begin(1)+2)" << endl;
		print(mhList);
	}

	template <typename T>
	void print(MultiHeadList<T>& mhList) {
		for (int i = 0; i != mhList.headSize(); i++) {
			cout << i << " : ";
			for (auto it = mhList.begin(i); it != mhList.end(); it++) {
				cout << *it << " ";
			}
			cout << endl;
		}
		cout << "=============" << endl;
	}
};