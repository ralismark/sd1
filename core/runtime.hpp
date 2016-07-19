#pragma once

#include <functional>
#include <queue>

// All core running libs
#include "sigslots.hpp"

namespace rt
{

	size_t frame_no = 0; // at 30fps, int won't overflow until running for about 2 years

	// Sig order:
	// 1. frame       (user input, window events, etc.)
	// 2. frame_early (misc things)
	// 3. frame_late  (for physics etc.)
	// 4. render      (graphics + sound)
	// 5. post_render (whatever?)
	// 6. frame_end   (end stuff?)
	//    (SFML does framerate limiting)

	sig<> frame, frame_early, frame_late, render, post_render, frame_end;

	// Function to be executed by window loop
	void loop();

	// Frame-based timing
	class frame_event
	{
	public: // Statics
		typedef std::function<void(void*)> fn_type;
	public: // Variables
		fn_type fn;
		void* data;
		size_t target_frame;
	public: // Methods
		frame_event(size_t target, fn_type fn_init, void* data_init = 0);

		void call() const;

		// Prio-queue: `greatest' at front
		bool operator<(const frame_event& other);
	};

	// Exec after n frames
	void frame_delay(size_t delay, frame_event::fn_type fn, void* data = 0);
	void frame_repeat(size_t count, frame_event::fn_type fn, void* data = 0);
}
