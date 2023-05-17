//ЮФУ, ИКТИБ, МОП ЭВМ
//Программирование и основы теории алгоритмов
//Индивидуальное задание №2
//КТбо1-7 ПоповДС
//Вариант №30
//07.05.2023

#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include <map>
#include <fstream>

//Структура для хранения ленты машины Тьюринга
//vector <char> lenta	- лента машины Тьюринга
//int golovka			- головка машины Тьюринга. Показывает на каком элементе вектора(ленты) находится головка.
struct lenta {
	vector <char> lenta;
	int golovka;
};

//Структура для хранения системы команд машины тьюринга
//map <char, char> DvigenieGol	- символ и направление сдвига головки машины Тьюринга в которое машина сдвинется по нему 
//map <char, char> Simvol		- символ и значение, которое запишется на ленту в зависимости от него. Символ 'O' означает, что символ остается без изменений
//map <char, int> SmenaSost		- символ и состояние в которое перейдет машина Тьюринга по нему
struct mashinaT {
	map <char, char> DvigenieGol;
	map <char, char> Simvol;
	map <char, int> SmenaSost;
};

//Функция инициализации системы команд
//Входные параметры:        struct mashinaT* ptr_mashinaT - указатель на структуру.
//Выходные данные:          функция ничего не возвращает
void initsializatsia(struct mashinaT* ptr_mashinaT) {
	ifstream fin("INPUT.txt");
	int N;
	fin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 7; j++) {
			char simvol, napr, znach;
			int sost;
			fin >> simvol >> napr >> znach >> sost;
			ptr_mashinaT[i].DvigenieGol[simvol] = napr;
			ptr_mashinaT[i].Simvol[simvol] = znach;
			ptr_mashinaT[i].SmenaSost[simvol] = sost;
		}
	}
}

//Функция проверки коректности строки
//Входные параметры:    string STR - сама строка
//Выходные данные:      true, если строка корректна или false, если некорректна
bool proverka(string STR) {
	int X = 0;
	int Y = 0;
	int Z = 0;
	int m = 0;
	int p = 0;
	for (int i = 0; i < STR.size(); i++) {
		if (STR[i] != '1' && STR[i] != '+' && STR[i] != '-') {
			return false;
			break;
		}
		if (STR[i] == '+') {
			p +=1;
		}
		if (STR[i] == '-') {
			m +=1;
		}
		if (STR[i] == '1' && p == false) {
			X++;
		}
		if (STR[i] == '1' && p == true && m == false) {
			Y++;
		}
		if (STR[i] == '1' && p == true && m == true) {
			Z++;
		}
	}
	if (p !=1 || m != 1 || (X + Y < Z)) {
		return false;
	}
	return true;
}

//Функция реализации одного шага работы машины Тьюринга.
//Входные параметры:	struct lenta* ptr_lenta - указатель на структуру ленты
//						struct mashinaT* ptr_mashinaT - указатель на структуру системы команд
//						int &sostoyanie - номер состояния машины
//Выходные данные:		Функция ничего не возвращает
void function_perehoda(struct lenta* ptr_lenta, struct mashinaT* ptr_mashinaT, int &sostoyanie) {
	char simvol = ptr_lenta->lenta[ptr_lenta->golovka];
	if (simvol == '!' && ptr_lenta->golovka == ptr_lenta->lenta.size() - 1) {
		ptr_lenta->lenta.insert(ptr_lenta->lenta.end(),'!');
	}
	if (ptr_mashinaT[sostoyanie].Simvol[simvol] != 'O') {
		ptr_lenta->lenta[ptr_lenta->golovka] = ptr_mashinaT[sostoyanie].Simvol[simvol];
	}
	if (ptr_mashinaT[sostoyanie].DvigenieGol[simvol] == 'R') {
		ptr_lenta->golovka++;
	}
	if (ptr_mashinaT[sostoyanie].DvigenieGol[simvol] == 'L') {
		ptr_lenta->golovka--;
	}
	sostoyanie = ptr_mashinaT[sostoyanie].SmenaSost[simvol];
}

int main()
{
	setlocale(LC_ALL, "Russian");
	struct lenta* ptr_lenta;
	ptr_lenta = new struct lenta;
	struct mashinaT* ptr_mashinaT;
	ptr_mashinaT = new struct mashinaT[27];
	string STR;
	bool chek = true;
	ptr_lenta->golovka = 1;
	int sostoyanie = 1;
	initsializatsia(ptr_mashinaT);
	do {
		ptr_lenta->lenta.insert(ptr_lenta->lenta.end(), '!');
		cout << "Введите задачу" << endl;
		cin >> STR;
		chek = proverka(STR);
		if (chek) {
			cout << "Текущее состояние:" << sostoyanie << endl;
			for (int i = 0; i < STR.size(); i++) {
				ptr_lenta->lenta.insert(ptr_lenta->lenta.end(), STR[i]);
			}
			ptr_lenta->lenta.insert(ptr_lenta->lenta.end(), '!');
			for (int j = 0; j < ptr_lenta->lenta.size(); j++) {
				cout << ptr_lenta->lenta[j];
			}
			cout << endl;
			for (int j = 0; j < ptr_lenta->golovka; j++) {
				cout << " "; 
			}
			cout << "^" << endl;
			int pol_gol;
			while (sostoyanie != 0) {
				function_perehoda(ptr_lenta, ptr_mashinaT, sostoyanie);
				cout << "Текущее состояние:" << sostoyanie << endl;
				pol_gol = 0;
				for (int j = 0; j < ptr_lenta->lenta.size(); j++) {
					if (ptr_lenta->lenta[j] != '!' || ptr_lenta->lenta[j + 1] != '!') {
						cout << ptr_lenta->lenta[j];
					}
					else {
						pol_gol++;
					}
				}
				cout << endl;
				for (int j = pol_gol; j < ptr_lenta->golovka; j++) {
					cout << " "; 
				}
				cout << "^" << endl;
			}
			cout << "Вычисление завершено" << endl;
		}
		else { 
			cout << "Ошибка! Введеная задача не соответствует условию" << endl;
		}
		cout << "Хотите продолжить работу?" << endl;
		cout << "1 - да" << endl;
		cout << "2 - нет" << endl;;
		int x;
		cin >> x;
		if (x == 1) {
			chek = true;
		}
		else {
			chek = false;
		}
		sostoyanie = 1;
		ptr_lenta->golovka = 1;
		ptr_lenta->lenta.clear();
	} while (chek);
	cout << "Хорошего дня!";
}