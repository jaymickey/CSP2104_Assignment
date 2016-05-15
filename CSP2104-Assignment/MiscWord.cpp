#include "MiscWord.h"

MiscWord::MiscWord(std::string word, std::string definition) :
	Word::Word(word, definition) {}

std::string MiscWord::getDefinition() {
	return "(misc.) " + Word::getDefinition();
}