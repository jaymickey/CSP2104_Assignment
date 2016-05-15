#include "Adjective.h"

Adjective::Adjective(std::string word, std::string definition) :
	Word::Word(word, definition) {}

std::string Adjective::getDefinition() {
	return "(adj.) " + Word::getDefinition();
}