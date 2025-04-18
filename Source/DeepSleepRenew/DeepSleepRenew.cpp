// Copyright Epic Games, Inc. All Rights Reserved.

#include "DeepSleepRenew.h"
#include "LogChannels.h"
#include "Modules/ModuleManager.h"

class FDeepSleepRenew : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

void FDeepSleepRenew::StartupModule()
{
	FDefaultGameModuleImpl::StartupModule();
	UE_LOG(LogDeepsleep, Display, TEXT("StartupModule started"));
}


void FDeepSleepRenew::ShutdownModule()
{
	FDefaultGameModuleImpl::ShutdownModule();
}
IMPLEMENT_PRIMARY_GAME_MODULE(FDeepSleepRenew, LyraClone, "LyraClone");