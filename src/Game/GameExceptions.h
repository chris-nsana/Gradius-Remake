#ifndef GAMEEXCEPTION_H_
#define GAMEEXCEPTION_H_

#include <exception>
#include <stdexcept>

class GameException : public std::exception{
public:
	
	GameException(std::string errorMessage) : message(errorMessage);
	
	const char* what() const noexcept override{
		return message.c_str();
	}
	
protected:

	std::string message;
};

class InternalError : public GameException{
public:
	
	InternalError(std::string errorMessage) : GameException(errorMesage);
};

class ExternalError : public GameException{
public:
	
	ExternalError(std::string errorMessage) : GameException(errorMesage);
};

class ObserverError : public InternalError{
public:
	
	ObserverError(std::string errorMessage) : InternalError(errorMessage);
	
};

class EntityNotFoundError : public InternalError{
public:
	
	EntityNotFoundError(std::string errorMessage) : InternalError(errorMessage);
};

class FileNotFoundError : public ExternalError{
public:
	FileNotFoundError(std::string type, std::string path) : ExternalError(""){
		//Do something
	} 
};


class InvalidFileError : public ExternalError{
public:
	InvalidFileError(std::string type, std::string path) : ExternalError(""){
		//Do something
	} 
};

class InvalidInputError : public ExternalError{
public:
	FileNotFoundError(std::string type, std::string path) : ExternalError(""){
		//Do something
	} 
};


















#endif /* GAMEEXCEPTION_H_ */ 