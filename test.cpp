#include "myofstream.hpp"
#include <iostream>
#include <cassert>
#include "testlib.h"
#include <fstream>

DECLARE_OOP_TEST(myofstream_test_create_constructor)//тестируем функцию конца строки
{
	try
	{
		MyOfStream print("I4618462267:\\TestFile.txt", MyOfStream::OpenMode::rewrite);
	}
	catch (const std::exception& e)
	{
		assert(!strcmp(e.what(), "Error: Failed to open target file."));
	}

}


DECLARE_OOP_TEST(myofstream_test_endline)//тестируем функцию конца строки
{
	MyOfStream print("TestFile.txt", MyOfStream::OpenMode::rewrite);
	print << endline;
	char buf[50];
	std::ifstream fin("TestFile.txt");
	fin.getline(buf, 50);
	assert(!strcmp("", buf));
}


DECLARE_OOP_TEST(myofstream_test_int_flag_oct)//тестируем флаг oct
{
	MyOfStream print("TestFile.txt", MyOfStream::OpenMode::rewrite);
	int intFlagOct{ 287 }; char resultInOct[] = "437";
	print << oct << intFlagOct << endline;
	std::ifstream fin("TestFile.txt");
	char buf[50];
	fin.getline(buf, 50);
	assert(!strcmp(resultInOct, buf));
}



DECLARE_OOP_TEST(myofstream_test_int_flag_dec)//тестируем флаг dec
{
	MyOfStream print("TestFile.txt", MyOfStream::OpenMode::rewrite);
	int intFlagDec{ 287 }; char resultInDec[] = "287";
	print << dec << intFlagDec << endline;
	std::ifstream fin("TestFile.txt");
	char buf[50];
	fin.getline(buf, 50);
	assert(!strcmp(resultInDec, buf));
}


DECLARE_OOP_TEST(myofstream_test_unsetf)//тестируем функцию установки флага по умолчанию(dec).в начале ставим флаг hex,а затем unsetf. в результате устанавливается hex а потом перекрывается unsetf(по умолчанию dec).
{
	MyOfStream print("TestFile.txt", MyOfStream::OpenMode::rewrite);
	int intFlagHex{ 287 }; char resultUnflag[] = "287"; 
	print << hex << unsetf << intFlagHex << endline;
	std::ifstream fin("TestFile.txt");
	char buf[50];
	fin.getline(buf, 50);
	assert(!strcmp(resultUnflag, buf));
}


DECLARE_OOP_TEST(myofstream_test_int_flag_hex)//тестируем флаг hex
{
	MyOfStream print("TestFile.txt", MyOfStream::OpenMode::rewrite);
	int intFlagHex{ 287 }; char resultInHex[] = "11f";
	print << hex << intFlagHex << endline;
	std::ifstream fin("TestFile.txt");
	char buf[50];
	fin.getline(buf, 50);
	assert(!strcmp(resultInHex, buf));
}

DECLARE_OOP_TEST(myofstream_test_int_flag_binary)//тестируем флаг bin
{
	MyOfStream print("TestFile.txt", MyOfStream::OpenMode::rewrite);
	int intFlagBin{ 287 }; char resultInBin[] = "100011111";
	print << bin << intFlagBin << endline;
	std::ifstream fin("TestFile.txt");
	char buf[50];
	fin.getline(buf, 50);
	assert(!strcmp(resultInBin, buf));
}

DECLARE_OOP_TEST(myofstream_test_double)//тестируем вывод double
{
	MyOfStream print("TestFile.txt", MyOfStream::OpenMode::rewrite);
	double testdoublevalue{ 10.123 }; char resultTestDouble[] = "10.123000";
	print << testdoublevalue << endline;
	std::ifstream fin("TestFile.txt");
	char buf[50];
	fin.getline(buf, 50);
	assert(!strcmp(buf, resultTestDouble));
};



DECLARE_OOP_TEST(myofstream_test_char)//тестируем вывод неконстантной строки (сhar)
{
	MyOfStream print("TestFile.txt", MyOfStream::OpenMode::rewrite);
	print << "Test string" << endline; char resultstring[] = "Test string";
	std::ifstream fin("TestFile.txt");
	char buf[50];
	fin.getline(buf, 50);
	assert(!strcmp(resultstring, buf));

}

DECLARE_OOP_TEST(myofstream_test_const_char)//тестируем вывод константной строки (сhar)
{
	MyOfStream print("TestFile.txt", MyOfStream::OpenMode::rewrite);
	const char mytestconstchar[] = "This string";
	print << mytestconstchar << endline;
	std::ifstream fin("TestFile.txt");
	char buf[50];
	fin.getline(buf, 50);
	assert(!strcmp(mytestconstchar, buf));
};


DECLARE_OOP_TEST(myofstream_test_bool)//тестируем вывод булевого значения
{
	MyOfStream print("TestFile.txt", MyOfStream::OpenMode::rewrite);
	bool testbool{ 1 }; char resultvalue[] = "1";
	print << testbool << endline;
	std::ifstream fin("TestFile.txt");
	char buf[50];
	fin >> buf;
	assert(!strcmp(resultvalue, buf));
}

