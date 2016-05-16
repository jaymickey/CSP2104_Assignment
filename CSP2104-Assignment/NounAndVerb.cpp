#include "NounAndVerb.h"

NounAndVerb::NounAndVerb(std::string word, std::string definition) :
	Word::Word(word, definition) {}

std::string NounAndVerb::getDefinition() {
	return "(n. v.) " + Word::getDefinition();
}