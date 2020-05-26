// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GHBasePlayerController.h"
#include "ARBasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GRASSHOPPERAR_API AARBasePlayerController : public AGHBasePlayerController
{
	GENERATED_BODY()
	
public:
    UPROPERTY(BlueprintReadOnly)
    FTransform ArAlignment;
    
    UFUNCTION(BlueprintCallable)
    void setArAlignment(FTransform transform);
    
    UFUNCTION(BlueprintCallable)
    void updateArAlignment(FTransform transform);
};
