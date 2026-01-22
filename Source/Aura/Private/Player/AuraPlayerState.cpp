// Copyright Votive Sudios


#include "Player/AuraPlayerState.h"

AAuraPlayerState::AAuraPlayerState()
{
	// Set a high update frequency for player state to ensure smooth replication of important data.
	SetNetUpdateFrequency(100.f);
}
