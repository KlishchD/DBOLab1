#include "DataOperations.h"
#include "Utils.h"

vector<pair<int, long int>> g_indexes;
vector <long int> g_freeSpace;

FILE* g_authorsFile;
FILE* g_booksFile;
char* g_freeSpacesAdressesFilePath;
char* g_indexFilePath;

int findAuthorInIndex(int id) {
	int l = 0, r = g_indexes.size() - 1, mid;
	while (r >= l) {
		mid = (l + r) / 2;
		if (g_indexes[mid].first == id) {
			return mid;
		}
		if (g_indexes[mid].first > id) {
			r = mid - 1;
		}
		else {
			l = mid + 1;
		}
	}
	return ABSENT_MARK;
}

long int findAuthorAddress(int id) {
	int index = findAuthorInIndex(id);
	return index == ABSENT_MARK ? ABSENT_MARK : g_indexes[index].second;
}

void loadIndexes(int &error) {
	FILE* file;
	fopen_s(&file, g_indexFilePath, "rb");

	if (file == NULL) {
		error = CAN_NOT_LOAD_INDEX_FILE_ERROR_CODE;
		return;
	}
	if (!fileEmpty(file)) {
		int id;
		long int position;

		fread(&id, sizeof(int), 1, file);
		fread(&position, sizeof(long int), 1, file);
		while (!feof(file)) {
			g_indexes.push_back({ id, position });
			fread(&id, sizeof(int), 1, file);
			fread(&position, sizeof(long int), 1, file);
		} 
	}
	fclose(file);
}

void writeIndexes(int& error) {
	FILE* file;
	fopen_s(&file, g_indexFilePath, "wb");

	if (file == NULL) {
		error = CAN_NOT_LOAD_INDEX_FILE_ERROR_CODE;
		return;
	}
	for (pair<int, long int>& item : g_indexes) {
		fwrite(&item.first, sizeof(int), 1, file);
		fwrite(&item.second, sizeof(long int), 1, file);
	}
	fclose(file);
}

void loadFreeSpaceAdresses(int& error) {
	if (fileEmpty(g_freeSpacesAdressesFilePath)) return;

	FILE* file;
	fopen_s(&file, g_freeSpacesAdressesFilePath, "rb");
	
	if (file == NULL) {
		error = CAN_NOT_LOAD_FREE_SPACES_FILE_ERROR_CODE;
		return;
	}

	int freeSpace;
	do {
		fread(&freeSpace, sizeof(long int), 1, file);
		g_freeSpace.push_back(freeSpace);
	} while (!feof(file));

	fclose(file);
}

void writeFreeSpaceAdresses(int& error) {
	FILE* file;
	fopen_s(&file, g_freeSpacesAdressesFilePath, "wb");

	if (file == NULL) {
		error = CAN_NOT_LOAD_FREE_SPACES_FILE_ERROR_CODE;
		return;
	}

	for (long int freeSpace : g_freeSpace) {
		fwrite(&freeSpace, sizeof(int), 1, file);
	}

	fclose(file);
}

long int findBookAddress(int authorId, int bookId, int& error) {
	long int address = getAuthor(authorId, error).getFirstBook();
	if (error) return ABSENT_MARK;
	while (address != END_MARK) {
		Book book = readBook(g_booksFile, address);
		if (book.getId() == bookId) break;
		address = book.getNextBook();
	}
	return address;
}

void setup(char* authorsFilePath, char* freeSpacesAdressesFilePath, char* indexFilePath, char* booksFilePath, int& error) {
	fopen_s(&g_authorsFile, authorsFilePath, (char*)"rb+");
	if (g_authorsFile == NULL) {
		error = CAN_NOT_LOAD_AUTHORS_FILE_ERROR_CODE;
		return;
	}

	g_freeSpacesAdressesFilePath = freeSpacesAdressesFilePath;
	loadFreeSpaceAdresses(error);
	if (error) return;

	g_indexFilePath = indexFilePath;
	loadIndexes(error);
	if (error) return;

	fopen_s(&g_booksFile, booksFilePath, "rb+");
	if (g_booksFile == NULL) {
		error = CAN_NOT_LOAD_BOOKS_FILE_ERROR_CODE;
		return;
	}
}

void close(int& error) {
	fclose(g_authorsFile);

	writeFreeSpaceAdresses(error);
	if (error) return;

	writeIndexes(error);
	if (error) return;

	fclose(g_booksFile);
}

bool existAuthor(int id) {
	return findAuthorAddress(id) != ABSENT_MARK;
}

bool existsBook(int authorId, int bookId, int& error) {
	return findBookAddress(authorId, bookId, error) != ABSENT_MARK;
}

void insertAuthor(Author author, int& error) {
	if (g_freeSpace.empty()) {
		fseek(g_authorsFile, 0, SEEK_END);
	}
	else {
		fseek(g_authorsFile, g_freeSpace.back(), SEEK_SET);
		g_freeSpace.pop_back();
	}
	g_indexes.push_back({ author.getId(), ftell(g_authorsFile) });
	sort(begin(g_indexes), end(g_indexes));
	writeAuthor(author, g_authorsFile);
}

void insertBook(Book book, int& error) {
	Author author = getAuthor(book.getAuthorId(), error);
	if (error) return;

	long int newBookAdress = getLastAddressInFile(g_booksFile);
	book.setNextBook(author.getFirstBook());
	writeBook(book, newBookAdress, g_booksFile);

	Book nextBook = readBook(g_booksFile, author.getFirstBook());
	nextBook.setPreviousBook(newBookAdress);
	writeBook(nextBook, author.getFirstBook(), g_booksFile);

	author.setFirstBook(newBookAdress);
	updateAuthor(author, author.getId(), error);
}

void removeAuthor(int id, int& error) {
	int index = findAuthorInIndex(id);
	if (index == ABSENT_MARK) {
		error = CAN_NOT_FIND_AUTHOR_ERROR_CODE;
		return;
	}

	long int address = g_indexes[index].second;
	Author author = readAuthor(g_authorsFile, address);
	author.setState(BOOK_REMOVED_STATE);
	writeAuthor(author, address, g_authorsFile);

	g_freeSpace.push_back(address);
	g_indexes.erase(begin(g_indexes) + index);
}

void removeBook(int authorId, int bookId, int& error) {
	long int bookAddress = findBookAddress(authorId, bookId, error);
	if (error) return;
	if (bookAddress == ABSENT_MARK) {
		error = CAN_NOT_FIND_BOOK_ERROR_CODE;
		return;
	}

	Book book = readBook(g_booksFile, bookAddress);

	if (book.getPreviousBook() == ABSENT_MARK) {
		Author author = getAuthor(authorId, error);
		author.setFirstBook(book.getNextBook());
		updateAuthor(author, author.getId(), error);
	}
	else {
		Book previousBook = readBook(g_booksFile, book.getPreviousBook());
		previousBook.setNextBook(book.getNextBook());
		updateBook(previousBook, authorId, previousBook.getId(), error);
	}

	book.setState(BOOK_REMOVED_STATE);
	writeBook(book, bookAddress, g_booksFile);
}

void updateAuthor(Author author, int id, int& error) {
	int address = findAuthorAddress(id);
	if (address == ABSENT_MARK) {
		error = CAN_NOT_FIND_AUTHOR_ERROR_CODE;
		return;
	}
	writeAuthor(author, address, g_authorsFile);
}

void updateBook(Book book, int authorId, int id, int& error) {
	int address = findBookAddress(authorId, id, error);
	if (error) return;
	if (address == ABSENT_MARK) {
		error = CAN_NOT_FIND_BOOK_ERROR_CODE;
		return;
	}
	writeBook(book, address, g_booksFile);
}

Author getAuthor(int id, int& error) {
	int address = findAuthorAddress(id);
	if (address == ABSENT_MARK) {
		error = CAN_NOT_FIND_AUTHOR_ERROR_CODE;
		return Author();
	}
	return readAuthor(g_authorsFile, address);
}

Book getBook(int authorId, int id, int& error) {
	long int address = findBookAddress(authorId, id, error);
	if (error) return Book();
	if (address == ABSENT_MARK) {
		error = CAN_NOT_FIND_BOOK_ERROR_CODE;
		return Book();
	}
	return readBook(g_booksFile, address);
}

int countAllAuthor() {
	return g_indexes.size();
}

int countAllBooks() {
	if (fileEmpty(g_booksFile)) return 0;
	fseek(g_booksFile, 0, SEEK_SET);
	int result = 0;
	Book book = readBook(g_booksFile);
	while (!feof(g_booksFile)) {
		result += book.getState() == BOOK_ACTIVE_STATE;
		book = readBook(g_booksFile);
	}
	return result;
}

int countBooksForAuthor(int authorId, int& error) {
	int address = getAuthor(authorId, error).getFirstBook(), result = 0;
	if (error) return 0;
	while (address != END_MARK) {
		Book book = readBook(g_booksFile, address);
		address = book.getNextBook();
		result += book.getState() == BOOK_ACTIVE_STATE;
	}
	return result;
}