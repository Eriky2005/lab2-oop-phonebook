#include <iostream>
#include "note.h"

class PhoneBook
{
private:
	NOTE **contacts;
	int capacity;
	int size;

	void resize();

public:
	PhoneBook();
	~PhoneBook();

	void addContact(NOTE *contact);
	int getSize() const { return size; }
	NOTE *getContact(int index) const;
};

PhoneBook::PhoneBook() : contacts(nullptr), capacity(0), size(0)
{
	contacts = new NOTE *[1];
	capacity = 1;
	std::cout << "Создана телефонная книга" << std::endl;
}

PhoneBook::~PhoneBook()
{
	for (int i = 0; i < size; i++)
	{
		delete contacts[i];
	}
	delete[] contacts;
	std::cout << "Телефонная книга удалена" << std::endl;
}

void PhoneBook::resize()
{
	int newCapacity = capacity * 2 + 1;
	NOTE **newContacts = new NOTE *[newCapacity];

	for (int i = 0; i < size; i++)
	{
		newContacts[i] = contacts[i];
	}

	delete[] contacts;
	contacts = newContacts;
	capacity = newCapacity;
}

void PhoneBook::addContact(NOTE *contact)
{
	if (size >= capacity)
	{
		resize();
	}
	contacts[size++] = contact;
}

NOTE *PhoneBook::getContact(int index) const
{
	if (index < 0 || index >= size)
	{
		throw std::out_of_range("Неверный индекс контакта");
	}
	return contacts[index];
}

// Заглушки функций
void displayMenu()
{
	std::cout << "\n=== ЗАПИСНАЯ КНИГА ===" << std::endl;
	std::cout << "1. Добавить базовый контакт" << std::endl;
	std::cout << "2. Добавить рабочий контакт" << std::endl;
	std::cout << "3. Удалить контакт" << std::endl;
	std::cout << "4. Поиск по телефону" << std::endl;
	std::cout << "5. Показать все контакты" << std::endl;
	std::cout << "6. Обработать текстовый файл" << std::endl;
	std::cout << "0. Выход" << std::endl;
	std::cout << "Выберите действие: ";
}

void addBasicContact(PhoneBook &book)
{
	std::cout << "\n[ЗАГЛУШКА] Добавление базового контакта будет реализовано в коммите 2" << std::endl;
}

void addWorkContact(PhoneBook &book)
{
	std::cout << "\n[ЗАГЛУШКА] Добавление рабочего контакта будет реализовано в коммите 2" << std::endl;
}

void deleteContact(PhoneBook &book)
{
	std::cout << "\n[ЗАГЛУШКА] Удаление контакта будет реализовано в коммите 2" << std::endl;
}

void searchByPhone(PhoneBook &book)
{
	std::cout << "\n[ЗАГЛУШКА] Поиск по телефону будет реализовано в коммите 2" << std::endl;
}

void displayAllContacts(PhoneBook &book)
{
	std::cout << "\n[ЗАГЛУШКА] Показ всех контактов будет реализовано в коммите 2" << std::endl;
}

void processTextFile()
{
	std::cout << "\n[ЗАГЛУШКА] Обработка текстового файла будет реализована в коммите 3" << std::endl;
}

void demonstrateClasses()
{
	std::cout << "=== ДЕМОНСТРАЦИЯ РАБОТЫ КЛАССОВ ===" << std::endl;

	try
	{
		// Демонстрация базового класса
		NOTE note1("Иван Иванов", "+79123456789", 15, 5, 1990);
		note1.printInfo();

		std::cout << "\n--- Демонстрация наследования ---" << std::endl;
		WorkNote workNote1("Петр Петров", "+79987654321", 20, 10, 1985, "ООО Ромашка", "Менеджер");
		workNote1.printInfo();

		std::cout << "\n--- Демонстрация исключений ---" << std::endl;
		try
		{
			NOTE invalidNote("", "+79123456789", 15, 5, 1990);
		}
		catch (const EmptyFieldException &e)
		{
			std::cout << "Поймано исключение: " << e.what() << std::endl;
		}

		try
		{
			NOTE invalidDateNote("Иван", "+79123456789", 32, 13, 1990);
		}
		catch (const InvalidDateException &e)
		{
			std::cout << "Поймано исключение: " << e.what() << std::endl;
		}
	}
	catch (const std::exception &e)
	{
		std::cout << "Ошибка: " << e.what() << std::endl;
	}
}

int main()
{
	std::cout << "ЛАБОРАТОРНАЯ РАБОТА №2 - КОММИТ 1" << std::endl;
	std::cout << "Базовая структура классов с наследованием и исключениями" << std::endl;

	PhoneBook book;
	demonstrateClasses();

	int choice;
	do
	{
		displayMenu();
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			addBasicContact(book);
			break;
		case 2:
			addWorkContact(book);
			break;
		case 3:
			deleteContact(book);
			break;
		case 4:
			searchByPhone(book);
			break;
		case 5:
			displayAllContacts(book);
			break;
		case 6:
			processTextFile();
			break;
		case 0:
			std::cout << "Выход из программы..." << std::endl;
			break;
		default:
			std::cout << "Неверный выбор!" << std::endl;
		}
	} while (choice != 0);

	return 0;
}