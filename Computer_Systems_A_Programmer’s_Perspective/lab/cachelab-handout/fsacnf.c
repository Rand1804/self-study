#include <stdio.h>


int main () {
    FILE * pFile; //pointer to FILE object

    pFile = fopen("tracefile.txt", "r"); //open file for reading

    char identifier;
    unsigned address;
    int size;
    // Reading lines like "M 20,1" or "L 19,3"
    while (fscanf(pFile, "%c %x,%d", &identifier, &address, &size)>0)
    {
        // Do stuff
    }
    fclose(pFile); // remember to close file when done
}
