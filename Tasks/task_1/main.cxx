#include<iostream>
#include <vector>
using namespace std;
enum status {
	BEGIN,//состояния начала 
	READ,//состояние чтения с консоли
	EXIT,//состояния проверки на выход со стороны пользователя
	ERROR,//состояние ошибки при вводе
	DO,//выполнеине задания
	END//состояние конца работы программы
};
int main()
{
	setlocale(LC_ALL, "RUS");
	int value; //число, считанное из консоли
	status st = BEGIN; //присвоить автомату начальное состояние
	string str; //Переменная для чтения из консоли
	int sum = 0; //Сумма делителей
	vector<int> vresult; //вектор значений делителей
	while (st != END)
	{
		switch (st)
		{
		case BEGIN:
			st = READ; //Переход из начального состояния в состояние чтения
			break;
		case READ:
			st = DO;
			cout << "[+] Введите натуральное число: ";
			cin >> str;
			for (int i = 0; i < str.size(); i++)
			{
				if (!isdigit(str.c_str()[i]))//проверка на натуральные числа
					st = EXIT;
			}
			break;
		case EXIT:
			if (str == "exit")
			{
				st = END;
				break;
			}
			else
				st = ERROR;
		case ERROR:
			cout << "[+] Введите натуральное число\t Для выхода введите exit\n";
			st = READ;
			break;
		case DO:
			value = atoi(str.c_str());
			if (value == 0) //Проверка на 0
			{
				cout << "0 не натуральное число\n";
				st = READ;
				break;
			}
			for (int i = 1; i <= value / 2; i++) //Расчет делителей
			{
				if (value % i == 0)
				{
					vresult.push_back(i);//Запись делителей в вектор в порядке возрастания
				}
			}
			vresult.push_back(value);
			cout << "Делители: ";
			for (vector<int>::iterator it = vresult.begin(); it != vresult.end()-1; ++it)
				cout << *it << ", ";
			cout << vresult.back() << "." << endl;
			cout << "Количество: " << vresult.size() <<"." << endl;
			for (vector<int>::iterator it = vresult.begin(); it != vresult.end(); ++it) //расчет суммы делителей
			{
				sum += *it;
			}
			cout << "Сумма: " << sum <<"."<< endl;
			st = END;
			break;
		case END:
			break;
		default:
			break;
		}
	}
	cout << endl;
	return 0;
}