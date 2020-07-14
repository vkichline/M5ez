#include "SortedMenu.h"


SortedMenu::SortedMenu(String hdr) : ezMenu(hdr) {
    _sortFunction = NULL;
}


bool SortedMenu::addItem(String nameAndCaption, void (*simpleFunction)(), bool (*advancedFunction)(ezMenu* callingMenu), void (*drawFunction)(ezMenu* callingMenu, int16_t x, int16_t y, int16_t w, int16_t h)) {
	return addItem(NULL, nameAndCaption, simpleFunction, advancedFunction, drawFunction);
}


bool SortedMenu::addItem(const char *image, String nameAndCaption, void (*simpleFunction)(), bool (*advancedFunction)(ezMenu* callingMenu), void (*drawFunction)(ezMenu* callingMenu, int16_t x, int16_t y, int16_t w, int16_t h)) {
    bool result = ezMenu::addItem(image, nameAndCaption, simpleFunction, advancedFunction, drawFunction);
    if(result) {
        _sortItems();
    }
    return result;
}


bool SortedMenu::addItem(fs::FS &fs, String path, String nameAndCaption, void (*simpleFunction)(), bool (*advancedFunction)(ezMenu* callingMenu), void (*drawFunction)(ezMenu* callingMenu, int16_t x, int16_t y, int16_t w, int16_t h)) {
    bool result = ezMenu::addItem(fs, path, nameAndCaption, simpleFunction, advancedFunction, drawFunction);
    if(result) {
        _sortItems();
    }
    return result;
}


void SortedMenu::setSortFunction(bool (*sortFunction)(const char* s1, const char* s2)) {
	_sortFunction = sortFunction;
	_sortItems();	// In case the menu is already populated
}


void SortedMenu::_sortItems() {
	if(_sortFunction && _items.size() > 1) {
		using namespace std::placeholders;	// For _1, _2
		sort(_items.begin(), _items.end(), std::bind(&SortedMenu::_sortWrapper, this, _1, _2));
        M5ez::redraw();
	}
}


bool SortedMenu::_sortWrapper(MenuItem_t& item1, MenuItem_t& item2) {
	// Be sure to set _sortFunction before calling _sortWrapper(), as _sortItems ensures.
	return _sortFunction(item1.nameAndCaption.c_str(), item2.nameAndCaption.c_str());
}


// A selection of sorting functions.
// If you just add a single string in menu.addItem(), the first set is fast and simple.
// Padding is not stripped from the from of a name when sorted.
// If you specify both a Name and a Caption, as in menu.addItem("This is the Name | This is the Caption which is displayed"),
// use the second group of functions so that the menu is ordered as the user sees it.

// For sorting by Names as quickly as possible
bool ascendingNameCaseSensitive   (const char* s1, const char* s2) { return 0 >     strcmp(s1, s2); }
bool ascendingNameCaseInsensitive (const char* s1, const char* s2) { return 0 > strcasecmp(s1, s2); }
bool descendingNameCaseSensitive  (const char* s1, const char* s2) { return 0 <     strcmp(s1, s2); }
bool descendingNameCaseInsensitive(const char* s1, const char* s2) { return 0 < strcasecmp(s1, s2); }

// For sorting by Caption if there is one, falling back to sorting by Name if no Caption is provided (all purpose)
const char* captionHelper(const char* nameAndCaption) {
	char* sub = strchr(nameAndCaption, '|');	// Find the divider
	if(nullptr == sub) return nameAndCaption;	// If none, return the entire string
	sub++;                          			// move past the divider
	while(isspace(sub[0])) sub++;				// trim whitespace
	return sub;
}
bool ascendingCaptionCaseSensitive   (const char* s1, const char* s2) { return 0 >     strcmp(captionHelper(s1), captionHelper(s2)); }
bool ascendingCaptionCaseInsensitive (const char* s1, const char* s2) { return 0 > strcasecmp(captionHelper(s1), captionHelper(s2)); }
bool descendingCaptionCaseSensitive  (const char* s1, const char* s2) { return 0 <     strcmp(captionHelper(s1), captionHelper(s2)); }
bool descendingCaptionCaseInsensitive(const char* s1, const char* s2) { return 0 < strcasecmp(captionHelper(s1), captionHelper(s2)); }
