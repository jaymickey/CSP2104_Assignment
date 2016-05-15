#ifndef MISCWORD_H
#define MISCWORD_H
#include <string>
#include "Word.h"

class MiscWord : public Word {
	private:
	public:
		MiscWord(std::string, std::string);
		virtual std::string getDefinition();
};

#endif // MISCWORD_H