#include "Field.h"
#include "Snake.h"
#include "GameExceptions.h" // для использования исключений

/* Тип:                   Метод
   Параметры:             ссылка на поле
   Возвращаемое значение: -
   Описание:              рисование на поле всей змеи */
void Snake::DrawSnake(Field* field) const
{
	// Если нечего рисовать или змея мертва
	if (body == nullptr || isDead)
		return;

	// Создаем указатель на часть змеи
	const Body * current = body;

	// Пока указатель не пройдется по всем частям тела
	do
	{
		field->SetPoint(current->point, 'o'); // рисуем часть тела

		// Если следующей части нету - мы дошли до головы змеи.
		// Рисуем голову специальным символом
		if (current->next == nullptr)
			field->SetPoint(current->point, 'O');

		current = current->next; // переходим к следующей части

	} while (current != nullptr);
}

/* Тип:                   Конструктор
   Параметры:             поле на котором размещается змея, точка размещения головы
   Возвращаемое значение: -
   Описание:              создание змеи на поле и рисование ее головы на нем */
Snake::Snake(Field * field, const Point & start)
	: apples(0), isDead(false)
{
	// Если точка на границе
	if (start.x == 0 || start.y == 0 ||
		start.x == field->GetCols() - 1 || start.y == field->GetRows() - 1)
		throw CoordinatesOnBorder("Snake Constuctor");

	// Если точка неккоректная
	if (start.x < 0 || start.y < 0 ||
		start.x >= field->GetCols() || start.y >= field->GetRows())
		throw IncorrectCoordinates("Snake Constructor");

	// Выделение памяти под голову змеи
	body = new Body{ start };

	// Начальное размещение на поле яблока.
	field->SetApple();

	// Размещение головы на поле
	Move(field, start);
}

/* Тип:                   Деструктор
   Параметры:             -
   Возвращаемое значение: -
   Описание:              очищение памяти под змею на куче */
Snake::~Snake()
{
	// Если нечего рисовать
	if (body == nullptr)
		return;

	// Удаление тела змеи, начиная с хвоста (поля-указателя body)
	Body * next;

	// Пока не пройдемся по всем частям тела
	do
	{
		next = body->next; // запоминаем адрес следующей части
		delete body;       // удаляем данную часть
		body = next;       // переходим к следующей

	} while (next != nullptr);
}

/* Тип:                   Метод
   Параметры:             указатель на поле, точка для перемещения головы
   Возвращаемое значение: -
   Описание:              установка новой точки для головы и передвижение всего тела */
void Snake::Move(Field * field, const Point & point)
{
	// Если змея мертва
	if (isDead)
		return;

	// Если точка неккоректная
	if (point.x < 0 || point.y < 0 ||
		point.x >= field->GetCols() || point.y >= field->GetRows())
		throw IncorrectCoordinates("Snake::Move");

	// достаем символ, который находится в даной точке
	char fieldPlace = field->GetElement(point);

	Body* current; // указатель на данную часть тела

	// Анализируем символ
	switch (fieldPlace)
	{
	case 'A': // если змея наткнулась на яблоко
		EatApple();       // съедаем яблоко
		field->SetApple(); // генерируем новое яблоко

		// Чтобы увеличить змею, нужно добавить еще одну часть тела.
		// Доходим до головы (пока указатель на следующую часть не будет нулевой)
		current = body;
		while (current->next != nullptr)
			current = current->next;

		// Теперь current указывает на голову. Добавляем новую часть тела
		// и рисуем змею на поле
		current->next = new Body{ point };
		DrawSnake(field);
		break;

	case ' ': // если змея попала на пустое место
		field->SetPoint(body->point, ' '); // очищаем бывшее место хвоста

		// Если змея имеет только одну часть - меняем координаты этой части
		if (body->next == nullptr)
			body->point = point;
		// Если змея имеет 2 и больше частей
		else
		{
			// С помощью указателя current проходимся по всем частям тела змеи,
			// при этом переписываем координаты каждой предыдущей части на координаты
			// следующей части. И так идем, пока не дойдем до головы
			current = body;
			while (current->next != nullptr)
			{
				current->point = current->next->point;
				current = current->next;
			}

			// Меняем координаты головы на новые координаты
			current->point = point;
		}

		DrawSnake(field); // рисуем змею на поле
		break;
	case '*':        // если змея попала на границу,
	case 'o':        // или сама на себя, то
		KillSnake(); // убиваем змею
		break;
	default:  // если некорректный символ
		throw IncorrectCharacter("Snake::Move", fieldPlace);
	}
}
