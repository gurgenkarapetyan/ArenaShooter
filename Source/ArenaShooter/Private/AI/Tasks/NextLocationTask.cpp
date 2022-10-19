// Arena Shooter


#include "AI/Tasks/NextLocationTask.h"

UNextLocationTask::UNextLocationTask()
{
}

EBTNodeResult::Type UNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
