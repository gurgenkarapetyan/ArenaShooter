// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UHealthComponent;
class UTextRenderComponent;

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

	FORCEINLINE UHealthComponent* GetHealthComponent() const { return HealthComponent; }

protected:
	virtual void BeginPlay() override;

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
	
	/** Handle Character death. */
	void OnDeath();

	/** Update Character display health.
	 * @param Health updated health to be displayed.
	 */
	void OnHealthChanged(float Health) const;

protected:
	/** Camera spring arm positioning the camera behind the Character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;
	
	/** Camera that follows the Character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	/** Health Component. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UHealthComponent* HealthComponent;

	/** Health Text to display above Character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathAnimMontage;
	
private:
	bool IsRunPressed = false;
	bool IsMovingForward = false;
};
