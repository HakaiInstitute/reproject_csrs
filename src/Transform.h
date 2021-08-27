//
// Created by taylor on 2021-08-24.
//

#ifndef HAKAI_LAS2CSRS_TRANSFORM_H
#define HAKAI_LAS2CSRS_TRANSFORM_H

#include <proj.h>

namespace hakai_csrs {
class Transform {
public:
	virtual void forward(PJ_COORD& coord) = 0;
	virtual void backward(PJ_COORD& coord) = 0;
};
}

#endif //HAKAI_LAS2CSRS_TRANSFORM_H
