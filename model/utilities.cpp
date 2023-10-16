#include "utilities.h"

vector<string> stringToVectorBySpaces(string given) {
	vector<string> words;

	string currentWord = "";
	for (char letter : given) {
		if (letter == ' ') {
			words.push_back(currentWord);
			currentWord = "";
		}
		else {
			currentWord += letter;
		}
	}
	if (!currentWord.empty()) {
		words.push_back(currentWord);
	}

	return words;
}

int countWordsInString(string given) {
	return 1 + count(given.begin(), given.end(), ' ');
}
