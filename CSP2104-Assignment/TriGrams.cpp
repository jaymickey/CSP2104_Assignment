#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include "TriGrams.h"

TriGrams::TriGrams(Dictionary *dict) : m_dict(dict) {}

/* This method, for the purposes of this class, can be destructive to the original string,
unlike in the Dictionary class, where we don't want to be destructive */
void TriGrams::toLower(std::string &inString) {
	std::transform(inString.begin(), inString.end(), inString.begin(), tolower);
}

void TriGrams::loadFile() {
	// Assuming "text document" in the assignment requirements refers to a text file.

	/* As we can't make any assumptions as to the name and location of the document,
	we're going to need to have the user enter this. */
	std::string filePath;
	// Full path required, eg. C:\SomeFolder\Test.txt
	/* Santise the file first to avoid incompatible characters, otherwise an error will occur:
	https://jhy.io/tools/convert-word-to-plain-text */
	std::cout << "Enter path to plain text file to \"learn\" from: ";
	std::getline(std::cin, filePath);
	std::ifstream file(filePath);

	if (file.is_open()) {
		std::string line;
		while (getline(file, line)) {
			if (line.length() >= 3) {
				for (size_t i = 0; i < (line.length() - 2); i++) {
					std::string biGram = line.substr(i, 2);
					/* Make everything lowercase for the sake of consistency. When a word is being
					generated, there is no point discriminating between upper and lowercase */
					toLower(biGram);
					/* Requirements don't specify what should happen to punctuation or spaces that are not
					the first character of the bi-gram. Punctuation and spaces are an easy way to end a word
					when generating it, so in this case we'll keep them if they are the 3rd character in the 
					tri-gram, otherwise they don't really have any benefit. */
					// Also check if characters are legal, if char <= 0 then the char is illegal
					if (line[i] > 0 && line[i + 1] > 0 && line[i + 2] > 0
						&& !ispunct(line[i]) && !ispunct(line[i + 1]) && !isspace(line[i + 1])
						&& !isdigit(line[i]) && !isdigit(line[i + 1]) && !isdigit(line[i + 2])) { // We're also ignoring all numbers
						// Maps are pretty cool, they automatically create the keys when you assign a value
						m_triGramMap[biGram][tolower(line[i + 2])]++;
					}
				}
			}
		}
		file.close();
	}
	else {
		throw "File could not be opened!";
	}
}

// Sort by the value of the pair in descending order
bool compare(const std::pair<char, int> &i, const std::pair<char, int> &j) {
	return i.second > j.second;
}

void TriGrams::findNextThreeChars() {
	std::vector<std::pair<char, int>> pairs;
	std::string twoChars;
	bool valid = true;
	std::cout << "Enter 2 characters (a-z, leading space allowed): " << std::endl;
	do {
		std::cout << "> ";
		std::cin >> twoChars;
		toLower(twoChars);
		// Validate the input
		if (twoChars.length() > 2 || isspace(twoChars[1])
			|| ispunct(twoChars[0]) || ispunct(twoChars[1])) {
			std::cout << "\n\n Invalid input, try again." << std::endl;
			valid = false;
		}
	} while (!valid); // Loop while input is not valid
	// Check that the pair entered is in the map
	std::cout << std::endl;
	if (m_triGramMap.find(twoChars) != m_triGramMap.end()) {
		for (auto &i : m_triGramMap[twoChars]) {
			// Add all pairs into a vector
			pairs.push_back(i);
		}
		// Sort the vector by the number of occurrences (value, as opposed to key)
		std::sort(pairs.begin(), pairs.end(), ::compare);
		// Format output depending on "next" characters available
		if (pairs.size() < 3) {
			std::cout << "Only " << pairs.size() << " characters most likely to follow \""
				<< twoChars << "\" from data provided:" << std::endl << std::endl;
			for (int i = 0; i < pairs.size(); i++) {
				std::cout << pairs[i].first << std::endl;
			}
		}
		else {
			std::cout << "Three characters most likely to follow \"" << twoChars
				<< "\": " << std::endl << std::endl;
			for (int i = 0; i < 3; i++) {
				std::cout << pairs[i].first << std::endl;
			}
		}
		std::cout << std::endl;
	}
	else {
		std::cout << "No data for available for \"" << twoChars << "\"" << std::endl << std::endl;
	}
}

void TriGrams::generateWords() {
	std::cout << "Generating 10 random words that are not in the dictionary. This can take a while..." << std::endl << std::endl;
	std::vector<std::string> possibleFirst;
	for (auto &i : m_triGramMap) {
		if (isspace(i.first[0])) {
			// Any pair with a space as the first char can form the basis of our word
			possibleFirst.push_back(i.first);
		}
		/* The map is sorted automatically by key, so we kill the loop once the first char
		of the map key is not a space */
		else break;
	}

	// Random number generator
	// Source: http://www.dreamincode.net/forums/topic/379290-generating-random-numbers-the-c-way/
	// Seed generator
	std::random_device randomDevice;
	// Random number engine using Mersenne-Twister
	std::mt19937 randomNumGen(randomDevice());
	std::uniform_int_distribution<int> intDistribution(0, possibleFirst.size() - 1);

	for (int i = 0; i < 10; i++) {
		// Generate a random int
		int randomInt = intDistribution(randomNumGen);
		std::string word;
		int pos = 0;
		word = possibleFirst[randomInt];
		while (true) {
			// If the next 2 chars aren't in the map then there is no point continuing
			if (m_triGramMap.find(word.substr(pos, 2)) == m_triGramMap.end()) break;
			int interval = 0;
			// Setup containers for generating next character
			std::vector<std::pair<char, int>> possibleChars;
			std::vector<int> intervals{ 0 };
			std::vector<int> weights;
			for (auto &j : m_triGramMap[word.substr(pos, 2)]) {
				interval++;
				possibleChars.push_back(j);
				intervals.push_back(interval);
				weights.push_back(j.second);
			}
			int index = 0;
			if (possibleChars.size() > 1) {
				/* Create a distribution of floats between intervals, each with it's own weight
				Source: http://stackoverflow.com/a/5629319/6050866 */
				std::piecewise_constant_distribution<> dist(intervals.begin(),
					intervals.end(), weights.begin());
				// Convert to an int because we don't care about anything after the decimal place
				index = dist(randomNumGen);
				// I tested this over a sample size of 10,000, it works very well
			}
			// Break the loop if the char selected a space or punctuation
			
			if (!isalpha(possibleChars[index].first)) {
				if (word.length() > 3) break;
			} else {
				word += possibleChars[index].first;
				pos++;
			}
		}
		// Remove the space from the start of the word
		word.erase(word.begin());
		// Check if the word exists in the dictionary and decrement i by 1 if it does
		/* Note: Attempting to find the word in the dictionary slows the generator considerably. 
		Unfortunately I don't really know how to speed it up. */
		Word *checkWord = m_dict->findWord(word, false);
		if (checkWord) {
			i--;
		}
		else std::cout << word << std::endl;
	}
	std::cout << std::endl << std::endl;
}