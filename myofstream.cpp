/*
-------------------------------------------------------------------------------------------------------------------
Created by staskond.
-------------------------------------------------------------------------------------------------------------------
*/

#include "myofstream.hpp"
#include <cassert>
#include <bitset>
#include <string>





inline char BitToChar(int _buf)//перводит биті в символьное представление
{
	assert((_buf > -1) && (_buf < 2));
 
	return (_buf) ? '1' : '0';//тернарный условнй оператор, если условие выполняется - возвращает '1', не выполняется - возвращает '0'.
}

void BinaryToCString(char * _array, int _nOfBits, int _digit) {//Запись битового представления числа _digit в строку старого типа
	for (int i = _nOfBits - 1; i != -1; --i) {
		_array[i] = BitToChar(_digit % 2);
		_digit = _digit >> 1;
	}

	assert(_digit == 0);
}

int CountBits(int _digit) {//подсчет количество битов в числе, возвращаем counter.
	int counter = 0;
	for (int x = _digit; x != 0; x = x >> 1)	
		++counter;

	return counter;
}

void MyOfStream::PrintBinary(int _digit) {//вывод в бинарном формате(двоичном)
	int nOfBits = CountBits(_digit);
	char *charArray = new char[nOfBits + 1];

	charArray[nOfBits] = '\0';

	BinaryToCString(charArray, nOfBits, _digit);
	*this << (charArray);

	delete[] charArray;
}

MyOfStream::MyOfStream(const char *_file, OpenMode _mode)//конструктор принемающий имя файла на запись, перезапись, чтение и режим.
	: m_currentFlag(Mode::dec)
{

	switch (_mode)
	{
	case OpenMode::append:
		m_file = fopen(_file, "a");
		break;
	case OpenMode::rewrite:
		m_file = fopen(_file, "w");
		break;
	default:
		assert(!"Unknown mode");
		m_file = NULL;
		break;
	}

	if (m_file == NULL)
	{
		throw std::logic_error("Error: Failed to open target file.");
	}

};


MyOfStream::~MyOfStream()//деструктор, открытый файл должен быть закрыт
{
	fclose(m_file);
};


 MyOfStream & MyOfStream::operator << (bool _mystring)//перегрузка оператора для типа bool
{
	
	fprintf(m_file, "%d", _mystring);
	return *this;
};

MyOfStream & MyOfStream::operator << (char _mystring)//перегрузка оператора для типа char
{
	fprintf(m_file, "%c", _mystring);

	return *this;
};

MyOfStream & MyOfStream::operator << (const char *_mystring)//перегрузка оператора для строк старого типа.
{
	fprintf(m_file, "%s", _mystring);

	return *this;
};

MyOfStream & MyOfStream::operator << (int _mystring)//перегрузка оператора для типа int
{
	switch(this->m_currentFlag)
	{
	case Mode::oct: fprintf(m_file, "%o", _mystring); break;
	case Mode::dec: fprintf(m_file, "%d", _mystring); break;
	case Mode::hex: fprintf(m_file, "%x", _mystring); break;
	case Mode::bin: PrintBinary(_mystring); break;

	default:assert(!"Error: unknown flag"); break;
	}
	return *this;
};

/*MyOfStream & MyOfStream::operator << (float _mystring)//перегрузка оператора для типа float
{
	fprintf(m_file, "%f", _mystring);

	return *this;
};*/

MyOfStream & MyOfStream::operator << (double _mystring)//перегрузка оператора для типа double
{
	fprintf(m_file, "%f", _mystring);

	return *this;
};


MyOfStream & MyOfStream::flush() {//функция сброса буфера
	fflush(m_file);

	return *this;
}



MyOfStream & MyOfStream::operator << (MyOfStream & (*manipulator)(MyOfStream &))//функция манипулятор
{
	manipulator(*this);

	return *this;
}

MyOfStream & endline(MyOfStream &_o)//функция выводящая в файл символ конца строки
{
	
	fprintf(_o.m_file, "%s", "\n");
	_o.flush();
	return _o;
}

void MyOfStream::unsetflag()//Функция для сброса флага обратно на десятичную СИС
{
	m_currentFlag = Mode::dec;
}

