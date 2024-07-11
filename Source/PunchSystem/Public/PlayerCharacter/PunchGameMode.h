

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PunchGameMode.generated.h"


UCLASS()
class PUNCHSYSTEM_API APunchGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	
};
