import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Scanner;

public class Lab4 {

	public static void main(String[] args) {
		
		Scanner scan = new Scanner(System.in);
		
		int N = scan.nextInt();
		ArrayList<Point> Px = new ArrayList<Point>(N);
		ArrayList<Point> Py = new ArrayList<Point>(N);
		for(int i = 0; i < N; i++) {
			Point temp = new Point(scan.nextInt(),scan.nextInt());
			Px.add(temp);
			Py.add(temp);
		}
		scan.close();
		
		double ans = closestPoint(Px,Py,N);
		
		//System.out.println(ans);
		
		DecimalFormat df = new DecimalFormat("###.000000");
		
		System.out.println(df.format(ans));
	}
	
	public static double closestPoint(ArrayList<Point> Px, ArrayList<Point> Py, int N) {
		Px.sort((p1,p2) -> {
			int ans = p1.getX()-p2.getX();
			if (ans == 0) {
				return p1.getY()-p2.getY();
			}else {
				return ans;
			}			 
		});
		
		Py.sort((p1,p2) -> {
			int ans = p1.getY()-p2.getY();
			if (ans == 0) {
				return p1.getX()-p2.getX();
			}else {
				return ans;
			}
		});
		
		Point[] APx = new Point[N];
		Point[] APy = new Point[N];
		
		for (int i = 0; i < N; i++) {
			APx[i] = Px.get(i);
			APy[i] = Py.get(i);
		}
		
		return rabbitHole(APx,APy,N);
	}
	
	public static double rabbitHole(Point[] Px, Point[] Py, int N) {
		if (N == 2) {
			return dist(Px[0],Px[1]); 
		} else if (N == 3) {
			double d1 = Math.min(dist(Px[0],Px[1]),dist(Px[0],Px[2]));
			double delta = Math.min(dist(Px[1],Px[2]),d1);
			return delta;
		} else {
			
			int half = Math.floorDiv(N + 1, 2);
			Point[] Lx = new Point[half];
			Point[] Rx = new Point[N-half];
			Point[] Ly = new Point[half];
			Point[] Ry = new Point[N-half];
			int l = 0;
			int r = 0;
			boolean check = false;
			for (int i = 0; i < N; i++) {
				if (check || i == half) {
					Rx[r] = Px[i];
					r++;
					check = true;
				}else {
					Lx[l] = Px[i];
					l++;
				}
			}
		
			int midx = Lx[half-1].getX();
			int midy = Lx[half-1].getY();
		
			l = 0;
			r = 0;
			for (int i = 0; i < N; i++) {
				if (Py[i].getX() < midx) {
					Ly[l] = Py[i];
					l++;
				}else if (Py[i].getX() == midx && Py[i].getY() <= midy) {
					Ly[l] = Py[i];
					l++;			
				}else {
					Ry[r] = Py[i];
					r++;
				}
			}
		
			double delta = Math.min(rabbitHole(Lx,Ly,half),rabbitHole(Rx,Ry,N-half));
			
			ArrayList<Point> Sy = new ArrayList<>();
			for (Point p : Py) {
				if (Math.abs(p.getX()-midx) < delta) {
					Sy.add(p);
				}
			}
			
			int stor = Sy.size();
			for (int i = 0; i < stor; i++) {
				for (int j = i + 1; j < i + 11; j++) {
					if (j < stor) {
						delta = Math.min(dist(Sy.get(i),Sy.get(j)),delta);						
					} else {
						break;
					}
				}
			}
			
			return delta;
		}
	}
	
	
	public static double dist(Point p1, Point p2) {
		double dis = Math.sqrt(Math.pow((p1.getX()-p2.getX()),2) + Math.pow((p1.getY()-p2.getY()),2));
		return dis;
	}
}

class Point {
	private int x;
	private int y;
	
	public Point(int a, int b) {
		x = a;
		y = b;
	}
	
	public int getX() {
		return x;
	}
	
	public int getY() {
		return y;
	}
	
	public String toString() {
		return x + " " + y;
	}
}