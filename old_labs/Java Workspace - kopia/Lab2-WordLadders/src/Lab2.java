import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Scanner;

public class Lab2 {
	
	public static int makeHash(String s) {		// makes a semi-unique index for any string O(1)
		int h = 7;
		for(int i = 0; i < s.length(); i++) {
			h = h*13 + s.charAt(i);
		}
		return h;
	}

	public static void main(String[] args) {
		
		Scanner scan = new Scanner(System.in);
		NodeCluster core;
		
		int N = scan.nextInt();								// Get amount of Nodes O(1)
		int Q = scan.nextInt();								// Get amount of paths O(1)
		core = new NodeCluster(N);							// Make a cluster      O(1)
			
		for(int i = 0; i < N; i++) {						// O(n^2)
			core.addNode(new Node(scan.next()));			// Record all nodes and put them in the cluster 
		}													// in addNode they also gets connected to corresponding node in the cluster
		
		for (int i = 0; i < Q; i++) {						//start Implementation of BFS
			Node start = core.findNode(scan.next());			// Scan in start   O(n)
			Node end = core.findNode(scan.next());				// Scan in end     O(n)
			
			for (Node n: core.getCluster()) {					// O(n)		
				n.setVisit(false);								// Reset visit boolean
				n.setNum(0);									// Reset number of steps to start
			}
			
			LinkedList<Node> que = new LinkedList<>();			// Creates the queue in which the unvisited nodes lie
			start.setVisit(true);								// Visit the start node
			que.offer(start);									// Put the start node in the queue
			boolean check = true;
			while (que.size() != 0) {
				Node curr = que.poll();							// Take out the first node in the queue
				if (curr.equals(end)) {							// Check if the current node is the end
					System.out.println(curr.getNum());			// Prints expected value aka how many steps it took
					check = false;
					break;	
				}
				for (Node list : curr.getList()) {				// Loop through every connected node
					if (!list.getVisit()) {						// Ignore already visited nodes
						list.setVisit(true);					// Set visit boolean to true
						list.setNum(curr.getNum() + 1);			// Records the steps to the current node + 1 correctly
						que.offer(list);						// adds connected nodes to the queue
					}
				}
			}
			if (check) {
				System.out.println("Impossible");				// If queue is empty and the end was not found print Imp.
			}
		}													//end
		scan.close();
	}

}

class NodeCluster {
	private Node[] allWords;				// All nodes in the cluster (graph)
	private int amount;						// Number of current Nodes in the cluster 
	
	public NodeCluster(int n) {
		allWords = new Node[n];
		amount = 0;
	}
	
	public Node[] getCluster() {
		return allWords;
	}
	
	public void addNode(Node nN) {			// This method adds the node and connects the node to is corresponding nodes in the cluster 
		if (amount != 0) {
			for (int i = 0; i < amount; i++) {
				Node oN = allWords[i];
				if (oN.check(nN)) {
					oN.addConnection(nN);
				}
				if (nN.check(oN)) {
					nN.addConnection(oN);
				}
			}		
		}
		allWords[amount] = nN;
		amount++;
	}
	
	public Node findNode(String s) {		// Using equals method to find the node with the string s
//		int hash = Lab2.makeHash(s);
		for (Node n : allWords) { 
			if (n.equals(s)) {
				return n;
			}
		}
		return null;
	}
}

class Node {
	private ArrayList<Node> list;
	private char[] word = new char[5];
	private int hash;						//"Unique" identifier 
	private boolean visit;					//If it has been visited or not
	private int num;						//Number of steps from start to this node
	
	public Node(String s) {
		list = new ArrayList<>();
		for(int i = 0; i < 5; i++) {
			word[i] = s.charAt(i);
		}
		hash = Lab2.makeHash(s);
		visit = false;
		num = 0;
	}
	
	public void addConnection(Node n) {
		list.add(n);
	}
	
	public int getHash() {
		return hash;
	}
	
	public int getSize() {
		return list.size();
	}
	
	public void setVisit(boolean b) {
		visit = b;
	}
	
	public boolean getVisit() {
		return visit;
	}
	
	public void setNum(int n) {
		num = n;
	}
	
	public int getNum() {
		return num;
	}
	
	public char[] getWord() {
		return word;
	}
	
	public ArrayList<Node> getList() {
		return list;
	}
	
	public boolean equals(String s) {
		for(int i = 0; i < 5; i++) {
			if (this.word[i] != s.charAt(i)) {
				return false;
			}
		}
		return true;
	}
	
	public boolean check(Node n) {
		ArrayList<Integer> temp = new ArrayList<>();
		for(int i = 1; i < 5; i++) {
			char c = this.word[i];
			for (int j = 0; j < 5; j++) {
				if (n.word[j] == c && !temp.contains(j)) {
					temp.add(j);
					break;
				}
			}
			if (temp.size() != i) {
				return false;
			}
			
		}
		return true;
	}
}