#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>

void BruteForce(char *pat,int num_of_File,int *files);
void KMPSearch(char*,int,int*);
void computeLPSArray(char* pat, int M, int* lps);
void CrateFiles();

int main(int argc, char *argv[])
{
        printf("## Welcome to the txt matcing program \n");
        printf("##\tEnter the pattern that you want, note (10-char MAX)\n");
        char pat[11] ={0};
        fgets(pat,11,stdin);
        printf("##\tEnter the files names -1 is for terminate\n");

        int num=0;//the number of file
        int files[99]={0};//arry for files names
        int in=0;//variaple to save the file name from the user

        scanf("%d",&in);//ask the user to enter firist file name
        while (in!=-1) {//enter files name until we get -1 as terminated number
                files[num]=in;
                num++;
                scanf("%d",&in);
        }//for the while
        void CrateFiles();
        BruteForce(pat,num,files);
        printf("\n\n" );
        KMPSearch(pat,num,files);
        return 0;
}
void BruteForce(char *pat,int num_of_File,int *files){
        printf("\t\tBruteForce Starting\n");
        for (int f = 0; f < num_of_File; f++) {//run the BruteForce for num_of_File that we enterd
                int M = strlen(pat)-1;//the length of the pattern
                int N = 0;//num of char in the file
                int i = 0; // index for txt[]
                int j = 0; // index for pat[]
                char tmp_char;//we will use this char in difirent plases in the code
                char file_name[3]={0};

                sprintf(file_name,"%d",files[f]);//convert form int to char

                int file=open(file_name,O_RDONLY);
                read(file,&tmp_char,1);//one read to check,if the file is empty we will not inter the while
                /////////////////////////////////////////////
                while (tmp_char!='?') {
                        N++;
                        read(file,&tmp_char,1);
                }
                lseek(file,0,SEEK_SET);
                int read_Char =read(file,&tmp_char,1);
                if(read_Char<0) {
                        perror("");
                        exit(1);
                }
                i++;
                while (i < N) {
                        if (pat[j] == tmp_char) {
                                i++;
                                j++;
                                read(file,&tmp_char,1);
                                if (j == M) {
                                        printf("##############################################\n" );
                                        printf("\t-->Found in file -> %s\n",file_name);
                                        printf("\t-->At index [%d] \n", (i - j));
                                        j=0;
                                        lseek(file,(i-j+1),SEEK_SET);
                                        i--;
                                        read(file,&tmp_char,1);
                                        lseek(file,(-1),SEEK_SET);
                                }
                                else if (pat[j] != tmp_char) {
                                        if (j>=2) {
                                                int l=lseek(file,(i-j+1),SEEK_SET);

                                                i=l;
                                        }
                                        j=0;
                                }
                        }
                        else{
                                j=0;
                                read(file,&tmp_char,1);
                                i++;
                        }
                }

        }//for the for
         // close(file);
}//for the BruteForce function

void KMPSearch(char *pat,int num_of_File,int *files){
        printf("\t\tKMPS Starting\n");
        for (int f = 0; f < num_of_File; f++) {//run the KMPS for num_of_File that we enterd
                int M = strlen(pat)-1;//the length of the pattern
                int N = 0;//num of char in the file
                char tmp_char;//we will use this char in difirent plases in the code
                char file_name[3]={0};

                sprintf(file_name,"%d",files[f]);//convert form int to char
                int file=open(file_name,O_RDONLY);
                read(file,&tmp_char,1);//one read to check,if the file is empty we will not inter the while
                while (tmp_char!='?') {
                        N++;
                        read(file,&tmp_char,1);
                }
                lseek(file,0,SEEK_SET);
                /////////////////////////////////////

                // create lps[] that will hold the longest prefix suffix
                // values for pattern
                int lps[M];
                // Preprocess the pattern (calculate lps[] array)
                computeLPSArray(pat, M, lps);
                int i = 0; // index for txt[]
                int j = 0; // index for pat[]
                int read_Char =read(file,&tmp_char,1);
                if(read_Char<0) {
                        perror("");
                        exit(1);
                }
                i++;

                while (i < N) {
                        if (pat[j] == tmp_char) {
                                read(file,&tmp_char,1);
                                j++;
                                i++;
                        }

                        if (j == M) {
                                printf("##############################################\n" );
                                printf("\t-->Found in file -> %s\n",file_name);
                                printf("\t-->At index [%d] \n", (i - j));
                                j = lps[j - 1];
                        }
                        // mismatch after j matches
                        else if (i < N && pat[j] != tmp_char) {
                                // Do not match lps[0..lps[j-1]] characters,
                                // they will match anyway
                                if (j != 0)
                                        j = lps[j - 1];
                                else{
                                        read(file,&tmp_char,1);
                                        i++;
                                }
                        }
                }
                close(file);
        }
}//for the function

// Fills lps[] for given patttern pat[0..M-1]
void computeLPSArray(char* pat, int M, int* lps)
{
        // length of the previous longest prefix suffix
        int len = 0;
        lps[0] = 0; // lps[0] is always 0
        // the loop calculates lps[i] for i = 1 to M-1
        int i = 1;
        while (i < M) {
                if (pat[i] == pat[len]) {
                        len++;
                        lps[i] = len;
                        i++;
                }
                else if (len != 0) {
                        // len = lps[len - 1];
                        len = 0;//my code
                        // Also, note that we do not increment
                        // i here
                }
                else {        // if (len == 0)
                        lps[i]=0;
                        i++;
                }
        }
}

void CreteFiles(){
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
}
