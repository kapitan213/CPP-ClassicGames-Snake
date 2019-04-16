#pragma once

// Абстрактный класс для представления игрового исключения
class GameException
{
protected:
	// Поле
	char errorPlace[30]; // место генерации исключения
public:
	/* Тип:                   Конструктор
	   Параметры:             указатель на строку, описывающую место генерации ошибки
	   Возвращаемое значение: -
	   Описание:              копирование элементов из where в errorPlace */
	GameException(const char* where);

	/* Тип:                   Метод
	   Параметры:             -
	   Возвращаемое значение: -
	   Описание:              вывод информации об ошибке на экран */
	virtual void Show() const = 0;
};

// Производный класс для генерации ошибки некорректных размеров
class IncorrectSizes : public GameException
{
public:
	IncorrectSizes(const char* where)
		: GameException(where) { }

	virtual void Show() const;
};

// Производный класс для генерации ошибки точки, которая находится на границе поля
class CoordinatesOnBorder : public GameException
{
public:
	CoordinatesOnBorder(const char* where)
		: GameException(where) { }

	virtual void Show() const;
};

// Производный класс для генерации ошибки точки, которая находится за границами поля
class IncorrectCoordinates : public GameException
{
public:
	IncorrectCoordinates(const char* where)
		: GameException(where) { }

	virtual void Show() const;
};

// Производный класс для генерации ошибки неправильного символа
class IncorrectCharacter : public GameException
{
private:
	// Поле
	char whatCharacter; // неправильный символ
public:
	IncorrectCharacter(const char* where, char what)
		: GameException(where), whatCharacter(what) { }

	virtual void Show() const;
};

// Производный класс для генерации ошибки работы с несуществующим полем
class FieldIsNotCreated : public GameException
{
public:
	FieldIsNotCreated(const char* where)
		: GameException(where) { }

	virtual void Show() const;
};