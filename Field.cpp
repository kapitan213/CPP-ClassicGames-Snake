#include "Field.h"
#include "GameExceptions.h" // ��� ������������� ����������
#include <iostream>         // ��� cout
#include <cstdlib>          // ��� rand(), srand()
#include <ctime>            // ��� time()

/* ���:                   �����������
   ���������:             ���������� �����, ���������� ��������
   ������������ ��������: -
   ��������:              ��������� ������ ��� ���� �� ���� � ��� ���������� */
Field::Field(int rows, int cols)
	: rows(0), cols(0), field(nullptr)
{
	// �������� ������������ ��������
	if (rows <= 0 || cols <= 0)
		throw IncorrectSizes("Field Constructor");

	// �������� ������������ � �������
	srand(time(nullptr));

	// ������������ ��������
	this->rows = rows;
	this->cols = cols;

	// ��������� ������ �� ����
	field = new char* [rows];
	for (int i = 0; i < rows; i++)
		field[i] = new char[cols];

	Clear(); // ��������� ���������� ����
}

/* ���:                   ����������
   ���������:             -
   ������������ ��������: -
   ��������:              �������� ������ ��� ���� �� ���� */
Field::~Field()
{
	if (field != nullptr)
	{
		for (int i = 0; i < rows; i++)
			delete[] field[i];
		delete[] field;
	}
}

/* ���:                   �����
   ���������:             -
   ������������ ��������: -
   ��������:              ���������� ���� ��������� � ������� �������� */
void Field::Clear()
{
	// ���� ���� �� ����������
	if (field == nullptr)
		return;

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			// ���� ��������� �� ������� - ������ ���������, ����� ������
			field[i][j] = (i == 0 || j == 0 || i == rows - 1 || j == cols - 1) ? '*' : ' ';
}

/* ���:                   �����
   ���������:             -
   ������������ ��������: -
   ��������:              ����� ���� �� ����� */
void Field::Show() const
{
	// ���� ���� �� ����������
	if (field == nullptr)
		return;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			std::cout << field[i][j];
		std::cout << '\n';
	}
}

/* ���:                   �����
   ���������:             ����� ��� ���������� �������, ������
   ������������ ��������: -
   ��������:              ��������� ������� �� ���� �� ��������� ������������ */
void Field::SetPoint(const Point & point, char ch)
{
	// ���� ���� �� ����������
	if (field == nullptr)
		return;

	// ���� ����� �� �������
	if (point.x == 0 || point.y == 0 || point.x == cols - 1 || point.y == rows - 1)
		throw CoordinatesOnBorder("Field::SetPoint Method");

	// ���� ����� ������������
	if (point.x < 0 || point.y < 0 || point.x >= cols || point.y >= rows)
		throw IncorrectCoordinates("Field::SetPoint Mehtod");

	// ���� ������ ������������ (�� ����� ���� ��� �� ������)
	if (ch != 'O' && ch != 'o' && ch != ' ')
		throw IncorrectCharacter("Field::SetPoint Method", ch);

	// ��������� ������� �� ������� �����������
	field[point.y][point.x] = ch;
}

/* ���:                   �����
   ���������:             -
   ������������ ��������: -
   ��������:              ��������� ������ �� ���� � ��������� ����� */
void Field::SetApple()
{
	// ���� ���� �� ����������
	if (field == nullptr)
		return;

	// ����� ���������� �����
	bool isFree = false;
	for (int i = 0; i < rows && !isFree; i++)
		for (int j = 0; j < cols; j++)
			if (field[i][j] == ' ')
			{
				isFree = true;
				break;
			}

	// ���� ���� ���������� �����
	if (!isFree)
		return;

	// ������� 0, rows - 1, cols - 1 ��� ������� ����. ��� ��� �� �����.
	// ���������� ��������� ����������
	int appleX;
	int appleY;

	// ���� �� ������ ������ �����
	do
	{
		// �������� ���������� ������
		appleX = rand() % (cols - 3) + 1; // 1 ... cols - 2
		appleY = rand() % (rows - 3) + 1; // 1 ... rows - 2
	} while (field[appleY][appleX] != ' ');

	// ��������� ������� ������ (Apple) �� ����
	field[appleY][appleX] = 'A';
}

/* ���:                   �����
   ���������:             �����
   ������������ ��������: ������, ������� ��������� � ���� �����
   ��������:              ����������� �������, ������� ��������� � �������� ����� */
char Field::GetElement(const Point & point) const
{
	// ���� ���� �� ����������
	if (field == nullptr)
		throw FieldIsNotCreated("Field::GetElement");

	// ���� ����� ������������
	if (point.x < 0 || point.y < 0 || point.x >= cols || point.y >= rows)
		IncorrectCoordinates("Field::GetElement");

	return field[point.y][point.x];
}
