#include<stdio.h>
#include<string.h>

#define MAX 100

typedef struct{
    int val;
    char d;
} inp;

int lcs(char a[], char b[], int m, int n, inp cost[][MAX]){
    for(int i=0; i<=m; i++){
        for(int j=0; j<=n; j++){
            if(i==0 || j==0){
                cost[i][j].val=0;
                cost[i][j].d='H';
            }
        }
    }

    for(int i=1; i<=m; i++){
        for(int j=1; j<=n; j++){
            if(a[i-1] == b[j-1] && i != j){
                cost[i][j].val = cost[i-1][j-1].val + 1;
                cost[i][j].d = 'D';
            }
            else{
                if(cost[i-1][j].val > cost[i][j-1].val){
                    cost[i][j].val = cost[i-1][j].val;
                    cost[i][j].d = 'U';
                }
                else{
                    cost[i][j].val = cost[i][j-1].val;
                    cost[i][j].d = 'S';
                }
            }
        }
    }
    return cost[m][n].val;
}

void lcs_print(char a[], int i, int j, inp cost[][MAX]){
    if(i == 0 || j == 0)
        return;

    if(cost[i][j].d == 'D'){
        lcs_print(a, i-1, j-1, cost);
        printf("%c", a[i-1]);
    }
    else if(cost[i][j].d == 'U')
        lcs_print(a, i-1, j, cost);
    else
        lcs_print(a, i, j-1, cost);
}

int main(){
    char a[MAX];
    inp cost[MAX][MAX];

    printf("Enter the string: ");
    fgets(a, MAX, stdin);
    a[strcspn(a, "\n")] = 0;

    int m = strlen(a);

    int len = lcs(a, a, m, m, cost);

    printf("Cost Matrix\n");
    for(int i = 0; i <= m; i++){
        for(int j = 0; j <= m; j++){
            printf("\t%d%c", cost[i][j].val, cost[i][j].d);
        }
        printf("\n");
    }

    printf("\nLength of Longest Repeating Subsequence: %d\n", len);
    printf("Longest Repeating Subsequence: ");
    lcs_print(a, m, m, cost);
    printf("\n");

    return 0;
}