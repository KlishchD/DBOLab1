#ifndef INCLUDED_Utils_H
#define INCLUDED_Utils_H

#include <iostream>
#include "Author.h"
#include "Book.h"
#include <vector>

long int getLastAddressInFile(FILE* file);

void writeAuthor(Author& author, FILE* file);

void writeAuthor(Author& author, long int address, FILE* file);

void writeBook(Book& book, FILE* file);

void writeBook(Book& book, long int address, FILE* file);

Author readAuthor(FILE* file);

Author readAuthor(FILE* file, long int address);

Book readBook(FILE* file);

Book readBook(FILE* file, long int address);

bool fileEmpty(char* path);

bool fileEmpty(FILE* file);



#endif // !INCLUDED_Utils_H