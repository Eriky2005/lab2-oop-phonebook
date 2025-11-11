#include "note.h"
#include <cstring>
#include <iostream>

// NOTE implementation
bool NOTE::isValidDate(int day, int month, int year) const
{
	if (year < 1900 || year > 2100)
		return false;
	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > 31)
		return false;

	// Простая проверка дней в месяце
	if (month == 2)
	{
		bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (day > (isLeap ? 29 : 28))
			return false;
	}
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return false;

	return true;
}

void NOTE::copyData(const NOTE &other)
{
	if (other.name)
	{
		name = new char[strlen(other.name) + 1];
		strcpy(name, other.name);
	}
	else
	{
		name = nullptr;
	}

	if (other.phone)
	{
		phone = new char[strlen(other.phone) + 1];
		strcpy(phone, other.phone);
	}
	else
	{
		phone = nullptr;
	}

	birthday[0] = other.birthday[0];
	birthday[1] = other.birthday[1];
	birthday[2] = other.birthday[2];
}

void NOTE::freeMemory()
{
	delete[] name;
	delete[] phone;
}

NOTE::NOTE() : name(nullptr), phone(nullptr)
{
	birthday[0] = birthday[1] = birthday[2] = 0;
	std::cout << "Вызван конструктор по умолчанию для объекта NOTE" << std::endl;
}

NOTE::NOTE(const char *name, const char *phone, int day, int month, int year)
{
	if (!name || !phone)
	{
		throw EmptyFieldException();
	}
	if (!isValidDate(day, month, year))
	{
		throw InvalidDateException();
	}

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);

	this->phone = new char[strlen(phone) + 1];
	strcpy(this->phone, phone);

	birthday[0] = day;
	birthday[1] = month;
	birthday[2] = year;

	std::cout << "Вызван конструктор с параметрами для объекта NOTE: " << name << std::endl;
}

NOTE::NOTE(const NOTE &other)
{
	copyData(other);
	std::cout << "Вызван конструктор копирования для объекта NOTE: " << (name ? name : "unknown") << std::endl;
}

NOTE::~NOTE()
{
	std::cout << "Вызван деструктор для объекта NOTE: " << (name ? name : "unknown") << std::endl;
	freeMemory();
}

NOTE &NOTE::operator=(const NOTE &other)
{
	if (this != &other)
	{
		freeMemory();
		copyData(other);
	}
	return *this;
}

void NOTE::setName(const char *name)
{
	if (!name || strlen(name) == 0)
	{
		throw EmptyFieldException();
	}
	delete[] this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void NOTE::setPhone(const char *phone)
{
	if (!phone || strlen(phone) == 0)
	{
		throw EmptyFieldException();
	}
	delete[] this->phone;
	this->phone = new char[strlen(phone) + 1];
	strcpy(this->phone, phone);
}

void NOTE::setBirthday(int day, int month, int year)
{
	if (!isValidDate(day, month, year))
	{
		throw InvalidDateException();
	}
	birthday[0] = day;
	birthday[1] = month;
	birthday[2] = year;
}

const char *NOTE::getName() const { return name; }
const char *NOTE::getPhone() const { return phone; }
const int *NOTE::getBirthday() const { return birthday; }

bool NOTE::operator<(const NOTE &other) const
{
	// Сравнение по дате рождения (год, месяц, день)
	if (birthday[2] != other.birthday[2])
		return birthday[2] < other.birthday[2];
	if (birthday[1] != other.birthday[1])
		return birthday[1] < other.birthday[1];
	return birthday[0] < other.birthday[0];
}

bool NOTE::operator==(const NOTE &other) const
{
	return strcmp(phone, other.phone) == 0;
}

void NOTE::printInfo() const
{
	std::cout << "Тип: " << getType() << std::endl;
	std::cout << "ФИО: " << (name ? name : "не указано") << std::endl;
	std::cout << "Телефон: " << (phone ? phone : "не указан") << std::endl;
	std::cout << "Дата рождения: " << birthday[0] << "." << birthday[1] << "." << birthday[2] << std::endl;
}

std::ostream &operator<<(std::ostream &os, const NOTE &note)
{
	os << "Тип: " << note.getType() << "\n";
	os << "ФИО: " << (note.name ? note.name : "не указано") << "\n";
	os << "Телефон: " << (note.phone ? note.phone : "не указан") << "\n";
	os << "Дата рождения: " << note.birthday[0] << "." << note.birthday[1] << "." << note.birthday[2];
	return os;
}

std::istream &operator>>(std::istream &is, NOTE &note)
{
	char buffer[100];

	std::cout << "Введите ФИО: ";
	is.ignore();
	is.getline(buffer, 100);
	note.setName(buffer);

	std::cout << "Введите телефон: ";
	is.getline(buffer, 100);
	note.setPhone(buffer);

	std::cout << "Введите день рождения (день месяц год): ";
	int day, month, year;
	is >> day >> month >> year;
	note.setBirthday(day, month, year);

	return is;
}

// WorkNote implementation
WorkNote::WorkNote() : NOTE(), company(nullptr), position(nullptr)
{
	std::cout << "Вызван конструктор по умолчанию для объекта WorkNote" << std::endl;
}

WorkNote::WorkNote(const char *name, const char *phone, int day, int month, int year,
				   const char *company, const char *position)
	: NOTE(name, phone, day, month, year)
{

	this->company = new char[strlen(company) + 1];
	strcpy(this->company, company);

	this->position = new char[strlen(position) + 1];
	strcpy(this->position, position);

	std::cout << "Вызван конструктор с параметрами для объекта WorkNote: " << name << std::endl;
}

WorkNote::WorkNote(const WorkNote &other) : NOTE(other)
{
	if (other.company)
	{
		company = new char[strlen(other.company) + 1];
		strcpy(company, other.company);
	}
	else
	{
		company = nullptr;
	}

	if (other.position)
	{
		position = new char[strlen(other.position) + 1];
		strcpy(position, other.position);
	}
	else
	{
		position = nullptr;
	}

	std::cout << "Вызван конструктор копирования для объекта WorkNote: " << (name ? name : "unknown") << std::endl;
}

WorkNote::~WorkNote()
{
	std::cout << "Вызван деструктор для объекта WorkNote: " << (name ? name : "unknown") << std::endl;
	delete[] company;
	delete[] position;
}

WorkNote &WorkNote::operator=(const WorkNote &other)
{
	if (this != &other)
	{
		NOTE::operator=(other);

		delete[] company;
		delete[] position;

		if (other.company)
		{
			company = new char[strlen(other.company) + 1];
			strcpy(company, other.company);
		}
		else
		{
			company = nullptr;
		}

		if (other.position)
		{
			position = new char[strlen(other.position) + 1];
			strcpy(position, other.position);
		}
		else
		{
			position = nullptr;
		}
	}
	return *this;
}

void WorkNote::setCompany(const char *company)
{
	delete[] this->company;
	this->company = new char[strlen(company) + 1];
	strcpy(this->company, company);
}

void WorkNote::setPosition(const char *position)
{
	delete[] this->position;
	this->position = new char[strlen(position) + 1];
	strcpy(this->position, position);
}

const char *WorkNote::getCompany() const { return company; }
const char *WorkNote::getPosition() const { return position; }

void WorkNote::printInfo() const
{
	NOTE::printInfo();
	std::cout << "Компания: " << (company ? company : "не указана") << std::endl;
	std::cout << "Должность: " << (position ? position : "не указана") << std::endl;
}