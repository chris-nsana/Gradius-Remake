#ifndef GAMEEXCEPTION_H_
#define GAMEEXCEPTION_H_

#include <exception>
#include <stdexcept>

namespace Game{

class GameException : public std::exception{
public:
	
	GameException(std::string errorMessage) : message(errorMessage){}
	
	const char* what() const noexcept override{
		return message.c_str();
	}
	
protected:

	std::string message;
};

class InternalError : public GameException{
public:
	
	InternalError(std::string errorMessage) : GameException(errorMessage){}
};

class ExternalError : public GameException{
public:
	
	ExternalError(std::string errorMessage) : GameException(errorMessage){}
};

class ObserverError : public InternalError{
public:
	
	ObserverError(std::string errorMessage) : InternalError(errorMessage){}
	
};

class EntityNotFoundError : public InternalError{
public:
	
	EntityNotFoundError(int id) : InternalError(""){
		std::string full_message = "No player with id " + std::to_string(id) + " found in Model.";
		GameException::message = full_message;
	}
};

class FileNotFoundError : public ExternalError{
public:
	FileNotFoundError(std::string type, std::string path) : ExternalError(""){
		//Do something
	} 
};


class InvalidFileError : public ExternalError{
public:
	InvalidFileError(std::string fileName) : ExternalError(""){
		//Do something
	} 
};

class InvalidInputError : public ExternalError{
public:
	InvalidInputError(std::string fileName, std::string details) : ExternalError(""){
		//Do something
	} 
};

}


















#endif /* GAMEEXCEPTION_H_ */ 