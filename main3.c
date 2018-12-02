#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[])
{
        // void computeLPSArray(char* pat, int M, int* lps)
        // char txt[] = "ABABDABACDABABCABAB";
        char pat[] = "ABDCABDXA";
        // KMPSearch(pat,argv,argc);

        // length of the previous longest prefix suffix
        int len = 0;
        /////////////////////////////////الكود الاضافي
        int f=open("0",O_RDONLY);
        printf("file num =%d\n",f );
        int N=0;//num of char in the file
        char ch;
        read(f,&ch,1);//one read to check
        while (ch!=EOF) {
                N++;
                read(f,&ch,1);
        }
        printf("%d\n", N);
        int M = strlen(pat);
        printf("M= %d\n",M );//FOR TEST
        /////////////////////////////////
        int lps[M];
/////////////////////////////////

        lps[0] = 0; // lps[0] is always 0

        // the loop calculates lps[i] for i = 1 to M-1
        int i = 1;
        while (i < M) {
                if (pat[i] == pat[len]) {
                        len++;
                        lps[i] = len;
                        printf("-------------match--------------------------\n" );
                        printf("lps %d\n",lps[i] );
                        printf("len %d\n",len );
                        i++;
                }
                else if (len != 0) {
                        // len = lps[len - 1];//orignal code
                        len = 0;//my code

                        printf("-------------not match--------------------------\n" );
                        printf("lps %d\n",lps[i] );
                        printf("len %d\n",len );

                        // Also, note that we do not increment
                        // i here
                }
                else {        // if (len == 0)
                        lps[i]=0;
                        printf("-------------len =0--------------------------\n" );

                        printf("lps %d\n",lps[i]);
                        i++;
                        printf("len =%d\n",len );
                }
        }

        printf("-------=======+++++++++++++\n" );
        for (int i = 0; i < M; i++)
                printf("%d\n",lps[i]);
        printf("i=%d\n",i );

        return 0;
}
