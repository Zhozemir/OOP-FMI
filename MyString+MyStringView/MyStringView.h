#pragma once
#include <fstream>
#include "MyString.h"

class MyStringView{

	const char* _begin;
	const char* _end; 

public:

	MyStringView(const char* begin, const char* end);
	MyStringView(const char* str);
	MyStringView(const MyString& string);

	size_t length() const;
	char operator[](size_t ind) const;

	MyStringView substr(size_t from, size_t length) const;
	friend std::ostream& operator<<(std::ostream&, const MyStringView& strView);

};
