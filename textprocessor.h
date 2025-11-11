#ifndef TEXTPROCESSOR_H
#define TEXTPROCESSOR_H

#include <iostream>
#include <exception>
#include <fstream>

class TextProcessorException : public std::exception
{
private:
	const char *message;

public:
	TextProcessorException(const char *msg) : message(msg) {}
	const char *what() const noexcept override
	{
		return message;
	}
};

class FileNotFoundException : public TextProcessorException
{
public:
	FileNotFoundException() : TextProcessorException("Ошибка: Файл не найден") {}
};

class FileReadException : public TextProcessorException
{
public:
	FileReadException() : TextProcessorException("Ошибка: Не удалось прочитать файл") {}
};

class TextProcessor
{
private:
	char *filename;

	// Вспомогательные методы
	bool isWhitespace(char c) const;
	bool isSentenceEnd(char c) const;

public:
	TextProcessor();
	TextProcessor(const char *filename);
	TextProcessor(const TextProcessor &other);
	~TextProcessor();

	TextProcessor &operator=(const TextProcessor &other);

	// Основные методы
	void setFilename(const char *filename);
	const char *getFilename() const;
	void findDashSentences();
};

#endif