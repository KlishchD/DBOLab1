#ifndef INCLUDED_constants_H
#define INCLUDED_constants_H


const int STRING_SIZE = 100;

const int AUTHOR_ACTIVE_STATE = 1;
const int AUTHOR_REMOVED_STATE = 0;

const int BOOK_ACTIVE_STATE = 1;
const int BOOK_REMOVED_STATE = 0;

const int END_MARK = -1;
const int ABSENT_MARK = -1;


const int CAN_NOT_LOAD_INDEX_FILE_ERROR_CODE = 1;
const int CAN_NOT_LOAD_FREE_SPACES_FILE_ERROR_CODE = 2;
const int CAN_NOT_LOAD_AUTHORS_FILE_ERROR_CODE = 3;
const int CAN_NOT_LOAD_BOOKS_FILE_ERROR_CODE = 4;
const int CAN_NOT_FIND_AUTHOR_ERROR_CODE = 5;
const int CAN_NOT_FIND_BOOK_ERROR_CODE = 6;


#endif // !INCLUDED_constants_H