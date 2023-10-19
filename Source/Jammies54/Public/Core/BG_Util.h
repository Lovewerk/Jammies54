#include "CoreMinimal.h"
#include "BG_GameInstance.h"
#include "BG_Util.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnFPSCalculatedSignature, const float&, aRate);

UENUM()
enum class EConditionalOutput : uint8
{
	Success,
	Failure
};

UENUM()
enum class EBoolOutput : uint8
{
	IsTrue,
	IsFalse
};

UCLASS()
class JAMMIES54_API UBG_Util : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//////////////////////////////////////////////////////////////////////////
   // Enum To String
   // Usage Example:
   //		FString EnumString = EnumToString( EnumValue );
   //////////////////////////////////////////////////////////////////////////
	template< typename T >
	static FString EnumToString(T EnumValue)
	{
		static_assert(TIsUEnumClass< T >::Value, "'T' template parameter to EnumToString must be a valid UEnum");
		return StaticEnum< T >()->GetNameStringByIndex((int32)EnumValue);
	}


	UFUNCTION(BlueprintCallable, Category = "Bounced|Core", meta = (WorldContext = "aWorldContextObject", Keywords = "game instance gameinstance", DefaultToSelf = "aWorldContextObject", ExpandEnumAsExecs = "someOutputs"))
		static UBG_GameInstance* GetGameInstance(const UObject* aWorldContextObject, EConditionalOutput& someOutputs);

	UFUNCTION(BlueprintCallable, Category = "Bounced|Debug", meta = (WorldContext = "aWorldContextObject", Keywords = "debug", DefaultToSelf = "aWorldContextObject", ExpandEnumAsExecs = "someOutputs"))
		static bool IsDebug(const UObject* aWorldContextObject, EBoolOutput& someOutputs, const bool anAdditionalCondition = true);

	UFUNCTION(BlueprintCallable, Category = "Bounced|Util", meta = (WorldContext = "aWorldContextObject", Keywords = "quit game exit", DefaultToSelf = "aWorldContextObject"))
		//making fade duration constref prevents showing a default value in blueprint?
		static void QuitGameWithFade(const UObject* aWorldContextObject, float aFadeDuration = 0.8f, float aWaitAfterFadeDuration = 0.5f);


	UFUNCTION(BlueprintCallable, Category = "Bounced|Util", meta = (WorldContext = "aWorldContextObject", AutoCreateRefTerm = "anFPSCallback"))
	static void TrackFPS_Trigger(const UObject* aWorldContextObject, const FOnFPSCalculatedSignature& anFPSCallback, UPARAM(ref) FTimerHandle& aTimerHandle); 
	
	static void TrackFPS(const TWeakObjectPtr<const UObject> aWorldContextObject, const FOnFPSCalculatedSignature& anFPSCallback, FTimerHandle& aTimerHandle);


};