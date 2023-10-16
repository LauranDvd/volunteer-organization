#pragma once
#include <exception>

class ControllerException : public std::exception {
private:
	const char* message;
public:
	ControllerException(const char* message) : message{ message } {}
	const char* what() {
		return message;
	}
};
