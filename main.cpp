#include "DataOperations.h"
#include "Author.h"
#include "UI.h"

int main() {
	int error = 0;
	setup((char *)"authors.bin", (char*)"free.bin", (char*)"indexes.bin", (char*)"books.bin", error);
	
	start();

	close(error);
}
 