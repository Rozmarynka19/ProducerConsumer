#include <io.h>
#include <sys\stat.h>
#include <sys\types.h>
#include <fcntl.h>
#include <string.h>
#include <windows.h>
HANDLE mutex;

int main(int argc, char *argv[])
{
    mutex = CreateMutex(NULL,0,"SynchMutex");
    if(mutex==NULL) write(2,"Mutex creation failed!\n",strlen("Mutex creation failed!\n"));
    char* c;

    do
    {
        WaitForSingleObject(mutex,INFINITE);

        //1.otwórz plik
        int descriptor = open("warehouse.txt",O_RDONLY);
        if(descriptor<0) write(2,"Creation file error\n",strlen("Creation file error\n"));

        //2.odczytaj znak z pliku
        int r = read(descriptor,c,1);
        if(r<0) write(2,"Read file error\n",strlen("Read file error\n"));

        //3.wypisz na stdout
        int w = write(1,c,1);
        if(w<0) write(2,"Write stdout error\n",strlen("Write stdout error\n"));

        //4.zamknij plik
        int cl = close(descriptor);
        if(cl<0) write(2,"Close file error\n",strlen("Close file error\n"));

        //5.usuń plik
        int ul = unlink("warehouse.txt");
        if(cl<0) write(2,"Unlink file error\n",strlen("Unlink file error\n"));

        _Bool succeed = ReleaseMutex(mutex);
        if(succeed==0) write(2,"Mutex release failed!\n",strlen("Mutex release failed!\n"));
    }while(*c !='*');

    CloseHandle(mutex);
    return 0;
}