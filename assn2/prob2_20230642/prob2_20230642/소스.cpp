#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
using namespace std;
string cypertext;

double calculate_noise(string text) { // ������ ��� �Լ�
	int noise_cnt = 0; // ������ ���� ����
	for (char ch : text) {
		if (ch == '#' || ch == '$' || ch == '%' || ch == '&' || ch == '*')
			noise_cnt++;
	}
	return 100 * (double) noise_cnt / text.size(); // ������ �� ����
}

string hexadecimal(string text) {
	string hexadecimal_text = "";
	for (char ch : text) {
		if (isxdigit(ch) != 0 && (isdigit(ch) != 0 || isupper(ch) != 0)) { // 16���� ���� �� �빮�� ���ĺ�/���ڸ� ����
			hexadecimal_text += ch;
		}
	}
	return hexadecimal_text;
}

void decryption(string text) {
	int cnt = text.size();
	if (cnt % 2 == 1) { // 16���� ���� ������ Ȧ��
		cout << "Undercryptable: the number of hexadecimal digits is odd!" << endl;
		return;
	}
	else if (cnt == 0) { // 16���� ���ڰ� ���� ���
		cout << "Undecryptable: where are the hexadecimal digits!" << endl;
		return;
	}

	string hex; // 16���� ���ڿ����� ���ڵ��� �� ���� ���� ���� �ӽ÷� �����ϴ� string
	string decrypted_text; // �ص��� ���ڰ� ����Ǵ� string
	int decrypted_int = 0;

	for (int i = 0; i < cnt; i += 2) {
		hex = "";
		hex += text[i]; 
		hex += text[i + 1];
		decrypted_int= stoi(hex, nullptr, 16); // 16������ 10������ ��ȯ

		if (decrypted_int > 126) { // �ƽ�Ű �ڵ� ������ ����� ���
			cout << "Undecryptable: invalid hexadecimal digits pair!" << endl;
			return;
		}
		decrypted_text += (char)decrypted_int; //�ƽ�Ű �ڵ� ����->���ڷ� ��ȯ�Ͽ� string�� ����
	}

	cout << "Decryption result: " << decrypted_text << endl;
	return;

}

int main()
{
	char ch;
	string cypertext; // �Է¹��� ���ڿ�

	cout << "Enter a cyphertext" << endl;
	while (cin.get(ch)) {
		if (ch == '.' && cypertext.size() >= 1 && cypertext.back() == '.') { //..�� �ԷµǸ� ..������ string�� ����
			cypertext += ch;
			break;
		}
		else
			cypertext += ch;
	}

	cout << "Ciphertext noise rate: " << setprecision(5) << calculate_noise(cypertext) << "%" << endl; // ����� ����� ��ȿ���� 5�ڸ��� ���
	
	string hexadecimal_text = hexadecimal(cypertext); // ���ڿ� �� 16���� ���ڸ� ���� �����ϴ� string
	cout << "Hexadecimal digits: " << hexadecimal_text << endl;

	decryption(hexadecimal_text); // ��ȣ �ص�
	
	cout << "Decryptor turn off!" << endl;
}