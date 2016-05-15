#ifndef ADVERB_H
#define ADVERB_H
#include <string>
#include "Word.h"

class Adverb : public Word {
	private:
	public:
		Adverb(std::string, std::string);
		virtual std::string getDefinition();
};

#endif // ADVERB_H