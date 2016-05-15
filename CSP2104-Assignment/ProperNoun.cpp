#include "ProperNoun.h"

ProperNoun::ProperNoun(std::string word, std::string definition) :
	Noun::Noun(word, definition) {}

std::string ProperNoun::getDefinition() {
	return "(pn.) " + Word::getDefinition();
}