#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <SFML/Graphics.hpp>
#define g_TextPrinter TextPrinter::GetInstance()

using std::vector;
using std::string;

class TextPrinter{
public:
	TextPrinter();
	~TextPrinter();
	static TextPrinter&	GetInstance();

	void				Update(float deltaTime);
	void				Draw(sf::RenderWindow& window);

	void				PrintFloatingText( sf::Vector2i position, float nGames, float timeToLive );
	void				PrintText( const string& str, sf::Vector2i position, int fontSize, sf::Color color, sf::Vector2f origin );
	void				PrintNumber( double number, sf::Vector2i position, int fontSize, sf::Color color, sf::Vector2f origin );
	void				PrintTextAndNumber( const string& str, double number, sf::Vector2i position, int fontSize, sf::Color color, sf::Vector2f origin );

private:
	string				NumberToFormatedString( double number );
	string				ConditionalMakeThreeDigit( long number, bool doTheWork );

	vector<sf::Text>	m_Texts;
	vector<sf::Text>	m_FrameTexts;
	vector<float>		m_TimeToLive;
	sf::Font			m_Font;
};