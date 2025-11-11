#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include <exception>

// Пользовательские исключения
class NoteException : public std::exception
{
private:
	const char *message;

public:
	NoteException(const char *msg) : message(msg) {}
	const char *what() const noexcept override
	{
		return message;
	}
};

class InvalidDateException : public NoteException
{
public:
	InvalidDateException() : NoteException("Ошибка: Неверная дата рождения") {}
};

class EmptyFieldException : public NoteException
{
public:
	EmptyFieldException() : NoteException("Ошибка: Обязательные поля не заполнены") {}
};

class NOTE
{
protected:
	char *name;
	char *phone;
	int birthday[3]; // день, месяц, год

	// Вспомогательные методы
	bool isValidDate(int day, int month, int year) const;
	void copyData(const NOTE &other);
	void freeMemory();

public:
	// Конструкторы
	NOTE();
	NOTE(const char *name, const char *phone, int day, int month, int year);
	NOTE(const NOTE &other);

	// Деструктор
	virtual ~NOTE();

	// Оператор присваивания
	NOTE &operator=(const NOTE &other);

	// Set методы с проверками
	void setName(const char *name);
	void setPhone(const char *phone);
	void setBirthday(int day, int month, int year);

	// Get методы
	const char *getName() const;
	const char *getPhone() const;
	const int *getBirthday() const;
	int getBirthYear() const { return birthday[2]; }
	int getBirthMonth() const { return birthday[1]; }
	int getBirthDay() const { return birthday[0]; }

	// Виртуальные методы для наследования
	virtual void printInfo() const;
	virtual const char *getType() const { return "Базовый контакт"; }

	// Методы для сравнения (для сортировки по дате рождения)
	bool operator<(const NOTE &other) const;
	bool operator==(const NOTE &other) const;

	// Дружественные операторы ввода/вывода
	friend std::ostream &operator<<(std::ostream &os, const NOTE &note);
	friend std::istream &operator>>(std::istream &is, NOTE &note);
};

// Класс-наследник для расширенного контакта
class WorkNote : public NOTE
{
private:
	char *company;
	char *position;

public:
	WorkNote();
	WorkNote(const char *name, const char *phone, int day, int month, int year,
			 const char *company, const char *position);
	WorkNote(const WorkNote &other);
	~WorkNote();

	WorkNote &operator=(const WorkNote &other);

	void setCompany(const char *company);
	void setPosition(const char *position);
	const char *getCompany() const;
	const char *getPosition() const;

	void printInfo() const override;
	const char *getType() const override { return "Рабочий контакт"; }
};

#endif