#include <iostream>
#include <map>
#include "Word.h"

// Mapping letters to numbers to create a scrabble score
namespace CSP2104 {
	std::map<char, int> scrabbleMap{
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

Word::Word(std::string word, std::string definition) :
    m_word(word), m_definition(definition) {}

std::string Word::getWord() {
	return m_word;
}

std::string Word::getDefinition() {
	return m_definition;
}

int Word::calculateScrabbleScore() {
	int score = 0;
	if (isHyphenated() != true) {
		for (auto& i : m_word) {
			score += CSP2104::scrabbleMap[i];
		}
	}
	return score;
}

bool Word::isHyphenated() {
	return (m_word.find('-') != std::string::npos);
}

// Source: http://stackoverflow.com/a/8362657
bool Word::isPalindrome() {
	return equal(m_word.begin(), m_word.begin() + m_word.size() / 2, m_word.rbegin());
}

bool Word::isNoun() {
	return false;
}

bool Word::isVerb() {
	return false;
}