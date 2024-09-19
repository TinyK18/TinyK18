#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct note{
    int x,y;
    char d,s[50];
};//structure to store the unavaliable word
struct cooridiate{
    int xx,yy;
    char h,v;
};//structure to store input values
int main() {
    // insert code here...
    int n,w,count=0,F;//count: the number of the not eligible word
    //n:the size of matrix;w:the number of the lines entered(problem1)
    //F:the number of the lines(problem3)
    scanf("%d\n%d",&n,&w);
    char board[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            board[i][j]='.';
        }
    }
    //problem1 and 2
    struct note arr[w];//arr:store unavaliable word
    for(int i=0;i<w;i++){
        int X=0,Y=0,num=0,k=0,value=0,check=0;/*X and Y are the coordinates in the two-dimensional array;num:the length of the input word
            k:show the number of digits in the input word
            value:indicates whether the word is eligible,0 is eligible,1 is not eligible
            check:find if there are the same letters
        */
        char D,S[50];//D:indicates horizontal or vertical;S :store word
        scanf("%d %d %c %49s",&X,&Y,&D,S);
        num=(int)strlen(S);
        if(i==0){check=1;}
        if(D=='H'){
            if((n-X)<num){
                value=1;
            }
            else{
                for(int j=X,k1=0;k1<num;j++,k1++){
                    if(board[Y][j]=='.'){
                        continue;}
                    else if(board[Y][j]==S[k1]){
                        check=1;}
                }
                if(check==1){
                    for(int j=X;k<num;j++){
                        board[Y][j]=S[k];
                        k++;}
                }
                else{value=1;}
            }
        }
        if(D=='V'){
            if((n-Y)<num){
                value=1;
            }
            else{
                for(int j=Y,k1=0;k1<num;j++,k1++){
                    if(board[j][Y]=='.'){
                        continue;}
                    else if (board[j][X]==S[k1]){
                        check=1;}
                }
                if(check==1){
                    for(int j=Y;k<num;j++){
                        board[j][X]=S[k];
                        k++;}
                }
                else{value=1;}
            }
        }
        if(value==1){
            arr[count].x=X;
            arr[count].y=Y;
            arr[count].d=D;
            for(int m=0;m<num;m++){
                arr[count].s[m]=S[m];
		if(m==num-1){arr[count].s[m+1]='\0';}
	    }
            count++;
        }
    }
    //problem3,search avaliable position
    scanf("%d",&F);
    struct cooridiate array[(n*n)];//store matching values
    int count1=0;//indicate the number of calculated values
    for(int i=0;i<F;i++){
        int B,A;//dedignated space
        char L;//locked letters
        scanf("%d %c %d",&B,&L,&A);
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){//to find the position of the letter
                if(board[j][k]==L){
                    //check horizontal orientation
		    if((k-B>=0)&&(k+A<n)){
                    for(int p=(k-B);p<=(k+A);p++){
                        if((board[j][p]!='.')&&(p!=k)){
                            break;
                        }
                        if(p==k+A){
                            array[count1].xx=k;
                            array[count1].yy=j;
                            array[count1].h='t';
                            count1++;
                        }
                    }
		    }
                    //check vertical orientation
		    if((j-B>=0)&&(j+A<n)){
                    for(int p=(j-B);p<=(j+A);p++){
                        if((board[p][k]!='.')&&(p!=j)){
                            break;
                        }
                        if(p==(j+A)){
                            array[count1].v='t';
                            if(array[count1].h!='t'){
                                array[count1].xx=k;
                                array[count1].yy=j;
                                count1++;
                            }
                        }
                    }
		    }
                }
            }
        }
    }
        for(int i=0;i<count;i++){
            printf("Invalid word placement:(%d,%d) %c, %s\n",arr[i].x,arr[i].y,arr[i].d,arr[i].s);
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                printf("%c",board[i][j]);
            }
            printf("\n");
        }
    for(int i=0;i<count1;i++){
        if(array[i].h=='t'){
            printf("Place horizontally at (%d,%d)\n",array[i].xx,array[i].yy);}
        if(array[i].v=='t'){
            printf("Place vertically at (%d,%d)\n",array[i].xx,array[i].yy);}
    }
        return 0;
    }
