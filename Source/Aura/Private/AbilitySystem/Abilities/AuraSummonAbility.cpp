// Copyright Votive Game Studio


#include "AbilitySystem/Abilities/AuraSummonAbility.h"


TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnAngle / NumMinions;
	
	const FVector LeftOfSpawnAngle = Forward.RotateAngleAxis(-SpawnAngle * 0.5f, FVector::UpVector);
	
	TArray<FVector> SpawnLocations;
	
	for (int32 i = 0; i < NumMinions; ++i)
	{
		const FVector Direction = LeftOfSpawnAngle.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);
		
		// Perform a line trace to find the ground below the chosen spawn location 
		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, ChosenSpawnLocation + FVector(0.f, 0.f, 500.f), ChosenSpawnLocation - FVector(0.f, 0.f, 500.f), ECC_Visibility);
		if (Hit.bBlockingHit)
		{
			// If the line trace hits the ground, use the impact point as the spawn location
			ChosenSpawnLocation = Hit.ImpactPoint;
		}
		SpawnLocations.Add(ChosenSpawnLocation);
	}
	
	return SpawnLocations;
}
