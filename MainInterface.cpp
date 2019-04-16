#include <iostream>  // для cout, cin
#include <fstream>   // для открытия файлов
#include "MainInterface.h"

/* Тип:                   Функция
   Параметры:             -
   Возвращаемое значение: -
   Описание:              вывод пукнктов главного меню */
void ShowMainMenu()
{
	using std::cout;
	cout << "1 - Start Game   \n";
	cout << "2 - Options      \n";
	cout << "3 - About Author \n";
	cout << "0 - Quit         \n";
}

/* Тип:                   Функция
   Параметры:             -
   Возвращаемое значение: -
   Описание:              вывод пунктов меню опций */
void ShowOptionsMenu()
{
	using std::cout;
	cout << "1 - Change size of the field  \n";
	cout << "2 - Change speed of the snake \n";
	cout << "0 - Return to the main menu   \n";
}

/* Тип:                   Функция
   Параметры:             -
   Возвращаемое значение: -
   Описание:              очищение буфера от лишних символов */
void ClearBuffer()
{
	while (std::cin.get() != '\n')
		continue;

	system("cls");
}

/* Тип:                   Функция
   Параметры:             -
   Возвращаемое значение: -
   Описание:              вывод сообщения о конце игры */
void ShowTheEnd()
{
	using std::cout;
	system("cls");
	cout << "You are dead\n";
	system("pause");
	system("cls");
}

/* Тип:                   Функция
   Параметры:             ссылка на количество строк, ссылка на количество столбцев
   Возвращаемое значение: -
   Описание:              ввод размеров поля */
void SetSizes(int& rows, int& columns)
{
	using std::cout;
	using std::cin;

	// Ввод количества строк
	do
	{
		cout << "Enter a number of rows (10...40): ";
		cin >> rows;
		ClearBuffer();
		if (rows < 10 || rows > 40)
			cout << "Incorrect number. Enter a number in the diapason. Try again.\n";
	} while (rows < 10 || rows > 40);

	// Ввод количества столбцев
	do
	{
		cout << "Enter a number of columns (10...40): ";
		cin >> columns;
		ClearBuffer();
		if (columns < 10 || columns > 40)
			cout << "Incorrect number. Enter a number in the diapason. Try again.\n";
	} while (columns < 10 || columns > 40);
}

/* Тип:                   Функция
   Параметры:             ссылка на значение скорости
   Возвращаемое значение: -
   Описание:              ввод скорости змейки */
void EnterSpeed(int& speed)
{
	using std::cout;
	using std::cin;

	// Ввод скорости
	do
	{
		cout << "Enter a new speed (100...500): ";
		cin >> speed;
		ClearBuffer();
		if (speed < 100 || speed > 500)
			cout << "Incorrect speed. Enter a number in the diapason. Try again.\n";
	
	} while (speed < 100 || speed > 500);
}

/* Тип:                   Функция
   Параметры:             -
   Возвращаемое значение: -
   Описание:              вывод информации о создателе игры и версии */
void AboutAuthor()
{
	// Создание массива для текста
	const int SIZE = 400;
	char text[SIZE] = "";

	// Открытие файла
	std::ifstream fin("AboutAuthor.txt", std::ios_base::in);

	// Если файл удалось открыть
	if (fin.is_open())
	{
		// считываем в масив символы, пока не дойдем до последнего элемента
		// (чтобы нуль-символ сохранить) или пока не дойдем до конца файла
		for (int i = 0; i < SIZE - 1 && !fin.eof(); i++)
			text[i] = fin.get();

		// выводим текст на экран, делаем паузу, очищаем экран
		// и отсоединаем поток от файла
		std::cout << text << std::endl;
		system("pause");
		system("cls");
		fin.close();
	}
	else
	{
		std::cout << "Couldn't find a file about the author.\n";
		system("pause");
	}
}
