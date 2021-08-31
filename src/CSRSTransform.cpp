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
CSRSTransform::CSRSTransform(const std::string& sRefFrame, std::string sCrs, std::string tCrs,
		double sEpoch, double tEpoch)
		:helmert_factory{sRefFrame}, s_crs{std::move(sCrs)}, t_crs{std::move(tCrs)}, s_epoch{sEpoch}, t_epoch{tEpoch}
{
	PJ_ptr P_in2cartesian{proj_create_crs_to_crs(this->ctx, this->s_crs.c_str(), cart_srid.c_str(), nullptr)};
	if (!P_in2cartesian) this->throwProjErr();
	else this->transforms.push_back(std::move(P_in2cartesian));

	PJ_ptr P_helmert{helmert_factory.create_pj(this->ctx)};
	if (!P_helmert) this->throwProjErr();
	else this->transforms.push_back(std::move(P_helmert));

	if (t_epoch>1 && std::abs(t_epoch-s_epoch)>1e-8) {
		// Grid shift transform
		char grid_shift_proj_str[256]{};
		sprintf(grid_shift_proj_str, "proj=deformation t_epoch=%.5f grids=ca_nrc_NAD83v70VG.tif inv", t_epoch);
		PJ_ptr grid_shift{proj_create(this->ctx, grid_shift_proj_str)};
		if (!grid_shift) this->throwProjErr();
		else this->transforms.push_back(std::move(grid_shift));
	}

	// Transform to user output CRS
	PJ_ptr P_csrs2out{proj_create_crs_to_crs(this->ctx, nad83csrs_srid.c_str(), this->t_crs.c_str(), nullptr)};
	if (!P_csrs2out) this->throwProjErr();
	else this->transforms.push_back(std::move(P_csrs2out));
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
	size_t stride = sizeof(coord);
	for (PJ_ptr& P: this->transforms) {
		proj_trans_generic(
				P.get(), direction,
				&(coord.xyzt.x), stride, 1,
				&(coord.xyzt.y), stride, 1,
				&(coord.xyzt.z), stride, 1,
				&(coord.xyzt.t), stride, 1
		);
	}
}
}