#ifndef INCLUDED_DataOperations_H
#define INCLUDED_DataOperations_H

#include "Author.h"
#include "Utils.h"
#include "Book.h"
#include <iostream>
#include <cstdio>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;

void setup(char* authorsFilePath, char* freeSpacesAdressesFilePath, char* indexFilePath, char* booksFilePath, int& error);

void close(int &error);

bool existAuthor(int id);

bool existsBook(int idAuthor, int bookId, int& error);

void insertAuthor(Author author, int &error);

void insertBook(Book book, int &error);

void removeAuthor(int id, int &error);

void removeBook(int bookId, int authorId, int &error);

void updateAuthor(Author author, int id,  int &error);

void updateBook(Book book, int authorId, int bookId, int& error);

Author getAuthor(int id, int &error);

Book getBook(int authorId, int id, int& error);

int countAllAuthor();

int countAllBooks();

int countBooksForAuthor(int authorId, int& error);

#endif // INCLUDED_DataOperations