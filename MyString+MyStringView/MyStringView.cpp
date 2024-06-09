#include "MyStringView.h"

MyStringView::MyStringView(const char* begin, const char* end) : _begin(begin), _end(end) {}

MyStringView::MyStringView(const char* str) : MyStringView(str, str + strlen(str)) {}

MyStringView::MyStringView(const MyString& str) : MyStringView(str.c_str()) {}

size_t MyStringView::length() const {

	return _end - _begin;

}

char MyStringView::operator[](size_t index) const {

	return _begin[index];

}

MyStringView MyStringView::substr(size_t from, size_t length) const {

	if (_begin + from + length > _end)
		throw std::length_error("Error, Substr out of range");

	return MyStringView(_begin + from, _begin + from + length);

}

std::ostream& operator<<(std::ostream& os, const MyStringView& strView) {

	const char* iter = strView._begin;

	while (iter != strView._end) {

		os << *iter;
		iter++;

	}

	return os;

}