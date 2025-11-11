#include "textprocessor.h"
#include <cstring>
#include <fstream>
#include <iostream>

TextProcessor::TextProcessor() : filename(nullptr)
{
	std::cout << "Вызван конструктор по умолчанию для объекта TextProcessor" << std::endl;
}

TextProcessor::TextProcessor(const char *filename)
{
	if (!filename)
	{
		throw TextProcessorException("Ошибка: Имя файла не может быть пустым");
	}

	this->filename = new char[strlen(filename) + 1];
	strcpy(this->filename, filename);

	std::cout << "Вызван конструктор с параметрами для объекта TextProcessor: " << filename << std::endl;
}

TextProcessor::TextProcessor(const TextProcessor &other)
{
	if (other.filename)
	{
		filename = new char[strlen(other.filename) + 1];
		strcpy(filename, other.filename);
	}
	else
	{
		filename = nullptr;
	}

	std::cout << "Вызван конструктор копирования для объекта TextProcessor" << std::endl;
}

TextProcessor::~TextProcessor()
{
	std::cout << "Вызван деструктор для объекта TextProcessor" << std::endl;
	delete[] filename;
}

TextProcessor &TextProcessor::operator=(const TextProcessor &other)
{
	if (this != &other)
	{
		delete[] filename;

		if (other.filename)
		{
			filename = new char[strlen(other.filename) + 1];
			strcpy(filename, other.filename);
		}
		else
		{
			filename = nullptr;
		}
	}
	return *this;
}

bool TextProcessor::isWhitespace(char c) const
{
	return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool TextProcessor::isSentenceEnd(char c) const
{
	return c == '.' || c == '!' || c == '?';
}

void TextProcessor::setFilename(const char *filename)
{
	if (!filename)
	{
		throw TextProcessorException("Ошибка: Имя файла не может быть пустым");
	}

	delete[] this->filename;
	this->filename = new char[strlen(filename) + 1];
	strcpy(this->filename, filename);
}

const char *TextProcessor::getFilename() const
{
	return filename;
}

void TextProcessor::findDashSentences()
{
	if (!filename)
	{
		throw TextProcessorException("Ошибка: Имя файла не установлено");
	}

	std::ifstream file(filename);
	if (!file.is_open())
	{
		throw FileNotFoundException();
	}

	std::cout << "\n=== ПРЕДЛОЖЕНИЯ, НАЧИНАЮЩИЕСЯ С ТИРЕ ===" << std::endl;
	std::cout << "Файл: " << filename << std::endl;
	std::cout << "----------------------------------------" << std::endl;

	char line[1000];
	bool foundAny = false;
	int sentenceCount = 0;

	while (file.getline(line, sizeof(line)))
	{
		if (file.fail() && !file.eof())
		{
			throw FileReadException();
		}

		const char *current = line;
		while (*current)
		{
			// Пропускаем пробельные символы
			while (isWhitespace(*current))
			{
				current++;
			}

			// Если нашли тире после пробелов - это наше предложение
			if (*current == '-')
			{
				foundAny = true;
				sentenceCount++;

				// Выводим номер предложения
				std::cout << "Предложение " << sentenceCount << ": ";

				// Выводим тире
				std::cout << "-";
				current++;

				// Выводим остаток предложения до конца строки или до конца предложения
				while (*current && !isSentenceEnd(*current))
				{
					std::cout << *current;
					current++;
				}

				// Выводим символ конца предложения, если есть
				if (isSentenceEnd(*current))
				{
					std::cout << *current;
				}

				std::cout << std::endl;
				break; // Переходим к следующей строке после нахождения предложения
			}
			else if (*current)
			{
				// Не тире - пропускаем до конца строки
				break;
			}
		}
	}

	if (!foundAny)
	{
		std::cout << "Предложений, начинающихся с тире, не найдено." << std::endl;
	}
	else
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Найдено предложений: " << sentenceCount << std::endl;
	}

	file.close();
}