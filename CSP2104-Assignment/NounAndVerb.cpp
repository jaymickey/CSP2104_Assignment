#include "NounAndVerb.h"

NounAndVerb::NounAndVerb(std::string word, std::string definition) :
	Noun::Noun(word, definition), Verb::Verb(word, definition) {}

std::string NounAndVerb::getDefinition() {
	return "(n. v.) " + Word::getDefinition();
}