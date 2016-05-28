#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <string>
#include <vector>
#include <memory>
#include "Word.h"


class Dictionary {
	private:
		// unique_ptr allows for derived classes to be stored in the vector
		// Source: http://stackoverflow.com/questions/10154977/c-vector-with-inheritance
		std::vector<std::unique_ptr<Word>> m_wordVector;
		const std::string DICTFILE = "dictionary.txt";
	public:
		void loadDictionary();
		Word *findWord(const std::string &);
		int getTotalNumberOfWords();
		std::string toLower(std::string);
		void printWords(const std::vector<std::string> *);
		void outputDefinitionAndScore();
		void findThreeZ();
		void findQWithoutU();
		void listNounAndVerb();
		void listPalindromes();
		void listHighestScrabble();
		void findScrabbleWord();
		void findAnagrams();
};

#endif // DICTIONARY_H