#ifndef PREPOSITION_H
#define PREPOSITION_H
#include <string>
#include "MiscWord.h"
#include "Word.h"

class Preposition : public MiscWord {
	private:
	public:
		Preposition(std::string, std::string);
		std::string getDefinition();
};

#endif // PREPOSITION_H