#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    int guess[3];
    int wrong;
    int right;
    int misplaced;
} Attempt;

// how many of each color : red / green / blue ......

int score_candidate( int code[3] , int guess[3] , int *right, int *misplaced, int *wrong) {
    
    int usedC[3] = {0}, usedG[3] = {0};
    
    int r = 0, m = 0;

    // count greens : 

    for(int i=0;i<3;i++){
        if(code[i]==guess[i]){
            r++;
            usedC[i]=usedG[i]=1;
        }
    }

    // count blues :

    for(int i=0; i<3 ; i++){
        if(!usedG[i]){
            for( int j=0 ; j <3 ;j++ ){
                if( !usedC[j] && guess[i]==code[j]){
                    m++;
                    usedC[j]=1;
                    usedG[i]=1;
                    break;
                }
            }
        }
    }

    *right = r;
    *misplaced = m;
    *wrong = 3 - r - m;
    return 1;
}

int next_int() {
    int c;

    // separation des entiers ..
    do {
        c = getchar();
    
    } while(!isdigit(c));

    int value = 0;
    while(isdigit(c)) {
        value = value * 10 + (c - '0');
        c = getchar();
    }

    return value;
}


int main(){
    
  
        printf(" your input :\n");
        Attempt A[50];
        int count=0;
        char ch;

        while((ch=getchar()) != '}'){
            if(ch=='['){
                // in order : r / g / b ...
                A[count].wrong     = next_int();  // r
                A[count].right     = next_int();  // g 
                A[count].misplaced = next_int();  // b

                // Skip until next '[' or '}'
                while((ch=getchar())!='[' && ch!='}') if(ch==EOF) break;
                if(ch=='}') break;

                // sepearation des entiers

                A[count].guess[0] = next_int();  // 1st 
                A[count].guess[1] = next_int();  // 2nd
                A[count].guess[2] = next_int();  // 3rd

                count++;
            }
        }

        

        int nb_sol=0;

        for( int d0=0 ; d0 <= 9 ; d0++){
            for(int d1=0 ; d1 <= 9 ; d1++){
                for(int d2=0 ;d2 <= 9 ; d2++){
                    int code[3]={d0,d1,d2};
                    
                    int valid=1;

                    for( int i=0; i < count; i++){
                        int r ,m,w ;
                        score_candidate(code ,A[i].guess, &r ,&m , &w );
                        if( r!=A[i].right || m!=A[i].misplaced || w!=A[i].wrong){
                            valid=0;
                            break;
                        }
                    }

                    if(valid)
                    {
                        printf("Answer is :[%d %d %d]\n", d0,d1,d2 );
                        
                    }
                }
            }
        }

    
    

return 0;
}
