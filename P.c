#include <io.h>
#include <sys\stat.h>
#include <sys\types.h>
#include <fcntl.h>
#include <string.h>
#include <windows.h>

int main(int argc, char *argv[])
{
	int descriptor;
	char* c;

	do
	{
		//1.utwórz plik
		do
		{
			descriptor = open("warehouse.txt", O_WRONLY | O_CREAT | O_EXCL, _S_IREAD | _S_IWRITE);
		} while (descriptor < 0);

		//2.odczytaj znak z stdin
		int r = read(0, c, 1);
		if (r < 0) {
			write(2, "Read stdin error\n", strlen("Read stdin error\n"));
		}

		//3.wrzuc znak do pliku
		int w = write(descriptor, c, 1);
		if (w < 0) write(2, "Write file error\n", strlen("Write file error\n"));

		//4.zamknij plik
		int cl = close(descriptor);
		if (cl < 0) write(2, "Close file error\n", strlen("Close file error\n"));

	} while (*c != '*');

	return 0;
}