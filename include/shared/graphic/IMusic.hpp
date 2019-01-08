/*
** rtype
** Created on 26/11/18.
*/

#pragma once

namespace graphic
{
	class IMusic
	{
		public:
			virtual ~IMusic() = default;

			virtual void play() = 0;
			virtual void pause() = 0;
			virtual void stop() = 0;
			virtual void setVolume(float volume) = 0;
	};
}