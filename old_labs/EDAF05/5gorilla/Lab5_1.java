import java.util.Scanner;

public class Lab5_1 {

	public static void main(String[] args) {
		
		Scanner scan = new Scanner(System.in);
		String alph = scan.nextLine();
		alph = alph.replaceAll(" ","");
		int c = alph.length();

		int[][] align = new int[c][c];
		int row = 0;
		int col = 0;
		while(row*col < Math.pow((c-1), 2)) {
			align[row][col] = scan.nextInt();
			if (col == c-1) {
				row++;
				col = 0;
			}else {
				col++;
			}
		}
		align[row][col] = scan.nextInt();
		
		int N = scan.nextInt();
		scan.nextLine();
		for (int i = 0; i < N; i++) {
			String query = scan.nextLine();
			int size = query.length();
			int place = query.indexOf(" ");
			String word1 = query.substring(0, place);
			String word2 = query.substring(place + 1, size);
			
			
			String outPut = DP(align, alph, word1, word2);
			
			System.out.println(outPut);
						
		}
		
		scan.close();
	}
	
	public static String DP(int[][] align, String alph, String word1, String word2) {
		int N = word1.length();
		int M = word2.length();
		wClass word = new wClass(0, 0);
		wClass[][] ans = new wClass[N+1][M+1];
		
		wClass temp = vortex(align, alph, ans, N, M, word, word1, word2);
		
		return myToString(word1, word2, ans, N, M);
	}
	
	public static wClass vortex(int[][] align, String alph, wClass[][] ans, int i, int j, wClass word, String word1, String word2) {
		if (ans[i][j] == null) {
			wClass w1 = null;
			wClass w2 = null;
			wClass w3 = null;
			int c1 = 0;
			int c2 = 0;
			if (i != 0 && j != 0) {
				int cost = align[alph.indexOf(word1.charAt(i-1))][alph.indexOf(word2.charAt(j-1))];
				w3 = vortex(align, alph, ans,i-1,j-1,word, word1, word2);
				w3 = new wClass(3, cost + w3.getW());			
			} else if (i == 0 && j == 0) {
				ans[i][j] = word;
				return word;
			}
			if (i != 0) {
				w1 = vortex(align, alph, ans,i-1,j,word, word1, word2);
				w1 = new wClass(1, -4 + w1.getW());				
				c1 = 1;
			} else {
				w1 = new wClass(word);
				for (int k = 0; k < j; k++) {
					w1 = new wClass(2, -4 + w1.getW());
				
					ans[i][k+1] = w1;
				}
				
				return ans[i][j];
			}
			if (j != 0) {
				w2 = vortex(align, alph, ans,i,j-1,word, word1, word2);
				w2 = new wClass(2, -4 + w2.getW());				
				c2 = 1;
			} else {
				w2 = new wClass(word);
				for (int k = 0; k < i; k++) {
					w2 = new wClass(1, -4 + w2.getW());
				
					ans[k+1][j] = w2;
				}
				return ans[i][j];
			}
			
			if (c1 == 1 && c2 != 1) {
				ans[i][j] = w1;
				return w1;
			} else if (c2 == 1 && c1 != 1) {
				ans[i][j] = w2;
				return w2;
			} else if (c1 != 1 && c2 != 1){
				ans[i][j] = word;
				return word;
			}else {
				wClass temp1 = myCompare(w1,w2);
				wClass temp2 = myCompare(temp1,w3);
				ans[i][j] = temp2;
				return temp2;
			}					
		}else {
			wClass temp = ans[i][j];
			wClass newword = new wClass(temp);
			return newword;
		}
	}
	
	public static wClass myCompare(wClass w1, wClass w2) {
		if (w1.getW() > w2.getW()) {
			return w1;
		} else {
			return w2;
		}
	}
	public static String myToString(String w1, String w2, wClass[][] ans, int N, int M) {
		String f = "";
		String l = "";
		while (N != 0 || M != 0) {
			if (ans[N][M].getDir() == 1) {
				f = w1.charAt(N-1) + f;
				l = "*" + l;
				N--;
			} else if (ans[N][M].getDir() == 2) {
				f = "*" + f;
				l = w2.charAt(M-1) + l;
				M--;
			} else {
				f = w1.charAt(N-1) + f;
				l = w2.charAt(M-1) + l;
				N--;
				M--;
			}
		}
				
		return f + " " + l;
	}
}

class wClass{
	private int dir;
	private int w;

	
	public wClass(int d, int weight) {
		dir = d;
		w = weight;
	}
	
	public wClass(wClass old) {
		this.dir = old.dir;
		this.w = old.w;
	}
	
	public void serDir(int d) {
		dir = d;
	}
		
	public int getDir() {
		return dir;
	}
	
	public int getW() {
		return w;
	}
	
	public void setW(int wcurr) {
		w += wcurr;
	}
}
