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
    if(mutex==NULL) write(2,"Mutex creation failed!",strlen("Mutex creation failed!"));
    char* c;

    do
    {
        WaitForSingleObject(mutex,INFINITE);

        //1.otwórz plik
        int descriptor = open("warehouse.txt",O_RDONLY);
        if(descriptor<0) write(2,"Creation file error",strlen("Creation file error"));

        //2.odczytaj znak z pliku
        int r = read(descriptor,c,1);
        if(r<0) write(2,"Read file error",strlen("Read file error"));

        //3.wypisz na stdout
        int w = write(1,c,1);
        if(w<0) write(2,"Write stdout error",strlen("Write stdout error"));

        //4.zamknij plik
        int cl = close(descriptor);
        if(cl<0) write(2,"Close file error",strlen("Close file error"));

        //5.usuń plik
        int ul = unlink("warehouse.txt");
        if(cl<0) write(2,"Unlink file error",strlen("Unlink file error"));

        _Bool succeed = ReleaseMutex(mutex);
        if(succeed==0) write(2,"Mutex release failed!",strlen("Mutex release failed!"));
    }while(*c !='*');

    CloseHandle(mutex);
    return 0;
}