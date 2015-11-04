/*
-------------------------------------------------------------------------------------------------------------------
Created by staskond.
-------------------------------------------------------------------------------------------------------------------
*/

#ifndef _MYOFSTREAM_HPP_
#define _MYOFSTREAM_HPP_

#include <string.h>
#include <cstdio>

class MyOfStream
{
public:

	enum class Mode {
		dec = 0x0010,
		oct = 0x0020,
		hex = 0x0040,
		bin = 0x0080,
	};

	enum class OpenMode {
		rewrite, append
	};

	MyOfStream() = delete;//удаленный конструктор по умолчанию
	MyOfStream(const MyOfStream & _data) = delete;// удаленный конструктор копий
	MyOfStream & operator = (const MyOfStream &) = delete;//удаленный оператор присвоения

	MyOfStream::MyOfStream(const char *_file, OpenMode _mode);//конструктор принемающий имя файла на запись, перезапись, чтение и режим.
	~MyOfStream();//деструктор, открытый файл должен быть закрыт

	 MyOfStream & operator << (bool _mystring);//перегрузка оператора для типа bool

	MyOfStream & operator << (char _mystring);//перегрузка оператора для типа char

	MyOfStream & operator << (const char *_mystring);//перегрузка оператора для строк старого типа.

	MyOfStream & operator << (int _mystring);//перегрузка оператора для типа int

	//MyOfStream & operator << (float _mystring);//перегрузка оператора для типа float

	MyOfStream & operator << (double _mystring);//перегрузка оператора для типа double

	MyOfStream & operator << (MyOfStream & (*manipulator) (MyOfStream &));

	
	MyOfStream & flush();
	
	void setflag(Mode _m);
	void unsetflag();//Функция для сброса флага обратно на десятичную СИС
private:
	Mode m_currentFlag;
	FILE *m_file;
	friend MyOfStream & endline(MyOfStream &_o);
	void PrintBinary(int _digit);
	friend inline MyOfStream & unsetflag();
	
};

MyOfStream & endline(MyOfStream &_o);//функция выводящая в файл символ конца строки

inline MyOfStream & dec(MyOfStream & _o)//Функция для установки флага десятичной СИС
{
	_o.setflag(MyOfStream::Mode::dec);

	return _o;
};

inline MyOfStream & oct(MyOfStream & _o)//Функция для установки флага восмеричной СИС
{
	_o.setflag(MyOfStream::Mode::oct);

	return _o;
};

inline MyOfStream & hex(MyOfStream & _o)//Функция для установки флага шестн СИС
{
	_o.setflag(MyOfStream::Mode::hex);

	return _o;
};

inline MyOfStream & bin(MyOfStream & _o)//Функция для установки флага двоичной СИС
{
	_o.setflag(MyOfStream::Mode::bin);

	return _o;
};

inline void MyOfStream::setflag(Mode _m)
{
	m_currentFlag = _m;
}

inline MyOfStream & unsetf(MyOfStream & _o)//Функция для установки флага десятичной СИС
{
	_o.unsetflag();

	return _o;
};


#endif//_MYOFSTREAM_HPP_
