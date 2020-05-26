// Fill out your copyright notice in the Description page of Project Settings.


#include "ARBasePlayerController.h"
#include "ARBlueprintLibrary.h"

void
AARBasePlayerController::setArAlignment(FTransform transform)
{
    ArAlignment = transform;
    UARBlueprintLibrary::SetAlignmentTransform(ArAlignment);
}

void
AARBasePlayerController::updateArAlignment(FTransform transform)
{
    FTransform newT;
    FTransform::Multiply(&newT, &ArAlignment, &transform);
    
    setArAlignment(newT);
}
