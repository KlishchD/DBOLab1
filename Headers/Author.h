#ifndef INCLUDED_Author_H
#define INCLUDED_Author_H

#include "constants.h"
#include <string>
#include <vector>
#include <stdlib.h>

struct Author {
private:
	int id = -1;
	char* name = new char[STRING_SIZE];
	char* surname = new char[STRING_SIZE];
	int state = AUTHOR_ACTIVE_STATE;
	long int firstBook;
public:
	char* getName() {
		return name;
	}
	char* getSurname() {
		return surname;
	}
	int getId() {
		return id;
	}
	void setName(char* newName) {
		memcpy(name, newName, STRING_SIZE);
	}
	void setSurname(char* newSurname) {
		memcpy(surname, newSurname, STRING_SIZE);
	}
	void setId(int newId) {
		id = newId;
	}
	void setState(int newState) {
		state = newState;
	}
	int getState() {
		return state;
	}
	void setFirstBook(long int newFirstBook) {
		firstBook = newFirstBook;
	}
	long int getFirstBook() {
		return firstBook;
	}
	Author(int id, const char* name, const char* surname, int state = AUTHOR_ACTIVE_STATE, long int firstBook = END_MARK) {
		this->id = id;
		memcpy(this->name, name, STRING_SIZE);
		memcpy(this->surname, surname, STRING_SIZE);
		this->state = state;
		this->firstBook = firstBook;
	}

	std::string toString() {
		return std::to_string(id) + " " + name + " " + surname;
	}

	Author() {}
};

#endif // INCLUDED_Author_H
