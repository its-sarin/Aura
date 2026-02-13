// Copyright Votive Studios


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Aura/Public/AuraGameplayTags.h"


void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	// Get the socket location from which to spawn the projectile
	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(
		GetAvatarActorFromActorInfo(), 
		FAuraGameplayTags::Get().CombatSocket_Weapon);
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
		
	// Set up spawn transform
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());
		
	// Spawn projectile deferred to allow for initialization
	AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
		ProjectileClass, 
		SpawnTransform, 
		GetAvatarActorFromActorInfo(), 
		Cast<APawn>(GetAvatarActorFromActorInfo()), 
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		
	// Create damage effect spec handle
	const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContextHandle);
		
	// Set damage magnitude via SetByCaller
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
		
	// Iterate over all defined Damage Types and assign their scaled magnitudes to the effect spec
	for (TTuple<FGameplayTag, FScalableFloat>& DamageTypePair : DamageTypes)
	{
		// -- Scale damage with ability level
		const float ScaledDamageTypeValue = DamageTypePair.Value.GetValueAtLevel(GetAbilityLevel());
		// -- Assign the scaled damage to the effect spec
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DamageTypePair.Key, ScaledDamageTypeValue);
	}
		
	// Assign the damage effect spec handle to the projectile
	Projectile->DamageEffectSpecHandle = SpecHandle;
		
	// Finish spawning the projectile
	Projectile->FinishSpawning(SpawnTransform);
}
