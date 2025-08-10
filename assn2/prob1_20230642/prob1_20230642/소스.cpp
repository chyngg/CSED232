#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;
int cnt = 0; // �Է¹��� �л� ��

struct student { // ����ü�� ����� �л��� ���� ����
	long long id; //�й�
	string name; // �̸�
	int midterm_score; // �߰���� ����
	int final_score; // �⸻��� ����
	int retake; // ����� ����
	int sum; // �߰����+�⸻��� ���� �հ�
	char grade; // ���
};

student students[101] = {};

void print_menu() // �޴� ���
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

void add_student(student students[], int cnt) { // �л� �߰�
	long id = 0; string name = ""; 
	int midterm_score = 0, final_score = 0, retake = -1;
	cout << "Student id: ";
	cin >> id;
	if (id < 10000000 || id > 99999999) { // �й��� 8�ڸ� ���� ������ �ƴ� ���
		cout << "Failed to add: invalid student id!" << endl;
		return;
	}

	cout << "Name: ";
	cin >> name;
	for (char ch : name) {
		if (!isalpha(static_cast<unsigned char>(ch))) { // �̸��� ���ĺ� �̿��� ���ڰ� �� ���� ���
			cout << "Failed to add: invalid name!" << endl;
			return;
		}
	}

	cout << "Midterm exam score: ";
	cin >> midterm_score;
	if (midterm_score < 0 || midterm_score > 100) { // �߰���� ���� ������ 0~100�� �ƴ� ���
		cout << "Failed to add: invalid midterm exam score!" << endl;
		return;
	}

	cout << "Final exam score: ";
	cin >> final_score;
	if (final_score < 0 || final_score > 100) { // �⸻��� ���� ������ 0~100�� �ƴ� ���
		cout << "Failed to add: invalid final exam score!" << endl;
		return;
	}
	
	cout << "Retake: ";
	cin >> retake;
	if (retake != 0 && retake != 1) { // ����� ���� - 0 or 1 ���� �ٸ� ���� �ԷµǾ��� ���
		cout << "Failed to add: invalid retake value!" << endl;
		return;
	}
	// ��� ������ �ùٸ��� ������ ����ü �迭�� ���� ����
	students[cnt].id = id;  students[cnt].name = name;
	students[cnt].midterm_score = midterm_score; students[cnt].final_score = final_score;
	students[cnt].retake = retake;
	students[cnt].sum = midterm_score + final_score;

	cout << "The student is added!" << endl;
} 

void sort_student(student students[], int cnt) { // ������ ���� ������������ �л��� ����
	student temp = students[0];
	for (int i = 1; i < cnt; i++) {
		for (int j = 1; j <= cnt - i; j++) { // Bubble Sort
			if (students[j].sum < students[j + 1].sum) { 
				temp = students[j];
				students[j] = students[j + 1];
				students[j + 1] = temp;
			}
			else if (students[j].sum == students[j + 1].sum && students[j].id > students[j + 1].id) { // ������ ���� ��� �й��� �������� �������� ����
				temp = students[j];
				students[j] = students[j + 1];
				students[j + 1] = temp;
			}
		}
	}
	return;
}

void edit_score(student students[]) { // ���� ����
	int exam;
	int a = 1;
	long id_to_find = 0;
	int how_to_fix = 0;

	cout << "--------Function--------\n";
	cout << "1. Edit the midterm exam score" << endl;
	cout << "2. Edit the final exam score" << endl;
	cout << "------------------------\n" << "Selection: ";
	cin >> exam; // � ���� ������ �������� ����

	cout << "Student id: ";
	cin >> id_to_find; // ������ �л��� �й�
	if (id_to_find < 10000000 || id_to_find > 99999999) { // �й��� 8�ڸ� ���� ������ �ƴ� ���
		cout << "Failed to edit: invalid student id!" << endl; 
		return;
	}

	while (a != 0) { //�й����� ������ �л��� ã�� ����
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
	cin >> how_to_fix; // ���� �� ����
	if (how_to_fix < 0 || how_to_fix > 100) { // ������ 0~100 ���� ���� ���� ���
		cout << "Failed to edit: invalid exam score!" << endl;
		return;
	}

	if (exam == 1) // �߰���� ���� ����
		students[a].midterm_score = how_to_fix;
	else if (exam == 2) // �⸻��� ���� ����
		students[a].final_score = how_to_fix;

	students[a].sum = students[a].midterm_score + students[a].final_score; // ���������Ƿ� �հ赵 ���� ����

	cout << "Score editing done!" << endl;
	return;

}

void print_average(student students[], int cnt) { // ��� ���
	int average = 0, whole_sum = 0;
	double square_sum = 0, sd = 0;

	if (cnt == 0) { // �л��� 0�� �Էµ� ���
		average = 0; sd = 0;
	}
	else 
	{
		for (int i = 1; i <= cnt; i++) {
			whole_sum += (students[i].sum);
		}

		average = whole_sum / cnt; // ���

		for (int i = 1; i <= cnt; i++) {
			square_sum += (students[i].sum - average) * (students[i].sum - average);
		}

		sd = sqrt((double) square_sum / cnt); // ǥ������
	}
		

	cout << "Average score: " << setprecision(5) << average << endl;
	cout << "Standard deviation: " << setprecision(5) << sd << endl;

	return;
}

void print_score_list(student students[], int cnt) { // ���� ����Ʈ ���
	sort_student(students, cnt); // ������ �������� ������������ �л��� ����
	if (cnt != 0) { // �л��� 0���� �ƴ� ��
		for (int i = 1; i <= cnt; i++) {
			if (students[i].id == 0) break;
			cout << students[i].id << " " << students[i].name << " " << students[i].midterm_score << " ";
			cout << students[i].final_score << " " << students[i].sum << endl;
		}
	}
	cout << "Finished printing the list!" << endl;
}

char decide_grade(int sum, double top, int rank) { // ��� ����, top�� �л��� ���� ����� ����, rank�� ��� ���� 
	if (sum > 150 && (top <= 30 || (cnt * 0.3 < 1 && rank <= 1))) 
		return 'A';

	else if (sum > 100 && (top <= 70 || (cnt * 0.7 && rank <= 2))) 
		return 'B';
	
	else if (sum > 50 && (!(top >= 90) || (cnt * 0.9 < 3 && rank <= 3))) 
		return 'C';
	
	else
		return 'D';

}

void print_grade_list(student students[], int cnt) { // ��� ����Ʈ ���
	sort_student(students, cnt); // �л��� ������ ���� ������������ ����

	if (cnt != 0) //�л��� 0���� �ƴ� ���
	{
		for (int i = 1; i <= cnt; i++) {
			double top = ((double)i / cnt) * 100; // �л��� ������ ���� �� �ۼ�Ʈ����(���� �����) ���
			students[i].grade = decide_grade(students[i].sum, top, i); //��� ���

			if (students[i].retake == 1 && students[i].grade != 'D') // ������� �л��� ��� ��� �ϳ� ����
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
		case 1: cnt++; add_student(students, cnt); break; // �л� �߰�
		case 2: edit_score(students); break; // ���� ����
		case 3: print_average(students, cnt); break; // ��� ���
 		case 4: print_score_list(students, cnt); break; // ����ǥ ���
		case 5: print_grade_list(students, cnt); break; // ���ǥ ���
		case 6: cout << "Good Bye!"; return 0; // ���α׷� ����
		default: cout << "Invalid input!" << endl; break; // selection ������ 1~6 �̿��� ���� ���� ���
		}
	
	}
}