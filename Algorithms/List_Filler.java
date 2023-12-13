package sorting_algorithm;

import java.util.*;

public class List_Filler {
	public static void listSelection(List<Integer> theList) {
		//Opening dialogue. . .
		System.out.println("Please select a list to test with.");
		System.out.println("Enter 'sorted' to make a sorted list.");
		System.out.println("Enter 'jumbled' to make a jumbled list.");
		System.out.println("Enter 'big' to make a big list.");
		if (theList.size() > 1) {System.out.println("Enter 'continued' to continue with the current list.");}
		System.out.println("Enter 'quit' to exit.");
		Main_Class.query = Main_Class.myScanner.nextLine();
		//
		
		//Setting dialogue responses. . .
		if (Main_Class.query.equals("sorted")) {
			System.out.println("You requested a 'sorted' list.");
			
			theList.clear();
			Collections.addAll(theList, 
			1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
			11, 12, 13, 14, 15, 16, 17, 18, 19, 20);
					

			int i = 0;
			System.out.print("[ ");
			for (i = 0; i < theList.size(); i++) {
				System.out.print(theList.get(i) + " ");
			}
			System.out.print("]\n\n");
			List_Sorter.sortSelection(theList);
		}
		else if (Main_Class.query.equals("jumbled")) {
			System.out.println("You requested a 'jumbled' list.");
			
			theList.clear();
			Collections.addAll(theList, 
			20,  7,  3,  4,  5,  8,  7,  8,  9, 11,
			13, 12, 14,  1,  5,  5,  5, 18, 19, 17);
					

			int i = 0;
			System.out.print("[ ");
			for (i = 0; i < theList.size(); i++) {
				System.out.print(theList.get(i) + " ");
			}
			System.out.print("]\n\n");
			List_Sorter.sortSelection(theList);
		}
		else if (Main_Class.query.equals("big")) {
			
			System.out.println("You requested a 'big' list.");
			
			theList.clear();
			Collections.addAll(theList, 
			 1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
			11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
			20,  7,  3,  4,  5,  8,  7,  8,  9, 11,
			13, 12, 14,  1,  5,  5,  5, 18, 19, 17);
					

			int i = 0;
			System.out.print("[ ");
			for (i = 0; i < theList.size(); i++) {
				System.out.print(theList.get(i) + " ");
			}
			System.out.print("]\n\n");
			List_Sorter.sortSelection(theList);
		}
		else if (Main_Class.query.equals("continued")) {
			if (theList.size() > 1) {
				System.out.println("You requested to continue with the current list.");
				List_Sorter.sortSelection(theList);
			}
			else {
				System.out.println("You must have a list to start with.");
				List_Filler.listSelection(theList);
			}
		}
		else if (Main_Class.query.equals("quit") || Main_Class.query.equals("q")) {
			System.out.println("Goodbye.");
			return;
		}
		else { 
			List_Filler.listSelection(theList);
		}
		//
	}
}
