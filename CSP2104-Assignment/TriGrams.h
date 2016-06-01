#ifndef TRIGRAMS_H
#define TRIGRAMS_H
#include <string>
#include <map>
#include "Dictionary.h"

/* The requirements advise that this task should be in a "separate file", but isn't
totally clear on what a separate file means. Further down it uses "separate program"
to refer to the audit system, so I am assuming that in this case, "seperate file" is 
referring to a seperate .h and .cpp file within the existing project/solution?
I might be overthinking it, but it felt important to clarify my thought process incase
this task was implemented incorrectly. */

/* NOTE: A number of assuptions were made in the completion of this task.
Each of these will be mentioned in the comments in the .cpp file */

class TriGrams {
	private:
		std::map<std::string, std::map<char, int>> m_triGramMap;
		Dictionary *m_dict;
	public:
		TriGrams(Dictionary *);
		void toLower(std::string &);
		void loadFile();
		void findNextThreeChars();
		void generateWords();
};

#endif // TRIGRAMS_H