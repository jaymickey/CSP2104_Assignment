#include <iostream>
#include <Windows.h>
#include "Dictionary.h"

// No std namespace, as recommended here: http://stackoverflow.com/questions/1452721/why-is-using-namespace-std-in-c-considered-bad-practice

/* Classes:
		- Word
			* calculateScrabbleScore-
			* isHyphenated-
			* isPalindrome-
			* isVerb-
			* isNoun-
			- Noun-
				- ProperNoun-
				- NounAndVerb-
			- Verb-
				- NounAndVerb
			- Adverb-
			- Adjective-
			- MiscWord-
				- Preposition-
		- Dictionary
			* getTotalNumberOfWords-
			* loadDictionary-

Word types:
	n
	v
	n_and_v
	pn
	adv
	adj
	misc
	prep
*/

void loadMenu() {
	//load the menu
}

// Main function
int main() {
	COORD newSize = {80,1000};
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), newSize);
    std::string wordString;
	Dictionary dict;
	dict.loadDictionary();
    //std::cout << "Enter the word to find: ";
    //std::cin >> wordString;
	// dict.outputDefinitionAndScore(wordString);
	// dict.findThreeZ();
	// dict.findQWithoutU();
	// dict.listNounAndVerb();
	// dict.listPalindromes();
	// dict.listHighestScrabble();
	dict.findScrabbleWord();
	system("pause");
}