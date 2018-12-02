#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void KMPSearch(char* pat, char* txt);
void computeLPSArray(char* pat, int M, int lps[]);

int main(int argc, char const *argv[]) {

        printf("\t '############ Starting Making The Fils ############\n" );

        /*srand = sets its argument seed as the seed for a new sequence of
           pseudo-random numbers -> from man page*/
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
                // strcat(FileName,".txt");

                int file=creat(FileName,0666);
                counter++;
                //Check if we get an error while creating the file
                if(file<0) {
                        perror("");
                        exit(1);
                }
/*in this for loop we will fill the file with random charactors*/
                for ( int i=0; i < counterForChar; i++) {
                        randChar=(rand()%(122-97))+97; //get new random char
                        write(file,&randChar,1);
                }
                char e='?';
                write(file,&e,1);
                counterForChar+=100;
                close(file);//optinal: we can close the file that we created
        }

        return 0;
}

void KMPSearch(char* pat, char* txt){
        int M = sizeof(pat);
        int N = sizeof(txt);

        // create lps[] that will hold the
        // "longest prefix suffix" values for pattern
        int lps[M];
        int j = 0;

        computeLPSArray(pat, M, lps);

        int i = 0; // index for the text
        while(i<N) {
                if(pat[j] == txt[i]) {
                        j++;
                        i++;
                }
                if (j==M) {
                        printf("index %d",i-j);
                        j=lps[j-1];
                }// mismatch after j matches

                else if(i<N && pat[j] != txt[i-j]) {
                        // Do not match lps[0 to lps[j-1]] chars,
                        // they will match anyway
                        if(j != 0) {
                                j=lps[j-1];
                        }
                        else{
                                i=i+1;
                        }
                }
        }
}
void computeLPSArray(char* pat, int M, int lps[]){
        // length of the previous longest prefix suffix
        int l = 0;
        int i = 1;
        lps[0] = 0; //l[0] is always zero

        // the loop calculates l[i] for i = 1 to M-1
        while(i < M) {
                if(pat[i]==pat[l]) {
                        l++;
                        lps[i]=1;
                        i++;
                }
                else{// (pat[i] != pat[l])
                     // This is an example.
                     // AAACAAAA and i = 7. The idea is the same to search step.
                        if(l != 0) {
                                l = lps[l - 1];
                                // Also, note that we do not increment i here
                        }
                        else{
                                // if l is zero
                                lps[i]=1;
                                i++;
                        }
                }
        }
}
