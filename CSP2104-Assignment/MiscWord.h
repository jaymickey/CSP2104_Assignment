#ifndef MISCWORD_H
#define MISCWORD_H
#include <string>
#include "Word.h"

class MiscWord : virtual public Word {
	private:
	public:
		MiscWord();
		MiscWord(std::string, std::string);
		virtual std::string getDefinition();
		virtual int calculateScrabbleScore();
};

#endif // MISCWORD_H