#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <string>
#include <vector>
#include <memory>
#include "Adjective.h"
#include "Adverb.h"
#include "MiscWord.h"
#include "Noun.h"
#include "NounAndVerb.h"
#include "Preposition.h"
#include "ProperNoun.h"
#include "Verb.h"
#include "Word.h"


class Dictionary {
	private:
		// unique_ptr allows for derived classes to be stored in the vector
		std::vector<std::unique_ptr<Word>> m_wordVector;
		const std::string DICTFILE = "dictionary.txt";
	public:
		void loadDictionary();
		Word* findWord(std::string);
		int getTotalNumberOfWords();
		std::string toLower(std::string);
		void outputDefinitionAndScore(std::string);
		void findThreeZ();
		void findQWithoutU();
		void listNounAndVerb();
		void listPalindromes();
		void listHighestScrabble();
};

#endif // DICTIONARY_H