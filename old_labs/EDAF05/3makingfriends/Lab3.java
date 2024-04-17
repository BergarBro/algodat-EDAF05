import java.util.ArrayList;
import java.util.Scanner;

public class Lab3 {

	public static void main(String args[]) {
		Scanner scan = new Scanner(System.in);
		
		int N = scan.nextInt();
		int M = scan.nextInt();
		Heap que = new Heap(N);
		
		Vertex[] list = new Vertex[N];
		for (int i = 0; i < N; i++) {
			list[i] = new Vertex(i);
		}
		
		for (int i = 0; i < M; i++ ) {										//nodes start from 0 to N-1
			int s = scan.nextInt() - 1;
			int e = scan.nextInt() - 1;
			int w = scan.nextInt();
			list[s].addEdge(new Edge(list[e],w));
			list[e].addEdge(new Edge(list[s],w));
		}
		scan.close();
		int sum = 0;
		int ant = 0;
		list[2].setDist(0);													// pick a random start node
		que.add(list[2]);													// put that node in the queue
		while (que.getSize() != 0 || ant == N - 1) {
			Vertex temp = que.getSmall();									// get the smallest node that is "near"
			sum += temp.getDist();											// add the distance to the sum
			ant++;															// count the amount of nodes in the tree
			temp.setStat(true);												// show the the node is in the tree
			for (Edge e : temp.getList()) {									// check the nodes neighbors
				if (!e.getPoint().getStat()) {								// not in the tree
					if (e.getPoint().getDist() == Integer.MAX_VALUE) {		// not looked at before 
						e.getPoint().setDist(e.getWeight());				// set the right weight
						que.add(e.getPoint());								// add to the queue
					} else if (e.getPoint().getDist() > e.getWeight()) {	// is the new way faster?
						e.getPoint().setDist(e.getWeight());				// change to the smallest weight
						que.organizeUp(e.getPoint());						// reorganize the tree
					}
				}
			}
			
		}
		System.out.println(sum);
	}	
}
class Edge {
	
	private Vertex pointer;						// Connection Points
	private int w;								// weight
	
	public Edge(Vertex p, int weight) {
		pointer = p;
		w = weight;
	}
	
	public int getWeight() {
		return w;
	}
	
	public Vertex getPoint() {
		return pointer;
	}
}

class Vertex {
	
	private int index;
	private ArrayList<Edge> list;
	private int dist;
	private boolean inTree;
	
	public Vertex(int i) {
		index = i;
		dist = Integer.MAX_VALUE;
		inTree = false;
		list = new ArrayList<>();
	}
	
	public int getIndex() {							// from 0 to N-1
		return index;
	}
	
	public int getDist() {
		return dist;
	}
	
	public void setDist(int d) {
		dist = d;
	}
	
	public void addEdge(Edge e) {
		list.add(e);
	}
	
	public void setStat(boolean c) {
		inTree = c;
	}
	
	public boolean getStat() {
		return inTree;
	}
	
	public ArrayList<Edge> getList() {
		return list;
	}
}

class Heap {
	
	private Vertex[] array;
	private int size;
	private int[] sort;
	
	public Heap(int s) {
		array = new Vertex[s];
		size = 0;
		sort = new int[s];
		for (int i = 0; i < s; i++) {
			sort[i] = -1;
		}
	}
	
	public int getSize() {
		return size;
	}
	
	public void add(Vertex e) {
		array[size] = e;
		sort[e.getIndex()] = size;
		organizeUp(size);
		size++;
	}
	
	public Vertex getSmall() {
		Vertex temp = array[0];
		sort[temp.getIndex()] = -2;
		size--;
		if (size == 0) {
			array[0] = null;
			return temp;
		} 
		array[0] = array[size];
		sort[array[size].getIndex()] = 0;
		array[size] = null;		
		organizeDown(0);
		return temp;
	}
	
	private void organizeUp(int index) {
		int i = index;
		while (array[i].getDist() < array[getParent(i)].getDist() && i != 0) {
			swap(i,getParent(i));
			i = getParent(i);
		}
	}
	
	public void organizeUp(Vertex v) {
		int i = sort[v.getIndex()];
		organizeUp(i);
	}
	
	private void organizeDown(int index) {
		int i = index;
		while (getLeft(i) < size) {
			int min = getLeft(i);
			int minW = array[min].getDist();
			if (getRight(i) < size) {
				if (minW > array[getRight(i)].getDist()) {
					min = getRight(i);
					minW = array[min].getDist();
				}				
			}
			if (minW < array[i].getDist()) {
				swap(i,min);
				i = min;
			} else {
				break;
			}
		}
	}
	
	private int getParent(int i) {
		return Math.max(Math.floorDiv((i-1), 2),0);
	}
	
	private int getLeft(int i) {
		return (i*2) + 1;
	}
	
	private int getRight(int i) {
		return (i*2) + 2;
	}
	
	private void swap(int i1, int i2) {									// Swap to nodes in the tree
		Vertex temp = array[i1];										// and fix "sort" accordingly 
		int tempI = sort[temp.getIndex()];
		array[i1] = array[i2];
		sort[array[i2].getIndex()] = tempI;	
		array[i2] = temp;
		sort[array[i2].getIndex()] = i2;
		
	}
}