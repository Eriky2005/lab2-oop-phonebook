#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include "note.h"
#include <exception>

class PhoneBookException : public std::exception
{
private:
	const char *message;

public:
	PhoneBookException(const char *msg) : message(msg) {}
	const char *what() const noexcept override
	{
		return message;
	}
};

class PhoneBookFullException : public PhoneBookException
{
public:
	PhoneBookFullException() : PhoneBookException("Ошибка: Телефонная книга переполнена") {}
};

class ContactNotFoundException : public PhoneBookException
{
public:
	ContactNotFoundException() : PhoneBookException("Ошибка: Контакт не найден") {}
};

class PhoneBook
{
private:
	NOTE **contacts;
	int capacity;
	int size;

	void resize();
	int findContactIndexByPhone(const char *phone) const;
	void sortContactsByBirthday();

public:
	PhoneBook();
	~PhoneBook();

	// Основные операции
	void addContact(NOTE *contact, int position = -1);
	void removeContact(int index);
	void removeContactByPhone(const char *phone);
	void editContact(int index);

	// Поиск и вывод
	NOTE *findContactByPhone(const char *phone) const;
	void displayAllContacts() const;
	void displayContact(int index) const;

	// Сервисные методы
	int getSize() const { return size; }
	bool isEmpty() const { return size == 0; }
	void clear();

	// Операторы
	NOTE *operator[](int index) const;
};

#endif