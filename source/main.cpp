/*  
    - Curso : Compiladores - Laboratorio
    - Alumno: Alexander Arturo Baylon Ibanez
    - Parte del programa compilador, SCANNER

    Compilar y correr:
    $ g++ -std=c++11 -o main main.cpp helper.cpp scanner.cpp
    $ ./main "nombre del archivo de texto"
*/
#include <iostream>
#include "scanner.h"

using namespace std;

int main(int argc, char *argv[])
{
    char * fileName = argv[1];
    FILE * fd = fopen(fileName, "r");
    cout << fileName << endl;

    if (fd != NULL)
    {
        fseek(fd, 0, SEEK_END);
        int len = ftell(fd);
        rewind(fd);
        char * buffer = (char *) malloc(len);

        // read program text
        int size = fread(buffer, 1, len, fd);
        string inputString(buffer);
        Scanner s(inputString);
        s.begin_scan();
        
        
    }

    //cout << "hola amigo" << endl;
	return 0;

}