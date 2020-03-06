// Fill out your copyright notice in the Description page of Project Settings.


#include "GHGameInstance.h"
#include "DDLog.h"


UGHGameInstance::UGHGameInstance()
:UGameInstance()
{
    DLOG_DEBUG("GAME INSTANCE DEFAULT CTOR");
}

UGHGameInstance::UGHGameInstance(const FObjectInitializer& ObjectInitializer)
:UGameInstance(ObjectInitializer)
{
    DLOG_DEBUG("GAME INSTANCE CTOR");
}

UGHGameInstance::~UGHGameInstance()
{
    DLOG_DEBUG("GAME INSTANCE DTOR");
}
