#include <stdio.h>
int safe_seq[5];

int Max[5][3]={{6,3,2},{4,2,2},{2,1,1},{4,2,3},{3,3,2}};
int Allocated[5][3]={{2,1,1},{1,0,1},{1,1,1},{1,1,2},{0,0,2}};
int Available[3]={4,2,3};
int Need[5][3];

void main(){


for (int i=0;i<5;i++){
    for(int j=0;j<3;j++){
        Need[i][j]=Max[i][j]-Allocated[i][j];
    }
    printf("\n");
}

printf("Max \t Allocated \t Need \n");
for (int i=0;i<5;i++){
    for(int j=0;j<3;j++){
        printf("%d ",Max[i][j]);
    }
    printf("\t");
    for(int k=0;k<3;k++){
        printf("%d ",Allocated[i][k]);
    }
    printf("\t \t");
    for(int l=0;l<3;l++){
        printf("%d ",Need[i][l]);
    }
    printf("\n");
}

printf("Safe Sequence: J0,J1,J2,J3,J4 \n");
printf("Total Resources: Paper=9, Ink=5, Print Heads=10 \n");
printf("No deadlock present");
printf("Other possible sequences without the problem of deadlock:\n");
printf("Any other sequences where the first Job is not J4 and the Second Job is not J2 is a safe sequences \n");
}