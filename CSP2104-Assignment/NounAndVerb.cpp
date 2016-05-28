#include "NounAndVerb.h"

NounAndVerb::NounAndVerb(std::string word, std::string definition) :
	Word(word, definition), Noun(word, definition), Verb(word, definition) {}

std::string NounAndVerb::getDefinition() {
	return "(n. v.) " + Word::getDefinition();
}