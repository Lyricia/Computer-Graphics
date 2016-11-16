#include <malloc.h>


int main()
{
	char *a = reinterpret_cast<char *>(malloc(1024 * 1024));
}