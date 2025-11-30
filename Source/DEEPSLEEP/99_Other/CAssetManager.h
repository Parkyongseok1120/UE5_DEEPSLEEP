// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "CAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class DEEPSLEEP_API UCAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	UCAssetManager();

	static UCAssetManager& Get();

	virtual void StartInitialLoading() override;

	//해당 함수는 FScopeLogTime을 사용할지 않을지 유무를 판단하기 위해서 사용.
	//굳이 클론 코딩할 필요는 없긴 하지만, 알아두면 좋은 점이 있음. 
	static bool ShouldLogAssetLoads();

	static UObject* SynchronousLoadAsset(const FSoftObjectPath& AssetPath);

	//GetAsset은 정적 로딩으로 BP class와 Object를 로딩.
	//주목해야 할 부분은 bKeepInMemory

	template <typename AssetType> //cpp에 정의를 할 수 있긴한데 좀 불편함. 컴파일 단게에서 코드로 만들어져서 무조건 웬만하면 헤더파일에서 항상 템플릿을 만들어줘야 함.
	static AssetType* GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bkeepInMemory = true);

	template <typename AssetType>
	static TSubclassOf<AssetType> GetSubclass(const TSoftObjectPtr<AssetType>& AssetPointer, bool bkeepInMemory = true);

	//[THREAD-SAFE] 메모리에 로딩된 에셋 캐싱
	void AddLoadedAsset(const UObject* Asset);

	//GC의 대상
	UPROPERTY()
	TSet<TObjectPtr<const UObject>> LoadedAssets; //UObject를 Set으로 저장.

	//Object 단위 Locking
	FCriticalSection SyncObject;
};




template <typename AssetType> //얘는 AssetType이라는 거 밖에 없음.(아래 인자)
AssetType* UCAssetManager::GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bkeepInMemory)
{
	AssetType* LoadedAsset = nullptr;
	const FSoftObjectPath& AssetPath = AssetPointer.ToSoftObjectPath();//에셋의 경로를 가지고 온다.
	if (AssetPath.IsValid())
	{
		LoadedAsset = AssetPointer.Get();
		//Get()이 중요함. 소프트 오브젝트 패스는 로딩이 되어있다? 바로 가지고옴. / 반대로 안되어있으면 null을 반환. 
		if (!LoadedAsset)
		{
			//그러면 동기 로딩을 진행.
			LoadedAsset = Cast<AssetType>(SynchronousLoadAsset(AssetPath));//마음대로 삭제가 되면 안되니 에셋들은 가비지 컬렉션으로 관리를 하니까 저장을 위에 SET LoadedAsset에 캐싱용도로 저장.
			ensureAlwaysMsgf(LoadedAsset, TEXT("Failed to load asset [%s]"), *AssetPointer.ToString());
		}

		//웬만해서는 수정할 일이 없으니 bKeepInMemory는 true임.
		if (LoadedAsset && bkeepInMemory)
		{
			//여기서 AddLoadAsset은 메모리에 상주하기 위한 장치라고 생각하면 됨.
			// - 한번 등록 되면 직접 내리지 않는 한 Unload가 되지 않음.(==캐싱)
			Get().AddLoadedAsset(Cast<UObject>(LoadedAsset)); //래핑을 굳이 한번더 하는데. FScopeLock이 있음.
			//FScopelock이란...?  절차적으로 한명씩만 들어와서 로딩해라. ㅋㅋㅋ 위에 크리티컬 섹션 변수가 하나의 자물쇠.
			//하나를 열면 열쇠를 반납. 그다음에 한테 또 열쇠를 쥐어주고 다시로드, 다시 반납을 반복. 그래서 따로 락을 걸고 함. 
		}
	}
	return LoadedAsset;
}

template <typename AssetType>//얘는 TSubclassOf이라는 거 밖에 없음.(아래 인자)
TSubclassOf<AssetType> UCAssetManager::GetSubclass(const TSoftObjectPtr<AssetType>& AssetPointer, bool bkeepInMemory)
{
	TSubclassOf<AssetType> LoadedSubclass;

	const FSoftObjectPath& AssetPath = AssetPointer.ToSoftObjectPath();
	if (AssetPath.IsValid())
	{
		LoadedSubclass = AssetPointer.Get();
		if (!LoadedSubclass)
		{
			LoadedSubclass = Cast<AssetType>(SynchronousLoadAsset(AssetPath));
			ensureAlwaysMsgf(LoadedSubclass, TEXT("Failed to load asset [%s]"), *AssetPointer.ToString());
		}
		if (LoadedSubclass && bkeepInMemory)
		{
			Get().AddLoadedAsset(Cast<UObject>(LoadedSubclass));
		}
	}
	return LoadedSubclass;
}
