#include "ExceptionHandler.h"

#include <sstream>
#include <sdkddkver.h>


ExceptionHandler::ExceptionHandler(int line, const char* file) noexcept
	: 
	line(line),
	file(file)
{

}

const char* ExceptionHandler::what() const noexcept
{
	std::ostringstream ostrStream;
	ostrStream << GetType() << std::endl
		<< GetStartString();
	errBuffer = ostrStream.str();
	return errBuffer.c_str();
}

const char* ExceptionHandler::GetType() const noexcept
{
	return "Base Type";
}

std::string ExceptionHandler::GetStartString() const noexcept
{
	std::ostringstream ostrStream;
	ostrStream << "[File] " << file << std::endl
		<< "[Line] " << line;
	return ostrStream.str();
}

const std::string& ExceptionHandler::GetFile() const noexcept
{
	return file;
}
