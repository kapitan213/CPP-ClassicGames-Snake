#include <iostream>       // для cout, cin
#include <Windows.h>      // для Sleep()
#include <conio.h>        // для _kbhit(), _getch()
#include "SnakePackage.h" // пакет файлов с игрой

enum Direction { UP, DOWN, LEFT, RIGHT };

int main()
{
	using std::cout;
	using std::cin;

	// Предупреждение о переключении языка (в скором времени будет убрано)
	cout << "Switch your language to English to use WASD (wasd) to control the snake!!!\n";
	system("pause");

	system("cls");
	int rows = 10, columns = 10; // размеры поля
	Field* field;                // указатель на поле
	Snake* snake;                // указатель на змею
	Point head;                  // координаты головы змеи
	char mainMenu;               // символ выбора пользователя в главном меню
	char optionsMenu;            // символ выбора пользователя в меню опций
	int userKey;                 // клавиша, на которую жмет игрок
	Direction direction;         // направление движення змеи
	int speed = 400;             // скорость змеи

	try
	{
		

		// меню
		do
		{
			ShowMainMenu();
			cin >> mainMenu;
			ClearBuffer();

			switch (mainMenu)
			{
			case '0':
				cout << "Goodbye!\n";
				break;
			case '1':

				// начальная установка параметров
				head.y = rows / 2;
				head.x = columns / 2;
				direction = Direction::UP; // змея будет ползти вверх

				field = new Field(rows, columns); // размещение поля на куче
				snake = new Snake(field, head); // размещение змеи на куче (и на поле)

				// пока змея не умерла
				while (!snake->IsDead())
				{
					// если была нажата клавиша
					if (_kbhit())
					{
						userKey = _getch(); // считываем клавишу

						// Изменение координаты направления змеи при анализе символа клавиши
						// В каждом case есть проверка. Ее суть в том, чтобы игрок не смог
						// развернуть змею на 180° (и ударится об себя же)
						switch (userKey)
						{
						case 'w': case 'W':
							if (direction != Direction::DOWN)
								direction = Direction::UP;
							break;
						case 's': case 'S':
							if (direction != Direction::UP)
								direction = Direction::DOWN;
							break;
						case 'a': case 'A':
							if (direction != Direction::RIGHT)
								direction = Direction::LEFT;
							break;
						case 'd': case 'D':
							if (direction != Direction::LEFT)
								direction = Direction::RIGHT;
							break;
						}
					}

					// Анализируем направление змеи и перемещаем координату головы
					switch (direction)
					{
					case UP:    head.y--; break;
					case DOWN:  head.y++; break;
					case LEFT:  head.x--; break;
					case RIGHT: head.x++; break;
					}


					snake->Move(field, head); // передвигаем змею

					// Выводим поле вместе с количеством съеденых яблок
					field->Show();
					cout << "Apples: " << snake->GetApples() << "\n";

					// Остановка игры на время, которое установлено по умолчанию
					// (или которое установил пользователь в настройках)
					Sleep(speed);
					system("cls");
				}

				// Как только змея умрет - выводим сообщение про конец игры
				ShowTheEnd();

				delete snake; // удаление змеи
				delete field; // удаление поля
				break;

			case '2':
				// Меню опций
				do
				{
					ShowOptionsMenu();
					cin >> optionsMenu;
					ClearBuffer();

					switch (optionsMenu)
					{
					case '1': // изменение размеров поля (минимум 10 на 10, максимум 40 на 40)
						cout << "Now field size: rows = " << rows << ", columns = " << columns << "\n";
						SetSizes(rows, columns); // установка новых размеров
						system("cls");
						break;
					case '2': // изменение скорости змеи (минимум 100, максимум 500)
						cout << "Now snake's speed is " << speed << "\n";
						EnterSpeed(speed); // установка новой скорости
						break;
					case '0': // возвращение в главное меню (ничего не делать)
						break;
					default:
						cout << "Incorrect symbol. Try again.\n";
						break;
					}
				} while (optionsMenu != '0');
				break;
			case '3': 
				AboutAuthor(); // вывод информации о создателе игры
				break;
			default:
				cout << "Incorrect symbol. Try again.\n";
				break;
			}

		} while (mainMenu != '0');
	}
	catch (const GameException& ex)
	{
		// при любом исключении выводим информацию о нем и закрываем программу
		system("cls");
		ex.Show();
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}
