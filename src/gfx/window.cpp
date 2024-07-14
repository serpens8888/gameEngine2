#include "window.hpp"

namespace gfx {

            window* window::get(i32 w, i32 h, std::string name){
                        static window* screen = new window(w,h,name);
                        return screen;
            }

            window::window(i32 width, i32 height, std::string name) : width{width}, height{height}, name{name} {
                        if(!glfwInit()){
                                    throw std::runtime_error("failed to initialize glfw");
                        }

                        monitor = glfwGetPrimaryMonitor();

                        if(!monitor){
                                    throw std::runtime_error("failed to get primary monitor");
                        }

                        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
                        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
                        screen = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr); //learn about vidmode and borderless fullscreen when the time comes, then change the 4th arg to monitor
                        
                        if(!screen){
                                    throw std::runtime_error("failed to create window");
                        }

            }
            
	    bool window::shouldClose(){
                        if(glfwGetKey(screen, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(screen) == true){
                                    return true;
                        }
                        return false;

            }

            window::~window(){
                        glfwDestroyWindow(screen);
                        glfwTerminate();
            }









} // namespace gfx
