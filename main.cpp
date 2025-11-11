#include <iostream>
#include "note.h"
#include "phonebook.h"
#include "textprocessor.h"

// Прототипы функций
void displayMainMenu();
void displayAddMenu();
void addBasicContact(PhoneBook &book);
void addWorkContact(PhoneBook &book);
void deleteContact(PhoneBook &book);
void searchByPhone(PhoneBook &book);
void displayAllContacts(PhoneBook &book);
void editContact(PhoneBook &book);
void processTextFile();
void demonstrateFunctionality();
void demonstrateClasses();
void demonstrateTextProcessing();

// Глобальные объекты
PhoneBook book;
TextProcessor textProcessor;

void displayMainMenu()
{
	std::cout << "\n=== СИСТЕМА УПРАВЛЕНИЯ ЗАПИСНОЙ КНИГОЙ ===" << std::endl;
	std::cout << "1. Добавить контакт" << std::endl;
	std::cout << "2. Удалить контакт" << std::endl;
	std::cout << "3. Редактировать контакт" << std::endl;
	std::cout << "4. Поиск по телефону" << std::endl;
	std::cout << "5. Показать все контакты" << std::endl;
	std::cout << "6. Обработать текстовый файл" << std::endl;
	std::cout << "7. Информация о системе" << std::endl;
	std::cout << "0. Выход" << std::endl;
	std::cout << "Выберите действие: ";
}

void displayAddMenu()
{
	std::cout << "\n=== ДОБАВЛЕНИЕ КОНТАКТА ===" << std::endl;
	std::cout << "1. Базовый контакт" << std::endl;
	std::cout << "2. Рабочий контакт" << std::endl;
	std::cout << "0. Назад" << std::endl;
	std::cout << "Выберите тип контакта: ";
}

void addBasicContact(PhoneBook &book)
{
	try
	{
		NOTE *newContact = new NOTE();
		std::cout << "\n--- Создание базового контакта ---" << std::endl;
		std::cin >> *newContact;

		int position;
		std::cout << "Введите позицию для добавления (-1 для автоматической в конец): ";
		std::cin >> position;

		book.addContact(newContact, position);
		std::cout << "✅ Базовый контакт успешно добавлен!" << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "❌ Ошибка при добавлении: " << e.what() << std::endl;
	}
}

void addWorkContact(PhoneBook &book)
{
	try
	{
		char name[100], phone[20], company[100], position[100];
		int day, month, year;

		std::cout << "\n--- Создание рабочего контакта ---" << std::endl;
		std::cout << "Введите ФИО: ";
		std::cin.ignore();
		std::cin.getline(name, 100);

		std::cout << "Введите телефон: ";
		std::cin.getline(phone, 20);

		std::cout << "Введите день рождения (день месяц год): ";
		std::cin >> day >> month >> year;

		std::cout << "Введите компанию: ";
		std::cin.ignore();
		std::cin.getline(company, 100);

		std::cout << "Введите должность: ";
		std::cin.getline(position, 100);

		WorkNote *newContact = new WorkNote(name, phone, day, month, year, company, position);

		int pos;
		std::cout << "Введите позицию для добавления (-1 для автоматической в конец): ";
		std::cin >> pos;

		book.addContact(newContact, pos);
		std::cout << "✅ Рабочий контакт успешно добавлен!" << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "❌ Ошибка при добавлении: " << e.what() << std::endl;
	}
}

void deleteContact(PhoneBook &book)
{
	if (book.isEmpty())
	{
		std::cout << "📭 Телефонная книга пуста!" << std::endl;
		return;
	}

	std::cout << "\n=== УДАЛЕНИЕ КОНТАКТА ===" << std::endl;
	std::cout << "1. Удалить по индексу" << std::endl;
	std::cout << "2. Удалить по номеру телефона" << std::endl;
	std::cout << "0. Назад" << std::endl;
	std::cout << "Выберите способ: ";

	int choice;
	std::cin >> choice;

	try
	{
		switch (choice)
		{
		case 1:
		{
			int index;
			std::cout << "Введите индекс контакта (1-" << book.getSize() << "): ";
			std::cin >> index;
			book.removeContact(index - 1);
			std::cout << "✅ Контакт успешно удален!" << std::endl;
			break;
		}
		case 2:
		{
			char phone[20];
			std::cout << "Введите номер телефона: ";
			std::cin >> phone;
			book.removeContactByPhone(phone);
			std::cout << "✅ Контакт успешно удален!" << std::endl;
			break;
		}
		case 0:
			return;
		default:
			std::cout << "❌ Неверный выбор!" << std::endl;
		}
	}
	catch (const std::exception &e)
	{
		std::cout << "❌ Ошибка при удалении: " << e.what() << std::endl;
	}
}

void searchByPhone(PhoneBook &book)
{
	if (book.isEmpty())
	{
		std::cout << "📭 Телефонная книга пуста!" << std::endl;
		return;
	}

	char phone[20];
	std::cout << "\n=== ПОИСК ПО ТЕЛЕФОНУ ===" << std::endl;
	std::cout << "Введите номер телефона: ";
	std::cin >> phone;

	NOTE *found = book.findContactByPhone(phone);
	if (found)
	{
		std::cout << "✅ Контакт найден!" << std::endl;
		found->printInfo();
	}
	else
	{
		std::cout << "❌ Контакт с номером '" << phone << "' не найден." << std::endl;
	}
}

void displayAllContacts(PhoneBook &book)
{
	book.displayAllContacts();
}

void editContact(PhoneBook &book)
{
	if (book.isEmpty())
	{
		std::cout << "📭 Телефонная книга пуста!" << std::endl;
		return;
	}

	std::cout << "\n=== РЕДАКТИРОВАНИЕ КОНТАКТА ===" << std::endl;
	book.displayAllContacts();

	int index;
	std::cout << "Введите индекс контакта для редактирования (1-" << book.getSize() << "): ";
	std::cin >> index;

	try
	{
		book.editContact(index - 1);
		std::cout << "✅ Контакт успешно отредактирован!" << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "❌ Ошибка при редактировании: " << e.what() << std::endl;
	}
}

void processTextFile()
{
	try
	{
		char filename[100];
		std::cout << "\n=== ОБРАБОТКА ТЕКСТОВОГО ФАЙЛА ===" << std::endl;
		std::cout << "Введите имя файла: ";
		std::cin.ignore();
		std::cin.getline(filename, 100);

		textProcessor.setFilename(filename);
		textProcessor.findDashSentences();
	}
	catch (const std::exception &e)
	{
		std::cout << "❌ Ошибка при обработке файла: " << e.what() << std::endl;
	}
}

void demonstrateFunctionality()
{
	std::cout << "\n=== ДЕМОНСТРАЦИЯ РАБОТЫ ЗАПИСНОЙ КНИГИ ===" << std::endl;

	try
	{
		// Добавление тестовых контактов в разном порядке
		NOTE *contact1 = new NOTE("Петров Петр", "+79123456789", 15, 5, 1990);
		NOTE *contact2 = new NOTE("Иванов Иван", "+79987654321", 20, 10, 1985);
		WorkNote *contact3 = new WorkNote("Сидорова Мария", "+79551234567", 10, 3, 1988, "ООО Ромашка", "Директор");
		NOTE *contact4 = new NOTE("Алексеев Алексей", "+79031234567", 5, 1, 1995);

		std::cout << "\nДобавление контактов..." << std::endl;
		book.addContact(contact1);
		book.addContact(contact2);
		book.addContact(contact3);
		book.addContact(contact4);

		std::cout << "\n--- Все контакты (отсортированы по дате рождения) ---" << std::endl;
		book.displayAllContacts();

		std::cout << "\n--- Поиск по телефону '+79987654321' ---" << std::endl;
		NOTE *found = book.findContactByPhone("+79987654321");
		if (found)
		{
			std::cout << "Найден контакт: " << std::endl;
			found->printInfo();
		}

		std::cout << "\n--- Поиск по несуществующему телефону '+70000000000' ---" << std::endl;
		NOTE *notFound = book.findContactByPhone("+70000000000");
		if (!notFound)
		{
			std::cout << "Контакт не найден (ожидаемое поведение)" << std::endl;
		}
	}
	catch (const std::exception &e)
	{
		std::cout << "Ошибка: " << e.what() << std::endl;
	}
}

void demonstrateTextProcessing()
{
	std::cout << "\n=== ДЕМОНСТРАЦИЯ ОБРАБОТКИ ТЕКСТА ===" << std::endl;

	try
	{
		// Создаем тестовый файл
		std::ofstream testFile("demo_text.txt");
		if (testFile.is_open())
		{
			testFile << "Это обычное предложение.\n";
			testFile << "   - А это предложение начинается с тире после пробелов.\n";
			testFile << "-Это предложение сразу с тире.\n";
			testFile << "    Еще одно обычное предложение. - А это тире в середине.\n";
			testFile << "\t- Предложение с табуляцией перед тире.\n";
			testFile << "   - Еще одно предложение с тире! Оно заканчивается восклицательным знаком.\n";
			testFile.close();

			std::cout << "Создан тестовый файл: demo_text.txt" << std::endl;
		}

		// Демонстрируем обработку
		TextProcessor processor("demo_text.txt");
		processor.findDashSentences();
	}
	catch (const std::exception &e)
	{
		std::cout << "Ошибка при демонстрации: " << e.what() << std::endl;
	}
}

void demonstrateClasses()
{
	std::cout << "=== ДЕМОНСТРАЦИЯ РАБОТЫ КЛАССОВ ===" << std::endl;

	try
	{
		// Демонстрация базового класса
		NOTE note1("Иванов Иван", "+79123456789", 15, 5, 1990);
		note1.printInfo();

		std::cout << "\n--- Демонстрация наследования ---" << std::endl;
		WorkNote workNote1("Петров Петр", "+79987654321", 20, 10, 1985, "ООО Ромашка", "Менеджер");
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
			NOTE invalidDateNote("Сидоров Алексей", "+79123456789", 32, 13, 1990);
		}
		catch (const InvalidDateException &e)
		{
			std::cout << "Поймано исключение: " << e.what() << std::endl;
		}

		std::cout << "\n--- Демонстрация сравнения по дате рождения ---" << std::endl;
		NOTE note2("Алексеев Алексей", "+79234567890", 10, 3, 1988);
		std::cout << "note1 < note2: " << (note1 < note2 ? "true" : "false") << std::endl;
		std::cout << "note2 < note1: " << (note2 < note1 ? "true" : "false") << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Ошибка: " << e.what() << std::endl;
	}
}

int main()
{
	std::cout << "ЛАБОРАТОРНАЯ РАБОТА №2 - ВАРИАНТ 12" << std::endl;
	std::cout << "Система управления записной книгой и обработки текста" << std::endl;
	std::cout << "=====================================================" << std::endl;

	// Демонстрация работы классов
	demonstrateClasses();

	// Демонстрация работы записной книги
	demonstrateFunctionality();

	// Демонстрация обработки текста
	demonstrateTextProcessing();

	std::cout << "\n=====================================================" << std::endl;
	std::cout << "Демонстрация завершена. Переходим в режим меню." << std::endl;

	// Основное меню
	int choice;
	do
	{
		displayMainMenu();
		std::cin >> choice;

		switch (choice)
		{
		case 1:
		{
			int addChoice;
			do
			{
				displayAddMenu();
				std::cin >> addChoice;
				switch (addChoice)
				{
				case 1:
					addBasicContact(book);
					break;
				case 2:
					addWorkContact(book);
					break;
				case 0:
					break;
				default:
					std::cout << "❌ Неверный выбор!" << std::endl;
				}
			} while (addChoice != 0);
			break;
		}
		case 2:
			deleteContact(book);
			break;
		case 3:
			editContact(book);
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
		case 7:
			std::cout << "\n=== ИНФОРМАЦИЯ О СИСТЕМЕ ===" << std::endl;
			std::cout << "Количество контактов: " << book.getSize() << std::endl;
			std::cout << "Состояние книги: " << (book.isEmpty() ? "пуста" : "есть контакты") << std::endl;
			if (textProcessor.getFilename())
			{
				std::cout << "Текущий файл для обработки: " << textProcessor.getFilename() << std::endl;
			}
			else
			{
				std::cout << "Файл для обработки не установлен" << std::endl;
			}
			break;
		case 0:
			std::cout << "Выход из программы..." << std::endl;
			break;
		default:
			std::cout << "❌ Неверный выбор!" << std::endl;
		}
	} while (choice != 0);

	return 0;
}