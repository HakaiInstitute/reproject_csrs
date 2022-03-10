#include <pybind11/pybind11.h>
#include "CSRSTransform.h"

namespace py = pybind11;

PYBIND11_MODULE(csrspy, m)
{
	m.doc() = R"pbdoc(
		Project coordinates to and from NAD83(CSRS).
)pbdoc";

	py::class_<hakai_csrs::CSRSTransform>(m, "CSRSTransformer")
			.def(py::init<const std::string&, std::string, double, double, const std::string&, std::string>(),
			        R"pbdoc(
						Initializes the transformer with the tranformation parameters.
					)pbdoc",
					py::arg("s_ref_frame"),
					py::arg("s_crs"),
					py::arg("s_epoch"),
					py::arg("t_epoch") = 0,
					py::arg("t_vd") = "",
					py::arg("out") = "geog")

			.def("forward",
					static_cast<std::tuple<double, double, double> (hakai_csrs::CSRSTransform::*)(double, double, double)>(&hakai_csrs::CSRSTransform::forward),
					R"pbdoc(
						Transform coordinates in the forwards direction
					)pbdoc",
					py::arg("x"), py::arg("y"), py::arg("z"))

			.def("backward",
					static_cast<std::tuple<double, double, double> (hakai_csrs::CSRSTransform::*)(double, double, double)>(&hakai_csrs::CSRSTransform::backward),
					R"pbdoc(
						Transform coordinates in the backwards direction
					)pbdoc",
					py::arg("x"), py::arg("y"), py::arg("z"));
}
