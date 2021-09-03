//
// Created by taylor on 2021-08-27.
//

#ifndef REPROJECT_CSRS_HELMERTFACTORY_H
#define REPROJECT_CSRS_HELMERTFACTORY_H

#include <string>
#include <proj.h>
#include <ProjectionFactory.h>

namespace hakai_csrs {
class HelmertFactory : public ProjectionFactory {
private:
	double itrf_epoch{2010}, x, dx, y, dy, z, dz, rx, drx, ry, dry, rz, drz, s, ds;
	[[nodiscard]] std::string proj_str() const;

public:
	explicit HelmertFactory(const std::string& s_ref_frame);
	PJ* create_pj(PJ_CONTEXT* ctx) const { return proj_create(ctx, this->proj_str().c_str()); }
};
}

#endif //REPROJECT_CSRS_HELMERTFACTORY_H
