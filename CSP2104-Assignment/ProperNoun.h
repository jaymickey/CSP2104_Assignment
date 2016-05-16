#ifndef PROPERNOUN_H
#define PROPERNOUN_H
#include <string>
#include "Noun.h"

class ProperNoun : public Noun {
	private:
	public:
		ProperNoun(std::string, std::string);
		virtual std::string getWord();
		virtual std::string getDefinition();
		virtual int calculateScrabbleScore();
};

#endif // PROPERNOUN_H