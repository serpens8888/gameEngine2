#ifndef __WINDOW_HPP
#define __WINDOW_HPP

#include "../headers.hpp"

namespace gfx{

	struct window{
	
	static window* get(i32 w, i32 h, std::string name);
	window(const window&) = delete;
	window& operator=(const window&) = delete;

	bool shouldClose();


	GLFWmonitor* monitor;
	GLFWwindow * screen;
	const i32 width;
	const i32 height;
	std::string name;

	window(i32 width, i32 height, std::string name);
	~window();


	

	};



} //namespace gfx



#endif
