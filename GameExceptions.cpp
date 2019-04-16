#include "GameExceptions.h"
#include <iostream>
#include <cstring>

/* ���:                   �����������
   ���������:             ��������� �� ������, ����������� ����� ��������� ������
   ������������ ��������: -
   ��������:              ����������� ��������� �� where � errorPlace */
GameException::GameException(const char* where)
{
	strcpy_s(errorPlace, 30, strlen(where) < 30 ? where : "NOTHING");
}

/* ���:                   �����
   ���������:             -
   ������������ ��������: -
   ��������:              ����� ���������� �� ������ �� ����� */
void IncorrectSizes::Show() const
{
	std::cout << "Error. Incorrect sizes in " << errorPlace << std::endl;
}

/* ���:                   �����
   ���������:             -
   ������������ ��������: -
   ��������:              ����� ���������� �� ������ �� ����� */
void CoordinatesOnBorder::Show() const
{
	std::cout << "Error. Coordinates of the point on a border in " << errorPlace << std::endl;
}

/* ���:                   �����
   ���������:             -
   ������������ ��������: -
   ��������:              ����� ���������� �� ������ �� ����� */
void IncorrectCoordinates::Show() const
{
	std::cout << "Error. Incorrect coordinates in " << errorPlace << std::endl;
}

/* ���:                   �����
   ���������:             -
   ������������ ��������: -
   ��������:              ����� ���������� �� ������ �� ����� */
void IncorrectCharacter::Show() const
{
	std::cout << "Error. Incorrect character \'" << whatCharacter << "\'";
	std::cout << " in " << errorPlace << std::endl;
}

/* ���:                   �����
   ���������:             -
   ������������ ��������: -
   ��������:              ����� ���������� �� ������ �� ����� */
void FieldIsNotCreated::Show() const
{
	std::cout << "Error. Field is not created in " << errorPlace << std::endl;
}
