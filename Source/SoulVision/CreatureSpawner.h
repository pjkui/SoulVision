// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CreatureAIController.h"
#include "CreatureSpawner.generated.h"

UCLASS()
class SOULVISION_API ACreatureSpawner : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawner, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* SpawnerBounds;

	TArray<ACreatureAIController*> SpawnedCreatures;

	FTimerHandle RetrySpawnTimer;

	uint8 SpawnTries = 0;
	
public:	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, NoClear, Category = "Spawner")
	TSubclassOf<class ABaseCreature> CreatureToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner", meta = (ClampMin = "0", ClampMax = "50", UIMin = "0", UIMax = "50"))
	int32 NumberOfCreatures = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner", meta = (ClampMin = "5", ClampMax = "100", UIMin = "5", UIMax = "100"))
	int32 MinLevel = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner", meta = (ClampMin = "5", ClampMax = "100", UIMin = "5", UIMax = "100"))
	int32 MaxLevel = 10;

	// Sets default values for this actor's properties
	ACreatureSpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when class default values are changed
	virtual void PostInitProperties() override;

	// Called when class values are changed in editor
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	void ValidateSpawnerValues();

	void InitSpawner();

	FORCEINLINE void RegisterCreature(ACreatureAIController* CreatureController)
	{
		SpawnedCreatures.Add(CreatureController);
	}

	FORCEINLINE void DeregisterCreature(ACreatureAIController* CreatureController)
	{
		SpawnedCreatures.Remove(CreatureController);	
	}
};
