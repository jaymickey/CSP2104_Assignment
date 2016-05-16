#include "Verb.h"

Verb::Verb() {}

Verb::Verb(std::string word, std::string definition) :
	Word::Word(word, definition) {}

std::string Verb::getDefinition() {
	return "(v.) " + Word::getDefinition();
}

bool Verb::isVerb() {
	return true;
}