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
#include "HelmertFactory.h"

namespace hakai_csrs {
// Custom smart pointer for PJ transformation objects
struct PJ_deleter { void operator()(PJ* P) { proj_destroy(P); }};
typedef std::unique_ptr<PJ, PJ_deleter> PJ_ptr;

class CSRSTransform : public Transform {
private:
	PJ_CONTEXT* ctx{proj_context_create()};

	HelmertFactory helmert_factory;     // Helmert transform params
	std::string s_crs;                  // e.g. EPSG:4326
	double s_epoch;                     // e.g. 2020.5342
	double t_epoch{};                   // e.g. 1997.0000
	std::string t_vd{};					// Target orthometric height vertical datum
	std::string out{"geog"};			// One of geog, cart, utmXX (where XX is a number)

	std::vector<PJ_ptr> transforms;

	void throwProjErr();

	void trans(PJ_COORD& coord, PJ_DIRECTION direction);

public:
	// Constructor
	CSRSTransform(const std::string& sRefFrame, std::string sCrs, double sEpoch, double tEpoch,
			std::string tVd, std::string outCoords);

	// Destructor
	virtual ~CSRSTransform();

	// Transform functions
	void forward(PJ_COORD& coord) override { trans(coord, PJ_FWD); }
	void backward(PJ_COORD& coord) override;
};
}

#endif //REPROJECT_CSRS_CSRSTRANSFORM_H
