#include <iostream>
#include <fstream>
#include <algorithm>
#include "Adjective.h"
#include "Adverb.h"
#include "MiscWord.h"
#include "Noun.h"
#include "NounAndVerb.h"
#include "Preposition.h"
#include "ProperNoun.h"
#include "Verb.h"
#include "Dictionary.h"

// enum evaluation for type strings via a hash table
// Source: http://stackoverflow.com/a/650307
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

word_code hashIt(const std::string &inString) {
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
	std::ifstream file(M_DICTFILE);
	// Temp variables for loading lines
	std::string line, word, definition, type;
	// Check if file is open
	if (file.is_open()) {
		/* Read the file line by line and load into temp variables, this really only 
		works because we know the exact format of the file */
		// Avoid additional loop with .eof()
		while (getline(file, word)) {
			getline(file, definition);
			getline(file, type);
			getline(file, line);
			// Create object based on word type
			switch (::hashIt(type)) {
			case eNoun:
				// make_unique returns a unique_ptr to an instance of the type
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
		file.close();
	} else {
		// Throw exception if file couldn't be opened
		throw "File could not be opened!";
	}
}

Word *Dictionary::findWord(const std::string &wordString, bool log = true) {
	// Add the word to the log file
	if (log) m_logFile.addToLog(toLower(wordString));
	for (auto &i : m_wordVector) {
        if (toLower(i->getWord()) == toLower(wordString)) {
			return i.get();
		}
    }
	// Return a nullptr if word not found
	// Originally threw an exception, but a nullptr is easier to work with
	return nullptr;
}

int Dictionary::getTotalNumberOfWords() {
	return m_wordVector.size();
}

std::string Dictionary::toLower(const std::string &inString) {
	// Convert to lowercase
	// Source: https://notfaq.wordpress.com/2007/08/04/cc-convert-string-to-upperlower-case/
	std::string lowerString = inString;
	std::transform(inString.begin(), inString.end(), lowerString.begin(), ::tolower);
	return lowerString;
}

/* Instead of including formatting code for every function, given the formatting will
generally follow the same rules, this function does it instead. Originally I simply printed
the word, however, adding to a vector allows for greater formatting control. In this case
I opted for aesthetics over efficiency. */
void Dictionary::printWords(const std::vector<std::string> &wordVector) {
	int formattingInt = 1;
	const int WORDSPERLINE = 10;
	for (const std::string &word : wordVector) {
		// Test if current word is the last word in the vector
		// Only possible because we know each word is unique
		if (word != wordVector.back()) {
			// Add a line break after 5 words have been printed
			std::cout << word << (((formattingInt % WORDSPERLINE) == 0) ? "\n" : ", ");
			formattingInt++;
		}
		else {
			std::cout << word << std::endl << std::endl;
		}
	}
}

void Dictionary::outputDefinitionAndScore() {

	// Variables for splitting definition
	// Source: http://stackoverflow.com/a/14266139
	std::string delim = "  ";
	size_t last = 0, next = 0;

	std::string wordString;
	std::cout << "Enter the word to find: ";
	std::cin >> wordString;
	std::cout << std::endl;

	std::cout << "Finding definition for word: " << wordString << std::endl << std::endl;
	// nullptr will evaluate to bool false
	if (Word *word = findWord(wordString)) {
		std::cout << "Definitions for word: " << word->getWord() << std::endl;
		
		std::string wordDefinition = word->getDefinition();
		/* I chose to split by double space because definitions that are separated
		by a single space (after ;) appear to be related. Readability is slightly
		improved this way */
		while ((next = wordDefinition.find(delim, last)) != std::string::npos) {
			std::cout << wordDefinition.substr(last, next - last) << std::endl;
			last = next + 2;
		}
		std::cout << wordDefinition.substr(last) << std::endl << std::endl;

		int scrabbleScore = word->calculateScrabbleScore();
		if (scrabbleScore == 0) {
			// Words with a score of 0 are invalid
			std::cout << "\"" << word->getWord() << "\"" << " not valid in scrabble." << std::endl << std::endl;
		}
		else {
			std::cout << "Scrabble score for " << word->getWord() << ": " << scrabbleScore << std::endl << std::endl;
		}
	}
	else {
		std::cout << "Word not found!" << std::endl;
	}
}

void Dictionary::findThreeZ() {
	std::cout << "Words containing more than 3 'z''s: " << std::endl << std::endl;
	for (auto &i : m_wordVector) {
		// Convert to lower to ensure consistency
		std::string word = toLower(i->getWord());
		// Count the number of z's in the word, proceed if more than 3
		if (std::count(std::begin(word), std::end(word), 'z') > 3) {
			std::cout << word << std::endl;
		}
	}
	std::cout << std::endl;
}

void Dictionary::findQWithoutU() {
	std::vector<std::string> matches;
	for (auto &i : m_wordVector) {
		// Convert to lower to ensure consistency
		std::string word = toLower(i->getWord());
		size_t pos = 0;
		if ((pos = word.find('q')) != std::string::npos) {
			if (word[pos + 1] != 'u') {
				matches.push_back(i->getWord());
			}
		}
	}
	std::cout << "Words with 'q' not followed by 'u': " << std::endl << std::endl;
	printWords(matches);
}

void Dictionary::listNounAndVerb() {
	std::vector<std::string> matches;
	for (auto &i : m_wordVector) {
		if ((i->isVerb()) && (i->isNoun())) {
			matches.push_back(i->getWord());
		}
	}
	std::cout << "Words that are both a noun and a verb: " << std::endl << std::endl;
	printWords(matches);
}

void Dictionary::listPalindromes() {
	std::vector<std::string> matches;
	for (auto &i : m_wordVector) {
		if (i->isPalindrome()) {
			matches.push_back(i->getWord());
		}
	}
	std::cout << "Words that are palindromes: " << std::endl << std::endl;
	printWords(matches);
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
	std::cout << "Highest scoring scrabbles word(s): " << std::endl << std::endl;
	printWords(highestScoreWords);
	std::cout << "Scrabble score: " << highestScore << std::endl << std::endl;
}

void Dictionary::findScrabbleWord() {
	std::string letterString;
	int highestScore = 0;
	std::vector<std::string> possibleWords;
	bool found = false;
	std::cout << "Enter a string of letters: ";
	std::cin >> letterString;
	// Convert to lowercase to ensure consistency
	letterString = toLower(letterString);

	for (auto &i : m_wordVector) {
		// Convert to lowercase to ensure consistency
		std::string word = toLower(i->getWord());
		for (char j : word) {
			// 
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
				// Clear the vector, and add the new highest scoring word to it
				possibleWords.clear();
				highestScore = currentScore;
				possibleWords.push_back(i->getWord());
			}
			else if (currentScore == highestScore) {
				// Add the word to the vector of words with an equally high score
				possibleWords.push_back(i->getWord());
			}
		}
	}

	std::cout << "Highest scoring words possible with letters \"" << letterString << "\":" << std::endl << std::endl;
	printWords(possibleWords);
	std::cout << "Score: " << highestScore << std::endl << std::endl;
}

void Dictionary::findAnagrams() {
	std::vector<std::string> matches;
	std::string wordString;
	std::cout << "Enter the word you wish to find anagrams for: ";
	std::cin >> wordString;
	wordString = toLower(wordString);
	std::cout << std::endl;
	// Sort is destructive to the original string, so making a copy before sorting is required
	std::string originalWord = wordString;
	std::sort(wordString.begin(), wordString.end());

	for (auto &i : m_wordVector) {
		std::string word = toLower(i->getWord());
		// Skip words that are not of the same length, as we know these cannot be anagrams
		if (wordString.length() == word.length() && word != originalWord) {
			// Now we sort the word from the dictionary to compare
			std::sort(word.begin(), word.end());
			if (wordString == word) {
				matches.push_back(i->getWord());
			}
		}
	}
	if (!matches.empty()) {
		std::cout << "Anagrams for \"" << originalWord << "\":" << std::endl << std::endl;
		printWords(matches);
	} else 
		std::cout << "No anagrams for \"" << originalWord << "\"!" << std::endl << std::endl;
}