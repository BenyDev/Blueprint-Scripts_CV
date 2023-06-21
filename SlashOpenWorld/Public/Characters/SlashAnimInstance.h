// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterTypes.h"
#include "SlashAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SLASHOPENWORLD_API USlashAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;
	
	UPROPERTY(BlueprintReadOnly)
		class ASlashCharacter* SlashCharacter;
	
	UPROPERTY(BlueprintReadOnly, category = movement)
		class UCharacterMovementComponent* SlashCharacterMovement;
	
	UPROPERTY(BlueprintReadOnly, category = movement)
		float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, category = movement)
		bool IsFalling;
	UPROPERTY(BlueprintReadOnly, category = movement)
		bool IsRunning;


	UPROPERTY(BlueprintReadOnly, category = "Movement | Character State")
		ECharacterState CharacterState;
	UPROPERTY(BlueprintReadOnly, category = "Movement | Movement State")
		EMovementStyle MovementStyle;
	
};
