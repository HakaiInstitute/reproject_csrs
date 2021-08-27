//
// Created by taylor on 2021-08-24.
//

#include <proj.h>
#include <stdexcept>
#include <utility>
#include <memory>
#include <functional>
#include "Nad83CSRSTransform.h"

namespace hakai_csrs {
// Constructor
Nad83CSRSTransform::Nad83CSRSTransform(const std::string& sRefFrame, std::string sCrs, std::string tCrs,
		double sEpoch, double tEpoch)
		:helmert{sRefFrame}, s_crs{std::move(sCrs)}, t_crs{std::move(tCrs)},
		 s_epoch{sEpoch}, t_epoch{tEpoch}
{
	PJ_ptr P_in2cartesian{proj_create_crs_to_crs(this->ctx, this->s_crs.c_str(), cart_srid.c_str(), nullptr)};
	if (!P_in2cartesian) this->throwProjErr();
	else this->transforms.push_back(std::move(P_in2cartesian));

	PJ_ptr P_helmert{helmert.create_pj(this->ctx)};
	if (!P_helmert) this->throwProjErr();
	else this->transforms.push_back(std::move(P_helmert));

	// Add epoch change transforms if target and source epoch are different
	if (std::abs(t_epoch-s_epoch)<1e-8) {
		PJ_ptr P_cartesian2latlng{
				proj_create_crs_to_crs(this->ctx, nad83csrs_srid.c_str(), latlng_srid.c_str(), nullptr)};
		if (!P_cartesian2latlng) this->throwProjErr();
		else this->transforms.push_back(std::move(P_cartesian2latlng));

		// TODO: Grid shift transform here
		// PJ *gridshift

		PJ_ptr latlng2out{proj_create_crs_to_crs(this->ctx, latlng_srid.c_str(), this->t_crs.c_str(), nullptr)};
		if (!latlng2out) this->throwProjErr();
		else this->transforms.push_back(std::move(latlng2out));
	}
	else {
		PJ_ptr P_cartesian2out{proj_create_crs_to_crs(this->ctx, nad83csrs_srid.c_str(), this->t_crs.c_str(), nullptr)};
		if (!P_cartesian2out) this->throwProjErr();
		else this->transforms.push_back(std::move(P_cartesian2out));
	}
}

Nad83CSRSTransform::~Nad83CSRSTransform()
{
	this->transforms.clear();
	proj_context_destroy(ctx);
	proj_cleanup();
}

void Nad83CSRSTransform::throwProjErr()
{
	const char* err = proj_errno_string(proj_context_errno(this->ctx));
	throw std::runtime_error(err);
}

void Nad83CSRSTransform::trans(PJ_COORD& coord, PJ_DIRECTION direction)
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