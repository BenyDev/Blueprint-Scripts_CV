

#include "Items/Tresure.h"
#include "Characters/SlashCharacter.h"
#include "Kismet/GameplayStatics.h"



void ATresure::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASlashCharacter* SlashCharacter = Cast<ASlashCharacter>(OtherActor);

	if (SlashCharacter)
	{
		if (PickUpSound) {
			UGameplayStatics::PlaySoundAtLocation(
			this,
			PickUpSound,
			GetActorLocation()
				);
		}
		Destroy();
	}
}
