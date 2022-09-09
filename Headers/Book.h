#ifndef INCLUDED_Book_H
#define INCLUDED_Book_H

#include "constants.h"
#include <vector>
#include <string>

const int BOOK_TOTAL_SIZE = sizeof(int) * 4 + sizeof(char) * STRING_SIZE + sizeof(long int) * 2;

struct Book {
private:
	int id;
	int authorId;
	char* title = new char[STRING_SIZE];
	int pagesNumber;
	long int nextBook = -1;
	long int previousBook = -1;
	int state;
public:
	void setId(int newId) {
		id = newId;
	}
	
	int getId() {
		return id;
	}
	
	void setAuthorId(int newAuthorId) {
		authorId = newAuthorId;
	}
	
	int getAuthorId() {
		return authorId;
	}
	
	void setTitle(char* newTitle) {
		memcpy(title, newTitle, STRING_SIZE);
	}
	
	char* getTitle() {
		return title;
	}
	
	void setPagesNumber(int newPagesNumber) {
		pagesNumber = newPagesNumber;
	}
	
	int getPagesNumber() {
		return pagesNumber;
	}

	
	void setNextBook(long int newNextBook) {
		nextBook = newNextBook;
	}

	long int getNextBook() {
		return nextBook;
	
	}void setPreviousBook(long int newPreviousBook) {
		previousBook = newPreviousBook;
	}

	long int getPreviousBook() {
		return previousBook;
	}

	void setState(int newState) {
		state = newState;
	}

	int getState() {
		return state;
	}

	std::string toString() {
		return std::to_string(id) + " "  + std::to_string(authorId) + " " + title + " " + std::to_string(pagesNumber);
	}

	Book(int id, int authorId, const char* title, int pagesNumber, int previousBook = END_MARK, int nextBook = END_MARK, int state = BOOK_ACTIVE_STATE) {
		this->id = id;
		this->authorId = authorId;
		memcpy(this->title, title, STRING_SIZE);
		this->pagesNumber = pagesNumber;
		this->nextBook = nextBook;
		this->state = state;
		this->previousBook = previousBook;
	}


	Book(){}
};


#endif
