#ifndef __QUEUE_HPP
#define __QUEUE_HPP

#include "../headers.hpp"

namespace gfx{

	struct queueFamilyIndices{
	std::optional<u32> graphicsFamily;

	bool isComplete();
	};

	struct queueFamily{
		
		queueFamily(VkPhysicalDevice GPU);
		~queueFamily();

		queueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		u32 queueFamilyCount;
		std::vector<VkQueueFamilyProperties> queueFamilies;
	

	};




} //gfx namespace



#endif
