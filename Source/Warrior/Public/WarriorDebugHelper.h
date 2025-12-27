// No Copyright

#pragma once

namespace Debug
{
	static void Print(const FString& Message, const FColor& Color = FColor::MakeRandomColor(), int32 InKey = -1)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, 10.f, Color, Message);

			UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
		}
	}

	static void Print(const FString& FloatTitle, float FloatValueToPrint, const FColor& Color = FColor::MakeRandomColor(), int32 InKey = -1)
	{
		if (GEngine)
		{
			const FString Message = FString::Printf(TEXT("%s: %f"), *FloatTitle, FloatValueToPrint);

			GEngine->AddOnScreenDebugMessage(InKey, 10.f, Color, Message);

			UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
		}
	}
}
