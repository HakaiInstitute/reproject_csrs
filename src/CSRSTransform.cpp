//
// Created by taylor on 2021-08-24.
//

#include <proj.h>
#include <stdexcept>
#include <utility>
#include <memory>
#include <functional>
#include "CSRSTransform.h"

namespace hakai_csrs {
// Constructor
CSRSTransform::CSRSTransform(const std::string& sRefFrame, std::string sCrs, double sEpoch, double tEpoch,
		std::string tVd, std::string outCoords)
		:helmert_factory{sRefFrame}, s_crs{std::move(sCrs)}, s_epoch{sEpoch}, t_epoch{tEpoch!=0 ? tEpoch : sEpoch},
		 t_vd{std::move(tVd)}, out{std::move(outCoords)}
{
	// 1. ITRFxx Ellips -> NAD83(CSRS) Ellips
	PJ_ptr P_in2cartesian{proj_create_crs_to_crs(this->ctx, this->s_crs.c_str(), "+proj=cart +ellps=GRS80", nullptr)};
	if (!P_in2cartesian) this->throwProjErr();
	else this->transforms.push_back(std::move(P_in2cartesian));

	PJ_ptr P_helmert{helmert_factory.create_pj(this->ctx)};
	if (!P_helmert) this->throwProjErr();
	else this->transforms.push_back(std::move(P_helmert));

	// 2. NAD83(CSRS) Ellips s_epoch -> NAD83(CSRS) Ellips t_epoch
	if (std::abs(t_epoch-s_epoch)>1e-8) {
		// Grid shift transform
		char grid_shift_proj_str[256]{};
		sprintf(grid_shift_proj_str, "+inv +proj=deformation +t_epoch=%.5f +grids=ca_nrc_NAD83v70VG.tif", t_epoch);
		PJ_ptr grid_shift{proj_create(this->ctx, grid_shift_proj_str)};
		if (!grid_shift) this->throwProjErr();
		else this->transforms.push_back(std::move(grid_shift));
	}

	// Convert cartographic coords to lonlat in radians
	PJ_ptr P_lonlat_rad{proj_create(this->ctx, "+inv +proj=cart +ellps=GRS80")};
	if (!P_lonlat_rad) this->throwProjErr();
	else this->transforms.push_back(std::move(P_lonlat_rad));

	// 3. NAD83(CSRS) Ellips t_epoch -> NAD83(CSRS) Orthometric t_epoch
	if (!t_vd.empty()) {
		if (t_vd=="cgvd2013_cgg2013a") {
			// Note: Assumes input is EPSG:8251 (NAD83(CSRS)v6), but we're passing EPSG:8254 (NAD83(CSRS)v7).
			PJ_ptr P{proj_create(this->ctx, "+inv +proj=vgridshift +grids=ca_nrc_CGG2013n83.tif +multiplier=1")};
			if (!P) throwProjErr();
			else this->transforms.push_back(std::move(P));
		}
		else if (t_vd=="cgvd28") {
			// Note: Assumes input is EPSG:4955 (NAD83(CSRS)), but we're passing EPSG:8254 (NAD83(CSRS)v7).
			PJ_ptr P{proj_create(this->ctx, "+inv +proj=vgridshift +grids=ca_nrc_HT2_2010v70.tif +multiplier=1")};
			if (!P) throwProjErr();
			else this->transforms.push_back(std::move(P));
		}
		else {
			throw std::runtime_error("Invalid vertical datum name. Must be one of [cgvd2013_cgg2013a, cgvd28]");
		}
	}

	// Final transform to output
	if (out=="geog") {
		// Convert lonlat in radians to latlon in degrees
		PJ_ptr P_lonlat_rad_to_latlon_deg{proj_create(this->ctx,
				"+proj=pipeline +step +proj=unitconvert +xy_in=rad +xy_out=deg +step +proj=axisswap +order=2,1")};
		if (!P_lonlat_rad_to_latlon_deg) throwProjErr();
		else this->transforms.push_back(std::move(P_lonlat_rad_to_latlon_deg));
	}
	else if (out=="cart") {
		// Convert lonlat in radians to cartographic coords
		PJ_ptr P_csrs2out{proj_create(this->ctx, "+proj=cart")};
		if (!P_csrs2out) this->throwProjErr();
		else this->transforms.push_back(std::move(P_csrs2out));
	}
	else if ((std::string)out.substr(0, 3)=="utm") {
		// Transform to UTM coordinates
		char out_str[128];

		try {
			int zone = std::stoi((std::string)out.substr(3));
			sprintf(out_str, "+proj=utm +zone=%d", zone);
		}
		catch (...) {
			throw std::runtime_error("Invalid UTM zone specified in 'out'");
		}

		PJ_ptr P_csrs2out{proj_create(this->ctx, out_str)};
		if (!P_csrs2out) this->throwProjErr();
		else this->transforms.push_back(std::move(P_csrs2out));
	}
	else {
		throw std::runtime_error("Invalid 'outCoords' specified. Should be one of 'geog', 'cart', 'utmX'");
	}
}

CSRSTransform::~CSRSTransform()
{
	this->transforms.clear();
	proj_context_destroy(ctx);
	proj_cleanup();
}

void CSRSTransform::throwProjErr()
{
	const char* err = proj_errno_string(proj_context_errno(this->ctx));
	throw std::runtime_error(err);
}

void CSRSTransform::trans(PJ_COORD& coord, PJ_DIRECTION direction)
{
	for (PJ_ptr& P: this->transforms) {
		coord = proj_trans(P.get(), direction, coord);
	}
}

void CSRSTransform::backward(PJ_COORD& coord)
{
	// Reverse the transforms list
	std::reverse(this->transforms.begin(), this->transforms.end());

	trans(coord, PJ_INV);

	// Un-reverse the transforms list
	std::reverse(this->transforms.begin(), this->transforms.end());
}
}