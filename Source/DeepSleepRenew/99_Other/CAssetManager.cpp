// Fill out your copyright notice in the Description page of Project Settings.


#include "99_Other/CAssetManager.h"
#include "LogChannels.h"
#include "00_Character/02_Component/CGameplayTags.h"

UCAssetManager::UCAssetManager()
{
}

UCAssetManager& UCAssetManager::Get()
{
    check(GEngine);

    //우리는 AssetManager를 UEngine의 AssetManager의 class를 오버라이드 했기 때문에 GEngine에 AssetManager가 있음.
    if (UCAssetManager* Singleton = Cast<UCAssetManager>(GEngine->AssetManager))
    {
        return *Singleton;
    }
    //문제가 있음. 크래쉬 냄.
    UE_LOG(LogDeepsleep, Fatal, TEXT("invalid AssetManagerClassname in DefaultEngine.ini(project settings); it must be HakAssetManager"));

    //위의 UE_LOG의 Fatal로 인해서 Crash 나기 때문에 도달하지 않지만 컴파일을 위해 더미로 리턴.
    return *NewObject<UCAssetManager>();
}


PRAGMA_DISABLE_OPTIMIZATION //디벨로프로 하면 디버깅 된 것들을 최소한으로 저장함.(로딩이 빠르지만 디버깅을 못가지고 와서 안되는데)

void UCAssetManager::StartInitialLoading()
{
    Super::StartInitialLoading();
}
PRAGMA_ENABLE_OPTIMIZATION




bool UCAssetManager::ShouldLogAssetLoads()
{//인자를 가지고 와서 활용하기.
    const TCHAR* CommandLineContent = FCommandLine::Get();//커맨드 라인에서 비교를 해서 로그에셋 로드라는게 있으면 텍스트를 넣음. 
    static bool bLogAssetLoads = FParse::Param(CommandLineContent, TEXT("LogAssetLoads"));//그럼 이게 TRUE가 됨.
    return bLogAssetLoads;
}




UObject* UCAssetManager::SynchronousLoadAsset(const FSoftObjectPath& AssetPath)
{
    if (AssetPath.IsValid())//존재 하고 경로가 문제가 없으면 로딩하기.
    {
        //FScopeLogTime을 확인해보자. -> ShouldLoadAsset에서 동기 로딩을 진행 할때마다 몇초가 걸렸는지 진행을 할거임.

        TUniquePtr<FScopeLogTime> LogTimePtr;
        if (ShouldLogAssetLoads())
        {
            //단순히 로깅하면서, 초단위로 로깅 진행. //동기 로딩이 얼마나 걸렸는지 아래 함수를 통해서 체크. 
            LogTimePtr = MakeUnique<FScopeLogTime>(*FString::Printf(TEXT("Synchronous loaded assets [%s]"), *AssetPath.ToString()), nullptr);
        }
        //얘 덕분에 로딩이 너무 오래 걸릴 떄 로그가 남아서 개좋음. 이 부분에서는 동기로딩을 하면 안돼겠구나를 알고 뺄 수 있음. (에셋 로딩 관리)
        //무기만 있는 거도 아니고 아바타도 있을텐데, 이 모든 에셋을 모두 메모리에 담을 수는 없으니,
        //필요한 거만 먼저 로딩을 하는 것이 이 SynchronousLoadAsset() 함수의 역할.

        //여기서 두가지의 분기가 있다.
        //1. Assetmanager가 있으면, Assetmanager의 StreamableMawnager를 통해서 정적 로딩.
        //2. 아니면, FSoftObjectPath를 통해서 바로 정적 로딩 하기.
        if (UAssetManager::IsValid())
        {
            //GetStreamableManager()는 로딩을 해줌. -> TryLoad()는 진짜 느려서 진짜 에셋이 없을때 사용함. 
            return UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath);
        }

        //if asset manager is not ready, use LoadObject()
        //슥 보면 StaticLoadObject가 보인다.
        //참고로 항상 StaticLoadObject를 하기 전에 StaticFindObject를 통해서 호가인하고 실패하면 진짜로 로딩한다는 것.
        //TryLoad()는 진짜 느려서 진짜 에셋이 없을때 사용함. 
        return AssetPath.TryLoad();
    }

    return nullptr;
}

void UCAssetManager::AddLoadedAsset(const UObject* Asset)
{
    if (ensureAlways(Asset))
    {
        FScopeLock Lock(&SyncObject);
        LoadedAssets.Add(Asset);
    }
}
