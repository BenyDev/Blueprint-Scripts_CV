// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "InputAction.h"
#include "CharacterTypes.h"
#include "SlashCharacter.generated.h"


class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
class AItem;
class UAnimMontage;



UCLASS()
class SLASHOPENWORLD_API ASlashCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ASlashCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

	// UInputAction //
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = input)
		UInputMappingContext* SlashMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = input)
		UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = input)
		UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = input)
		UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = input)
		UInputAction* RunAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = input)
		UInputAction* PickUpItemAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = input)
		UInputAction* MeleAttackAction;
	
	FORCEINLINE	void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
	FORCEINLINE EMovementStyle GetMovementStyle() const { return MovementStyle; }



	FORCEINLINE void SetRunningState(bool RunningState) { this->IsRunning = RunningState; }
	FORCEINLINE bool GetRunningState() const { return IsRunning; }

protected:

	virtual void BeginPlay() override;
	void EquipWeapon(AWeapon* Weapon);

	/**
	* Callbacks for input
	*/
	virtual void MeleAttack(const FInputActionValue& Value) override;
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void JumpAI();
	void PickUp(const FInputActionValue& Value);
	void Running(const FInputActionValue& Value);


	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EActionState ActionState = EActionState::EAS_Unoccupied;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAcces = "true"))
		EMovementStyle MovementStyle = EMovementStyle::EMS_WithoutWeapon;


	/**
	* Play montage functions
	*/

	void PlayEquipMontage(FName SectionName);
	




private:

	virtual void AttackEnd() override;
	virtual bool AllowToAttack() override;
	
	UPROPERTY(VisibleAnywhere, category = movement)
		bool IsRunning = false;

	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* Camera;

	UPROPERTY(VisibleInstanceOnly)
		AItem* OverlappingItem;

	UPROPERTY(EditDefaultsOnly, category = Montages)
		UAnimMontage* EquipMontage;




	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

};
