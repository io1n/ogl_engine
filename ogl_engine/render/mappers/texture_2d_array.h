#ifndef TEXTURE_2D_ARRAY_H
#define TEXTURE_2D_ARRAY_H

#include "base_mapper.h"

class texture_2d_array : public base_mapper<texture_2d_array>
{
public:
	const attrib
		POS				= {0, 3, 1},
		TEX_COORD		= {3, 2, 1},
		COLOR			= {5, 1, 0},
		ALPHA			= {6, 1, 0},
		TEX_ID_LAYER	= {7, 1, 0};
};

#endif
