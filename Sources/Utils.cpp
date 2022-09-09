#include "Utils.h"


long int getLastAddressInFile(FILE* file) {
	fseek(file, 0, SEEK_END);
	return ftell(file);
}

void writeAuthor(Author& author, FILE* file) {
	int id = author.getId();
	int state = author.getState();
	long int firstBook = author.getFirstBook();
	fwrite(&id, sizeof(int), 1, file);
	fwrite(author.getName(), sizeof(char), STRING_SIZE, file);
	fwrite(author.getSurname(), sizeof(char), STRING_SIZE, file);
	fwrite(&state, sizeof(int), 1, file);
	fwrite(&firstBook, sizeof(long int), 1, file);
}

void writeAuthor(Author& author, long int address, FILE* file) {
	fseek(file, address, SEEK_SET);
	writeAuthor(author, file);
}

void writeBook(Book& book, FILE* file) {
	int id = book.getId();
	int authorId = book.getAuthorId();
	int pagesNumber = book.getPagesNumber();
	long int previousBook = book.getPreviousBook();
	long int nextBook = book.getNextBook();
	fwrite(&id, sizeof(int), 1, file);
	fwrite(&authorId, sizeof(int), 1, file);
	fwrite(book.getTitle(), sizeof(char), STRING_SIZE, file);
	fwrite(&pagesNumber, sizeof(int), 1, file);
	fwrite(&previousBook, sizeof(long int), 1, file);
	fwrite(&nextBook, sizeof(long int), 1, file);
}

void writeBook(Book& book, long int address, FILE* file) {
	fseek(file, address, SEEK_SET);
	writeBook(book, file);
}

Author readAuthor(FILE* file) {
	char* name = new char[STRING_SIZE];
	char* surname = new char[STRING_SIZE];
	int id;
	int state;
	long int firstBook;
	fread(&id, sizeof(int), 1, file);
	fread(name, sizeof(char), STRING_SIZE, file);
	fread(surname, sizeof(char), STRING_SIZE, file);
	fread(&state, sizeof(int), 1, file);
	fread(&firstBook, sizeof(long int), 1, file);
	return Author(id, name, surname, state, firstBook);
}

Author readAuthor(FILE* file, long int address) {
	fseek(file, address, SEEK_SET);
	return readAuthor(file);
}

Book readBook(FILE* file) {
	int id;
	int authorId;
	char* title = new char[STRING_SIZE];
	int pagesNumber;
	long int previousBook;
	long int nextBook;
	fread(&id, sizeof(int), 1, file);
	fread(&authorId, sizeof(int), 1, file);
	fread(title, sizeof(char), STRING_SIZE, file);
	fread(&pagesNumber, sizeof(int), 1, file);
	fread(&previousBook, sizeof(long int), 1, file);
	fread(&nextBook, sizeof(long int), 1, file);
	return Book(id, authorId, title, pagesNumber, previousBook, nextBook);
}

Book readBook(FILE* file, long int address) {
	fseek(file, address, SEEK_SET);
	return readBook(file);
}

bool fileEmpty(char* path) {
	FILE* file;
	fopen_s(&file, path, "rb");

	if (file == NULL) return true;

	fseek(file, 0, SEEK_END);
	int address = ftell(file);
	fclose(file);

	return address == 0;
}


bool fileEmpty(FILE* file) {
	fseek(file, 0, SEEK_END);
	int address = ftell(file);
	fseek(file, 0, SEEK_SET);
	return address == 0;
}