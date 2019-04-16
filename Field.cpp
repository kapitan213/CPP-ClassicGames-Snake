#include "Field.h"
#include "GameExceptions.h" // для использования исключений
#include <iostream>         // для cout
#include <cstdlib>          // для rand(), srand()
#include <ctime>            // для time()

/* Тип:                   Конструктор
   Параметры:             количество строк, количество столбцев
   Возвращаемое значение: -
   Описание:              выделение памяти для поля на куче и его заполнение */
Field::Field(int rows, int cols)
	: rows(0), cols(0), field(nullptr)
{
	// Проверка корректности размеров
	if (rows <= 0 || cols <= 0)
		throw IncorrectSizes("Field Constructor");

	// привязка рандомизации к времени
	srand(time(nullptr));

	// Встановление размеров
	this->rows = rows;
	this->cols = cols;

	// Выделение памяти на куче
	field = new char* [rows];
	for (int i = 0; i < rows; i++)
		field[i] = new char[cols];

	Clear(); // начальное заполнение поля
}

/* Тип:                   Деструктор
   Параметры:             -
   Возвращаемое значение: -
   Описание:              очищение памяти под поле на кучи */
Field::~Field()
{
	if (field != nullptr)
	{
		for (int i = 0; i < rows; i++)
			delete[] field[i];
		delete[] field;
	}
}

/* Тип:                   Метод
   Параметры:             -
   Возвращаемое значение: -
   Описание:              заполнение поля границами и пустыми клетками */
void Field::Clear()
{
	// Если поля не существует
	if (field == nullptr)
		return;

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			// Если находимся на границе - ставим звездочку, иначе пробел
			field[i][j] = (i == 0 || j == 0 || i == rows - 1 || j == cols - 1) ? '*' : ' ';
}

/* Тип:                   Метод
   Параметры:             -
   Возвращаемое значение: -
   Описание:              вывод поля на экран */
void Field::Show() const
{
	// Если поля не существует
	if (field == nullptr)
		return;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			std::cout << field[i][j];
		std::cout << '\n';
	}
}

/* Тип:                   Метод
   Параметры:             точка для постановки символа, символ
   Возвращаемое значение: -
   Описание:              установка символа на поле за заданными координатами */
void Field::SetPoint(const Point & point, char ch)
{
	// Если поля не существует
	if (field == nullptr)
		return;

	// Если точка на границе
	if (point.x == 0 || point.y == 0 || point.x == cols - 1 || point.y == rows - 1)
		throw CoordinatesOnBorder("Field::SetPoint Method");

	// Если точка неккоректная
	if (point.x < 0 || point.y < 0 || point.x >= cols || point.y >= rows)
		throw IncorrectCoordinates("Field::SetPoint Mehtod");

	// Если символ неккоректный (не часть змеи или не пробел)
	if (ch != 'O' && ch != 'o' && ch != ' ')
		throw IncorrectCharacter("Field::SetPoint Method", ch);

	// Установка символа по заданым координатам
	field[point.y][point.x] = ch;
}

/* Тип:                   Метод
   Параметры:             -
   Возвращаемое значение: -
   Описание:              установка яблока на поле в рандомном месте */
void Field::SetApple()
{
	// Если поля не существует
	if (field == nullptr)
		return;

	// Поиск свободного места
	bool isFree = false;
	for (int i = 0; i < rows && !isFree; i++)
		for (int j = 0; j < cols; j++)
			if (field[i][j] == ' ')
			{
				isFree = true;
				break;
			}

	// Если нету свободного места
	if (!isFree)
		return;

	// Индексы 0, rows - 1, cols - 1 это границы поля. Нам они не нужны.
	// Генерируем рандомные координаты
	int appleX;
	int appleY;

	// Пока не найдем пустое место
	do
	{
		// Рандомим координаты яблока
		appleX = rand() % (cols - 3) + 1; // 1 ... cols - 2
		appleY = rand() % (rows - 3) + 1; // 1 ... rows - 2
	} while (field[appleY][appleX] != ' ');

	// Установка символа яблока (Apple) на поле
	field[appleY][appleX] = 'A';
}

/* Тип:                   Метод
   Параметры:             точка
   Возвращаемое значение: символ, который находится в этой точке
   Описание:              возвращение символа, который находится в указаной точке */
char Field::GetElement(const Point & point) const
{
	// Если поля не существует
	if (field == nullptr)
		throw FieldIsNotCreated("Field::GetElement");

	// Если точка неккоректная
	if (point.x < 0 || point.y < 0 || point.x >= cols || point.y >= rows)
		IncorrectCoordinates("Field::GetElement");

	return field[point.y][point.x];
}
