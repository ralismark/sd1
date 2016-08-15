#include "runtime.hpp"

namespace
{

	std::multiset<rt::frame_event> fd_queue;

	void fd_runner()
	{
		if(fd_queue.empty()) {
			return;
		}

		while(fd_queue.begin()->target_frame <= rt::frame_no) {
			auto fn = fd_queue.begin()->fn;
			fn(fd_queue.begin()->data);
			fd_queue.erase(fd_queue.begin());
		}
	}

	std::multiset<rt::frame_event> fr_queue;

	void fr_runner()
	{
		if(fr_queue.empty()) {
			return;
		}

		while(fr_queue.begin()->target_frame <= rt::frame_no) {
			fr_queue.erase(fr_queue.begin());
		}
		for(const auto& it : fr_queue) {
			it.call();
		}
	}

}

namespace rt
{

	size_t frame_no = 0;
	
	sig<> frame, frame_early, frame_late, render, post_render, frame_end;

	frame_event::frame_event(size_t target, fn_type fn_init, void* data_init)
		: fn(fn_init), data(data_init), target_frame(target)
	{ ; }

	void frame_event::call() const
	{
		fn(data);
	}

	bool frame_event::operator<(const frame_event& other) const
	{
		return target_frame < other.target_frame;
	}

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
		static bool run_once = false;
		if(!run_once) {
			run_once = true;
			frame_early.connect(fd_runner);
		}

		fd_queue.emplace(delay + frame_no, fn, data);
	}

	void frame_repeat(size_t count, frame_event::fn_type fn, void* data)
	{
		static bool run_once = false;
		if(!run_once) {
			run_once = true;
			frame_early.connect(fr_runner);
		}

		fr_queue.emplace(count + frame_no, fn, data);
	}

}
