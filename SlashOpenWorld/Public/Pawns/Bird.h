// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputAction.h"
#include "Bird.generated.h"



class UInputMappingContext;
class InputAction;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SLASHOPENWORLD_API ABird : public APawn
{
	GENERATED_BODY()

public:

	ABird();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = input)
		UInputMappingContext* BirdMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = input)
		UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = input)
		UInputAction* LookAction;

	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	


	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;
	
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* BirdMesh;

	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* Camera;

	
	


};
