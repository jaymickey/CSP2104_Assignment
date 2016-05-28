#ifndef NOUNANDVERB_H
#define NOUNANDVERB_H
#include <string>
#include "Noun.h"
#include "Verb.h"

class NounAndVerb : public Noun, public Verb {
	private:
	public:
		NounAndVerb(std::string, std::string);
		std::string getDefinition();
};

#endif // NOUNANDVERB_H