#include <iostream>       // ��� cout, cin
#include <Windows.h>      // ��� Sleep()
#include <conio.h>        // ��� _kbhit(), _getch()
#include "SnakePackage.h" // ����� ������ � �����

enum Direction { UP, DOWN, LEFT, RIGHT };

int main()
{
	using std::cout;
	using std::cin;

	// �������������� � ������������ ����� (� ������ ������� ����� ������)
	cout << "Switch your language to English to use WASD (wasd) to control the snake!!!\n";
	system("pause");

	system("cls");
	int rows = 10, columns = 10; // ������� ����
	Field* field;                // ��������� �� ����
	Snake* snake;                // ��������� �� ����
	Point head;                  // ���������� ������ ����
	char mainMenu;               // ������ ������ ������������ � ������� ����
	char optionsMenu;            // ������ ������ ������������ � ���� �����
	int userKey;                 // �������, �� ������� ���� �����
	Direction direction;         // ����������� �������� ����
	int speed = 400;             // �������� ����

	try
	{
		

		// ����
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

				// ��������� ��������� ����������
				head.y = rows / 2;
				head.x = columns / 2;
				direction = Direction::UP; // ���� ����� ������ �����

				field = new Field(rows, columns); // ���������� ���� �� ����
				snake = new Snake(field, head); // ���������� ���� �� ���� (� �� ����)

				// ���� ���� �� ������
				while (!snake->IsDead())
				{
					// ���� ���� ������ �������
					if (_kbhit())
					{
						userKey = _getch(); // ��������� �������

						// ��������� ���������� ����������� ���� ��� ������� ������� �������
						// � ������ case ���� ��������. �� ���� � ���, ����� ����� �� ����
						// ���������� ���� �� 180% (� �������� �� ���� ��)
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

					// ����������� ����������� ���� � ���������� ���������� ������
					switch (direction)
					{
					case UP:    head.y--; break;
					case DOWN:  head.y++; break;
					case LEFT:  head.x--; break;
					case RIGHT: head.x++; break;
					}


					snake->Move(field, head); // ����������� ����

					// ������� ���� ������ � ����������� �������� �����
					field->Show();
					cout << "Apples: " << snake->GetApples() << "\n";

					// ��������� ���� �� �����, ������� ����������� �� ���������
					// (��� ������� ��������� ������������ � ����������)
					Sleep(speed);
					system("cls");
				}

				// ��� ������ ���� ����� - ������� ��������� ��� ����� ����
				ShowTheEnd();

				delete snake; // �������� ����
				delete field; // �������� ����
				break;

			case '2':
				// ���� �����
				do
				{
					ShowOptionsMenu();
					cin >> optionsMenu;
					ClearBuffer();

					switch (optionsMenu)
					{
					case '1': // ��������� �������� ���� (������� 10 �� 10, �������� 40 �� 40)
						cout << "Now field size: rows = " << rows << ", columns = " << columns << "\n";
						SetSizes(rows, columns); // ��������� ����� ��������
						system("cls");
						break;
					case '2': // ��������� �������� ���� (������� 100, �������� 500)
						cout << "Now snake's speed is " << speed << "\n";
						EnterSpeed(speed); // ��������� ����� ��������
						break;
					case '0': // ����������� � ������� ���� (������ �� ������)
						break;
					default:
						cout << "Incorrect symbol. Try again.\n";
						break;
					}
				} while (optionsMenu != '0');
				break;
			case '3': 
				AboutAuthor(); // ����� ���������� � ��������� ����
				break;
			default:
				cout << "Incorrect symbol. Try again.\n";
				break;
			}

		} while (mainMenu != '0');
	}
	catch (const GameException& ex)
	{
		// ��� ����� ���������� ������� ���������� � ��� � ��������� ���������
		system("cls");
		ex.Show();
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}