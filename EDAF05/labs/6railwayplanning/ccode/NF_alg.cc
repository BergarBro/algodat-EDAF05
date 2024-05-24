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

    int capacityLeft(int i){

        return maximumCapacity - i * currentCapacity;
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
    std::vector<std::pair<int, int>> backconnections;

    Node() = default;
    Node(int i) : index(i) {}

    void print(){
        cout << "Index: " << index;
        cout << "  Connections(Node,Edge): ";
        for(std::pair<int,int> p : connections){
            cout << "(" << p.first << "," << p.second << ") ";
        }
        cout << "  BackConnections(Node,Edge): ";
        for(std::pair<int,int> p : backconnections){
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

void print(std::vector<std::pair<int,int>> list){
    cout << "List of all Pairs to remove:" << endl;
    for(std::pair<int,int> p : list){
        cout << "IndexEdge: " << p.first;
        cout << " MaxCap: " << p.second << endl;
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
    std::vector<std::pair<int,int>> planToRemove(numToRemove);

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

        Edge newEdge(i, startNode, endNode, edgeMaxCapacity);               // making a new edge with all its peramiters              
        vecOfEdges[i] = newEdge;                                            //addin the edge to the list
        vecOfNodes[startNode].connections.push_back(std::pair<int,int>(endNode,i));   // adding the edge to theier coresponding nodes 
        vecOfNodes[endNode].backconnections.push_back(std::pair<int,int>(startNode,i));     // adding the edge to theier coresponding nodes 
    }

    for(int i = 0; i < numToRemove; i++){
        int indexToRemove;
        cin >> indexToRemove;
        int edgeCap = vecOfEdges[indexToRemove].maximumCapacity;
        planToRemove[i] = std::pair<int,int> (indexToRemove,edgeCap);                        // geting all the egeds and theier order of removal
        vecOfEdges[indexToRemove].maximumCapacity = 0;
    }

    // print(vecOfEdges);
    // print(vecOfNodes);

    //Start of Ford-Fulkerson Alg.

    bool done = false;
    int currentNetworkFlow = 0;
    int bestNetworkFlow = 0;
    int totalEdgesRemoves = 0;
    int numLeftToAdd = numToRemove;

    while(!done){
        

        std::vector<std::pair<std::pair<int,int>,int>> path(numOfNodes);            //vector of pair(pair(Node,Edge),front/back) (front = 1, back = -1)
        //BFS function
        
        std::vector<bool> explored(numOfNodes, false);
        std::queue<int> que;

        bool pathFound = false;

        explored[0] = true;
        que.push(0);
        
        while(!que.empty()){
            int currentNode = que.front();
            que.pop();
            if(currentNode == numOfNodes - 1){      //checking if we have found the "end" of the graph
                pathFound = true;
                break;
            }
            bool foundFrontEdge = false;
            for(std::pair<int,int> nodeEdgePair : vecOfNodes[currentNode].connections){                     //Going through the front-edges 
                if(vecOfEdges[nodeEdgePair.second].capacityLeft(1) != 0){     //Checking if edge capacity is maxed in the front-direction
                    int tempNode = nodeEdgePair.first;
                    if(!explored[tempNode]){                        //checking if the node has been explored yet.
                        explored[tempNode] = true;
                        std::pair<int,int> tempPair = std::pair<int,int>(currentNode, nodeEdgePair.second);
                        path[tempNode] = std::pair<std::pair<int,int>,int>(tempPair,1);     //if the edge has capacity and the node is not exlored, it gets added to the current path
                        que.push(tempNode);                                                 // the new node gets added to the que to get checked
                        foundFrontEdge = true;
                    }
                }
            }
            if(!foundFrontEdge){                                                                                 //Going through the backwards-edges 
                for(std::pair<int,int> nodeEdgePair : vecOfNodes[currentNode].backconnections){
                    if(vecOfEdges[nodeEdgePair.second].capacityLeft(-1) != 0){ //Checking if edge capacity is maxed in the backward-direction
                        int tempNode = nodeEdgePair.first;
                        if(!explored[tempNode]){
                            explored[tempNode] = true;
                            std::pair<int,int> tempPair = std::pair<int,int>(currentNode, nodeEdgePair.second);
                            path[tempNode] = std::pair<std::pair<int,int>,int>(tempPair,-1);
                            que.push(tempNode);
                        }
                    }
                }
            }
        }

        int maxCap = std::numeric_limits<int>::max();
        std::vector<std::pair<int,int>> pathEdges;                       //vector of pair(Edges,front/back-edges) (front = 1, back = -1)
        if(pathFound){
            int currentNode = numOfNodes - 1;
            while(currentNode != 0){                                            //going through path to find the maximum capacity wa can increas the flow with
                int currentEdge = path[currentNode].first.second;
                int edgeDirection = path[currentNode].second;
                pathEdges.push_back(std::pair<int,int>(currentEdge,edgeDirection));
                if(maxCap > vecOfEdges[currentEdge].capacityLeft(edgeDirection)){
                    maxCap = vecOfEdges[currentEdge].capacityLeft(edgeDirection);
                }
                currentNode = path[currentNode].first.first;
            }
            for(std::pair<int,int> p : pathEdges){                           // going back to all the edges and setting their new currentcapacity
                vecOfEdges[p.first].currentCapacity += p.second * maxCap;       // if it is a backwardedge, we subcract the maxcapacity
            }
        }else{
            currentNetworkFlow = currentNetFlow(vecOfNodes, vecOfEdges);
            if(currentNetworkFlow >= goalCapacity){
                bestNetworkFlow = currentNetworkFlow;
                break;
            }else{
                int edgeToAdd = planToRemove[numLeftToAdd - 1].first;
                vecOfEdges[edgeToAdd].maximumCapacity = planToRemove[numLeftToAdd - 1].second;
                //cout << "hej " << planToRemove[numLeftToAdd - 1].second << endl;
                numLeftToAdd--;
            }
        }

        
        

        

        
        // cout << currentNetworkFlow << endl;
        // if(currentNetworkFlow >= goalCapacity){                      //checking if, after removing an edge, the currentflow is still more then the goalCapacity
        //     bestNetworkFlow = currentNetworkFlow;

        //     bool check = true;
        //     while(check){                               // a while loop to go through more then one edge in the plan
        //         int edgeToBeRemoved = planToRemove[totalEdgesRemoves++];
        //         vecOfEdges[edgeToBeRemoved].maximumCapacity = 0;
        //         if(vecOfEdges[edgeToBeRemoved].currentCapacity != 0){       // if the edge hade capacuity 0 it was not used, so we dont have to run the alg again, just remove another edge
        //             check = false;
        //             resetFlow(vecOfEdges);
        //             // for(std::pair<int,int> p : pathEdges){                           // going back to all the edges and setting their new currentcapacity
        //             //     vecOfEdges[p.first].currentCapacity -= p.second * maxCap;       // if it is a backwardedge, we subcract the maxcapacity
        //             // }
        //         }
        //     }
        // }

        // if(!pathFound){ 
        //     currentNetworkFlow = currentNetFlow(vecOfNodes, vecOfEdges);
        //     if(!(currentNetworkFlow >= goalCapacity)){                      //checking if, after removing an edge, the currentflow is still more then the goalCapacity
        //         break;
        //     }
        //     bestNetworkFlow = currentNetworkFlow;

        //     bool check = true;
        //     while(check){                               // a while loop to go through more then one edge in the plan
        //         int edgeToBeRemoved = planToRemove[totalEdgesRemoves++];
        //         vecOfEdges[edgeToBeRemoved].maximumCapacity = 0;
        //         if(vecOfEdges[edgeToBeRemoved].currentCapacity != 0){       // if the edge hade capacuity 0 it was not used, so we dont have to run the alg again, just remove another edge
        //             check = false;
        //         }
        //     }
        //     resetFlow(vecOfEdges);                                          // When an edge with "value" to the system is removed, we need to restart the alg 
        // }else{
        //     // get max capacity over path
        
        //     int maxCap = std::numeric_limits<int>::max();
        //     std::vector<std::pair<int,int>> pathEdges;                       //vector of pair(Edges,front/back-edges) (front = 1, back = -1)
        //     int currentNode = numOfNodes - 1;
        //     while(currentNode != 0){                                            //going through path to find the maximum capacity wa can increas the flow with
        //         int currentEdge = path[currentNode].first.second;
        //         int edgeDirection = path[currentNode].second;
        //         pathEdges.push_back(std::pair<int,int>(currentEdge,edgeDirection));
        //         if(maxCap > vecOfEdges[currentEdge].capacityLeft(edgeDirection)){
        //             maxCap = vecOfEdges[currentEdge].capacityLeft(edgeDirection);
        //         }
        //         currentNode = path[currentNode].first.first;
        //     }

        //     for(std::pair<int,int> p : pathEdges){                           // going back to all the edges and setting their new currentcapacity
        //         vecOfEdges[p.first].currentCapacity += p.second * maxCap;       // if it is a backwardedge, we subcract the maxcapacity
        //     }
        // }

        // print(vecOfEdges);
        // print(planToRemove);
        // cout << numLeftToAdd << " curFlow:" << currentNetFlow(vecOfNodes, vecOfEdges) << " goal:" << goalCapacity << endl;

    }

    //print(vecOfEdges);

    cout << numLeftToAdd << " " << bestNetworkFlow << endl;

    return 0;
}

//massa mög här 