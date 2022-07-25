#include <iostream>
#include <windows.h>

using namespace std;

void DisplayBits(unsigned int);
unsigned int ShiftRight(unsigned int value);
unsigned int DatePacking(unsigned int date);
void DateUnpacking(unsigned int date);
unsigned int CountingBitsMask(int value, unsigned int bits);
unsigned int CountingBitsTable(int value);

int main()
{
	unsigned int num, num1, date = 0, date1;
	int num2;

	//10 вариант

	// 1 задание: вести целое число, вывести его представление в десятичной и двоичной формах
	cout << "----- Task 1 -----" << endl << endl << "Number: ";
	cin >> num;
	cout << endl << "Decimal form: " << num << endl;
	cout << "Binary form: ";
	DisplayBits(num);

	// 2 задание: переместить биты введенного числа на 3 байта вправо, при сдвиге за правую границу биты должны "вталкиваться" в левую
	cout << endl << "----- Task 2 -----" << endl << endl << "Answer: ";
	num1 = ShiftRight(num);
	DisplayBits(num1);

	// 3 задание: ввести месяц, число, час, минуту и секунду, упаковать их в одну переменную, вывести дату в двоичном и десятичном представлениях до и после упаковки
	cout << endl << "----- Task 3 -----" << endl << endl;
	date1 = DatePacking(date);
	cout << endl << "Packing: ";
	cout << date1 << " = ";
	DisplayBits(date1);
	cout << endl << "Unpacking: " << endl;
	DateUnpacking(date1);

	//4 задание: сделать подсчет битов двумя способами, используя шаблон с битом равным 1 и с помощью таблицы (массива), вывести в двочином и десятичном представлениях
	cout << endl << "----- Task 4 -----" << endl << endl << "Number: ";
	cin >> num2;
	cout << "Binary form: ";
	DisplayBits(num2);
	cout << endl << "The number of zeros in the first two bytes: " << endl;
	cout << endl << "Using a mask: " << CountingBitsMask(num2, 16) << endl;
	cout << "Using the table: " << CountingBitsTable(num2);
	cout << endl << endl;

	system("PAUSE");
	return 0;
}

void DisplayBits(unsigned int value) {
	unsigned int c = 0;
	unsigned int displayMask = 1 << 31;

	for (c = 1; c <= 32; c++)
	{
		cout << (value & displayMask ? '1' : '0');
		displayMask >>= 1;
		if (c % 8 == 0)   //для разделения актетов
		{
			cout << ' ';
		}
	}
	cout << endl;
}


unsigned int ShiftRight(unsigned int value) {
	unsigned int ans;
	unsigned int displayMask = 31 >> 1;   //0x0001

	for (unsigned int i = 0; i < 24; i++) { 
		ans = value & displayMask;
		value >>= 1;   //сдвиг вправо               
		if (ans) {
			value |= ans << 31;   //склеивание
		}
	}
	return value;
}

unsigned int DatePacking(unsigned int date) {
	unsigned int month, day, hour, min, sec;

	cout << "Month (1-12): ";
	cin >> month;
	cout << "Day (1-31): ";
	cin >> day;
	cout << "Hour: (0-23): ";
	cin >> hour;
	cout << "Minute: (0-59): ";
	cin >> min;
	cout << "Second: (0-59): ";
	cin >> sec;

	date = month;                //максимум 12, битов 4 (<16)
	date = date | (day << 4);    //максимум 31, битов 5 (<32)
	date = date | (hour << 9);   //максимум 23, битов 5 (<32)
	date = date | (min << 14);   //максимум 59, битов 6 (<64)
	date = date | (sec << 20);   //максимум 59, битов 6 (<64)
	return date;
}

void DateUnpacking(unsigned int date) {
	unsigned int month, day, hour, min, sec;

	month = date & 15;          //(30 >> 1)
	day = date & (31 << 4);
	day >>= 4;
	hour = date & (31 << 9);
	hour >>= 9;
	min = date & (63 << 14);
	min >>= 14;
	sec = date & (63 << 20);
	sec >>= 20;

	cout << endl << "Month: " << month << " = ";
	DisplayBits(month);
	cout << "Day: " << day << " = ";
	DisplayBits(day);
	cout << "Hour: " << hour << " = ";
	DisplayBits(hour);
	cout << "Minute: " << min << " = ";
	DisplayBits(min);
	cout << "Second: " << sec << " = ";
	DisplayBits(sec);
}

unsigned int CountingBitsMask(int value, unsigned int bits) {
	//используя шаблон
	unsigned int count = 0, mask = 1, c;

	for (c = 1; c <= bits; c++) {
		if (value & mask)
			count++;
		mask <<= 1;
	}
	return bits - count;   //для вычисления нулей
}

unsigned int CountingBitsTable(int value) {
	//используя таблицу
	unsigned int count;
	unsigned int c;
	unsigned char bitsMas[256];

	//заполнение таблицы
	for (c = 0; c <= 255; c++) {
		bitsMas[c] = CountingBitsMask(c, 8);
	}

	/*для прохождения по всем байтам
	count = bitsMas[value & 255] + bitsMas[(value & (255 << 8)) >> 8] + bitsMas[(value & (255 << 16)) >> 16] + bitsMas[(value & (255 << 24)) >> 24];*/

	//для первых двух байтов по условию задания
	count = bitsMas[value & 255] + bitsMas[(value & (255 << 8)) >> 8];
	return count;
}