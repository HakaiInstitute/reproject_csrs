//
// Created by taylor on 2021-08-24.
//

#ifndef REPROJECT_CSRS_CSRSTRANSFORM_H
#define REPROJECT_CSRS_CSRSTRANSFORM_H

#include <string>
#include <utility>
#include <proj.h>
#include <vector>
#include "Transform.h"
#include "constants.h"
#include "HelmertFactory.h"

namespace hakai_csrs {
// Custom smart pointer for PJ transformation objects
struct PJ_deleter { void operator()(PJ* P) { proj_destroy(P); }};
typedef std::unique_ptr<PJ, PJ_deleter> PJ_ptr;

class CSRSTransform : public Transform {
private:
	PJ_CONTEXT* ctx{proj_context_create()};

	HelmertFactory helmert_factory;		// Helmert transform params
	std::string s_crs;                  // e.g. EPSG:4326
	std::string t_crs{nad83csrs_srid};  // e.g. EPSG:3157
	double s_epoch;                     // e.g. 2020.5342
	double t_epoch;                     // e.g. 1997.0000

	std::vector<PJ_ptr> transforms;

	void throwProjErr();

	void trans(PJ_COORD& coord, PJ_DIRECTION direction);

public:
	// Constructor
	CSRSTransform(const std::string& sRefFrame, std::string sCrs, std::string tCrs, double sEpoch,
			double tEpoch);

	// Destructor
	virtual ~CSRSTransform();

	// Transform functions
	void forward(PJ_COORD& coord) override { trans(coord, PJ_FWD); }
	void backward(PJ_COORD& coord) override { trans(coord, PJ_INV); }
};
}

#endif //REPROJECT_CSRS_CSRSTRANSFORM_H
