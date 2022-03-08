//
// Created by taylor on 2021-09-03.
//

#ifndef REPROJECT_CSRS_PROJECTIONFACTORY_H
#define REPROJECT_CSRS_PROJECTIONFACTORY_H

namespace hakai_csrs {
class ProjectionFactory {
public:
	virtual PJ* create_pj(PJ_CONTEXT* ctx) const = 0;
};
}

#endif //REPROJECT_CSRS_PROJECTIONFACTORY_H
