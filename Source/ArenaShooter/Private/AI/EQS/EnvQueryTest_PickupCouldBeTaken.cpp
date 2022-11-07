// Arena Shooter

#include "AI/EQS/EnvQueryTest_PickupCouldBeTaken.h"

#include "BasePickUp.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"

UEnvQueryTest_PickupCouldBeTaken::UEnvQueryTest_PickupCouldBeTaken(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
	SetWorkOnFloatValues(false);
}

void UEnvQueryTest_PickupCouldBeTaken::RunTest(FEnvQueryInstance& QueryInstance) const
{
	Super::RunTest(QueryInstance);
	UObject* DataOwner = QueryInstance.Owner.Get();
	BoolValue.BindData(DataOwner, QueryInstance.QueryID);
	const bool bWantsBeTakable = BoolValue.GetValue();
	
	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex());
		ABasePickUp* PickUpActor = Cast<ABasePickUp>(ItemActor);
		if (PickUpActor == nullptr)
		{
			continue;
		}

		const bool bCouldBeTaken = PickUpActor->CouldBeTaken();
		It.SetScore(TestPurpose, FilterType, bCouldBeTaken, bWantsBeTakable);
	}
}
