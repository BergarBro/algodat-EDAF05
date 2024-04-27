#include<iostream>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(){

    int numOfNodes;
    int numOfEdges;
    int capacity;
    int numToRemove;

    cin >> numOfNodes;
    cin >> numOfEdges;
    cin >> capacity;
    cin >> numToRemove;

    std::vector<std::vector<int>> capacityMatrix(numOfNodes,std::vector<int>(numOfNodes, -1));
    std::vector<std::pair<int,int>> plan(numOfEdges);
    std::vector<int> planToRemove(numToRemove);

    for(int i = 0; i < numOfEdges; i++){
        int startNode;
        int endNode;
        int edgeCapacity;

        cin >> startNode;
        cin >> endNode;
        cin >> edgeCapacity;

        capacityMatrix[startNode][endNode] = edgeCapacity;
        capacityMatrix[endNode][startNode] = edgeCapacity;
        plan[i] = std::pair<int,int>(startNode,endNode);
    }

    for(int i = 0; i < numToRemove; i++){
        int indexToRemove;
        planToRemove[i] = indexToRemove;
    }



    return 0;
}