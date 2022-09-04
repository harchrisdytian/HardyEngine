#pragma once

#include <string>
#include <exception>

class ExceptionHandler : public std::exception
{
public: 
	ExceptionHandler(int line, const char* file) noexcept;
	const char* what() const noexcept override;
	virtual const char* GetType() const noexcept;
	std::string GetStartString() const noexcept;
	const std::string& GetFile() const noexcept;
private:
	int line;
	std::string file;
protected:
	mutable std::string errBuffer;
};

