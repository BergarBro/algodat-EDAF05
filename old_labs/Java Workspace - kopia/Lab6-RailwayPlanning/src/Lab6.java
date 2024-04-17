import java.util.ArrayList;
import java.util.Scanner;

public class Lab6 {
	
	public static void main(String[] args) {
		
		Scanner scan = new Scanner(System.in);
		
		int N = scan.nextInt();
		int M = scan.nextInt();
		int C = scan.nextInt();
		int P = scan.nextInt();
		
		Node[] list = new Node[N];
		for (int i = 0; i < N; i++) {
			list[i] = new Node(i,M);
		}
		for (int i = 0; i < M; i++) {
			int t1 = scan.nextInt();
			int t2 = scan.nextInt();
			int w  = scan.nextInt();
			list[t1].addVert(new Vertex(w,list[t2]));
			list[t2].addVert(new Vertex(w,list[t1]));
		}
		int[] remove = new int[P];
		for (int i = 0; i < P; i++) {
			remove[i] = scan.nextInt();
		}
		scan.close();
		
		alg(N,M,C,P,list,remove);
	}
	
	public static void alg(int N, int M, int C, int P, Node[] list, int[] remove) {
		
		
		
		
		
	}
	
}

class Vertex{
	private int w;
	private Node dest;
	
	public Vertex(int weight, Node n) {
		w = weight;
		dest = n;
	}
	
	public Node getNode() {
		return dest;
	}
	
	public int getW() {
		return w;
	}
}

class Node {
	private int index;
	private ArrayList<Vertex> conection;
	
	public Node(int i, int n) {
		conection = new ArrayList<>(n);
		index = i;
	}
	
	public void addVert(Vertex v) {
		conection.add(v);
	}
	
	public ArrayList<Vertex> getCon() {
		return conection;
	}
}
