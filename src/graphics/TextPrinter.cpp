#include "TextPrinter.h"

#include <cassert>

TextPrinter::TextPrinter(){
	assert( m_Font.loadFromFile("../assets/arial.ttf") );
}

TextPrinter::~TextPrinter(){
	m_Texts.clear();
	m_TimeToLive.clear();
}

TextPrinter& TextPrinter::GetInstance(){
	static TextPrinter m_Instance;
	return m_Instance;
}

void TextPrinter::PrintFloatingText( sf::Vector2i position, float nGames, float timeToLive ){
	sf::Text t;
	t.setFont(m_Font);
	t.setColor(sf::Color::Black);
	t.setCharacterSize(25);
	t.setStyle(sf::Text::Bold);
	t.setPosition(position.x,position.y);

	std::stringstream ss;
	ss << nGames;
	t.setString(ss.str());

	m_Texts.push_back(t);
	m_TimeToLive.push_back(timeToLive);
}

void TextPrinter::PrintText( const string& str, sf::Vector2i position, int fontSize, sf::Color color, sf::Vector2f origin ){
	sf::Text t;
	t.setFont( m_Font );
	t.setColor( color );
	t.setCharacterSize( fontSize );
	t.setStyle( sf::Text::Bold );
	t.setPosition( position.x, position.y );
	t.setString( str );

	// Convert our origin style to sf style origin.
	sf::Vector2f sfOrigin = sf::Vector2f( origin.x * t.getLocalBounds().width, origin.y * t.getLocalBounds().height );
	t.setOrigin( sfOrigin );

	m_FrameTexts.push_back(t);
}

void TextPrinter::PrintNumber( double number, sf::Vector2i position, int fontSize, sf::Color color, sf::Vector2f origin ) {
	PrintText( NumberToFormatedString( number ), position, fontSize, color, origin );
}

void TextPrinter::PrintTextAndNumber( const string& str, double number, sf::Vector2i position, int fontSize, sf::Color color, sf::Vector2f origin ){
	std::stringstream ss;
	ss << str << NumberToFormatedString( number );
	PrintText( ss.str(), position, fontSize, color, origin );
}

void TextPrinter::Update(float deltaTime){
	for (int i = 0; i < m_Texts.size(); ++i){
		m_Texts[i].move(0, -100.0f * deltaTime);
		m_Texts[i].setColor(sf::Color(255, 255, 255, m_Texts[i].getColor().a * 0.99999f));
		m_TimeToLive[i] -= deltaTime;
	}

	for (int i = m_Texts.size() - 1; i >= 0; --i){
		if (m_TimeToLive[i] <= 0){
			m_Texts.erase(m_Texts.begin() + i);
			m_TimeToLive.erase(m_TimeToLive.begin() + i);
		}
	}

}

void TextPrinter::Draw(sf::RenderWindow& window){
	for (auto it : m_Texts){
		window.draw(it);
	}
	for (auto it : m_FrameTexts){
		window.draw(it);
	}

	m_FrameTexts.clear();
}

string TextPrinter::NumberToFormatedString( double number ) {
	std::stringstream ss;
	bool appendRemaining	= false;
	bool skipFraction		= false;
	bool printThreeDigits	= false;

	long long divisor	= 1e12L;
	long long parts	= ((long long)number) / divisor;
	if ( appendRemaining || parts > 0 ) {
		number -= parts * divisor;
		ss << ConditionalMakeThreeDigit( parts, printThreeDigits ) << ",";
		appendRemaining		= true;
		skipFraction		= true;
		printThreeDigits	= true;
	}

	divisor	= 1e9L;
	parts	= ((long long)number) / divisor;
	if ( appendRemaining || parts > 0 ) {
		number -= parts * divisor;
		ss << ConditionalMakeThreeDigit( parts, printThreeDigits ) << ",";
		appendRemaining		= true;
		skipFraction		= true;
		printThreeDigits	= true;
	}

	divisor	= 1e6L;
	parts	= ((long long)number) / divisor;
	if ( appendRemaining || parts > 0 ) {
		number -= parts * divisor;
		ss << ConditionalMakeThreeDigit( parts, printThreeDigits ) << ",";
		appendRemaining		= true;
		skipFraction		= true;
		printThreeDigits	= true;
	}

	divisor	= 1e3L;
	parts	= ((long long)number) / divisor;
	if ( appendRemaining || parts > 0 ) {
		number -= parts * divisor;
		ss << ConditionalMakeThreeDigit( parts, printThreeDigits ) << ",";
		appendRemaining		= true;
		printThreeDigits	= true;
	}

	divisor	= 1L;
	parts	= ((long long)number) / divisor;
	number -= parts * divisor;
	ss << ConditionalMakeThreeDigit( parts, printThreeDigits );

	number *= 10.0f;
	parts = ((long long)number) / 1L;
	if ( !skipFraction && parts > 0 ) {
		ss << "." << parts;
	}

	return ss.str();
}

string TextPrinter::ConditionalMakeThreeDigit( long number, bool doTheWork ) {
	std::stringstream ss;

	if ( doTheWork ) {
		if ( number < 100 ) {
			ss << "0";
		}
		if ( number < 10 ) {
			ss << "0";
		}
	}
	ss << number;

	return ss.str();
}