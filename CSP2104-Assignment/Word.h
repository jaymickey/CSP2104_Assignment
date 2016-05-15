#ifndef WORD_H
#define WORD_H
#include <string>

class Word {
	private:
		// m_ signifies a member variable
		std::string m_word;
		std::string m_definition;
	public:
		// Default constuctor. Required for virtual inheritance to work
		Word();
        Word(std::string, std::string);
		std::string getWord();
		virtual std::string getDefinition();
		virtual int calculateScrabbleScore();
		bool isHyphenated();
		bool isPalindrome();
		virtual bool isNoun();
		virtual bool isVerb();
		virtual ~Word();
};

#endif // WORD_H