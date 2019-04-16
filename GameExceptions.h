#pragma once

// ����������� ����� ��� ������������� �������� ����������
class GameException
{
protected:
	// ����
	char errorPlace[30]; // ����� ��������� ����������
public:
	/* ���:                   �����������
	   ���������:             ��������� �� ������, ����������� ����� ��������� ������
	   ������������ ��������: -
	   ��������:              ����������� ��������� �� where � errorPlace */
	GameException(const char* where);

	/* ���:                   �����
	   ���������:             -
	   ������������ ��������: -
	   ��������:              ����� ���������� �� ������ �� ����� */
	virtual void Show() const = 0;
};

// ����������� ����� ��� ��������� ������ ������������ ��������
class IncorrectSizes : public GameException
{
public:
	IncorrectSizes(const char* where)
		: GameException(where) { }

	virtual void Show() const;
};

// ����������� ����� ��� ��������� ������ �����, ������� ��������� �� ������� ����
class CoordinatesOnBorder : public GameException
{
public:
	CoordinatesOnBorder(const char* where)
		: GameException(where) { }

	virtual void Show() const;
};

// ����������� ����� ��� ��������� ������ �����, ������� ��������� �� ��������� ����
class IncorrectCoordinates : public GameException
{
public:
	IncorrectCoordinates(const char* where)
		: GameException(where) { }

	virtual void Show() const;
};

// ����������� ����� ��� ��������� ������ ������������� �������
class IncorrectCharacter : public GameException
{
private:
	// ����
	char whatCharacter; // ������������ ������
public:
	IncorrectCharacter(const char* where, char what)
		: GameException(where), whatCharacter(what) { }

	virtual void Show() const;
};

// ����������� ����� ��� ��������� ������ ������ � �������������� �����
class FieldIsNotCreated : public GameException
{
public:
	FieldIsNotCreated(const char* where)
		: GameException(where) { }

	virtual void Show() const;
};