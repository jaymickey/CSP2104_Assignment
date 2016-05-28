#ifndef VERB_H
#define VERB_H
#include <string>
#include "Word.h"

class Verb : virtual public Word {
	private:
	public:
		// Verb() {}
		Verb(std::string, std::string);
		virtual std::string getDefinition();
		bool isVerb();
};

#endif // VERB_H