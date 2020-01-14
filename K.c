#include <io.h>
#include <sys\stat.h>
#include <sys\types.h>
#include <fcntl.h>
#include <string.h>
#include <windows.h>

int main(int argc, char *argv[])
{
	char* c;
	int ul;
	int descriptor;
	int r;

	do
	{
		//1.otworz plik
		do
		{
			descriptor = open("warehouse.txt", O_RDONLY);
		} while (descriptor < 0);

		//2.odczytaj znak z pliku
		do
		{
			r = read(descriptor, c, 1);
		} while (r == 0);

		//3.wypisz na stdout
		int w = write(1, c, 1);
		if (w < 0) write(2, "Write stdout error\n", strlen("Write stdout error\n"));

		//4.zamknij plik
		int cl = close(descriptor);
		if (cl < 0) write(2, "Close file error\n", strlen("Close file error\n"));

		//5.usuń plik
		do
		{
			ul = unlink("warehouse.txt");
		} while (ul < 0);
	} while (*c != '*');

	return 0;
}