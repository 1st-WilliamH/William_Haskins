package sorting_algorithm;

import java.util.*;

public class Main_Class {
	//Initializing scanner. . .
	public static Scanner myScanner = new Scanner(System.in);
	public static String query = new String("x");
	//
	public static void main(String[] args) {
		List<Integer> theList = new ArrayList<Integer>();
		List_Filler.listSelection(theList);
		
		//Closing scanner.
		myScanner.close();
	}
}
