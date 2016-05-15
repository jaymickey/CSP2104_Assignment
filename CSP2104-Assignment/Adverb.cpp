#include "Adverb.h"

Adverb::Adverb(std::string word, std::string definition) :
	Word::Word(word, definition) {}

std::string Adverb::getDefinition() {
	return "(adv.) " + Word::getDefinition();
}