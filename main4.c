#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int main(int argc, char  *argv[]) {

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
        off_t seek=lseek(f,5,SEEK_SET);
        read(f,&ch,1);
        printf("seek =%d\n",(int)seek );
        printf("char =%c\n",ch );
        seek=lseek(f,-3,SEEK_CUR);
        read(f,&ch,1);
        printf("seek =%d\n",(int)seek );
        printf("char =%c\n",ch );













        return 0;
}
