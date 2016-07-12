#include "runtime.hpp"

namespace rt
{

	void loop()
	{
		frame.emit();
		frame_early.emit();
		frame_late.emit();
		render.emit();
		post_render.emit();
		frame_end.emit();

		++frame_no;
	}

	// Triggered at next frame_early
	void frame_delay(size_t delay, frame_event::fn_type fn, void* data)
	{
		static std::priority_queue<frame_event> fd_queue;
		static int run_once = ([&]() {
			auto slot = [&]() -> void {
				if(fd_queue.empty()) {
					return;
				}

				while(fd_queue.top().target_frame <= frame_no) {
					fd_queue.top().call();
					fd_queue.pop();
				}
			};
			frame_early.connect(slot); // Permanently

			return 0;
		})();

		fd_queue.emplace(delay + frame_no, fn, data);
	}

	void frame_repeat(size_t delay, frame_event::fn_type fn, void* data)
	{
		static std::priority_queue<frame_event> fr_queue;
		static int run_once = ([&]() {
			auto slot = [&]() -> void {
				if(fr_queue.empty()) {
					return;
				}

				while(fr_queue.top().target_frame <= frame_no) {
					fr_queue.pop();
				}
				for(auto&& it : fr_queue) {
					it.call();
				}
			}
			frame_early.connect(slot);

			return 0;
		})();

		fd_queue.emplace(count + frame_no, fn, data);
	}

}
