#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct item{
    unsigned char C;
    unsigned int L;
    int *E;
};/*C means character,L means the length of the encoding bit,
   E is a array to store the encoding*/
int main(int argc, const char * argv[]) {
    // insert code here...
    unsigned int T;
    int t;
    scanf("%x",&T);
    t=T;
    if(T==0){
        t=256;
    }/*T is hexadecimal number,means the line of input*/
    struct item items[t];/*array to place table*/
    for(int i=0;i<t;i++){
        unsigned char byte0,byte1,byte2;
        scanf("%hhx %hhx %hhx",&byte0,&byte1,&byte2);
        items[i].C=byte0;
        items[i].L=byte1>>4;
        items[i].E=malloc(items[i].L*sizeof(int));
        int byte=byte1<<4;
        byte=(byte<<4)|byte2;/*add two btyes content*/
        for(int j=0;j<items[i].L;j++){
            items[i].E[j]=(byte>>(11-j))&1;
        }
    }
    unsigned char byte[4];/*to store the input*/
    unsigned int N=0;/*store entered data*/
    for(int i=0;i<4;i++){
        scanf("%hhx",&byte[i]);
        N=N|byte[i];
        if(i<3){
            N=N<<8;}
    }
    if(N==0){
        for(int i=0;i<t;i++){
            printf("0x%.2x : %d ",items[i].C,items[i].L);
            for(int j=0;j<items[i].L;j++){
                printf("%d",items[i].E[j]);
            }
            printf("\n");
        }
    }
    else{
        int number=0;/*count the number of letters found*/
        unsigned int D=0;/*store the current bitstream*/
        int length=0;/*caculate the current bitstream lenght*/
        while (number<N) {
            unsigned char bytes;/*the entered byte*/
            scanf("%hhx",&bytes);
            for(int i=0;i<8;i++){
                D=D<<1;
                D=D|((bytes>>(7-i))&1);
                length++;
                for(int j=0;j<t;j++){
                    unsigned int Encodeing=0;
                    for(int k=0;k<items[j].L;k++){
                        Encodeing=Encodeing<<1;
                        Encodeing=Encodeing|items[j].E[k];
                    }
                    if((length==items[j].L)&&D==Encodeing){
                        printf("%c",items[j].C);
                        length=0;
                        D=0;
                        number++;
                        break;
                    }
                }
                if(length==12||number==N){
                    if(length==12){
                        D=0;
                        length=0;
                    }
                    break;
                }
            }
        }
    }
    return 0;
}

