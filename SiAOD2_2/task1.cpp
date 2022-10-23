#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

void createF(string name); //�������� � ���������� ����� � ����������
void createRandF(string name); //�������� � ���������� ����� ��������
void printF(string name); //���� ����������� �����
void addString(string name, string s); //���������� ����� ������ � ����� �����
string searchVal(string name, int num); //�������� ����� �� ������ � �����
int numSum(string name); //���������� ����� � �����
void createNewF(string name); //����� ���� � �������� �� ����� �����



int main()
{
	srand(time(0));
	setlocale(LC_ALL, "rus");
	short problem, typeCreate;
	bool flag = true;
	string fileName, s;
	int num;
	while (flag)
	{
		system("cls");
		cout << "������������ ������ �2 ����-06-21 �������� �.�. ������� 30" << "\n\n"
			"����\n"
			"1) �������� ���������� ����� ��������� ASCII, ����������� ���������� ����� �� ��������� ����� �� ������.\n"
			"2) ����� ����������� ���������� �����.\n"
			"3) ���������� ����� ������ � ����� �����.\n"
			"4) ��������� �������� �����, ������ ��� ���������� ����� � �����, � ������� ��� ��������.\n"
			"5) ���������� ���������� ����� � �����.\n"
			"6) ������� ���� � �������� �� ����� ��������� �����.\n";
		cout << "��� �����: ";
		cin >> problem;
		switch (problem) {
		case 1:
		{
			cout << "������� ��� �����: ";
			cin >> fileName;
			cout << "��� ���������� � ���������� ������� 0, ����� (���������� �������) ����� ������ �����: ";
			cin >> typeCreate;
			if (typeCreate == 0) createF(fileName);
			else createRandF(fileName);
			system("pause");
			break;
		}
		case 2:
		{
			cout << endl;
			printF(fileName);
			system("pause");
			break;
		}
		case 3:
		{
			cout << "������� �����: ";
			cin.ignore();
			getline(cin, s);
			addString(fileName, s);
			system("pause");
			break;
		}
		case 4:
		{
			cout << "������� ���������� ����� ����� � �����: ";
			cin >> num;
			if (searchVal(fileName, num) == "") {
				cout << "����� � �������� ������� �� �������\n";
			}
			else {
				cout << "�������� ����� �����: " << searchVal(fileName, num) << '\n';
			}
			system("pause");
			break;
		}
		case 5:
		{
			cout << "���������� ����� � �����:" << numSum(fileName) << '\n';
			system("pause");
			break;
		}
		case 6:
		{
			createNewF(fileName);
			cout << endl;
			printF("matrix.txt");
			system("pause");
			break;
		}
		break;
		default:
			cout << "��������, � �� ������ �������, ��� �� ������ �������. ���������� � ������ ���.\n";
			system("pause");
			break;
		}
	}
	return 0;
}

void createF(string name) {
	int lines;
	cout << "������� ���������� ����� � �����: ";
	cin >> lines;
	cout << "������� ���������� �����: \n";
	string s;
	ofstream f(name);
	cin.ignore();
	for (int i = 0; i < lines; i++) {
		getline(cin, s);
		f << s << '\n';
	}
	f.close();
}

void createRandF(string name) {
	int lines = 3 + (rand() % 8);
	string s;
	ofstream f(name);
	for (int i = 0; i < lines; i++) {
		int k = 3 + rand() % 8;
		for (int j = 0; j < k; j++) {
			if (j == k - 1) s = s + to_string(1 + (rand() % 1000));
			else s = s + to_string(1 + (rand() % 1000)) + " ";
		}
		f << s << '\n';
		s = "";
	}
	f.close();
}

void printF(string name) {
	ifstream f(name);
	string s;
	while (!f.eof())
	{
		getline(f, s);
		cout << s << '\n';
	}
	f.close();
}

void addString(string name, string s) {
	ofstream f(name, ios::app);
	f << s << '\n';
	f.close();
}

string searchVal(string name, int num) {
	ifstream f(name);
	string s, val="";
	int k = 0;
	while (!f.eof())
	{
		getline(f, s);
		for (int i = 0; i < s.length(); i++) {
			if ((char(s[i]) >= 48) && ((char(s[i]) <= 57))) {
				val = val +  s[i];
			}
			else
			{
				k++;
				if (k == num) break;
				else val = "";
			}
		}
		if (k == num) break;
		k++;
		if (k == num) break;
		else val = "";
	}
	f.close();
	return val;
}

int numSum(string name) {
	ifstream f(name);
	string s;
	int k = 0;
	while (!f.eof())
	{
		getline(f, s);
		for (int i = 0; i < s.length(); i++) {
			if ((char(s[i]) >= 48) && ((char(s[i]) <= 57))) {
				continue;
			}
			else
			{
				k++;
			}
		}
		k++;
	}
	f.close();
	return k-1;
}

void createNewF(string name) {
	ifstream f(name);
	ofstream f2("matrix.txt");
	int k = sqrt(numSum(name)), curK = k, currentK = k;
	string s, s2;
	f2 << "������ �������: " << k << '\n';
	while (!f.eof()){
		getline(f, s);
		for (int i = 0; i < s.length(); i++) {
			if ((char(s[i]) >= 48) && ((char(s[i]) <= 57))) {
				s2 = s2 + s[i];
			}
			else
			{
				currentK--;
				if (currentK == 0) {
					curK--;
					f2 << s2 << '\n';
					s2 = "";
					currentK = k;
					break;
				}
				else s2 = s2 + " ";
			}
		}
		currentK--;
		if (currentK == 0) {
			curK--;
			f2 << s2 << '\n';
			s2 = "";
			currentK = k;
		}
		else s2 = s2 + " ";
		if (curK == 0) {
			break;
		}
	}
	f.close();
	f2.close();
}