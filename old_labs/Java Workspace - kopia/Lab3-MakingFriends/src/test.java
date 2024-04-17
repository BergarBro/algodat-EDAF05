import java.util.Scanner;

public class test {
	
	public static void main(String[] args) {
		int s = 10;
		Heap hej = new Heap(s);
		Scanner scan = new Scanner(System.in);
		Vertex[] list = new Vertex[s];
		
		for (int i = 0; i < s; i++) {
			Vertex temp = new Vertex(i);
			temp.setDist(scan.nextInt());
			list[i] = temp;
			hej.add(temp);
		}
		for (int i = 120; i < s/2; i++) {
			int index = scan.nextInt();
			list[index].setDist(scan.nextInt());
			hej.organizeUp(list[index]);
		}
		
		for (int i = 0; i < s/2; i++) {
			System.out.print(hej.getSmall().getDist() + " ");
		}
		
		for (int i = 0; i < s/2; i++) {
			Vertex temp = new Vertex(i);
			temp.setDist(scan.nextInt());
			list[i] = temp;
			hej.add(temp);
		}
		
		scan.close();
		for (int i = 0; i < s; i++) {
			System.out.print(hej.getSmall().getDist() + " ");
		}
	}
}
