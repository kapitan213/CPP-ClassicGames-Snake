#include "GameExceptions.h"
#include <iostream>
#include <cstring>

/* Тип:                   Конструктор
   Параметры:             указатель на строку, описывающую место генерации ошибки
   Возвращаемое значение: -
   Описание:              копирование элементов из where в errorPlace */
GameException::GameException(const char* where)
{
	strcpy_s(errorPlace, 30, strlen(where) < 30 ? where : "NOTHING");
}

/* Тип:                   Метод
   Параметры:             -
   Возвращаемое значение: -
   Описание:              вывод информации об ошибке на экран */
void IncorrectSizes::Show() const
{
	std::cout << "Error. Incorrect sizes in " << errorPlace << std::endl;
}

/* Тип:                   Метод
   Параметры:             -
   Возвращаемое значение: -
   Описание:              вывод информации об ошибке на экран */
void CoordinatesOnBorder::Show() const
{
	std::cout << "Error. Coordinates of the point on a border in " << errorPlace << std::endl;
}

/* Тип:                   Метод
   Параметры:             -
   Возвращаемое значение: -
   Описание:              вывод информации об ошибке на экран */
void IncorrectCoordinates::Show() const
{
	std::cout << "Error. Incorrect coordinates in " << errorPlace << std::endl;
}

/* Тип:                   Метод
   Параметры:             -
   Возвращаемое значение: -
   Описание:              вывод информации об ошибке на экран */
void IncorrectCharacter::Show() const
{
	std::cout << "Error. Incorrect character \'" << whatCharacter << "\'";
	std::cout << " in " << errorPlace << std::endl;
}

/* Тип:                   Метод
   Параметры:             -
   Возвращаемое значение: -
   Описание:              вывод информации об ошибке на экран */
void FieldIsNotCreated::Show() const
{
	std::cout << "Error. Field is not created in " << errorPlace << std::endl;
}
