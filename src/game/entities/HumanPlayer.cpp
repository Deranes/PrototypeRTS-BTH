#include "HumanPlayer.h"

#include "../../input/GlobalMouse.h"
#include "Unit.h"

void HumanPlayer::Update( std::vector<Unit>& unitsFriendly, std::vector<Unit>& unitsHostile ) {
	if ( g_Mouse.RightClick() ) {
		Vector2f targetPosition = Vector2f( g_Mouse.Position().x, g_Mouse.Position().y );

		for ( auto& unit : unitsFriendly ) {
			unit.CommandMove( targetPosition );
		}
	}
}