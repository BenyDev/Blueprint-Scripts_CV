

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Characters/CharacterTypes.h"
#include "Enemy.generated.h"



class UHealthBarComponent;
class UPawnSensingComponent;

UCLASS()
class SLASHOPENWORLD_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()


public:

	AEnemy();

	// AActor //
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Destroyed() override;

	// IHitInterface //
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;



protected:

	 // CharacterTypes //
	UPROPERTY(BlueprintReadOnly)
		EEnemyState EnemyState = EEnemyState::EES_Patrolling;

	UPROPERTY(BlueprintReadOnly)
		TEnumAsByte<EDeathPose> DeathPose;

	// AActor //
	virtual void BeginPlay() override;

	

	// BaseCharacter //
	virtual void Die() override;
	virtual void AttackEnd() override;
	virtual bool AllowToAttack() override;
	void MeleAttack();
	virtual void HandleDamage(float DamageAmount) override;
	virtual int32 PlayDeathMontage() override;

	

private:

	// AI Behavior //
	void CheckPatrolTarget();
	void CheckCombatTarget();
	void PatrolTimerFinished();
	void HideHealthBar();
	void ShowHealthBar();
	void LoseInterest();
	void StartPatrolling();
	void ChaseTarget();
	void ClearPatrolTimer();
	void StartAttackTimer();
	void ClearAttackTimer();
	void MoveToTarget(AActor* Target);
	void SpawnDefaultWeapon();
	UFUNCTION()
	void PawnSeen(APawn* SeenPawn); // CallBack for UPawnSeen in UPawnSensingComponent

	bool IsOutsideCombatRadius();
	bool IsOutsideAttackRadius();
	bool IsInsideAttackRadius();
	bool IsDead();
	bool IsChasing();
	bool IsAttacking();
	bool IsEngaged();
	bool InTargetRange(AActor* Target, double Radius);
	
	

	AActor* ChoosePatrolTarget();



	UPROPERTY(VisibleAnywhere)
		UHealthBarComponent* HealtBarWidget;

	UPROPERTY(VisibleAnywhere)
		UPawnSensingComponent* PawnSensing;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
		double AttackRadius = 130.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
		double CombatRadius = 1000.f;

	UPROPERTY()
		AActor* CombatTarget;

	UPROPERTY()
		class AAIController* EnemyController;

	

	//Current patrol target
	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
		AActor* PatrolTarget;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
		TArray<AActor*> PatrolTargets;

	UPROPERTY(EditAnywhere)
		double PatrolRadius = 200.f;

	UPROPERTY(EditAnywhere, Category = Combat)
		float PatrollingSpeed = 125.f;
	
	FTimerHandle PatrolTimer;

	UPROPERTY(EditAnywhere, category = "AI Navigation")
		float PatrolWaitMin = 5.f;

	UPROPERTY(EditAnywhere, category = "AI Navigation")
		float PatrolWaitMax = 10.f;

	FTimerHandle AttackTimer;

	UPROPERTY(EditAnywhere, Category = Combat)
		float AttackTimerMin = 0.5f;

	UPROPERTY(EditAnywhere, Category = Combat)
		float AttackTimerMax = 1.f;

	UPROPERTY(EditAnywhere, Category = Combat)
		float DeathLifeSpan = 8.f;

	UPROPERTY(EditAnywhere, Category = Combat)
		float ChasingSpeed = 300.f;


};
