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

	Syllogism& operator++() { // ++ overloading(전위)
		if (currentIterator != nullptr && currentIterator.access_curr()->next != nullptr) {
			++currentIterator;
		}
		else if (currentHeadIndex < syl.headSize() - 1) {
			++currentHeadIndex;
			currentIterator = syl.begin(currentHeadIndex);
		}
		else {
			currentIterator = syl.end(); // 끝에 도달하면 end iterator를 설정
		}
		return *this;
	}

	Syllogism& operator++(int) { // ++ operator overloading(후위)
		Syllogism temp = *this;
		if (currentIterator != nullptr && currentIterator.access_curr()->next != nullptr) {
			++currentIterator;
		}
		else if (currentHeadIndex < syl.headSize() - 1) {
			++currentHeadIndex;
			currentIterator = syl.begin(currentHeadIndex);
		}
		else {
			currentIterator = syl.end(); // 끝에 도달하면 end iterator를 설정
		}
		return temp;
	}

	Syllogism& operator=(const Syllogism& other) { // = operator overloading
		if (this != &other) { // 자기 자신에 대한 대입 방지
			syl = other.syl; // 멤버 변수 간의 대입
		}
		return *this;
	}

	void put(const pair<string, string>& argument)
	{
		bool merge = false; // 다른 논리 chain에 합쳐질 수 있는지 검사
		int addedIndex = -1;

		// 각 head에 대해 연결할 수 있는지 확인
		for (int i = 0; i < syl.headSize(); ++i) {
			auto it = syl.begin(i); // i번째 headIdx의 헤드
			auto last = syl.end();  // nullptr

			// 논리 체인의 시작과 끝을 모두 검사
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

		// 겹치는 게 없으면 새로운 헤드로 추가
		if (!merge) 
			syl.push_back(argument);
		

		// 추가된 인덱스를 기준으로 다른 체인과 병합할 수 있는지 확인
		for (int i = 0; i < syl.headSize(); ++i) {
			if (i == addedIndex) continue;

			auto firstIt_1 = syl.begin(addedIndex);
			auto lastIt_1 = syl.end();
			auto firstIt_2 = syl.begin(i);
			auto lastIt_2 = syl.end();

			// 새로운 논리 체인의 첫 번째 논리와 다른 체인의 마지막 논리를 비교
			if (firstIt_1 != lastIt_1 && firstIt_2 != lastIt_2) {
				auto lastRit_2 = syl.rbegin(i);

				if (lastRit_2->second == firstIt_1->first) {
					syl.merge(i, addedIndex);
					break;
				}

				// 다른 체인의 첫 번째 논리와 새로운 논리 체인의 마지막 논리를 비교
				auto lastRit = syl.rbegin(addedIndex);
				if ((*lastRit).second == firstIt_2->first) {
					syl.merge(addedIndex, i);
					break;
				}
			}
		}

		return;
	}

	void qna(const string& q) // n단 논법의 결론 도출
	{
		for (int i = 0; i < syl.headSize(); ++i) {
			auto it = syl.begin(i);
			auto last = syl.end();

			while (it != last) {
				
				if (it->first == q) {
					// 논리 체인을 따라 결론 도출
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

