#pragma once

#include "base_mapper.h"

class test_mapper : public base_mapper<test_mapper>
{
public:
	const attrib
		SHIT	= { 0, 2, 0 },
		ASS		= { 2, 3, 1 },
		SHITASS = { 5, 1, 2 };
};