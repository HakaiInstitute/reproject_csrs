//
// Created by taylor on 2021-08-26.
//

#ifndef REPROJECT_CSRS_PDALFILTERREPROJECTCSRS_H
#define REPROJECT_CSRS_PDALFILTERREPROJECTCSRS_H

#include <pdal/pdal_internal.hpp>
#include <pdal/filters/StreamCallbackFilter.hpp>
#include "CSRSTransform.h"

namespace pdal {
class PDAL_DLL PdalFilterReprojectCSRS : public StreamCallbackFilter {
private:
	std::string s_ref_frame;            // e.g. itrf14
	std::string s_crs;                  // e.g. EPSG:4326
	std::string t_crs;				    // e.g. EPSG:3157
	double s_epoch;                     // e.g. 2020.5342
	double t_epoch;                     // e.g. 1997.0000

	std::unique_ptr<hakai_csrs::CSRSTransform> transformer{nullptr};

	void addArgs(ProgramArgs& args) override;
	void ready(BasePointTable& table) override;
	void done(BasePointTable& table) override;

	PdalFilterReprojectCSRS& operator=(const PdalFilterReprojectCSRS&); // not implemented
	PdalFilterReprojectCSRS(const PdalFilterReprojectCSRS&); // not implemented

protected:
	bool processOne(PointRef& point) override;

public:
	PdalFilterReprojectCSRS()
			:StreamCallbackFilter() {}

	std::string getName() const override;
};
}

#endif //REPROJECT_CSRS_PDALFILTERREPROJECTCSRS_H
