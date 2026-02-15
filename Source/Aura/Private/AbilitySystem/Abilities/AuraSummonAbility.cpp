// Copyright Votive Game Studio


#include "AbilitySystem/Abilities/AuraSummonAbility.h"

#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnAngle / NumMinions;
	
	const FVector LeftOfSpawnAngle = Forward.RotateAngleAxis(-SpawnAngle * 0.5f, FVector::UpVector);
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Location, Location + LeftOfSpawnAngle * MaxSpawnDistance, 5.f, FLinearColor::Green, 3.f);
	DrawDebugSphere(GetWorld(), Location + LeftOfSpawnAngle * MinSpawnDistance, 15.f, 12, FColor::Red, false, 3.f);
	DrawDebugSphere(GetWorld(), Location + LeftOfSpawnAngle * MaxSpawnDistance, 15.f, 12, FColor::Red, false, 3.f);
	
	for (int32 i = 0; i < NumMinions; ++i)
	{
		// TODO 
	}
	
	const FVector RightOfSpawnAngle = Forward.RotateAngleAxis(SpawnAngle * 0.5f, FVector::UpVector);
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Location, Location + RightOfSpawnAngle * MaxSpawnDistance, 5.f, FLinearColor::Blue, 3.f);
	DrawDebugSphere(GetWorld(), Location + RightOfSpawnAngle * MinSpawnDistance, 15.f, 12, FColor::Red, false, 3.f);
	DrawDebugSphere(GetWorld(), Location + RightOfSpawnAngle * MaxSpawnDistance, 15.f, 12, FColor::Red, false, 3.f);
	
	
	
	
	return TArray<FVector>();
}
