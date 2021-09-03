//
// Created by taylor on 2021-09-03.
//

#ifndef REPROJECT_CSRS_VERTICALGRIDSHIFTFACTORY_H
#define REPROJECT_CSRS_VERTICALGRIDSHIFTFACTORY_H

#include <ProjectionFactory.h>
#include <string>
#include <proj.h>

namespace hakai_csrs {

class VerticalGridShiftFactory : public ProjectionFactory {
private:
	std::string grid_shift_file;
public:
	explicit VerticalGridShiftFactory(const std::string& grid_shift_file);
	PJ* create_pj(PJ_CONTEXT* ctx) const override;
};

}

#endif //REPROJECT_CSRS_VERTICALGRIDSHIFTFACTORY_H
