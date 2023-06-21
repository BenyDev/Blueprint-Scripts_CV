// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class UStaticMeshComponent;
class USphereComponent;



enum class EItemState : int8
{
	EIS_Hovering,
	EIS_Equipped,
	
};


UCLASS()
class SLASHOPENWORLD_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AItem();

	virtual void Tick(float DeltaTime) override;

	template<typename T>
	T Avg(T First, T Second);
	
	EItemState GetItemState();
	void SetItemState(EItemState EItemState);

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
		float Amplitude = 0.25f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
		float TimeConstant = 5.f;
	
	UFUNCTION(BlueprintPure)
		float TransformedSin();

	UFUNCTION(BlueprintPure)
		float TransformedCos();

	float RunningTime;
	

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	 
	UFUNCTION()
	virtual void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* ItemMesh;

	EItemState ItemState = EItemState::EIS_Hovering;

	

	UPROPERTY(VisibleAnywhere)
		USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere)
		class UNiagaraComponent* EmbersEffect;

private:
	

	

	
	
	

};
template <typename T>
inline T AItem::Avg(T First, T Second)
{
	return(First + Second) / 2;
}