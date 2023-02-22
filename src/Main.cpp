#include "GameEngine.hpp"
#include "IntroState.hpp"

int main ()
{
	GameEngine game( "Jumpy", 350U, 570U );
	game.Run( game.Build<IntroState>() );

	while( game.Running() )
	{
		game.NextState();
		game.HandleEvents();
		game.Update();
		game.Draw();
	}

    return 0;
}

