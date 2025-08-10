#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
using namespace std;
string cypertext;

double calculate_noise(string text) { // 노이즈 계산 함수
	int noise_cnt = 0; // 노이즈 문자 개수
	for (char ch : text) {
		if (ch == '#' || ch == '$' || ch == '%' || ch == '&' || ch == '*')
			noise_cnt++;
	}
	return 100 * (double) noise_cnt / text.size(); // 노이즈 값 리턴
}

string hexadecimal(string text) {
	string hexadecimal_text = "";
	for (char ch : text) {
		if (isxdigit(ch) != 0 && (isdigit(ch) != 0 || isupper(ch) != 0)) { // 16진수 문자 중 대문자 알파벳/숫자만 저장
			hexadecimal_text += ch;
		}
	}
	return hexadecimal_text;
}

void decryption(string text) {
	int cnt = text.size();
	if (cnt % 2 == 1) { // 16진수 숫자 개수가 홀수
		cout << "Undercryptable: the number of hexadecimal digits is odd!" << endl;
		return;
	}
	else if (cnt == 0) { // 16진수 숫자가 없는 경우
		cout << "Undecryptable: where are the hexadecimal digits!" << endl;
		return;
	}

	string hex; // 16진수 문자열에서 문자들을 두 개씩 묶기 위해 임시로 저장하는 string
	string decrypted_text; // 해독된 문자가 저장되는 string
	int decrypted_int = 0;

	for (int i = 0; i < cnt; i += 2) {
		hex = "";
		hex += text[i]; 
		hex += text[i + 1];
		decrypted_int= stoi(hex, nullptr, 16); // 16진수를 10진수로 변환

		if (decrypted_int > 126) { // 아스키 코드 범위를 벗어나는 경우
			cout << "Undecryptable: invalid hexadecimal digits pair!" << endl;
			return;
		}
		decrypted_text += (char)decrypted_int; //아스키 코드 숫자->문자로 변환하여 string에 저장
	}

	cout << "Decryption result: " << decrypted_text << endl;
	return;

}

int main()
{
	char ch;
	string cypertext; // 입력받을 문자열

	cout << "Enter a cyphertext" << endl;
	while (cin.get(ch)) {
		if (ch == '.' && cypertext.size() >= 1 && cypertext.back() == '.') { //..이 입력되면 ..까지만 string에 저장
			cypertext += ch;
			break;
		}
		else
			cypertext += ch;
	}

	cout << "Ciphertext noise rate: " << setprecision(5) << calculate_noise(cypertext) << "%" << endl; // 노이즈를 계산해 유효숫자 5자리로 출력
	
	string hexadecimal_text = hexadecimal(cypertext); // 문자열 중 16진수 숫자를 따로 저장하는 string
	cout << "Hexadecimal digits: " << hexadecimal_text << endl;

	decryption(hexadecimal_text); // 암호 해독
	
	cout << "Decryptor turn off!" << endl;
}