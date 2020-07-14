#pragma once
#include <M5ez.h>

class SortedMenu : public ezMenu {
	public:
		SortedMenu(String hdr = "");
		bool addItem(String nameAndCaption, void (*simpleFunction)() = NULL, bool (*advancedFunction)(ezMenu* callingMenu) = NULL, void (*drawFunction)(ezMenu* callingMenu, int16_t x, int16_t y, int16_t w, int16_t h) = NULL);
		bool addItem(const char *image, String nameAndCaption, void (*simpleFunction)() = NULL, bool (*advancedFunction)(ezMenu* callingMenu) = NULL, void (*drawFunction)(ezMenu* callingMenu, int16_t x, int16_t y, int16_t w, int16_t h) = NULL);
		bool addItem(fs::FS &fs, String path, String nameAndCaption, void (*simpleFunction)() = NULL, bool (*advancedFunction)(ezMenu* callingMenu) = NULL, void (*drawFunction)(ezMenu* callingMenu, int16_t x, int16_t y, int16_t w, int16_t h) = NULL);
		void setSortFunction(bool (*sortFunction)(const char* s1, const char* s2));
	protected:
		bool (*_sortFunction)(const char* s1, const char* s2);
		void _sortItems();
		bool _sortWrapper(MenuItem_t& item1, MenuItem_t& item2);
};


// A selection of sorting functions.
// If you just add a single string in menu.addItem(), the first set is fast and simple.
// Padding is not stripped from the from of a name when sorted.
// If you specify both a Name and a Caption, as in menu.addItem("This is the Name | This is the Caption which is displayed"),
// use the second group of functions so that the menu is ordered as the user sees it.

// For sorting by Names as quickly as possible
bool ascendingNameCaseSensitive   (const char* s1, const char* s2);
bool ascendingNameCaseInsensitive (const char* s1, const char* s2);
bool descendingNameCaseSensitive  (const char* s1, const char* s2);
bool descendingNameCaseInsensitive(const char* s1, const char* s2);

// For sorting by Caption if there is one, falling back to sorting by Name if no Caption is provided (all purpose)
const char* captionHelper(const char* nameAndCaption);
bool ascendingCaptionCaseSensitive   (const char* s1, const char* s2);
bool ascendingCaptionCaseInsensitive (const char* s1, const char* s2);
bool descendingCaptionCaseSensitive  (const char* s1, const char* s2);
bool descendingCaptionCaseInsensitive(const char* s1, const char* s2);
