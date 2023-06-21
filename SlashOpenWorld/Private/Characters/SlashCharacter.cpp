
#include "Characters/SlashCharacter.h"
#include "Editor/EditorEngine.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Items/Item.h"
#include "Items/Weapons/Weapon.h"
#include "Animation/AnimMontage.h"
#include "Components/BoxComponent.h"


// Sets default values
ASlashCharacter::ASlashCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetMesh()->SetWorldLocationAndRotation(FVector(0.f, 0.f, -90.f), FQuat(FRotator(0.f, -90.f, 0.f)));


	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility,ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);


	 CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	 CameraBoom->SetupAttachment(GetRootComponent());
	 CameraBoom->TargetArmLength = 450.f;
	 CameraBoom->SetRelativeRotation(FQuat(FRotator(-20.f,0.f,0.f)));

	 Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraView"));
	 Camera->SetupAttachment(CameraBoom);

}

void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("EngageableTarget"));

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(SlashMappingContext, 0);
		}

	}
	
}





void ASlashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{ 
		//Movement
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Move);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Running);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ASlashCharacter::JumpAI);
		//InterAction

		EnhancedInputComponent->BindAction(PickUpItemAction, ETriggerEvent::Triggered, this, &ASlashCharacter::PickUp);

		//Combat
		EnhancedInputComponent->BindAction(MeleAttackAction, ETriggerEvent::Triggered, this, &ASlashCharacter::MeleAttack);
		
		
		
	}

	//PlayerInputComponent->BindAction(FName("Jump"),IE_Pressed, this, &ACharacter::Jump);
	


}

void ASlashCharacter::GetHit_Implementation(const FVector& ImpactPoint)
{
	PlayHitSound(ImpactPoint);
	SpawnHitParticle(ImpactPoint);
}

void ASlashCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D CurrentValue = Value.Get<FVector2D>();
	if (ActionState == EActionState::EAS_Attacking) return;
	
		if (Controller)
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			AddMovementInput(ForwardDirection, CurrentValue.Y);
			AddMovementInput(RightDirection, CurrentValue.X);


		}
		
	
	
}

void ASlashCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();
	if (GetController())
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);

	}


}

void ASlashCharacter::JumpAI()
{
	this->Jump();
}

void ASlashCharacter::Running(const FInputActionValue& Value)
{
		this->SetRunningState(Value.Get<bool>());
}

void ASlashCharacter::MeleAttack(const FInputActionValue& Value)
{

	if (AllowToAttack())
	{
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}


}

bool ASlashCharacter::AllowToAttack()
{
	return ((ActionState == EActionState::EAS_Unoccupied) && (CharacterState != ECharacterState::ECS_Unequipped));
}

void ASlashCharacter::AttackEnd()
{
	
	ActionState = EActionState::EAS_Unoccupied;
}

void ASlashCharacter::PickUp(const FInputActionValue& Value)
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon)
	{
		EquipWeapon(OverlappingWeapon);
	}	
}

void ASlashCharacter::EquipWeapon(AWeapon* Weapon)
{
	Weapon->Equip(GetMesh(), FName("RightHandSocket"), this, this);
	CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
	MovementStyle = EMovementStyle::EMS_OneHandWeapon;
	OverlappingItem = nullptr;
	EquippedWeapon = Weapon;

}

void ASlashCharacter::PlayEquipMontage(FName SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	
	if (AnimInstance && EquipMontage)
	{
		
		AnimInstance->Montage_Play(EquipMontage);
		AnimInstance->Montage_JumpToSection(SectionName, EquipMontage);
		
		
	}
}



//void ASlashCharacter::MoveForward(float Value)
//{
//	if (Controller && (Value != 0.f)) {
//		
//		// Find out which way is forward
//	const FRotator ControlRotation = GetControlRotation();
//	const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
//
//	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
//	AddMovementInput(Direction, Value);
//	}
//}


//void ASlashCharacter::Turn(float Value)
//{
//	AddControllerYawInput(Value);
//	
//}
//
//void ASlashCharacter::LookUp(float Value)
//{
//	AddControllerPitchInput(Value);
//	
//	
//}
//
//void ASlashCharacter::MoveRight(float Value)
//{
//	if (Controller && (Value != 0.f)) {
//		
//		const FRotator ControlRotation = GetControlRotation();
//		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
//		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
//
//		AddMovementInput(Direction, Value);
//	}
//}
