#ifndef UNICODETOKEY_HPP
#define UNICODETOKEY_HPP


#include <SFML/Window/Keyboard.hpp>


sf::Keyboard::Key UnicodeToKey(sf::Uint32 unicode)
{
	switch(unicode)
	{
		case 'A':
		case 'a':
			return sf::Keyboard::A;
		
		case 'B':
		case 'b':
			return sf::Keyboard::B;
		
		case 'C':
		case 'c':
			return sf::Keyboard::C;
		
		case 'D':
		case 'd':
			return sf::Keyboard::D;
		
		case 'E':
		case 'e':
			return sf::Keyboard::E;
		
		case 'F':
		case 'f':
			return sf::Keyboard::F;
		
		case 'G':
		case 'g':
			return sf::Keyboard::G;
		
		case 'H':
		case 'h':
			return sf::Keyboard::H;
			
		case 'I':
		case 'i':
			return sf::Keyboard::I;
		
		case 'J':
		case 'j':
			return sf::Keyboard::J;
		
		case 'K':
		case 'k':
			return sf::Keyboard::K;
		
		case 'L':
		case 'l':
			return sf::Keyboard::L;
		
		case 'M':
		case 'm':
			return sf::Keyboard::M;
		
		case 'N':
		case 'n':
			return sf::Keyboard::N;
			
		case 'O':
		case 'o':
			return sf::Keyboard::O;
		
		case 'P':
		case 'p':
			return sf::Keyboard::P;
		
		case 'Q':
		case 'q':
			return sf::Keyboard::Q;
		
		case 'R':
		case 'r':
			return sf::Keyboard::R;
		
		case 'S':
		case 's':
			return sf::Keyboard::S;
		
		case 'T':
		case 't':
			return sf::Keyboard::T;
		
		case 'U':
		case 'u':
			return sf::Keyboard::U;
		
		case 'V':
		case 'v':
			return sf::Keyboard::V;
		
		case 'W':
		case 'w':
			return sf::Keyboard::W;
		
		case 'X':
		case 'x':
			return sf::Keyboard::X;
		
		case 'Y':
		case 'y':
			return sf::Keyboard::Y;
		
		case 'Z':
		case 'z':
			return sf::Keyboard::Z;
		
		case '0':
			return sf::Keyboard::Numpad0;
		
		case '1':
			return sf::Keyboard::Numpad1;
		
		case '2':
			return sf::Keyboard::Numpad2;
		
		case '3':
			return sf::Keyboard::Numpad3;
		
		case '4':
			return sf::Keyboard::Numpad4;
		
		case '5':
			return sf::Keyboard::Numpad5;
		
		case '6':
			return sf::Keyboard::Numpad6;
		
		case '7':
			return sf::Keyboard::Numpad7;
		
		case '8':
			return sf::Keyboard::Numpad8;
		
		case '9':
			return sf::Keyboard::Numpad9;
		
		
		default:
			std::cerr << "Error: Key '" << unicode << "' can not be used as input key.\n";
		
	}
	
	return sf::Keyboard::KeyCount;
}


#endif


