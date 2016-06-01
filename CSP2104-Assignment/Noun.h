#ifndef NOUN_H
#define NOUN_H
#include <string>
#include "Word.h"

class Noun : virtual public Word {
	private:
	public:
		Noun(std::string, std::string);
		virtual std::string getDefinition();
		bool isNoun();
};

#endif // NOUN_H