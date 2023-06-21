
#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Tresure.generated.h"

/**
 * 
 */
UCLASS()
class SLASHOPENWORLD_API ATresure : public AItem
{
	GENERATED_BODY()

protected:
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:

	UPROPERTY(EditAnywhere, category = Sounds)
		USoundBase* PickUpSound;
	UPROPERTY(EditAnywhere, category = "Treasure Properties")
	int32 Gold;

};
