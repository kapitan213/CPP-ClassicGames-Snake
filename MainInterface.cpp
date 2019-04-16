#include <iostream>  // ��� cout, cin
#include <fstream>   // ��� �������� ������
#include "MainInterface.h"

/* ���:                   �������
   ���������:             -
   ������������ ��������: -
   ��������:              ����� �������� �������� ���� */
void ShowMainMenu()
{
	using std::cout;
	cout << "1 - Start Game   \n";
	cout << "2 - Options      \n";
	cout << "3 - About Author \n";
	cout << "0 - Quit         \n";
}

/* ���:                   �������
   ���������:             -
   ������������ ��������: -
   ��������:              ����� ������� ���� ����� */
void ShowOptionsMenu()
{
	using std::cout;
	cout << "1 - Change size of the field  \n";
	cout << "2 - Change speed of the snake \n";
	cout << "0 - Return to the main menu   \n";
}

/* ���:                   �������
   ���������:             -
   ������������ ��������: -
   ��������:              �������� ������ �� ������ �������� */
void ClearBuffer()
{
	while (std::cin.get() != '\n')
		continue;

	system("cls");
}

/* ���:                   �������
   ���������:             -
   ������������ ��������: -
   ��������:              ����� ��������� � ����� ���� */
void ShowTheEnd()
{
	using std::cout;
	system("cls");
	cout << "You are dead\n";
	system("pause");
	system("cls");
}

/* ���:                   �������
   ���������:             ������ �� ���������� �����, ������ �� ���������� ��������
   ������������ ��������: -
   ��������:              ���� �������� ���� */
void SetSizes(int& rows, int& columns)
{
	using std::cout;
	using std::cin;

	// ���� ���������� �����
	do
	{
		cout << "Enter a number of rows (10...40): ";
		cin >> rows;
		ClearBuffer();
		if (rows < 10 || rows > 40)
			cout << "Incorrect number. Enter a number in the diapason. Try again.\n";
	} while (rows < 10 || rows > 40);

	// ���� ���������� ��������
	do
	{
		cout << "Enter a number of columns (10...40): ";
		cin >> columns;
		ClearBuffer();
		if (columns < 10 || columns > 40)
			cout << "Incorrect number. Enter a number in the diapason. Try again.\n";
	} while (columns < 10 || columns > 40);
}

/* ���:                   �������
   ���������:             ������ �� �������� ��������
   ������������ ��������: -
   ��������:              ���� �������� ������ */
void EnterSpeed(int& speed)
{
	using std::cout;
	using std::cin;

	// ���� ��������
	do
	{
		cout << "Enter a new speed (100...500): ";
		cin >> speed;
		ClearBuffer();
		if (speed < 100 || speed > 500)
			cout << "Incorrect speed. Enter a number in the diapason. Try again.\n";
	
	} while (speed < 100 || speed > 500);
}

/* ���:                   �������
   ���������:             -
   ������������ ��������: -
   ��������:              ����� ���������� � ��������� ���� � ������ */
void AboutAuthor()
{
	// �������� ������� ��� ������
	const int SIZE = 400;
	char text[SIZE] = "";

	// �������� �����
	std::ifstream fin("AboutAuthor.txt", std::ios_base::in);

	// ���� ���� ������� �������
	if (fin.is_open())
	{
		// ��������� � ����� �������, ���� �� ������ �� ���������� ��������
		// (����� ����-������ ���������) ��� ���� �� ������ �� ����� �����
		for (int i = 0; i < SIZE - 1 && !fin.eof(); i++)
			text[i] = fin.get();

		// ������� ����� �� �����, ������ �����, ������� �����
		// � ����������� ����� �� �����
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
