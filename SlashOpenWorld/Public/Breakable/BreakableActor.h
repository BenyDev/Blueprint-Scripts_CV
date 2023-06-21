// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/HitInterface.h"
#include "BreakableActor.generated.h"

class UGeometryCollectionComponent;

UCLASS()
class SLASHOPENWORLD_API ABreakableActor : public AActor, public IHitInterface
{
	GENERATED_BODY()
	
public:	

	ABreakableActor();
	virtual void Tick(float DeltaTime) override;

	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;
	

protected:

	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UGeometryCollectionComponent* GeometryCollection;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* Box;

private:

	UWorld* World;

	bool bBroken = false;
	
	UPROPERTY(EditAnywhere, Category = "Breakable Properties")
		TArray<TSubclassOf<class ATresure>> TreasuerClasses;

		//TSubclassOf<class ATresure> TreasureClass;
};
