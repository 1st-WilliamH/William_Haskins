package sorting_algorithm;

import java.lang.reflect.Array;
import java.util.*;

public class List_Sorter {
	//Counts loop passes to help highlight Big O runtime differences. . .
	public static int passCounter;
	//
	public static void sortSelection(List<Integer> theList) {
		//Initializing variable. . .
		passCounter = 0;
		//
		//Opening dialogue. . .
		System.out.println("Please select a sorting method.");
		System.out.println("Enter 'reverse' to reverse the list.");
		System.out.println("Enter 'bubble' to bubblesort the list.");
		System.out.println("Enter 'selection' to selectionsort the list.");
		System.out.println("Enter 'quick' to quicksort the list.");
		System.out.println("Enter 'quit' to exit.");
		Main_Class.query = Main_Class.myScanner.nextLine();
		//
		//Setting dialogue responses. . .
		if (Main_Class.query.equals("reverse")) {
			List_Sorter.reverseList(theList);
		}
		else if (Main_Class.query.equals("bubble")) {
			System.out.println("Sorting the list with bubbles. . .");
			List_Sorter.bubbleSortList(theList);
			
			System.out.println("It took " + passCounter + " cycles but the list is now sorted.");
			List_Sorter.readTheList(theList);
			System.out.println();
			List_Filler.listSelection(theList);
		}
		else if (Main_Class.query.equals("selection")) {
			System.out.println("Sorting the list by selection. . .");
			List_Sorter.selectionSortList(theList);
			
			System.out.println("It took " + passCounter + " cycles but the list is now sorted.");
			List_Sorter.readTheList(theList);
			System.out.println();
			List_Filler.listSelection(theList);
		}
		else if (Main_Class.query.equals("quick")) {
			System.out.println("Sorting the list quickly. . .");
			List_Sorter.quickSortList(theList, 0, (theList.size() - 1));
			
			System.out.println("It took " + passCounter + " cycles but the list is now sorted.");
			List_Sorter.readTheList(theList);
			System.out.println();
			List_Filler.listSelection(theList);
		}
		else if (Main_Class.query.equals("quit") || Main_Class.query.equals("q")) {
			System.out.println("Goodbye.");
			return;
		}
		else {
			List_Sorter.sortSelection(theList);
		}
		//
	}
	//reversing list option. . .
	public static void reverseList(List<Integer> theList) {
		List<Integer> holdingList = new ArrayList<Integer>();
		int j = theList.size() - 1;
		int i = 0;
		
		System.out.println("Reversing the list. . .");
		holdingList.addAll(theList);
		System.out.print("[ ");
		for (i = 0; i < theList.size(); i++) {
			
			theList.set(i, holdingList.get(j));

			System.out.print(theList.get(i) + " ");
			j--;
		}
		System.out.print("]\n\n");
		List_Filler.listSelection(theList);
	}
	//
	//bubble sorting list option. . .
	public static void bubbleSortList(List<Integer> theList) {
		int sortedCheck = 0;
		int i = 0;
		int holderVariable = 0;
		
		while (sortedCheck != 1) {
			
			sortedCheck = 1;
			for (i = 0; i < (theList.size() - 1); i++) {
				if (theList.get(i) > theList.get(i + 1)) {
					holderVariable = theList.get(i);
					theList.set(i, theList.get(i + 1));
					theList.set(i + 1, holderVariable);
					sortedCheck = 0;
				}
				passCounter++;
			}
		}
	}
	//
	//selection sorting list option. . .
	public static void selectionSortList(List<Integer> theList) {
		
		for (int i = 0; i < (theList.size() - 1); i++) {
			int minimum = i;
			for (int j = i + 1; j < (theList.size()); j++) {
				if (theList.get(minimum) > theList.get(j)) {
					minimum = j;
				}
				passCounter++;
			}
			
			int holderVariable = theList.get(i);
			theList.set(i, theList.get(minimum));
			theList.set(minimum, holderVariable);
		}
	}
	//
	//quick sorting list option. . .
	public static void quickSortList(List<Integer> theList, int lowIndex, int highIndex) {
		//default return
		if (lowIndex >= highIndex) {
			return;
		}
		int pivotPointer = theList.get(highIndex);
		int leftPointer = lowIndex;
		int rightPointer = highIndex;
		while (leftPointer < rightPointer) {
			while (theList.get(leftPointer) <= pivotPointer && leftPointer < rightPointer) {
				leftPointer++;
				passCounter++;
			}
			while (theList.get(rightPointer) >= pivotPointer && leftPointer < rightPointer) {
				rightPointer--;
				passCounter++;
			}
			swaper(theList, leftPointer, rightPointer);
		}	
		swaper(theList, leftPointer, highIndex);
		//low half recursion
		List_Sorter.quickSortList(theList, lowIndex, leftPointer - 1);
		//high half recursion
		List_Sorter.quickSortList(theList, leftPointer + 1, highIndex);
	}
	//
	//swapper for quick sort. . .
	public static void swaper(List<Integer> theList, int num1, int num2) {
		int holderVariable = theList.get(num1);
		theList.set(num1, theList.get(num2));
		theList.set(num2, holderVariable);
	}
	//
	//list reader. . .
	public static void readTheList(List<Integer> theList) {
		System.out.print("[ ");
		for (int i = 0; i < theList.size(); i++) {
			System.out.print(theList.get(i) + " ");
		}
		System.out.print("]\n");
	}
}		


