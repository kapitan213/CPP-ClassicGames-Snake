#include "Field.h"
#include "Snake.h"
#include "GameExceptions.h" // ��� ������������� ����������

/* ���:                   �����
   ���������:             ������ �� ����
   ������������ ��������: -
   ��������:              ��������� �� ���� ���� ���� */
void Snake::DrawSnake(Field* field) const
{
	// ���� ������ �������� ��� ���� ������
	if (body == nullptr || isDead)
		return;

	// ������� ��������� �� ����� ����
	const Body * current = body;

	// ���� ��������� �� ��������� �� ���� ������ ����
	do
	{
		field->SetPoint(current->point, 'o'); // ������ ����� ����

		// ���� ��������� ����� ���� - �� ����� �� ������ ����.
		// ������ ������ ����������� ��������
		if (current->next == nullptr)
			field->SetPoint(current->point, 'O');

		current = current->next; // ��������� � ��������� �����

	} while (current != nullptr);
}

/* ���:                   �����������
   ���������:             ���� �� ������� ����������� ����, ����� ���������� ������
   ������������ ��������: -
   ��������:              �������� ���� �� ���� � ��������� �� ������ �� ��� */
Snake::Snake(Field * field, const Point & start)
	: apples(0), isDead(false)
{
	// ���� ����� �� �������
	if (start.x == 0 || start.y == 0 ||
		start.x == field->GetCols() - 1 || start.y == field->GetRows() - 1)
		throw CoordinatesOnBorder("Snake Constuctor");

	// ���� ����� ������������
	if (start.x < 0 || start.y < 0 ||
		start.x >= field->GetCols() || start.y >= field->GetRows())
		throw IncorrectCoordinates("Snake Constructor");

	// ��������� ������ ��� ������ ����
	body = new Body{ start };

	// ��������� ���������� �� ���� ������.
	field->SetApple();

	// ���������� ������ �� ����
	Move(field, start);
}

/* ���:                   ����������
   ���������:             -
   ������������ ��������: -
   ��������:              �������� ������ ��� ���� �� ���� */
Snake::~Snake()
{
	// ���� ������ ��������
	if (body == nullptr)
		return;

	// �������� ���� ����, ������� � ������ (����-��������� body)
	Body * next;

	// ���� �� ��������� �� ���� ������ ����
	do
	{
		next = body->next; // ���������� ����� ��������� �����
		delete body;       // ������� ������ �����
		body = next;       // ��������� � ���������

	} while (next != nullptr);
}

/* ���:                   �����
   ���������:             ��������� �� ����, ����� ��� ����������� ������
   ������������ ��������: -
   ��������:              ��������� ����� ����� ��� ������ � ������������ ����� ���� */
void Snake::Move(Field * field, const Point & point)
{
	// ���� ���� ������
	if (isDead)
		return;

	// ���� ����� ������������
	if (point.x < 0 || point.y < 0 ||
		point.x >= field->GetCols() || point.y >= field->GetRows())
		throw IncorrectCoordinates("Snake::Move");

	// ������� ������, ������� ��������� � ����� �����
	char fieldPlace = field->GetElement(point);

	Body* current; // ��������� �� ������ ����� ����

	// ����������� ������
	switch (fieldPlace)
	{
	case 'A': // ���� ���� ���������� �� ������
		EatApple();       // ������� ������
		field->SetApple(); // ���������� ����� ������

		// ����� ��������� ����, ����� �������� ��� ���� ����� ����.
		// ������� �� ������ (���� ��������� �� ��������� ����� �� ����� �������)
		current = body;
		while (current->next != nullptr)
			current = current->next;

		// ������ current ��������� �� ������. ��������� ����� ����� ����
		// � ������ ���� �� ����
		current->next = new Body{ point };
		DrawSnake(field);
		break;

	case ' ': // ���� ���� ������ �� ������ �����
		field->SetPoint(body->point, ' '); // ������� ������ ����� ������

		// ���� ���� ����� ������ ���� ����� - ������ ���������� ���� �����
		if (body->next == nullptr)
			body->point = point;
		// ���� ���� ����� 2 � ������ ������
		else
		{
			// � ������� ��������� current ���������� �� ���� ������ ���� ����,
			// ��� ���� ������������ ���������� ������ ���������� ����� �� ����������
			// ��������� �����. � ��� ����, ���� �� ������ �� ������
			current = body;
			while (current->next != nullptr)
			{
				current->point = current->next->point;
				current = current->next;
			}

			// ������ ���������� ������ �� ����� ����������
			current->point = point;
		}

		DrawSnake(field); // ������ ���� �� ����
		break;
	case '*':        // ���� ���� ������ �� �������,
	case 'o':        // ��� ���� �� ����, ��
		KillSnake(); // ������� ����
		break;
	default:  // ���� ������������ ������
		throw IncorrectCharacter("Snake::Move", fieldPlace);
	}
}
