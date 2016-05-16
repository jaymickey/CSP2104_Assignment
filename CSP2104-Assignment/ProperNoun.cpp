#include "ProperNoun.h"

ProperNoun::ProperNoun(std::string word, std::string definition) :
	Word::Word(word, definition) {}

std::string ProperNoun::getWord() {
	std::string word = Word::getWord();
	word[0] = toupper(word[0]);
	return word;
}

std::string ProperNoun::getDefinition() {
	return "(pn.) " + Word::getDefinition();
}

int ProperNoun::calculateScrabbleScore() {
	return 0;
}