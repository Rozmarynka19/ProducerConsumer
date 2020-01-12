#include <io.h>
#include <sys\stat.h>
#include <sys\types.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char* c;

    do
    {
        //1.utwórz plik
        int descriptor = open("warehouse.txt",O_WRONLY|O_CREAT|O_TRUNC, _S_IREAD | _S_IWRITE);
        if(descriptor<0) write(1,"Creation file error",strlen("Creation file error"));
        //2.odczytaj znak z stdin
        int r = read(0,c,1);
        if(r<0) write(1,"Read stdin error",strlen("Read stdin error"));
        //3.wrzuc znak do pliku
        int w = write(descriptor,c,1);
        if(w<0) write(1,"Write file error",strlen("Write file error"));
        //4.zamknij plik
        int cl = close(descriptor);
        if(cl<0) write(1,"Close file error",strlen("Close file error"));
    }while(*c !='*');

    //odczyt znaku pojedynczego z stdin (z klawiatury)
    //wysłanie znaku do pliku
    //K usuwa plik
    //jeśli K usunie plik, P tworzy nowy
    //K czeka na utworzenie pliku i wypelnienie go znakiem
    //K odczytuje znak z pliku i wysyla na stdout (terminal)
    //K po odczycie usuwa plik
}