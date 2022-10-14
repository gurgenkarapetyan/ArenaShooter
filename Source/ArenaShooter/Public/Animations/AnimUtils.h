#pragma once

class AnimUtils
{
public:
	/** static helper function to find anim notify in the animation.
	 * @param Animation to find the notify.
	 */
	template <typename T>
	static T* FindNotifyByClass(UAnimSequenceBase* Animation)
	{
		if (Animation == nullptr)
		{
			return nullptr;
		}
	
		const TArray<FAnimNotifyEvent> NotifyEvents = Animation->Notifies;
		for (const FAnimNotifyEvent NotifyEvent : NotifyEvents)
		{
			T* AnimNotify = Cast<T>(NotifyEvent.Notify);
			if (AnimNotify)
			{
				return AnimNotify;
			}
		}
		
		return nullptr;
	}
};
