#include "Preposition.h"

Preposition::Preposition(std::string word, std::string definition) :
	MiscWord::MiscWord(word, definition) {}

std::string Preposition::getDefinition() {
	return "(prep.) " + Word::getDefinition();
}