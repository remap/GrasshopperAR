// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "GHBasePlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FToggleMasterUiDelegate);

/**
 * 
 */
UCLASS()
class GRASSHOPPERAR_API AGHBasePlayerController : public APlayerController
{
    AGHBasePlayerController();
    AGHBasePlayerController(const FObjectInitializer& ObjectInitializer);
    ~AGHBasePlayerController();
    
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere)
    TSubclassOf<APawn> ghPawnClass;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    APlayerStart *playerStart;
    
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FToggleMasterUiDelegate OnToggleMasterUiDelegate;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_IsAvatarHidden)
    bool isAvatarHidden;
    
    UFUNCTION(BlueprintCallable)
    void SetIsAvatarHidden(bool isHidden);
    
    UFUNCTION(BlueprintNativeEvent)
    void OnRepNotify_IsAvatarHidden();
    
    /**
     * BP wrapper for APlayerController::ClientTravel
     * Performs seamless travel.
     */
    UFUNCTION(BlueprintCallable)
    void TravelToMap(FString mapName);
    
private:
    
    UFUNCTION()
    void OnRep_IsAvatarHidden();
    
};
