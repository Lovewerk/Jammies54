#include "CoreMinimal.h"
#include "BG_GameInstance.h"
#include "BG_Util.generated.h"

UENUM()
enum class EConditionalOutput : uint8
{
	Success,
	Failure
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

	UFUNCTION(BlueprintCallable, Category = "Bounced|Debug", BlueprintPure, meta = (WorldContext = "aWorldContextObject", Keywords = "debug", DefaultToSelf = "aWorldContextObject"))
		static bool IsDebug(const UObject* aWorldContextObject, const bool anAdditionalCondition = true);
};