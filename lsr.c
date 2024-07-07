#include <stdio.h>

void main(){
    int n,i,j,k,source,min;
    printf("Enter the number of routers: ");
    scanf("%d",&n);
    int costmatrix[n][n],flag[n],last[n],dist[n];
    printf("Enter the cost matrix:\n");
    for (i=0;i<n;i++){
        for (j=0;j<n;j++){
            scanf("%d",&costmatrix[i][j]);
        }
    }
    printf("Enter the source router: ");
    scanf("%d",&source);
    for (i=0;i<n;i++){
        flag[i]=0;
        last[i]=source;
        dist[i]=costmatrix[source][i];
    }
    flag[source]=1;
    for (i=0;i<n;i++){
        min = 1000;
        for (j=0;j<n;j++){
            if (!flag[j]){
                if(dist[j]<min){
                    k=j;
                    min = dist[j];
                }
            }
        }
        flag[k]=1;
        for(j=0;j<n;j++){
            if(!flag[j]){
                if(min+costmatrix[k][j]<dist[j]){
                    dist[j]=min+costmatrix[k][j];
                    last[j]=k;
                }
            }
        }
    }
    for(i=0;i<n;i++){
        printf("%d==>%d:Path taken:%d",source,i,i);
        j=i;
        while(j!=source){
            printf("<--%d",last[j]);
            j=last[j];
        }
        printf("\nShortest Distance : %d\n",dist[i]);
    }
    
}