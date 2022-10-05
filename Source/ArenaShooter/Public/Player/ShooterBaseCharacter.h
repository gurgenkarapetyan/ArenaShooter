// Arena Shooter

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class ARENASHOOTER_API AShooterBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterBaseCharacter(const FObjectInitializer& ObjInit);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Return Character running state. */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	FORCEINLINE bool IsRunning() const { return IsRunPressed && IsMovingForward && !GetVelocity().IsZero(); }
	
protected:
	// Called when the game starts or when spawned
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
	
protected:
	/** Camera spring arm positioning the camera behind the Character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;
	
	/** Camera that follows the Character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

private:
	bool IsRunPressed = false;
	bool IsMovingForward = false;
};
