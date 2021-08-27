//
// Created by taylor on 2021-08-24.
//

#ifndef HAKAI_LAS2CSRS_NAD83CSRSTRANSFORM_H
#define HAKAI_LAS2CSRS_NAD83CSRSTRANSFORM_H

#include <string>
#include <utility>
#include <proj.h>
#include <vector>
#include "Transform.h"
#include "constants.h"
#include "Helmert.h"

namespace hakai_csrs {
// Custom smart pointer for PJ transformation objects
struct PJ_deleter { void operator()(PJ* P) { proj_destroy(P); }};
typedef std::unique_ptr<PJ, PJ_deleter> PJ_ptr;

class Nad83CSRSTransform : public Transform {
private:
	PJ_CONTEXT* ctx{proj_context_create()};

	Helmert helmert;					// Hold helmert transform params
	std::string s_crs;                  // e.g. EPSG:4326
	std::string t_crs{nad83csrs_srid};  // e.g. EPSG:3157
	double s_epoch;                     // e.g. 2020.5342
	double t_epoch;                     // e.g. 1997.0000

	std::vector<PJ_ptr> transforms;

	void throwProjErr();

	void trans(PJ_COORD& coord, PJ_DIRECTION direction);

public:
	// Constructor
	Nad83CSRSTransform(const std::string& sRefFrame, std::string sCrs, std::string tCrs, double sEpoch,
			double tEpoch);

	// Destructor
	virtual ~Nad83CSRSTransform();

	// Transform functions
	void forward(PJ_COORD& coord) override { trans(coord, PJ_FWD); }
	void backward(PJ_COORD& coord) override { trans(coord, PJ_INV); }
};
}

#endif //HAKAI_LAS2CSRS_NAD83CSRSTRANSFORM_H
