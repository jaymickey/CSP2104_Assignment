#include <iostream>
#include <fstream>
#include <algorithm>
#include "Dictionary.h"

// enum evaluation for type strings via a hash table
// Source: http://stackoverflow.com/questions/650162/why-switch-statement-cannot-be-applied-on-strings
enum word_code {
	eNoun,
	eVerb,
	eNounAndVerb,
	eAdverb,
	eAdjective,
	eProperNoun,
	ePreposition,
	eMisc,
	eInvalid
};

word_code hashIt(std::string const &inString) {
	if (inString == "n") return eNoun;
	if (inString == "v") return eVerb;
	if (inString == "n_and_v") return eNounAndVerb;
	if (inString == "adv") return eAdverb;
	if (inString == "adj") return eAdjective;
	if (inString == "pn") return eProperNoun;
	if (inString == "prep") return ePreposition;
	if (inString == "misc") return eMisc;
	return eInvalid;
}

void Dictionary::loadDictionary() {
	std::ifstream file(DICTFILE);
	// Temp variables for loading lines
	std::string line, word, definition, type;
	// Check if file is open
	if (file.is_open()) {
		// Avoid additional loop with .eof()
		while (getline(file, word)) {
			getline(file, definition);
			getline(file, type);
			getline(file, line);
			// make_unique returns a unique_ptr of an instance of the type
			switch (::hashIt(type)) {
			case eNoun:
				m_wordVector.push_back(std::make_unique<Noun>(word, definition));
				break;
			case eVerb:
				m_wordVector.push_back(std::make_unique<Verb>(word, definition));
				break;
			case eNounAndVerb:
				m_wordVector.push_back(std::make_unique<NounAndVerb>(word, definition));
				break;
			case eAdverb:
				m_wordVector.push_back(std::make_unique<Adverb>(word, definition));
				break;
			case eAdjective:
				m_wordVector.push_back(std::make_unique<Adjective>(word, definition));
				break;
			case eProperNoun:
				m_wordVector.push_back(std::make_unique<ProperNoun>(word, definition));
				break;
			case ePreposition:
				m_wordVector.push_back(std::make_unique<Preposition>(word, definition));
				break;
			case eMisc:
				m_wordVector.push_back(std::make_unique<MiscWord>(word, definition));
				break;
			case eInvalid:
				// Throw an exception if there is in an invalid word type found
				throw "Invalid word type!";
				break;
			default:
				m_wordVector.push_back(std::make_unique<Word>(word, definition));
			}
		}
	}
	file.close();
	// Tests:
	/* std::cout << m_wordVector.size() << std::endl;
	std::cout << m_wordVector.at(460)->getWord() << std::endl;
	std::cout << m_wordVector.at(460)->getDefinition() << std::endl;
	std::cout << m_wordVector.at(460)->isNoun() << std::endl;
	std::cout << m_wordVector.at(460)->isVerb() << std::endl; */
}

Word* Dictionary::findWord(std::string wordString) {
    for (auto &i : m_wordVector) {
        if (toLower(i->getWord()) == wordString) {
			return i.get();
		}
    }
	// Throw exception if word not found
	throw std::invalid_argument("Word not found!");
}

int Dictionary::getTotalNumberOfWords() {
	return m_wordVector.size();
}

std::string Dictionary::toLower(std::string inString) {
	// Convert to lowercase
	// Source: https://notfaq.wordpress.com/2007/08/04/cc-convert-string-to-upperlower-case/
	std::transform(inString.begin(), inString.end(), inString.begin(), ::tolower);
	return inString;
}

void Dictionary::outputDefinitionAndScore(std::string wordString) {

	// Variables for splitting definition
	// Source: http://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
	// std::string delim = ";";
	// size_t last = 0, next = 0;

	std::cout << "Finding definition for word: " << wordString << std::endl << std::endl;
	try {
		Word* word = findWord(toLower(wordString));
		std::cout << "Definitions for word: " << word->getWord() << std::endl;
		
		/*std::string wordDefinition = word->getDefinition();
		while ((next = wordDefinition.find(delim, last)) != std::string::npos) {
			std::cout << wordDefinition.substr(last, next - last) << std::endl;
			last = next + 2;
		}
		std::cout << wordDefinition.substr(last) << std::endl << std::endl;*/

		std::cout << word->getDefinition() << std::endl << std::endl;
		int scrabbleScore = word->calculateScrabbleScore();
		if (scrabbleScore == 0) {
			std::cout << "\"" << word->getWord() << "\"" << " not valid in scrabble." << std::endl;
		}
		else {
			std::cout << "Scrabble score for " << word->getWord() << ": " << scrabbleScore << std::endl;
		}
	}
	catch (const std::invalid_argument& ex1) { // Catch exception if word not found
		std::cout << ex1.what() << std::endl;
	}
}

void Dictionary::findThreeZ() {
	for (auto &i : m_wordVector) {
		std::string word = toLower(i->getWord());
		if (std::count(std::begin(word), std::end(word), 'z') > 3) {
			std::cout << word << ", ";
		}
	}
}

void Dictionary::findQWithoutU() {
	for (auto &i : m_wordVector) {
		std::string word = toLower(i->getWord());
		size_t pos = 0;
		if ((pos = word.find('q')) != std::string::npos) {
			if (word[pos + 1] != 'u') {
				std::cout << word << ", ";
			}
		}
	}
}

void Dictionary::listNounAndVerb() {
	for (auto &i : m_wordVector) {
		if ((i->isVerb()) && (i->isNoun())) {
			std::cout << i->getWord() << ", ";
		}
	}
}

void Dictionary::listPalindromes() {
	for (auto &i : m_wordVector) {
		if (i->isPalindrome()) {
			std::cout << i->getWord() << std::endl;
		}
	}
}

void Dictionary::listHighestScrabble() {
	int highestScore = 0;
	std::vector<std::string> highestScoreWords;
	for (auto &i : m_wordVector) {
		int currentScore = i->calculateScrabbleScore();
		if (currentScore > highestScore) {
			highestScoreWords.clear();
			highestScore = currentScore;
			highestScoreWords.push_back(i->getWord());
		} else if (currentScore == highestScore) {
			highestScoreWords.push_back(i->getWord());
		}
	}
	for (std::string i : highestScoreWords) {
		std::cout << i << std::endl;
	}
}

void Dictionary::findScrabbleWord() {
	std::string letterString;
	int highestScore = 0;
	std::vector<std::string> possibleWords;
	bool found = false;
	std::cout << "Enter a string of letters: ";
	std::cin >> letterString;
	for (auto &i : m_wordVector) {
		std::string word = i->getWord();
		for (char j : word) {
			if (std::count(word.begin(), word.end(), j) <= std::count(letterString.begin(), letterString.end(), j)) {
				found = true;
			} else {
				found = false;
				break;
			}
		}
		if (found == true) {
			int currentScore = i->calculateScrabbleScore();
			if (currentScore > highestScore) {
				possibleWords.clear();
				highestScore = currentScore;
				possibleWords.push_back(word);
			}
			else if (currentScore == highestScore) {
				possibleWords.push_back(word);
			}
		}
	}
	std::cout << "Highest scoring words possible with letters \"" << letterString << "\"" << std::endl;
	for (std::string word : possibleWords) {
		std::cout << word << std::endl;
		std::cout << "Score: " << highestScore << std::endl;
	}
}