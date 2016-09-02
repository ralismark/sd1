#pragma once

#include <functional>

// All core running libs
#include "sigslots.hpp"
#include "resctl.hpp"

namespace rt
{

	/* frame count, beginning at 0 and incremented after each frame */
	extern size_t frame_no; // at 30fps, int won't overflow until running for about 2 years

	// Sig order:
	// 1. frame       (user input, window events, etc.)
	// 2. frame_early (misc things)
	// 3. frame_late  (for physics etc.)
	// 4. render      (graphics + sound)
	// 5. post_render (whatever?)
	// 6. frame_end   (end stuff?)
	//    (SFML does framerate limiting)

	/* hooks for the game look */
	extern sig<> frame, frame_early, frame_late, render, post_render, frame_end;

	// Function to be executed by window loop
	void loop();

	// Frame-based timing
	class frame_event
	{
	public: // Statics
		typedef std::function<void(void*)> fn_type;
	public: // Variables
		mutable fn_type fn; // Hack
		void* data;
		size_t target_frame;
	public: // Methods
		frame_event(size_t target, fn_type fn_init, void* data_init = 0);

		void call() const;

		// order for containers
		bool operator<(const frame_event& other) const;
	};

	// Exec after n frames
	/* executes fn with data after delay frames, during the frame signal */
	void frame_delay(size_t delay, frame_event::fn_type fn, void* data = 0);
	/* executes fn with data for each frame for count frames */
	void frame_repeat(size_t count, frame_event::fn_type fn, void* data = 0);
}
