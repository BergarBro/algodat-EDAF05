#include<iostream>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;

struct Edge{
    int index;
    Node& nodeOne;              // nodeOne is the node with the lower index
    Node& nodeTwo;
    int currentCapacity;        // positiv capacity refers to flow from nodeOne to nodeTwo, negativ is opposite
    int maximumCapacity;        // |currentCapacity| <= maximumCapacity

    Edge(int i, Node& one, Node& two, int cap) : index(i), nodeOne(one), nodeTwo(two), currentCapacity(0), maximumCapacity(cap) {};

    //int Edge::operator=(const Edge& newEdge){ *this = newEdge;};
};

struct Node{
    int index;
    std::vector<Edge&> connections;

    Node(int i) : index(i) {};
};

int main(){

    int numOfNodes;
    int numOfEdges;
    int goalCapacity;
    int numToRemove;

    cin >> numOfNodes;
    cin >> numOfEdges;
    cin >> goalCapacity;
    cin >> numToRemove;

    std::vector<Node> vecOfNodes(numOfNodes);
    std::vector<Edge> vecOfEdges(numOfEdges);
    std::vector<int> planToRemove(numToRemove);

    for(int i = 0; i < numOfNodes; i++){ vecOfNodes[i].index = i;}      // sets the index of all nodes, maybe not necassery.

    for(int i = 0; i < numOfEdges; i++){
        int startNode;
        int endNode;
        int edgeCapacity;

        cin >> startNode;
        cin >> endNode;
        cin >> edgeCapacity;

        if(startNode > endNode){        // If the nodes are in the "wrong" order
            int temp = startNode;
            startNode = endNode;
            endNode = temp;
        }

        Edge& newEdge = vecOfEdges[i];                          // setting the index of the edge
        newEdge.nodeOne = vecOfNodes[startNode];                // setting the first node of the edge
        newEdge.nodeTwo = vecOfNodes[endNode];                  // setting the second node of the edge
        newEdge.maximumCapacity = edgeCapacity;                 // setting the maxcapacity of the edge
        vecOfNodes[startNode].connections.push_back(newEdge);   // adding the edge to theier coresponding nodes 
        vecOfNodes[endNode].connections.push_back(newEdge);     // adding the edge to theier coresponding nodes 
    }

    for(int i = 0; i < numToRemove; i++){
        int indexToRemove;
        cin >> indexToRemove;
        planToRemove[i] = indexToRemove;                        // geting all the egeds and theier order of removal
    }



    return 0;
}