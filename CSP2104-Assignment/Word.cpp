#include <iostream>
#include <map>
#include "Word.h"

namespace WordCpp {
	std::map<char, int> scabbleMap{
		{'a', 1}, {'b', 3},
		{'c', 3}, {'d', 2},
		{'e', 1}, {'f', 4},
		{'g', 2}, {'h', 4},
		{'i', 1}, {'j', 8},
		{'k', 5}, {'l', 1},
		{'m', 3}, {'n', 1},
		{'o', 3}, {'p', 3},
		{'q', 2}, {'r', 1},
		{'s', 4}, {'t', 2},
		{'u', 4}, {'v', 1},
		{'w', 8}, {'x', 5},
		{'y', 1}, {'z', 3}
	};
}

//void Word::setWord(std::string word) {
//	m_word = word;
//}
//
//void Word::setDefinition(std::string definition) {
//	m_definition = definition;
//}

Word::Word() {}

Word::Word(std::string word, std::string definition) :
    m_word(word), m_definition(definition) {}

std::string Word::getWord() {
	return m_word;
}

std::string Word::getDefinition() {
	return m_definition;
}

int Word::calculateScabbleScore() {
	int score = 0;
	if (isHyphenated() != true) {
		for (auto& i : m_word) {
			score += WordCpp::scabbleMap[i];
		}
	}
	return score;
}

bool Word::isHyphenated() {
	return (m_word.find('-') != std::string::npos);
}

bool Word::isNoun() {
	return false;
}

bool Word::isVerb() {
	return false;
}