#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;
int cnt = 0; // 입력받은 학생 수

struct student { // 구조체를 사용해 학생의 정보 저장
	long long id; //학번
	string name; // 이름
	int midterm_score; // 중간고사 점수
	int final_score; // 기말고사 점수
	int retake; // 재수강 여부
	int sum; // 중간고사+기말고사 점수 합계
	char grade; // 등급
};

student students[101] = {};

void print_menu() // 메뉴 출력
{
	cout << "----------MENU----------\n";
	cout << "1. Add a student" << endl;
	cout << "2. Edit the score of a student" << endl;
	cout << "3. Print average score" << endl;
	cout << "4. Print scores list" << endl;
	cout << "5. Print grades list" << endl;
	cout << "6. Exit" << endl;
	cout << "------------------------\n";
	cout << "Selection: ";
	return;
}

void add_student(student students[], int cnt) { // 학생 추가
	long id = 0; string name = ""; 
	int midterm_score = 0, final_score = 0, retake = -1;
	cout << "Student id: ";
	cin >> id;
	if (id < 10000000 || id > 99999999) { // 학번이 8자리 양의 정수가 아닌 경우
		cout << "Failed to add: invalid student id!" << endl;
		return;
	}

	cout << "Name: ";
	cin >> name;
	for (char ch : name) {
		if (!isalpha(static_cast<unsigned char>(ch))) { // 이름에 알파벳 이외의 문자가 들어가 있을 경우
			cout << "Failed to add: invalid name!" << endl;
			return;
		}
	}

	cout << "Midterm exam score: ";
	cin >> midterm_score;
	if (midterm_score < 0 || midterm_score > 100) { // 중간고사 점수 범위가 0~100이 아닌 경우
		cout << "Failed to add: invalid midterm exam score!" << endl;
		return;
	}

	cout << "Final exam score: ";
	cin >> final_score;
	if (final_score < 0 || final_score > 100) { // 기말고사 점수 범위가 0~100이 아닌 경우
		cout << "Failed to add: invalid final exam score!" << endl;
		return;
	}
	
	cout << "Retake: ";
	cin >> retake;
	if (retake != 0 && retake != 1) { // 재수강 여부 - 0 or 1 외의 다른 수가 입력되었을 경우
		cout << "Failed to add: invalid retake value!" << endl;
		return;
	}
	// 모든 정보가 올바르게 들어오면 구조체 배열에 정보 저장
	students[cnt].id = id;  students[cnt].name = name;
	students[cnt].midterm_score = midterm_score; students[cnt].final_score = final_score;
	students[cnt].retake = retake;
	students[cnt].sum = midterm_score + final_score;

	cout << "The student is added!" << endl;
} 

void sort_student(student students[], int cnt) { // 성적에 따라 내림차순으로 학생을 정렬
	student temp = students[0];
	for (int i = 1; i < cnt; i++) {
		for (int j = 1; j <= cnt - i; j++) { // Bubble Sort
			if (students[j].sum < students[j + 1].sum) { 
				temp = students[j];
				students[j] = students[j + 1];
				students[j + 1] = temp;
			}
			else if (students[j].sum == students[j + 1].sum && students[j].id > students[j + 1].id) { // 성적이 같은 경우 학번을 기준으로 오름차순 정렬
				temp = students[j];
				students[j] = students[j + 1];
				students[j + 1] = temp;
			}
		}
	}
	return;
}

void edit_score(student students[]) { // 점수 수정
	int exam;
	int a = 1;
	long id_to_find = 0;
	int how_to_fix = 0;

	cout << "--------Function--------\n";
	cout << "1. Edit the midterm exam score" << endl;
	cout << "2. Edit the final exam score" << endl;
	cout << "------------------------\n" << "Selection: ";
	cin >> exam; // 어떤 시험 점수를 수정할지 저장

	cout << "Student id: ";
	cin >> id_to_find; // 수정할 학생의 학번
	if (id_to_find < 10000000 || id_to_find > 99999999) { // 학번이 8자리 양의 정수가 아닌 경우
		cout << "Failed to edit: invalid student id!" << endl; 
		return;
	}

	while (a != 0) { //학번으로 수정할 학생을 찾는 과정
		if (students[a].id == id_to_find) { 
			break;
		}
		if (a > cnt) {
			cout << "Can't find the student id: " << id_to_find << endl;
			return;
		}
		a++;
	} 

	cout << "Score: ";
	cin >> how_to_fix; // 수정 후 점수
	if (how_to_fix < 0 || how_to_fix > 100) { // 점수가 0~100 범위 밖의 수일 경우
		cout << "Failed to edit: invalid exam score!" << endl;
		return;
	}

	if (exam == 1) // 중간고사 점수 수정
		students[a].midterm_score = how_to_fix;
	else if (exam == 2) // 기말고사 점수 수정
		students[a].final_score = how_to_fix;

	students[a].sum = students[a].midterm_score + students[a].final_score; // 수정했으므로 합계도 새로 저장

	cout << "Score editing done!" << endl;
	return;

}

void print_average(student students[], int cnt) { // 평균 출력
	int average = 0, whole_sum = 0;
	double square_sum = 0, sd = 0;

	if (cnt == 0) { // 학생이 0명 입력된 경우
		average = 0; sd = 0;
	}
	else 
	{
		for (int i = 1; i <= cnt; i++) {
			whole_sum += (students[i].sum);
		}

		average = whole_sum / cnt; // 평균

		for (int i = 1; i <= cnt; i++) {
			square_sum += (students[i].sum - average) * (students[i].sum - average);
		}

		sd = sqrt((double) square_sum / cnt); // 표준편차
	}
		

	cout << "Average score: " << setprecision(5) << average << endl;
	cout << "Standard deviation: " << setprecision(5) << sd << endl;

	return;
}

void print_score_list(student students[], int cnt) { // 점수 리스트 출력
	sort_student(students, cnt); // 성적을 기준으로 내림차순으로 학생을 정렬
	if (cnt != 0) { // 학생이 0명이 아닐 때
		for (int i = 1; i <= cnt; i++) {
			if (students[i].id == 0) break;
			cout << students[i].id << " " << students[i].name << " " << students[i].midterm_score << " ";
			cout << students[i].final_score << " " << students[i].sum << endl;
		}
	}
	cout << "Finished printing the list!" << endl;
}

char decide_grade(int sum, double top, int rank) { // 등급 결정, top은 학생의 상위 백분율 저장, rank는 등수 저장 
	if (sum > 150 && (top <= 30 || (cnt * 0.3 < 1 && rank <= 1))) 
		return 'A';

	else if (sum > 100 && (top <= 70 || (cnt * 0.7 && rank <= 2))) 
		return 'B';
	
	else if (sum > 50 && (!(top >= 90) || (cnt * 0.9 < 3 && rank <= 3))) 
		return 'C';
	
	else
		return 'D';

}

void print_grade_list(student students[], int cnt) { // 등급 리스트 출력
	sort_student(students, cnt); // 학생을 성적에 따라 내림차순으로 정렬

	if (cnt != 0) //학생이 0명이 아닌 경우
	{
		for (int i = 1; i <= cnt; i++) {
			double top = ((double)i / cnt) * 100; // 학생의 성적이 상위 몇 퍼센트인지(상위 백분율) 계산
			students[i].grade = decide_grade(students[i].sum, top, i); //등급 계산

			if (students[i].retake == 1 && students[i].grade != 'D') // 재수강한 학생의 경우 등급 하나 내림
				students[i].grade = (char)(students[i].grade + 1);
		}

		for (int i = 1; i <= cnt; i++) {
			if (students[i].id == 0) break;
			cout << students[i].id << " " << students[i].name << " " << students[i].sum << " ";
			cout << students[i].retake << " " << students[i].grade << endl;
		}
	}
	
	cout << "Finished printing the list!" << endl;
}

int main()
{
	int selection = 0;

	while (selection != 6) {
		print_menu();
		cin >> selection;

		switch (selection) { 
		case 1: cnt++; add_student(students, cnt); break; // 학생 추가
		case 2: edit_score(students); break; // 점수 수정
		case 3: print_average(students, cnt); break; // 평균 출력
 		case 4: print_score_list(students, cnt); break; // 점수표 출력
		case 5: print_grade_list(students, cnt); break; // 등급표 출력
		case 6: cout << "Good Bye!"; return 0; // 프로그램 종료
		default: cout << "Invalid input!" << endl; break; // selection 값으로 1~6 이외의 수가 들어온 경우
		}
	
	}
}