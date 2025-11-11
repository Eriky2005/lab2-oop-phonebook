#include "phonebook.h"
#include <iostream>
#include <cstring>

PhoneBook::PhoneBook() : contacts(nullptr), capacity(0), size(0)
{
	contacts = new NOTE *[10];
	capacity = 10;
	std::cout << "Создана телефонная книга (емкость: " << capacity << ")" << std::endl;
}

PhoneBook::~PhoneBook()
{
	clear();
	delete[] contacts;
	std::cout << "Телефонная книга удалена" << std::endl;
}

void PhoneBook::resize()
{
	int newCapacity = capacity * 2;
	NOTE **newContacts = new NOTE *[newCapacity];

	for (int i = 0; i < size; i++)
	{
		newContacts[i] = contacts[i];
	}

	delete[] contacts;
	contacts = newContacts;
	capacity = newCapacity;
	std::cout << "Телефонная книга увеличена до " << capacity << " контактов" << std::endl;
}

void PhoneBook::sortContactsByBirthday()
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (!(*contacts[j] < *contacts[j + 1]))
			{
				NOTE *temp = contacts[j];
				contacts[j] = contacts[j + 1];
				contacts[j + 1] = temp;
			}
		}
	}
}

int PhoneBook::findContactIndexByPhone(const char *phone) const
{
	for (int i = 0; i < size; i++)
	{
		if (strcmp(contacts[i]->getPhone(), phone) == 0)
		{
			return i;
		}
	}
	return -1;
}

void PhoneBook::addContact(NOTE *contact, int position)
{
	if (size >= capacity)
	{
		resize();
	}

	if (position < 0 || position >= size)
	{
		// Добавление в конец
		contacts[size] = contact;
	}
	else
	{
		// Добавление на конкретную позицию
		for (int i = size; i > position; i--)
		{
			contacts[i] = contacts[i - 1];
		}
		contacts[position] = contact;
	}
	size++;

	// Автоматическая сортировка по дате рождения после добавления
	sortContactsByBirthday();
	std::cout << "Контакт добавлен. Всего контактов: " << size << std::endl;
}

void PhoneBook::removeContact(int index)
{
	if (index < 0 || index >= size)
	{
		throw ContactNotFoundException();
	}

	std::cout << "Удаление контакта: " << contacts[index]->getName() << std::endl;
	delete contacts[index];

	for (int i = index; i < size - 1; i++)
	{
		contacts[i] = contacts[i + 1];
	}
	size--;

	std::cout << "Контакт удален. Осталось контактов: " << size << std::endl;
}

void PhoneBook::removeContactByPhone(const char *phone)
{
	int index = findContactIndexByPhone(phone);
	if (index == -1)
	{
		throw ContactNotFoundException();
	}
	removeContact(index);
}

void PhoneBook::editContact(int index)
{
	if (index < 0 || index >= size)
	{
		throw ContactNotFoundException();
	}

	std::cout << "Редактирование контакта: " << contacts[index]->getName() << std::endl;
	std::cout << "Текущие данные:" << std::endl;
	contacts[index]->printInfo();

	std::cout << "\nВведите новые данные:" << std::endl;
	std::cin >> *contacts[index];

	// Пересортировка после редактирования
	sortContactsByBirthday();
	std::cout << "Контакт отредактирован и отсортирован" << std::endl;
}

NOTE *PhoneBook::findContactByPhone(const char *phone) const
{
	int index = findContactIndexByPhone(phone);
	if (index == -1)
	{
		return nullptr;
	}
	return contacts[index];
}

void PhoneBook::displayAllContacts() const
{
	if (isEmpty())
	{
		std::cout << "Телефонная книга пуста" << std::endl;
		return;
	}

	std::cout << "\n=== ВСЕ КОНТАКТЫ (" << size << ") ===" << std::endl;
	std::cout << "(отсортированы по дате рождения)" << std::endl;
	for (int i = 0; i < size; i++)
	{
		std::cout << "\n--- Контакт #" << (i + 1) << " ---" << std::endl;
		contacts[i]->printInfo();
	}
}

void PhoneBook::displayContact(int index) const
{
	if (index < 0 || index >= size)
	{
		throw ContactNotFoundException();
	}
	std::cout << "\n--- Информация о контакте ---" << std::endl;
	contacts[index]->printInfo();
}

void PhoneBook::clear()
{
	for (int i = 0; i < size; i++)
	{
		delete contacts[i];
	}
	size = 0;
	std::cout << "Телефонная книга очищена" << std::endl;
}

NOTE *PhoneBook::operator[](int index) const
{
	if (index < 0 || index >= size)
	{
		throw ContactNotFoundException();
	}
	return contacts[index];
}