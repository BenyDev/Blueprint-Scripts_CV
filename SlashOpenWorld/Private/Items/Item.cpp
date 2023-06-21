// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Containers/UnrealString.h"
#include "Characters/SlashCharacter.h"
#include "NiagaraComponent.h"


AItem::AItem()
{
 
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("ItemMesh")));
	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = ItemMesh;
	Sphere = CreateDefaultSubobject<USphereComponent>(FName(TEXT("SpherCollison")));
	Sphere->SetupAttachment(GetRootComponent());

	EmbersEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Embers"));
	EmbersEffect->SetupAttachment(GetRootComponent());
}




void AItem::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);

	Sphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnComponentEndOverlap);
	
}

void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//const FString OtherActorName = OtherActor->GetName();
	ASlashCharacter* SlashCharacter = Cast<ASlashCharacter>(OtherActor);

	if (SlashCharacter)
	{
		SlashCharacter->SetOverlappingItem(this);
	}

}

void AItem::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ASlashCharacter* SlashCharacter = Cast<ASlashCharacter>(OtherActor);

	if (SlashCharacter)
	{
		SlashCharacter->SetOverlappingItem(nullptr);
	}
}


void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;

	if (ItemState == EItemState::EIS_Hovering)
	{
		AddActorWorldOffset(FVector(0.f, 0.f, TransformedSin()));
	}
	


}

float AItem::TransformedSin()
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

float AItem::TransformedCos()
{
	return Amplitude * FMath::Cos(RunningTime * TimeConstant);
}

EItemState AItem::GetItemState() {
	return ItemState;
}

void AItem::SetItemState(EItemState eItemState) {
	ItemState = eItemState;
}



