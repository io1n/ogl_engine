#ifndef TEXTURE_2D_ARRAY_H
#define TEXTURE_2D_ARRAY_H

#include "base_mapper.h"
#include <thread>
#include <chrono>

class texture_2d_array : public base_mapper<texture_2d_array> {
public:
	const uint32_t
		POS				= 0x01030000,
		TEX_COORD		= 0x01020003,
		COLOR			= 0x00010005,
		ALPHA			= 0x00010006,
		TEX_ID_LAYER	= 0x00010007;
};

#endif
