//
// Created by taylor on 2021-08-26.
//

#include "PdalFilterReprojectCSRS.h"
#include "CSRSTransform.h"
#include <pdal/pdal_internal.hpp>

namespace pdal {

static PluginInfo const s_info{
		"filters.reprojectcsrs",
		"Reproject to NAD83(CSRS)",
		"https://github.com/HakaiInstitute/reproject_csrs"
};

CREATE_SHARED_STAGE(PdalFilterReprojectCSRS, s_info)

std::string PdalFilterReprojectCSRS::getName() const { return s_info.name; }

void PdalFilterReprojectCSRS::addArgs(ProgramArgs& args)
{
	args.add("s_ref_frame", "The source reference frame of the coordinates "
							"[itrf88|itrf89|itrf90|itrf91|itrf92|itrf93|itrf94|itrf96|itrf97|itrf00|itrf05|itrf08|itrf14]",
			s_ref_frame, "itrf14");
	args.add("s_crs",
			"The source CRS in 'AUTHORITY:CODE' format, or as a proj string like '+proj=longlat +datum=WGS84'or a CRS name found in the proj database",
			s_crs, "EPSG:4326");
	args.add("t_crs",
			"The target CRS in 'AUTHORITY:CODE' format, or as a proj string like '+proj=longlat +datum=WGS84' or a CRS name found in the proj database",
			t_crs, "EPSG:4954");
	args.add("s_epoch", "The reference epoch for the input in decimal year format, e.g. '2020.5342'",
			s_epoch, 2010.0000);
	args.add("t_epoch", "Optional reference epoch for the output in decimal year format, e.g. '1997.0000'. "
						"By default, the output epoch will match the s_epoch value.",
			t_epoch);
}

bool PdalFilterReprojectCSRS::processOne(PointRef& point)
{
	auto x = point.getFieldAs<double>(Dimension::Id::X);
	auto y = point.getFieldAs<double>(Dimension::Id::Y);
	auto z = point.getFieldAs<double>(Dimension::Id::Z);

	PJ_COORD coord = proj_coord(x, y, z, s_epoch);
	transformer->forward(coord);

	point.setField(Dimension::Id::X, coord.xyzt.x);
	point.setField(Dimension::Id::Y, coord.xyzt.y);
	point.setField(Dimension::Id::Z, coord.xyzt.z);

	return true;
}

void PdalFilterReprojectCSRS::ready(BasePointTable& table)
{
	this->transformer = std::make_unique<hakai_csrs::CSRSTransform>(s_ref_frame, s_crs, t_crs, s_epoch, t_epoch);
}

void PdalFilterReprojectCSRS::done(BasePointTable& table)
{
	// Set the SRS in the output
	table.setSpatialReference(SpatialReference(t_crs));
}

} // namespace pdal