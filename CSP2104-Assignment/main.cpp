#include <iostream>
#include <limits>
#include "Dictionary.h"
#include "TriGrams.h"

/* No std namespace, as recommended here: http://stackoverflow.com/q/1452721.
Obviously the issues mentioned in the thread aren't likely to occur with a programs like this one,
but it can't hurt to adhere to a sort of "best practice" no matter the size and complexity of the 
task at hand. */

void printMenu() {
	// Print the menu for the application
	std::cout << "Please select an option from the menu:" << std::endl;
	std::cout << "1. Find definition and scrabble score of a word." << std::endl;
	std::cout << "2. Find and list words with more than three 'z''s." << std::endl;
	std::cout << "3. Find and list words that have a 'q' without a following 'u'." << std::endl;
	std::cout << "4. Find and list words that are both a noun and a verb." << std::endl;
	std::cout << "5. Find and list words that are palindromes." << std::endl;
	std::cout << "6. Find and list the word(s) with the highest scrabble score." << std::endl;
	std::cout << "7. Find highest scrabble scoring word(s) from a random string of letters." << std::endl;
	std::cout << "8. Find anagram(s) of a word." << std::endl;
	std::cout << "9. Fun with Tri-Grams." << std::endl << std::endl;
	std::cout << "Choose by entering the corresponding number (1-9) or 0 to exit:" << std::endl;
}

void printTriMenu() {
	std::cout << "Please select an option from the menu:" << std::endl;
	std::cout << "1. Find the three most likely characters to occur after two given characters." << std::endl;
	std::cout << "2. Generate 10 random words which sound like English words, but do not exist in the dictionary." << std::endl << std::endl;
	std::cout << "Choose by entering the corresponding number (1 or 2) or 0 to go back to main menu:" << std::endl;
}

// Main function
int main() {
	Dictionary dict;
	int choice;
	bool quit = false, valid = true;

	std::cout << "LOADING DICTIONARY..." << std::endl;
	try {
		dict.loadDictionary();
	} catch (const char *ex) {
		/* If the dictionary textfile contains a word type that is not supported
		the application will advise the user and exit */
		std::cout << ex << std::endl;
		system("pause");
		exit(1);
	}
	TriGrams triGram(&dict);
	
	system("cls");
	std::cout << "------------- CSP2104 Assignment ------------" << std::endl;
	std::cout << "----------- Fun with a Dictionary -----------" << std::endl << std::endl;

	do {
		printMenu();
		// Don't reprint the menu if the input is invalid
		do {
			valid = true;
			bool triValid = true, mainMen = false;
			std::cout << "> ";
			std::cin >> choice;
			// Validate the input, if input fails, clear and move to default switch condition
			// Source: http://stackoverflow.com/questions/2075898/good-input-validation-loop-using-cin-c
			if (std::cin.fail()) {
				std::cin.clear();
				choice = -1;
			}
			// Flush the new line out of the buffer, if avoids issues with getline after cin >> something
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "----------------------------------------------------" << std::endl << std::endl;
			// This was originally going to be it's own function, but it seemed unnecessary
			switch (choice) {
			case 1:
				dict.outputDefinitionAndScore();
				break;
			case 2:
				dict.findThreeZ();
				break;
			case 3:
				dict.findQWithoutU();
				break;
			case 4:
				dict.listNounAndVerb();
				break;
			case 5:
				dict.listPalindromes();
				break;
			case 6:
				dict.listHighestScrabble();
				break;
			case 7:
				dict.findScrabbleWord();
				break;
			case 8:
				dict.findAnagrams();
				break;
			case 9:
				try {
					triGram.loadFile();
				} catch(const char *ex) {
					std::cout << ex << std::endl;
					break;
				}
				std::cout << std::endl;
				do {
					printTriMenu();
					do {
						triValid = true;
						int triChoice;
						std::cout << "> ";
						std::cin >> triChoice;
						// Validate choice and flush buffer
						if (std::cin.fail()) {
							std::cin.clear();
							choice = -1;
						}
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						std::cout << "----------------------------------------------------" << std::endl << std::endl;
						switch (triChoice) {
						case 1:
							triGram.findNextThreeChars();
							break;
						case 2:
							triGram.generateWords();
							break;
						case 0:
							mainMen = true;
							break;
						default:
							std::cout << "Invalid input!" << std::endl;
							triValid = false;
						}
					} while (!triValid);
				} while (!mainMen);
				break;
			case 0:
				char yesOrNo;
				std::cout << "Are you sure you want to quit? (Y/N): ";
				std::cin >> yesOrNo;
				if (yesOrNo == 'y' || yesOrNo == 'Y')
					quit = true;
				break;
			default:
				std::cout << "Invalid input, please try again!" << std::endl;
				valid = false;
				break;
			}
		}  while (!valid);
		std::cout << std::endl;
	} while (!quit);
}