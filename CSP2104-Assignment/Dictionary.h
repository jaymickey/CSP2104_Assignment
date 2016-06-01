#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <string>
#include <vector>
#include <memory>
#include "AuditLog.h"
#include "Word.h"

class Dictionary {
	private:
		// unique_ptr allows for derived classes to be stored in the vector
		// Source: http://stackoverflow.com/a/10155007
		std::vector<std::unique_ptr<Word>> m_wordVector;
		const std::string M_DICTFILE = "dictionary.txt";
		AuditLog m_logFile;
	public:
		void loadDictionary();
		Word *findWord(const std::string &, bool);
		int getTotalNumberOfWords();
		std::string toLower(const std::string &);
		void printWords(const std::vector<std::string> &);
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