#ifndef ADJECTIVE_H
#define ADJECTIVE_H
#include <string>
#include "Word.h"

class Adjective : public Word {
	private:
	public:
		Adjective(std::string, std::string);
		virtual std::string getDefinition();
};

#endif // ADJECTIVE_H