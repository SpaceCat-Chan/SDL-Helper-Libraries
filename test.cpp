#include "sfstream/sfstream.hpp"
#include <iostream>

int main() {
	SDL_Init(0);
	{
		sfbuf Buffer("Test.txt", "w+");
		std::iostream Stream(&Buffer);
		std::cout << "enter text please: ";
		std::string Text;
		std::cin >> Text;
		std::cout << "you entered: " << Text << '\n';
		Stream << Text;
	}
	{
		int SeekAmount;
		std::cout << "how much to seek?";
		std::cin >> SeekAmount;
		std::string Result;
		sfbuf Buffer("Test.txt", "r+");
		std::iostream Stream(&Buffer);
		Stream.seekp(SeekAmount);

		Stream >> Result;

		std::cout << "the result is: " << Result << '\n';
	}
	SDL_Quit();
}