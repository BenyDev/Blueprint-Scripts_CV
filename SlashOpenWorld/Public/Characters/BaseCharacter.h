// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "Interfaces/HitInterface.h"
#include "Components/AttributeComponent.h"
#include "BaseCharacter.generated.h"

class AWeapon;
class UInputAction;
class UHealthBarComponent;
class UAttributeComponent;
class UAnimeMontage;

UCLASS()
class SLASHOPENWORLD_API ABaseCharacter : public ACharacter, public IHitInterface
{
	GENERATED_BODY()



public:

	ABaseCharacter();
	virtual void Tick(float DeltaTime) override;
	


protected:

	// ABaseCharacter //
	virtual void MeleAttack(const FInputActionValue& Value);
	virtual void Die();

	virtual int32 PlayAttackMontage();
	virtual int32 PlayDeathMontage();
	virtual void HandleDamage(float DamageAmount);
	void PlayHitReactMontage(const FName& SelectionName);
	void DirectionalHitReact(const FVector& ImpactPoint);

	virtual bool AllowToAttack();
	bool IsAlive();
	

	void DisableCapsuleCollision();
	void PlayHitSound(const FVector& ImpactPoint);
	void PlayDeathSound(const FVector& ImpactPoint);
	void SpawnHitParticle(const FVector& ImpactPoint);
	void PlayMontageSection(UAnimMontage* Montage, const FName& SelectionName);
	
	int32 PlayRandomMontageSection(UAnimMontage* Montage, const TArray<FName>& SectionNames);


	UFUNCTION(BlueprintCallable)
		void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);

	UFUNCTION(BlueprintCallable)
		virtual void AttackEnd();

	// AActro //
	virtual void BeginPlay() override;

	// UAttributeComponent : UActorComponent //
	UPROPERTY(VisibleAnywhere, category = "Attribute")
		UAttributeComponent* Attribute;

	// AWeapon //
	UPROPERTY(VisibleAnywhere, category = "weapon")
		AWeapon* EquippedWeapon;

	// USoundBase //
	UPROPERTY(EditAnywhere, category = Combat)
		USoundBase* HitSound;

	UPROPERTY(EditAnywhere, category = "Combat")
		USoundBase* DeathSound;

	// UParticleSystem // 
	UPROPERTY(EditAnywhere, category = Combat)
		UParticleSystem* HitParticles;

private:

	UPROPERTY(EditDefaultsOnly, category = Combat)
		UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, category = Combat)
		UAnimMontage* HitReactMontage;

	UPROPERTY(EditDefaultsOnly, category = Combat)
		UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere, Category = Combat)
		TArray<FName> AttackMontageSections;

	UPROPERTY(EditAnywhere, Category = Combat)
		TArray<FName> DeathMontageSections;


};
