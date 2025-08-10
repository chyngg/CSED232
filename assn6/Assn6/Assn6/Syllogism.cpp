#include <iostream>
#include <utility>
#include <string>
#include "MultiHeadList.h"

using namespace std;

class Syllogism {
private:
	MultiHeadList<pair<string, string>>syl;
	int currentHeadIndex;
	typename MultiHeadList<pair<string, string>>::Iterator currentIterator;
public:
	Syllogism() : currentHeadIndex(0), currentIterator(nullptr) {}

	pair<string, string>* operator->() { return &(syl.begin(0).access_curr()->data); }
	pair<string, string>& operator*() { return *currentIterator; }

	Syllogism& operator++() { // ++ overloading(����)
		if (currentIterator != nullptr && currentIterator.access_curr()->next != nullptr) {
			++currentIterator;
		}
		else if (currentHeadIndex < syl.headSize() - 1) {
			++currentHeadIndex;
			currentIterator = syl.begin(currentHeadIndex);
		}
		else {
			currentIterator = syl.end(); // ���� �����ϸ� end iterator�� ����
		}
		return *this;
	}

	Syllogism& operator++(int) { // ++ operator overloading(����)
		Syllogism temp = *this;
		if (currentIterator != nullptr && currentIterator.access_curr()->next != nullptr) {
			++currentIterator;
		}
		else if (currentHeadIndex < syl.headSize() - 1) {
			++currentHeadIndex;
			currentIterator = syl.begin(currentHeadIndex);
		}
		else {
			currentIterator = syl.end(); // ���� �����ϸ� end iterator�� ����
		}
		return temp;
	}

	Syllogism& operator=(const Syllogism& other) { // = operator overloading
		if (this != &other) { // �ڱ� �ڽſ� ���� ���� ����
			syl = other.syl; // ��� ���� ���� ����
		}
		return *this;
	}

	void put(const pair<string, string>& argument)
	{
		bool merge = false; // �ٸ� �� chain�� ������ �� �ִ��� �˻�
		int addedIndex = -1;

		// �� head�� ���� ������ �� �ִ��� Ȯ��
		for (int i = 0; i < syl.headSize(); ++i) {
			auto it = syl.begin(i); // i��° headIdx�� ���
			auto last = syl.end();  // nullptr

			// �� ü���� ���۰� ���� ��� �˻�
			if (it != last && it->first == argument.second) {
				syl.push_front(argument, i);
				merge = true;
				addedIndex = i;
				break;
			}

			auto rit = syl.rbegin(i);
			auto rend = syl.rend();
			if (rit != rend && rit->second == argument.first) {
				syl.push_back(argument, i);
				merge = true;
				addedIndex = i;
				break;
			}
		}

		// ��ġ�� �� ������ ���ο� ���� �߰�
		if (!merge) 
			syl.push_back(argument);
		

		// �߰��� �ε����� �������� �ٸ� ü�ΰ� ������ �� �ִ��� Ȯ��
		for (int i = 0; i < syl.headSize(); ++i) {
			if (i == addedIndex) continue;

			auto firstIt_1 = syl.begin(addedIndex);
			auto lastIt_1 = syl.end();
			auto firstIt_2 = syl.begin(i);
			auto lastIt_2 = syl.end();

			// ���ο� �� ü���� ù ��° ���� �ٸ� ü���� ������ ���� ��
			if (firstIt_1 != lastIt_1 && firstIt_2 != lastIt_2) {
				auto lastRit_2 = syl.rbegin(i);

				if (lastRit_2->second == firstIt_1->first) {
					syl.merge(i, addedIndex);
					break;
				}

				// �ٸ� ü���� ù ��° ���� ���ο� �� ü���� ������ ���� ��
				auto lastRit = syl.rbegin(addedIndex);
				if ((*lastRit).second == firstIt_2->first) {
					syl.merge(addedIndex, i);
					break;
				}
			}
		}

		return;
	}

	void qna(const string& q) // n�� ����� ��� ����
	{
		for (int i = 0; i < syl.headSize(); ++i) {
			auto it = syl.begin(i);
			auto last = syl.end();

			while (it != last) {
				
				if (it->first == q) {
					// �� ü���� ���� ��� ����
					string result = it->second;
					auto next_it = it;
					++next_it; // Move to the next element
					while (next_it != last) {
						result = next_it->second;
						it = next_it;
						++next_it;
					}
					cout << "If " << q << ", then " << result << endl;
					return;
				}
				++it;
			}
		}
		cout << "No conclusion for " << q << endl;
	}


	void print() {
		cout << "=============" << endl;
		for (int i = 0; i != syl.headSize(); i++) {
			cout << i << " : ";
			for (auto it = syl.begin(i); it != syl.end(); it++) {
				if (it == syl.begin(i)) {
					cout << (*it).first << "->" << (*it).second;
				}
				else {
					cout << "->" << (*it).second;
				}
			}
			cout << endl;
		}
	}

};

