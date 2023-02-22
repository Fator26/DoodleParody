#include "GameEngine.hpp"

#include <memory>
#include <iostream>
#include "GameState.hpp"

GameEngine::GameEngine( const std::string& title, const unsigned int width, const unsigned int height, const unsigned int bpp, const bool fullscreen ) :
	m_running( false ),
	m_fullscreen( fullscreen )
{
	int flags = 0;

	if( fullscreen )
		flags = sf::Style::Fullscreen;
	else
		flags = sf::Style::Default;

	if( !mApplicationIcon.loadFromFile("res/jumpy.png") )
		std::cout << "Resource 'jumpy.png' is missing!" << std::endl;

	screen.create( sf::VideoMode( width, height, bpp ), title, flags );
	screen.setFramerateLimit( 60 );
	screen.setIcon( mApplicationIcon.getSize().x, mApplicationIcon.getSize().y, mApplicationIcon.getPixelsPtr() );

	std::cout << "GameEngine Init" << std::endl;
}

void GameEngine::Run( std::unique_ptr<GameState> state )
{
	m_running = true;
	
	states.push( std::move( state ) );
}

void GameEngine::NextState() 
{
	if ( !states.empty() )
	{
		std::unique_ptr<GameState> temp = states.top()->Next();

		if( temp != nullptr )
		{
			if( temp->isReplacing() )
				states.pop();
			else
				states.top()->Pause();
			
			states.push( std::move( temp ) );
		}
	}
}

void GameEngine::LastState()
{
	if ( !states.empty() )
	{
		states.pop();
	}

	if ( !states.empty() )
	{
		states.top()->Resume();
	}
}

void GameEngine::HandleEvents() 
{
	states.top()->HandleEvents( *this );
}

void GameEngine::Update() 
{
	states.top()->Update( *this );
}

void GameEngine::Draw() 
{
	states.top()->Draw( *this );
}

