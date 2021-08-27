//
// Created by taylor on 2021-08-26.
//

#ifndef REPROJECT_CSRS_PDALFILTERREPROJECTCSRS_H
#define REPROJECT_CSRS_PDALFILTERREPROJECTCSRS_H

#include <pdal/pdal_internal.hpp>
#include <pdal/Filter.hpp>
#include "Nad83CSRSTransform.h"

namespace pdal {
class PDAL_DLL PdalFilterReprojectCSRS : public Filter {
private:
	std::string s_ref_frame;             // e.g. itrf14
	std::string s_crs;                  // e.g. EPSG:4326
	std::string t_crs{"EPSG:4617"};  // e.g. EPSG:3157
	double s_epoch;                     // e.g. 2020.5342
	double t_epoch;                     // e.g. 1997.0000

	void addArgs(ProgramArgs& args) override;
	void filter(PointView& view) override;

	PdalFilterReprojectCSRS& operator=(const PdalFilterReprojectCSRS&); // not implemented
	PdalFilterReprojectCSRS(const PdalFilterReprojectCSRS&); // not implemented

public:
	PdalFilterReprojectCSRS()
			:Filter() { }
	std::string getName() const override;
};
}

#endif //REPROJECT_CSRS_PDALFILTERREPROJECTCSRS_H
