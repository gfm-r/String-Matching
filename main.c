#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
extern int errno;

int main(int argc, char const *argv[]) {

        printf("\t '############ Starting Making The Fils ############\n" );

        /*srand = sets its argument seed as the seed for a new sequence of
           pseudo-random numbers ->from man page*/
        srand(time(NULL));
        char randChar='0';

        char FileName[8];
        int counter=0;
        int counterForChar=100;

//for every eteration we will creat a new file
        for (int i = 0; i < 100; i++) {
                //sprintf will convert int to char in our case we want to convert the cunter number into digit to usit in the file name
                sprintf(FileName,"%d",counter);
                //add a '.txt' as an extention for every file we will created
                strcat(FileName,".txt");

                int file=creat(FileName,0666);
                counter++;
                //cheac if we get an error while creating the file
                if(file<0) {
                        perror("");
                        exit(1);
                }
/*in this for loop we will fill the file with random charactors*/
                for ( int i=0; i < counterForChar; i++) {
                        randChar=(rand()%(122-97))+97; //get new random char
                        write(file,&randChar,1);
                }

                counterForChar+=100;
                close(file);//optinal: we can close the file that we created
        }

        return 0;
}
