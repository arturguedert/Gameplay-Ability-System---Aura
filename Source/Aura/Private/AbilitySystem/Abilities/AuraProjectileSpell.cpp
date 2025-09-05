// Copyright Guedert Games


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include "Actors/AuraProjectile.h"
#include "Interaction/CombatInterface.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	UWorld* World = GetWorld();
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	const bool bIsServer = AvatarActor->HasAuthority();

	if (!IsValid(World) || !IsValid(ProjectileClass) || !IsValid(AvatarActor) || !bIsServer)
	{
		return;
	}

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(AvatarActor);
	if (!CombatInterface)
	{
		return;
	}

	const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	Rotation.Pitch = 0.f;

	FTransform SpawnTransform = FTransform();
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());

	AActor* OwningActor = GetOwningActorFromActorInfo();
	AAuraProjectile* Projectile = World->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform, OwningActor, Cast<APawn>(OwningActor), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	//TODO: Give the projectile a GameplayEffect Spect for causing damage.

	Projectile->FinishSpawning(SpawnTransform);
}