#include <stdio.h>

int costMatrix[20][20], n; // matrix to store the cost of each node

struct routers{
    int distance[20]; // distance of each node from the source node
    int adjNodes[20]; // adjacent nodes of each node
}node[20];

void readCostMatrix(){
    int i,j;
    printf("Enter the cost matrix\n");
    for(i=0;i<n;++i){
        for (j=0;j<n;++j){
            scanf("%d",&costMatrix[i][j]);
            node[i].distance[j]=costMatrix[i][j];
            node[i].adjNodes[j]=j;
        }
        costMatrix[i][i]=0;
    }
}

void calcRoutingTable(){
    int i,j,k;
    for (i=0;i<n;++i){
        for(j=0;j<n;++j){
            for(k=0;k<n;++k){
                if (node[i].distance[j] > node[i].distance[k] + node[k].distance[j]){
                    node[i].distance[j] = node[i].distance[k] + node[k].distance[j];
                    node[i].adjNodes[j]=k;
                }
            }
        }
    }
}

void displayRoutes(){
    int i,j;
    for (i=0;i<n;i++){
        printf("Router %d\n",i+1);
        for (j=0;j<n;j++){
            printf("Node %d via %d : Distance %d\n",j+1,node[i].adjNodes[j]+1,node[i].distance[j]);
        }
        printf("\n");
    }
}

int main(){
    int i,j;
    printf("Number of nodes: ");
    scanf("%d",&n);
    readCostMatrix();
    calcRoutingTable();
    displayRoutes();

    return 0;
}