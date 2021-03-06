#pragma once
// ��������� ��� ������������� ���������
struct Point
{
	int x;
	int y;
};

// ����� ��� ������������� ���� ��� ����
class Field
{
private:
	// ����
	int rows;     // ���������� �����
	int cols;     // ���������� ��������
	char** field; // ��������� �� ���� (��������� �����)

public:
	/* ���:                   �����������
	   ���������:             ���������� �����, ���������� ��������
	   ������������ ��������: -
	   ��������:              ��������� ������ ��� ���� �� ���� � ��� ���������� */
	Field(int rows = 10, int cols = 10);

	/* ���:                   ����������
	   ���������:             -
	   ������������ ��������: -
	   ��������:              �������� ������ ��� ���� �� ���� */
	~Field();

	/* ���:                   �����
	   ���������:             -
	   ������������ ��������: -
	   ��������:              ���������� ���� ��������� � ������� �������� */
	void Clear();

	/* ���:                   �����
	   ���������:             -
	   ������������ ��������: -
	   ��������:              ����� ���� �� ����� */
	void Show() const;

	/* ���:                   �����
	   ���������:             ����� ��� ���������� �������, ������
	   ������������ ��������: -
	   ��������:              ��������� ������� �� ���� �� ��������� ������������ */
	void SetPoint(const Point& point, char ch);

	/* ���:                   �����
	   ���������:             -
	   ������������ ��������: -
	   ��������:              ��������� ������ �� ���� � ��������� ����� */
	void SetApple();

	/* ���:                   �����
	   ���������:             �����
	   ������������ ��������: ������, ������� ��������� � ���� �����
	   ��������:              ����������� �������, ������� ��������� � �������� ����� */
	char GetElement(const Point& point) const;

	// ������, ������������ ������� ����
	int GetRows() const { return rows; }
	int GetCols() const { return cols; }
};