// All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_WaitSpawnEnemies.generated.h"

class AWarriorEnemyCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitSpawnEnemiesDelegate, const TArray<AWarriorEnemyCharacter*>&, SpawnedEnemies);
/**
 * 
 */
UCLASS()
class WARRIOR_API UAbilityTask_WaitSpawnEnemies : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Warrior|Abilitytasks", meta = (DisplayName = "Wait Gamelay Event And Spawn Enemies", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true", NumToSpawn = "1", RnadomSpawnRadius = "200"))
	static UAbilityTask_WaitSpawnEnemies* WaitSpawnEnemies(
		UGameplayAbility* OwningAbility,
		FGameplayTag EventTag,
		TSoftClassPtr< AWarriorEnemyCharacter> SoftEnemyClassToSpawn,
		int32 NumToSpawn,
		const FVector& SpawnOrigin,
		float RnadomSpawnRadius
	);

	UPROPERTY(BlueprintAssignable)
	FWaitSpawnEnemiesDelegate OnSpawnFinished;

	UPROPERTY(BlueprintAssignable)
	FWaitSpawnEnemiesDelegate DidNotSpawn;

	// ~Begin UGameplayTask Interface
	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
	// ~End UGameplayTask Interface


private:
	FGameplayTag CachedEventTag;
	TSoftClassPtr< AWarriorEnemyCharacter> CachedSoftEnemyClassToSpawn;
	int32 CachedNumToSpawn;
	FVector CachedSpawnOrigin;
	float CachedRnadomSpawnRadius;
	FDelegateHandle DelegateHandle;

	void OnGameplayEventReceived(const FGameplayEventData* InPayload);
	void OnEnemyClassLoaded();
};
