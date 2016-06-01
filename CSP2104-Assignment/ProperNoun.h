#ifndef PROPERNOUN_H
#define PROPERNOUN_H
#include <string>
#include "Noun.h"
#include "Word.h"

class ProperNoun : virtual public Noun {
	private:
	public:
		ProperNoun(std::string, std::string);
		std::string getWord();
		std::string getDefinition();
		int calculateScrabbleScore();
};

#endif // PROPERNOUN_H