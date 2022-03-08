//
// Created by taylor on 2021-09-03.
//

#include <stdexcept>
#include <proj.h>
#include "VerticalGridShiftFactory.h"

namespace hakai_csrs {

VerticalGridShiftFactory::VerticalGridShiftFactory(const std::string& geoid)
{
	if (geoid=="ht2_2010v70") grid_shift_file = "ca_nrc_HT2_2010v70.tif";
	else if (geoid=="cgg2013a") grid_shift_file = "ca_nrc_CGG2013an83.tif";
	else if (geoid.empty()) grid_shift_file = "";
	else throw std::runtime_error("Invalid Geoid name for vertical grid shift.");
}

PJ* VerticalGridShiftFactory::create_pj(PJ_CONTEXT* ctx) const
{
	if (grid_shift_file.empty())
		return proj_create(ctx, "+proj=noop");

	char proj_str[256];
	sprintf(proj_str, "+inv +proj=vgridshift +grids=%s +multiplier=1", grid_shift_file.c_str());
	return proj_create(ctx, proj_str);
}

}
