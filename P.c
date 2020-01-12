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

        //1.utwórz plik
        int descriptor = open("warehouse.txt",O_WRONLY|O_CREAT|O_TRUNC, _S_IREAD | _S_IWRITE);
        if(descriptor<0) write(2,"Creation file error\n",strlen("Creation file error\n"));

        //2.odczytaj znak z stdin
        int r = read(0,c,1);
        if(r<0) write(2,"Read stdin error\n",strlen("Read stdin error\n"));

        //3.wrzuc znak do pliku
        int w = write(descriptor,c,1);
        if(w<0) write(2,"Write file error\n",strlen("Write file error\n"));

        //4.zamknij plik
        int cl = close(descriptor);
        if(cl<0) write(2,"Close file error\n",strlen("Close file error\n"));

        _Bool succeed = ReleaseMutex(mutex);
        if(succeed==0) write(2,"Mutex release failed!\n",strlen("Mutex release failed!\n"));
    }while(*c !='*');

    CloseHandle(mutex);
    return 0;
}