#include <iostream>
#include <fstream>
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
	eMisc
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
			/* switch (::hashIt(type)) {
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
				default:
					m_wordVector.push_back(std::make_unique<Word>(word, definition)); */
			m_wordVector.push_back(std::make_unique<Noun>(word, definition));
		}
	}
	file.close();
	/* Tests */
	std::cout << m_wordVector.size() << std::endl;
	std::cout << m_wordVector.at(157)->getWord() << std::endl;
	std::cout << m_wordVector.at(157)->getDefinition() << std::endl;
	std::cout << m_wordVector.at(157)->isNoun() << std::endl;
	std::cout << m_wordVector.at(157)->isVerb() << std::endl;
}

Word Dictionary::findWord(std::string wordString) {
    for (auto &i : m_wordVector) {
        std::string word = i->getWord();
        if (word == wordString) {
			return *i;
		}
    }
	throw std::invalid_argument("Word not found!"); // Throw exception if word not found
}