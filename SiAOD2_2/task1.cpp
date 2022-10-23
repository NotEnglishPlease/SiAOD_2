#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

void createF(string name); //создание и заполнение файла с клавиатуры
void createRandF(string name); //создание и заполнение файла случайно
void printF(string name); //вывд содержимого файла
void addString(string name, string s); //добавление новой строки в конец файла
string searchVal(string name, int num); //значение числа по номеру в файле
int numSum(string name); //количество чисел в файле
void createNewF(string name); //новый файл с матрицей из чисел файла



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
		cout << "Практическая работа №2 ИКБО-06-21 Эрднеева Н.Д. Варинат 30" << "\n\n"
			"Меню\n"
			"1) Создание текстового файла кодировки ASCII, содержащего десятичные числа по несколько чисел на строке.\n"
			"2) Вывод содержимого текстового файла.\n"
			"3) Добавление новой строки в конец файла.\n"
			"4) Прочитать значение числа, указав его порядковый номер в файле, и вернуть его значение.\n"
			"5) Определить количество чисел в файле.\n"
			"6) Создать файл с матрицей из чисел исходного файла.\n";
		cout << "Ваш выбор: ";
		cin >> problem;
		switch (problem) {
		case 1:
		{
			cout << "Введине имя файла: ";
			cin >> fileName;
			cout << "Для заполнение с клавиатуры введите 0, иначе (случайными числами) любую другую цифру: ";
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
			cout << "Введите стоку: ";
			cin.ignore();
			getline(cin, s);
			addString(fileName, s);
			system("pause");
			break;
		}
		case 4:
		{
			cout << "Введите порядковый номер числа в файле: ";
			cin >> num;
			if (searchVal(fileName, num) == "") {
				cout << "Число с заданным номером не найдено\n";
			}
			else {
				cout << "Значение этого числа: " << searchVal(fileName, num) << '\n';
			}
			system("pause");
			break;
		}
		case 5:
		{
			cout << "Количество чисел в файле:" << numSum(fileName) << '\n';
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
			cout << "Извините, я не совсем понимаю, что вы хотите сделать. Попробуйте в другой раз.\n";
			system("pause");
			break;
		}
	}
	return 0;
}

void createF(string name) {
	int lines;
	cout << "Введите количество строк в файле: ";
	cin >> lines;
	cout << "Введите содержимое файла: \n";
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
	f2 << "Размер матрицы: " << k << '\n';
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