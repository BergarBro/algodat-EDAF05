package match;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class GS {

	public static void main(String[] args) {

		ArrayList<Opinion> job = new ArrayList<>(); 	// List of Jobs
		ArrayList<Opinion> stud = new ArrayList<>(); 	// List of Students

		Scanner input = new Scanner(System.in);

		// System.out.println("Amount of students:");

		int n = input.nextInt();						// Number of Individuals 
		int N = 2 * n * (n + 1);
				
		int[] data = new int[N];
		
		for (int i = 0; i < N; i++) {
			data[i] = input.nextInt();					// Recording all the individuals and the preferences 
		}
		input.close();
		
		// System.out.println("Preference List:");
		int altn = n + 1;
		for (int i = 0; i < 2 * n; i++) {				//start 
			int index = data[i * altn];					// Separate all individuals with there preferences 
			int[] temp = new int[n];
			for (int j = 1; j < altn; j++) {
				temp[j-1] = data[i * altn + j];
			}											//end
								
			Opinion op = new Opinion(index, n);			// Making a "Opinion" for each individual 
			op.setPref(temp);

			if (!job.contains(op)) {					//start
				op.invert();
				job.add(op);							// Categorizing individuals to Student and Jobs and
			} else {									// inverting Jobs preferences
				stud.add(op);
			}											//end
		}
		Collections.sort(job);							// Sorting the jobs for easy allocating later
														// .sort() has O(n log(n)) so it does not effect the overall O()
		
		while (stud.size() != 0) {						//start Implemented Gale–Shapley algorithm
			Opinion m = stud.remove(stud.size() - 1);			// Get first Student M
			Opinion w = job.get(m.getNextPref() - 1);			// Get M:s first unchecked preference Job W
			m.addCount();										// Annotate that M has been check one more time

			if (w.getPair() == null) {							// Unpaired W gets paired with M
				w.setPair(m);
			} else {
				Opinion mw = w.getPair();						// Get the Student MW that W is paired with
				if (w.getPref(mw.index()) < w.getPref(m.index())) {	// Check which Student the Job prefers best
					stud.add(m);								// Put back the student that did not get paired
				} else {
					w.setPair(m);
					stud.add(mw);								// Put back the student that did not get paired
				}
			}
		}												//end

		for (int i = 0; job.size() > i; i++) {
			System.out.println(job.get(i).getPair().index());	// Print the expected output
		}
	}
}

class Opinion implements Comparable<Opinion> {
	private int ind; 		// index
	private int[] pref; 	// Preference
	private int count;	 	// How many comparisons
	private Opinion pair;	// Pair

	public Opinion(int index, int num) {
		ind = index;
		count = 0;
		pair = null;
		pref = new int[num];
	}

	public int index() {
		return ind;
	}

	public void setPref(int[] temp) {
		pref = temp;
	}

	public int getPref(int n) {
		return pref[n - 1];
	}

	public void invert() { // Only for Jobs
		int[] temp = new int[pref.length];
		for (int i = 0; i < pref.length; i++) {
			int h = pref[i];
			temp[h - 1] = i;
		}
		pref = temp;
	}

	public void setPair(Opinion o) {
		pair = o;
	}

	public Opinion getPair() {
		return pair;
	}

	public void addCount() { // Only for Students
		count++;
	}

	public int getNextPref() { // Only for Students
		return pref[count];
	}

	@Override
	public boolean equals(Object o) {
		if (o instanceof Opinion) {
			Opinion s = (Opinion) o;
			return this.ind == s.index();
		}
		return false;
	}

	@Override
	public int compareTo(Opinion o) {
		return ind - o.index();
	}
}
