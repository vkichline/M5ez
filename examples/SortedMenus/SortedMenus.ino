#include <M5ez.h>
#include "SortedMenu.h"


void setup() {
	ez.begin();
}


void loop() {
	SortedMenu menu("Menu Sorting Demo");
	menu.txtSmall();
	// You can simply call setSortFunction once here, and the menu will always stay sorted.
	// menu.setSortFunction(yourSortingFunction);
	menu.buttons("asc # Asc # dsc # Dsc # Unsorted #");
	menu.addItem("Just a few");
	menu.addItem("words of");
	menu.addItem("random text in");
	menu.addItem("No Particular Order.");
	menu.addItem("Press buttons");
	menu.addItem("to re-sort");
	menu.addItem("NAME IS IGNORED! Value is sorted. | as you like.");

	// Or, you can call setSortFunction any time to re-sort the menu.
	// Once set, additional insertions are made in sorted order as well.
	// No need to call setSortFunction again unless you want to change to a different order.
	while(true) {
		menu.runOnce();
		String result = menu.pickButton();
		if     (result == "asc")      menu.setSortFunction(ascendingCaptionCaseInsensitive);
		else if(result == "Asc")      menu.setSortFunction(ascendingCaptionCaseSensitive);
		else if(result == "dsc")      menu.setSortFunction(descendingCaptionCaseInsensitive);
		else if(result == "Dsc")      menu.setSortFunction(descendingCaptionCaseSensitive);
		else if(result == "Unsorted") menu.setSortFunction(nullptr);
	}
}
