#pragma once

class Utils
{
public:
	template <typename T>
	static T* GetPlayerComponent(APawn* PlayerPawn)
	{
		if (PlayerPawn == nullptr)
		{
			return nullptr;
		}

		return Cast<T>(PlayerPawn->GetComponentByClass(T::StaticClass()));
	}
};
