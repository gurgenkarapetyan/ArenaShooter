#pragma once

class Utils
{
public:
	template <typename T>
	static T* GetPlayerComponent(AActor* Player)
	{
		if (Player == nullptr)
		{
			return nullptr;
		}

		return Cast<T>(Player->GetComponentByClass(T::StaticClass()));
	}
};
