import java.util.Scanner;

public class Lab5 {

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
		wordClass word = new wordClass(word1, word2, "", "", 0, alph);
		wordClass[][] ans = new wordClass[N+1][M+1];
		
		wordClass temp = vortex(align, ans, N, M, word);
		
		return ans[N][M].toString();
	}
	
	public static wordClass vortex(int[][] align, wordClass[][] ans, int i, int j, wordClass word) {
		if (ans[i][j] == null) {
			wordClass w1 = null;
			wordClass w2 = null;
			wordClass w3 = null;
			int c1 = 0;
			int c2 = 0;
			if (i != 0 && j != 0) {
				int cost = align[word.getIndex(1, i)][word.getIndex(2, j)];
				w3 = vortex(align,ans,i-1,j-1,word);
				w3 = new wordClass(3, i, j, cost, w3);			
			} else if (i == 0 && j == 0) {
				ans[i][j] = word;
				return word;
			}
			if (i != 0) {
				w1 = vortex(align,ans,i-1,j,word);
				w1 = new wordClass(1, i, j, 0, w1);				
				c1 = 1;
			} else {
				w1 = new wordClass(word);
				for (int k = 0; k < j; k++) {
					w1 = new wordClass(2, i, j-k, 0, w1);
					ans[i][k+1] = w1;
				}
				
				return ans[i][j];
			}
			if (j != 0) {
				w2 = vortex(align,ans,i,j-1,word);
				w2 = new wordClass(2, i, j, 0, w2);				
				c2 = 1;
			} else {
				w2 = new wordClass(word);
				for (int k = 0; k < i; k++) {
					w2 = new wordClass(1, i-k, j, 0, w2);
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
				wordClass temp1 = myCompare(w1,w2);
				wordClass temp2 = myCompare(temp1,w3);
				ans[i][j] = temp2;
				return temp2;
			}					
		}else {
			wordClass temp = ans[i][j];
			wordClass newword = new wordClass(word);
			newword.setW(temp.getW());
			newword.setAns(1, temp.getAns(1));
			newword.setAns(2, temp.getAns(2));
			return newword;
		}
	}
	
	public static wordClass myCompare(wordClass w1, wordClass w2) {
		if (w1.getW() > w2.getW()) {
			return w1;
		} else {
			return w2;
		}
	}

}

class wordClass{
	private String word1;
	private String word2;
	private String ans1;
	private String ans2;
	private int w;
	private String alph;
	
	public wordClass(String ch1, String ch2, String stat1, String stat2, int wstat, String al) {
		word1 = ch1;
		word2 = ch2;
		ans1 = stat1;
		ans2 = stat2;
		w = wstat;
		alph = al;
	}
	
	public wordClass(int i, int j, int k, int wcurr, wordClass old) {
		this.word1 = old.word1;
		this.word2 = old.word2;
		this.alph = old.alph;
		if (i == 1) {
			this.ans2 = old.ans2 + '*'; 
			this.ans1 = old.ans1 + word1.charAt(j-1);
			this.w = old.w - 4;
		} else if(i == 2) {
			this.ans1 = old.ans1 + '*'; 
			this.ans2 = old.ans2 + word2.charAt(k-1);
			this.w = old.w - 4;
		} else {
			this.ans1 = old.ans1 + word1.charAt(j-1);
			this.ans2 = old.ans2 + word2.charAt(k-1);
			this.w = old.w + wcurr;
		}
	}
	
	public wordClass(wordClass old) {
		this.word1 = old.word1;
		this.word2 = old.word2;
		this.alph = old.alph;
		this.ans1 = old.ans1;
		this.ans2 = old.ans2;
		this.w = old.w;
	}
	
	public String getAns(int i) {
		if (i == 1) {
			return ans1;
		} else {
			return ans2;
		}
	}
	
	public void setAns(int i, String ans) {
		if (i == 1) {
			ans1 = ans1 + ans;
		} else {
			ans2 = ans2 + ans;
		}
	}
	
	public int getW() {
		return w;
	}
	
	public void setW(int wcurr) {
		w += wcurr;
	}
	
	public void modAns(int i, int j, int k, int wcurr) {
		if (i == 1) {
			this.ans2 = ans2 + '*'; 
			this.ans1 = ans1 + word1.charAt(j-1);
			this.w = w - 4;
		} else if(i == 2) {
			this.ans1 = ans1 + '*'; 
			this.ans2 = ans2 + word2.charAt(k-1);
			this.w = w - 4;
		} else {
			this.ans1 = ans1 + word1.charAt(j-1);
			this.ans2 = ans2 + word2.charAt(k-1);
			this.w = w + wcurr;
		}
	}
	
	public int getIndex(int i, int j) {
		if (i == 1) {
			return alph.indexOf(word1.charAt(j-1));
		} else {
			return alph.indexOf(word2.charAt(j-1));
		}
	}
	
	public String toString() {
		return ans1 + " " + ans2;
	}
}
