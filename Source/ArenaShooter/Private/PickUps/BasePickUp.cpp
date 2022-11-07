// Arena Shooter


#include "PickUps/BasePickUp.h"

#include "Components/SphereComponent.h"

ABasePickUp::ABasePickUp()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	CollisionComponent->InitSphereRadius(50.f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);
}

void ABasePickUp::BeginPlay()
{
	Super::BeginPlay();
	check(CollisionComponent);

	GenerateRotationYaw();
}

void ABasePickUp::GenerateRotationYaw()
{
	const float Direction = FMath::RandBool() ? 1.f : -1.f;
	RotationYaw = FMath::RandRange(1.f, 2.f) * Direction;
}

void ABasePickUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	APawn* const PlayerPawn = Cast<APawn>(OtherActor);
	if (GivePickUpTo(PlayerPawn))
	{
		PickUpWasTaken();
	}
}

void ABasePickUp::PickUpWasTaken() 
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	if (!GetRootComponent())
	{
		return;
	}
	
	GetRootComponent()->SetVisibility(false, true);
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ABasePickUp::Respawn, RespawnTime);
}

void ABasePickUp::Respawn()
{
	GenerateRotationYaw();
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	if (!GetRootComponent())
	{
		return;
	}
	
	GetRootComponent()->SetVisibility(true, true);
}


void ABasePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.f, RotationYaw, 0.f));
}

bool ABasePickUp::CouldBeTaken() const
{
	// return GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
	return bCouldBeTaken;
}
