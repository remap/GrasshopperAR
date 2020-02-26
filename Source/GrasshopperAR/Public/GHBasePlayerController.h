// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GHBasePlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FToggleMasterUiDelegate);

/**
 * 
 */
UCLASS()
class GRASSHOPPERAR_API AGHBasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere)
    TSubclassOf<APawn> ghPawnClass;
    
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FToggleMasterUiDelegate OnToggleMasterUiDelegate;
};
