#include "Noun.h"

Noun::Noun(std::string word, std::string definition) :
	Word::Word(word, definition) {}

std::string Noun::getDefinition() {
	return "(n.) " + Word::getDefinition();
}

bool Noun::isNoun() {
	return true;
}