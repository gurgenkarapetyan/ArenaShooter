// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UHealthComponent;
class UTextRenderComponent;
class UWeaponComponent;

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All)

UCLASS()
class ARENASHOOTER_API AShooterBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AShooterBaseCharacter(const FObjectInitializer& ObjInit);

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Return Character running state. */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	FORCEINLINE bool IsRunning() const { return IsRunPressed && IsMovingForward && !GetVelocity().IsZero(); }
	
	/** Get character running direction for locomotion. */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;

	/** Get Character Health Component. */
	FORCEINLINE UHealthComponent* GetHealthComponent() const { return HealthComponent; }

	void SetPlayerColor(const FLinearColor& Color) const;
	
protected:
	virtual void BeginPlay() override;

	/** Handle Character death. */
	virtual void OnDeath();
	
private:
	/** Called for forward/backward input.
	 * @param Value movement input scale value and direction.
	 */
	void MoveForward(const float Value);

	/** Called for side to side input.
	 * @param Value movement input scale value and direction.
	 */
	void MoveRight(const float Value);
	
	/**
	* Rotate controller based on mouse Y movement.
	* @param Value The input value from mouse movement.
	*/
	void LookUp(const float Value);

	/**
	* Rotate controller based on mouse X movement.
	* @param Value The input value from mouse movement.
	*/
	void Turn(const float Value);

	/** Toggle Character running state. */
	void OnStartRunning();
	void OnStopRunning();
	
	/** Update Character display health.
	 * @param Health updated health to be displayed.
	 */
	void OnHealthChanged(float Health, float HealthDelta) const;

	/** Update Character health when landing on the ground.
	 * @param Hit Result describing the landing that resulted in a valid landing spot.
	 */
	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);
	
protected:
	/** Camera spring arm positioning the camera behind the Character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;
	
	/** Camera that follows the Character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComponent;

	/** Health Component. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHealthComponent* HealthComponent;

	/** Health Text to display above Character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTextRenderComponent* HealthTextComponent;

	/** Health Text to display above Character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWeaponComponent* WeaponComponent;
	
	/** Montage to play when Character dies. */
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	FVector2D LandedDamageVelocity = FVector2D(900.f, 1200.f);

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	FVector2D LandedDamage = FVector2D(10.f, 100.f);

	UPROPERTY(EditDefaultsOnly, Category = "Material")
	FName MaterialColorName = "Paint Color";
	
private:
	bool IsRunPressed = false;
	bool IsMovingForward = false;
};
