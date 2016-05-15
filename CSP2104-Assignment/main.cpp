#include <iostream>
#include "Dictionary.h"

// No std namespace, as recommended here: http://stackoverflow.com/questions/1452721/why-is-using-namespace-std-in-c-considered-bad-practice

/* Classes:
		- Word
			* calculateScrabbleScore
			* isHyphenated
			* isPalindrome
			* isVerb
			* isNoun
			- Noun
				- ProperNoun
				- NounAndVerb
			- Verb
				- NounAndVerb
			- Adverb
			- Adjective
			- MiscWord
				- Preposition
		- Dictionary
			* getTotalNumberOfWords
			* loadDictionary

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
    std::string wordString;
	Dictionary dict;
	dict.loadDictionary();
    std::cout << "Enter the word to find: ";
    std::cin >> wordString;
	try {
		std::cout << "Finding definition for word: " << wordString << std::endl << std::endl;
		Word word = dict.findWord(wordString);
		std::cout << word.getDefinition() << std::endl;
		std::cout << word.calculateScabbleScore() << std::endl;
		std::cout << word.isHyphenated() << std::endl;
	} catch (const std::invalid_argument& ex1) { // Catch exception if word not found
		std::cout << ex1.what() << std::endl;
	}
	system("pause");
}