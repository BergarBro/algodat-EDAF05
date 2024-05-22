#include<iostream>
#include<vector>
#include<queue>
#include<limits>


using std::cout;
using std::cin;
using std::endl;
using std::string;

struct Edge{
    int index;
    int nodeOne;              // nodeOne is the node with the lower index
    int nodeTwo;
    int currentCapacity;        // positiv capacity refers to flow from nodeOne to nodeTwo, negativ is opposite
    int maximumCapacity;        // |currentCapacity| <= maximumCapacity

    Edge() = default;
    Edge(int i, int one, int two, int cap) : index(i), nodeOne(one), nodeTwo(two), currentCapacity(0), maximumCapacity(cap) {};

    int capacityLeft(){
        return maximumCapacity-currentCapacity;
    }

    void print(){
        cout << "Index: " << index;
        cout << "  NodeOne: " << nodeOne;
        cout << "  NodeTwo: " << nodeTwo;
        cout << "  Flow: " << currentCapacity;
        cout << "  MaxFlow: " << maximumCapacity << endl;
    }

    //int Edge::operator=(const Edge& newEdge){ *this = newEdge;};
};

struct Node{
    int index;
    std::vector<std::pair<int, int>> connections;               // pair<"index of Node", "index of Edge">

    Node() = default;
    Node(int i) : index(i) {}

    void print(){
        cout << "Index: " << index;
        cout << "  Connections(Node,Edge): ";
        for(std::pair<int,int> p : connections){
            cout << "(" << p.first << "," << p.second << ") ";
        }
        cout << endl;
    }

    //std::vector<Edge> getEdges(){ return connections; }
};

void print(std::vector<Edge> list){
    cout << "List of all Edges:" << endl;
    for(Edge e : list){
        e.print();
    }
}

void print(std::vector<Node> list){
    cout << "List of all Nodes:" << endl;
    for(Node n : list){
        n.print();
    }
}

void resetFlow(std::vector<Edge>& list){
    for(Edge& e : list){
        e.currentCapacity = 0;
        //cout << "reseting flow!" << endl;
    }
}

int currentNetFlow(std::vector<Node>& listNode, std::vector<Edge>& listEdge){
    int temp = 0;
    for(std::pair<int,int>& edges : listNode[0].connections){
        temp += listEdge[edges.second].currentCapacity;
    }
    return temp;
}

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
    // std::vector<std::vector<int>> matrixOfCapacity(numOfNodes, std::vector<int>(numOfNodes, 0));
    // std::vector<std::vector<int>> matrixOfMaxCapacity(numOfNodes, std::vector<int>(numOfNodes, 0));

    for(int i = 0; i < numOfNodes; i++){ vecOfNodes[i].index = i;}      // sets the index of all nodes, maybe not necassery.

    for(int i = 0; i < numOfEdges; i++){
        int startNode;
        int endNode;
        int edgeMaxCapacity;

        cin >> startNode;
        cin >> endNode;
        cin >> edgeMaxCapacity;

        if(startNode > endNode){        // If the nodes are in the "wrong" order
            int temp = startNode;
            startNode = endNode;
            endNode = temp;
        }

        Edge newEdge(i, startNode, endNode, edgeMaxCapacity);                         
        // newEdge.index = i;                                      // setting the index of the edge
        // newEdge.nodeOne = startNode;                // setting the first node of the edge
        // newEdge.nodeTwo = endNode;                  // setting the second node of the edge
        // newEdge.maximumCapacity = edgeMaxCapacity;
        vecOfEdges[i] = newEdge;
        // matrixOfMaxCapacity[startNode][endNode] = edgeMaxCapacity;
        // matrixOfMaxCapacity[endNode][startNode] = edgeMaxCapacity;                 // setting the maxcapacity of the edge
        vecOfNodes[startNode].connections.push_back(std::pair<int,int>(endNode,i));   // adding the edge to theier coresponding nodes 
        vecOfNodes[endNode].connections.push_back(std::pair<int,int>(startNode,i));     // adding the edge to theier coresponding nodes 
    }

    for(int i = 0; i < numToRemove; i++){
        int indexToRemove;
        cin >> indexToRemove;
        planToRemove[i] = indexToRemove;                        // geting all the egeds and theier order of removal
    }

    // print(vecOfEdges);
    // print(vecOfNodes);

    //Start of Ford-Fulkerson Alg.

    bool done = false;
    int currentNetworkFlow = 0;
    int bestNetworkFlow = 0;
    int totalEdgesRemoves = 0;

    while(!done){
        

        std::vector<std::pair<int,int>> path(numOfNodes);
        //BFS function
        
        std::vector<bool> explored(numOfNodes, false);
        std::queue<int> que;

        bool pathFound = false;

        explored[0] = true;
        que.push(0);
        
        while(!que.empty()){
            int currentNode = que.front();
            que.pop();
            if(currentNode == numOfNodes - 1){
                pathFound = true;
                break;
            }
            for(std::pair<int,int> nodeEdgePair : vecOfNodes[currentNode].connections){
                if(vecOfEdges[nodeEdgePair.second].currentCapacity != vecOfEdges[nodeEdgePair.second].maximumCapacity){
                    int tempNode = nodeEdgePair.first;
                    if(!explored[tempNode]){
                        explored[tempNode] = true;
                        path[tempNode] = std::pair<int,int>(currentNode, nodeEdgePair.second);
                        que.push(tempNode);
                    }
                }
            }
        }
        if(!pathFound){// || currentNetFlow(vecOfNodes, vecOfEdges) >= goalCapacity){
            currentNetworkFlow = currentNetFlow(vecOfNodes, vecOfEdges);
            if(!(currentNetworkFlow >= goalCapacity)){
                break;
            }
            bestNetworkFlow = currentNetworkFlow;
            //vecOfEdges[planToRemove[totalEdgesRemoves++]].maximumCapacity = 0;
            bool check = true;
            while(check){
                int edgeToBeRemoved = planToRemove[totalEdgesRemoves++];
                vecOfEdges[edgeToBeRemoved].maximumCapacity = 0;
                if(vecOfEdges[edgeToBeRemoved].currentCapacity != 0){
                    check = false;
                }
            }
            resetFlow(vecOfEdges);
        }else{
            // get max capacity over path
        
            int maxCap = std::numeric_limits<int>::max();
            std::vector<int> currentEdges;
            int currentNode = numOfNodes - 1;
            while(currentNode != 0){
                currentEdges.push_back(path[currentNode].second);
                if(maxCap > vecOfEdges[path[currentNode].second].capacityLeft()){
                    maxCap = vecOfEdges[path[currentNode].second].capacityLeft();
                }
                currentNode = path[currentNode].first;
            }

            for(int edges : currentEdges){
                vecOfEdges[edges].currentCapacity += maxCap;
            }
        }

        //print(vecOfEdges);

        cout << totalEdgesRemoves-1 << " " << currentNetFlow(vecOfNodes, vecOfEdges) << endl;

    }

    //print(vecOfEdges);

    cout << totalEdgesRemoves-1 << " " << bestNetworkFlow << endl;

    return 0;
}