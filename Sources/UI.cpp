#include "UI.h"

const string AUTHOR_ID_REQUEST_TEXT = "Type id of an Author";

const string AUTHOR_NEW_ID_REQUEST_TEXT = "Type new id of an Author";

const string NEW_AUTHOR_NAME_REQUEST_TEXT = "Type name of a new Author";
const string AUTHOR_NEW_NAME_REQUEST_TEXT = "Type a new name for an Author";

const string NEW_AUTHOR_SURNAME_REQUEST_TEXT = "Type surname of a new Author";
const string AUTHOR_NEW_SURNAME_REQUEST_TEXT = "Type new surname for an Author";

const string AUTHOR_ID_IS_ALREADY_USED_TEXT = "Sorry this id is already occupied";

const string AUTHOR_SUCCESSFULY_ADDED_TEXT = "Successfully added author";
const string AUTHOR_SUCCESSFULY_DELETED_TEXT = "Succesfully deleted author";

const string AUTHOR_SELECT_FIELD_TO_UPDATE = "(0) stop updating\n(1) name\n(2) surname\n(3) id";

const string AUTHOR_SUCCESSFULY_UPDETED_TEXT = "Author was successfully updated";

const string MAIN_MENU_OPTIONS_TEXT = "(0) Exit\n(1) Add Author\n(2) Get Author\n(3) Remove Author\n(4) Update Author\n(5) Add book\n(6) Get Book\n(7) Remove Book\n(8) Update Book\n(9) Count all authors\n(10) Count all books\n(11) Count all books for a specific author";
const string MAIN_MENU_WRONG_INPUT = "Please type value between 0 and 4";

const string BOOK_ID_REQUEST_TEXT = "Please type id of a book";

const string NEW_BOOK_ID_REQUEST_TEXT = "Type an id of a new book";
const string NEW_BOOK_AUTHOR_ID_REQUEST_TEXT = "Type an id of a author of new book";
const string NEW_BOOK_TITLE_REQUEST_TEXT = "Type a title of this book";
const string NEW_BOOK_PAGES_NUMBER_REQUEST_TEXT = "Type a number of pages in this book";
const string BOOK_SUCCESSFULY_ADDED_TEXT = "Book was successfully added";

const string BOOK_SUCCESSFULY_DELETED_TEXT = "Book was successfully deleted";

const string BOOK_SELECT_FIELDS_TO_UPDATE_TEXT = "(0) stop updating\n(1) title\n(2) pages number\n(3) id\n(4) author id";
const string BOOK_NEW_AUTHOR_ID_REQUEST_TEXT = "Type a new author id of a book";
const string BOOK_NEW_ID_REQUEST_TEXT = "Type a new id of a book";
const string BOOK_NEW_PAGES_NUMBER_REQUEST_TEXT = "Type new page number of a book";
const string BOOK_NEW_TITLE_REQUEST_TEXT = "Type a new title of a book";

const string ALL_AUTHORS_COUNT_RESULT_TEXT = "Authors count: ";
const string ALL_BOOKS_COUNT_RESULT_TEXT = "Books count: ";
const string AUTHORS_BOOKS_COUNT_RESULT_TEXT = "Specified author's books count:";

int readInt(const string& text) {
	int value;
	cout << text << endl;
	cin >> value;
	return value;
}
char* readString(const string& text) {
	char* string = new char[STRING_SIZE];
	cout << text << endl;
	cin >> string;
	return string;
}

void addAuthorMenu() {
	int id;
	while (true) {
		id = readInt(AUTHOR_ID_REQUEST_TEXT);
		
		if (existAuthor(id)) {
			cout << AUTHOR_ID_IS_ALREADY_USED_TEXT << endl;
			continue;
		}

		break;
	}

	char* name = readString(NEW_AUTHOR_NAME_REQUEST_TEXT);
	char* surname = readString(NEW_AUTHOR_SURNAME_REQUEST_TEXT);

	int error = 0;
	insertAuthor(Author(id, name, surname), error);

	if (error) {
		printError(error);
		error = 0;
		return;
	}
	cout << AUTHOR_SUCCESSFULY_ADDED_TEXT << endl;
}

void getAuthorMenu() {
	int id = readInt(AUTHOR_ID_REQUEST_TEXT);

	int error = 0;
	Author author = getAuthor(id, error);
	
	if (error) {
		printError(error);
		error = 0;
		return;
	}
	cout << author.toString() << endl;
}

void removeAuthorMenu() {
	int id = readInt(AUTHOR_ID_REQUEST_TEXT), error = 0;
	removeAuthor(id, error);
	if (error) {
		printError(error);
		error = 0;
		return;
	}
	cout << AUTHOR_SUCCESSFULY_DELETED_TEXT << endl;
}

void updateBookName(Author& author) {
	char* name = readString(AUTHOR_NEW_NAME_REQUEST_TEXT);
	author.setName(name);
}

void updateBookSurname(Author& author) {
	char* surname = readString(AUTHOR_NEW_SURNAME_REQUEST_TEXT);
	author.setSurname(surname);
}

void updateBookId(Author& author) {
	int id = readInt(AUTHOR_NEW_ID_REQUEST_TEXT);
	author.setId(id);
}

void updateAuthorFields(Author &author) {
	int option;
	do {
		option = readInt(AUTHOR_SELECT_FIELD_TO_UPDATE);
		switch (option) {
		case 0:
			break;
		case 1:
			updateBookName(author);
			break;
		case 2:
			updateBookSurname(author);
			break;
		case 3:
			updateBookId(author);
			break;
		}
	} while (option != 0);
}

void updateAuthorMenu() {
	int id = readInt(AUTHOR_ID_REQUEST_TEXT), error = 0;
	Author author = getAuthor(id, error);

	if (error) {
		printError(error);
		error = 0;
		return;
	}

	updateAuthorFields(author);

	updateAuthor(author, id, error);

	if (error) {
		printError(error);
		error = 0;
		return;
	}
	
	cout << AUTHOR_SUCCESSFULY_UPDETED_TEXT << endl;
}


void addBookMenu() {
	int id = readInt(NEW_BOOK_ID_REQUEST_TEXT);
	int authorId = readInt(NEW_BOOK_AUTHOR_ID_REQUEST_TEXT);
	char* title = readString(NEW_BOOK_TITLE_REQUEST_TEXT);
	int pagesNumber = readInt(NEW_BOOK_PAGES_NUMBER_REQUEST_TEXT);

	int error = 0;
	insertBook(Book(id, authorId, title, pagesNumber), error);
	
	if (error) {
		printError(error);
		error = 0;
		return;
	}

	cout << BOOK_SUCCESSFULY_ADDED_TEXT << endl;
}

void getBookMenu() {
	int authorId = readInt(AUTHOR_ID_REQUEST_TEXT);
	int bookId = readInt(BOOK_ID_REQUEST_TEXT);
		
	int error = 0;
	Book book = getBook(authorId, bookId, error);
	if (error) {
		printError(error);
		error = 0;
		return;
	}

	Author author = getAuthor(authorId, error);
	if (error) {
		printError(error);
		error = 0;
		return;
	}

	cout << author.toString() << endl;
	cout << book.toString() << endl;
}

void removeBookMenu() {
	int authorId = readInt(AUTHOR_ID_REQUEST_TEXT);
	int bookId = readInt(BOOK_ID_REQUEST_TEXT);
	
	int error = 0;
	removeBook(authorId, bookId, error);
	if (error) {
		printError(error);
		error = 0;
		return;
	}
	cout << BOOK_SUCCESSFULY_DELETED_TEXT << endl;
}

void updateBookTiltle(Book &book) {
	char* title = readString(BOOK_NEW_TITLE_REQUEST_TEXT); 
	book.setTitle(title);
}

void updateBookPagesNumber(Book &book) {
	int pagesNumber = readInt(BOOK_NEW_PAGES_NUMBER_REQUEST_TEXT);
	book.setPagesNumber(pagesNumber);
}


void updateBookId(Book& book) {
	int id = readInt(BOOK_NEW_ID_REQUEST_TEXT);
	book.setId(id);
}

void updateBookAuthorId(Book& book) {
	int authorId = readInt(BOOK_NEW_AUTHOR_ID_REQUEST_TEXT);
	book.setAuthorId(authorId);
}

void updateBookFields(Book &book) {
	int options;
	do {
		options = readInt(BOOK_SELECT_FIELDS_TO_UPDATE_TEXT);
		switch (options) {
			case 1:
				updateBookTiltle(book);
				break;
			case 2:
				updateBookPagesNumber(book);
				break;
			case 3:
				updateBookId(book);
				break;
			case 4:
				updateBookAuthorId(book);
				break;
		}
	} while (options != 0);
}

void updateBookMenu() {
	int authorId = readInt(AUTHOR_ID_REQUEST_TEXT);
	int bookId = readInt(BOOK_ID_REQUEST_TEXT);

	int error = 0;
	Book book = getBook(authorId, bookId, error);
	if (error) {
		printError(error);
		error = 0;
		return;
	}
	updateBookFields(book);
	updateBook(book, authorId, bookId, error);
}

void countAllAuthorsMenu() {
	cout << ALL_AUTHORS_COUNT_RESULT_TEXT << countAllAuthor() << endl;
}

void coutAllBooksMenu() {
	cout << ALL_BOOKS_COUNT_RESULT_TEXT << countAllBooks() << endl;
}

void countAllBooksForAuthorMenu() {
	int authorId = readInt(AUTHOR_ID_REQUEST_TEXT), error = 0;
	int count = countBooksForAuthor(authorId, error);
	if (error) {
		printError(error);
		return;
	}
	cout << AUTHORS_BOOKS_COUNT_RESULT_TEXT << count << endl;
}

void start() {
	int option;
	do {
		option = readInt(MAIN_MENU_OPTIONS_TEXT);
		switch (option)
		{
		case 0:
			break;
		case 1:
			addAuthorMenu();
			break;
		case 2:
			getAuthorMenu();
			break;
		case 3:
			removeAuthorMenu();
			break;
		case 4:
			updateAuthorMenu();
			break;
		case 5:
			addBookMenu();
			break;
		case 6:
			getBookMenu();
			break;
		case 7:
			removeBookMenu();
			break;
		case 8:
			updateBookMenu();
			break;
		case 9:
			countAllAuthorsMenu();
			break;
		case 10:
			coutAllBooksMenu();
			break;
		case 11:
			countAllBooksForAuthorMenu();
			break;
		default:
			cout << MAIN_MENU_WRONG_INPUT << endl;
			break;
		}
	} while (option != 0);
}