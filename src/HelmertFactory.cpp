//
// Created by taylor on 2021-08-27.
//

#include <stdexcept>
#include "HelmertFactory.h"

namespace hakai_csrs {
HelmertFactory::HelmertFactory(const std::string& s_ref_frame)
{
	if (s_ref_frame=="nad83csrs") {
		x = 0;
		dx = 0;
		y = 0;
		dy = 0;
		z = 0;
		dz = 0;
		rx = 0;
		drx = 0;
		ry = 0;
		dry = 0;
		rz = 0;
		drz = 0;
		s = 0;
		ds = 0;
	}
	else if (s_ref_frame=="itrf88") {
		x = 0.97300;
		dx = 0.00000;
		y = -1.90720;
		dy = 0.00000;
		z = -0.42090;
		dz = 0.00000;
		rx = -26.58160;
		drx = -0.05320;
		ry = -0.00010;
		dry = 0.74230;
		rz = -11.24920;
		drz = 0.03160;
		s = -7.40000;
		ds = 0.00000;
	}
	else if (s_ref_frame=="itrf89") {
		x = 0.96800;
		dx = 0.00000;
		y = -1.94320;
		dy = 0.00000;
		z = -0.44490;
		dz = 0.00000;
		rx = -26.48160;
		drx = -0.05320;
		ry = -0.00010;
		dry = 0.74230;
		rz = -11.24920;
		drz = 0.03160;
		s = -4.30000;
		ds = 0.00000;
	}
	else if (s_ref_frame=="itrf90") {
		x = 0.97300;
		dx = 0.00000;
		y = -1.91920;
		dy = 0.00000;
		z = -0.48290;
		dz = 0.00000;
		rx = -26.48160;
		drx = -0.05320;
		ry = -0.00010;
		dry = 0.74230;
		rz = -11.24920;
		drz = 0.03160;
		s = -0.90000;
		ds = 0.00000;
	}
	else if (s_ref_frame=="itrf91") {
		x = 0.97100;
		dx = 0.00000;
		y = -1.92320;
		dy = 0.00000;
		z = -0.49890;
		dz = 0.00000;
		rx = -26.48160;
		drx = -0.05320;
		ry = -0.00010;
		dry = 0.74230;
		rz = -11.24920;
		drz = 0.03160;
		s = -0.60000;
		ds = 0.00000;
	}
	else if (s_ref_frame=="itrf92") {
		x = 0.98300;
		dx = 0.00000;
		y = -1.90920;
		dy = 0.00000;
		z = -0.50490;
		dz = 0.00000;
		rx = -26.48160;
		drx = -0.05320;
		ry = -0.00010;
		dry = 0.74230;
		rz = -11.24920;
		drz = 0.03160;
		s = 0.80000;
		ds = 0.00000;
	}
	else if (s_ref_frame=="itrf93") {
		x = 1.04880;
		dx = 0.00290;
		y = -1.91100;
		dy = -0.00040;
		z = -0.51550;
		dz = -0.00080;
		rx = -23.67160;
		drx = 0.05680;
		ry = 3.37990;
		dry = 0.93230;
		rz = -11.38920;
		drz = -0.01840;
		s = -0.40000;
		ds = 0.00000;
	}
	else if (s_ref_frame=="itrf94") {
		x = 0.99100;
		dx = 0.00000;
		y = -1.90720;
		dy = 0.00000;
		z = -0.51290;
		dz = 0.00000;
		rx = -26.48160;
		drx = -0.05320;
		ry = -0.00010;
		dry = 0.74230;
		rz = -11.24920;
		drz = 0.03160;
		s = 0.00000;
		ds = 0.00000;
	}
	else if (s_ref_frame=="itrf96") {
		x = 0.99100;
		dx = 0.00000;
		y = -1.90720;
		dy = 0.00000;
		z = -0.51290;
		dz = 0.00000;
		rx = -26.48160;
		drx = -0.05320;
		ry = -0.00010;
		dry = 0.74230;
		rz = -11.24920;
		drz = 0.03160;
		s = 0.00000;
		ds = 0.00000;
	}
	else if (s_ref_frame=="itrf97") {
		x = 0.99790;
		dx = 0.00069;
		y = -1.90871;
		dy = -0.00010;
		z = -0.47877;
		dz = 0.00186;
		rx = -26.78138;
		drx = -0.06667;
		ry = 0.42027;
		dry = 0.75744;
		rz = -11.19206;
		drz = 0.03133;
		s = -3.43109;
		ds = -0.19201;
	}
	else if (s_ref_frame=="itrf00") {
		x = 1.00460;
		dx = 0.00069;
		y = -1.91041;
		dy = -0.00070;
		z = -0.51547;
		dz = 0.00046;
		rx = -26.78138;
		drx = -0.06667;
		ry = 0.42027;
		dry = 0.75744;
		rz = -10.93206;
		drz = 0.05133;
		s = -1.75109;
		ds = -0.18201;
	}
	else if (s_ref_frame=="itrf05") {
		x = 1.00270;
		dx = 0.00049;
		y = -1.91021;
		dy = -0.00060;
		z = -0.53927;
		dz = -0.00134;
		rx = -26.78138;
		drx = -0.06667;
		ry = 0.42027;
		dry = 0.75744;
		rz = -10.93206;
		drz = 0.05133;
		s = -0.55109;
		ds = -0.10201;
	}
	else if (s_ref_frame=="itrf08") {
		x = 1.00370;
		dx = 0.00079;
		y = -1.91111;
		dy = -0.00060;
		z = -0.54397;
		dz = -0.00134;
		rx = -26.78138;
		drx = -0.06667;
		ry = 0.42027;
		dry = 0.75744;
		rz = -10.93206;
		drz = 0.05133;
		s = 0.38891;
		ds = -0.10201;
	}
	else if (s_ref_frame=="itrf14") {
		x = 1.00530;
		dx = 0.00079;
		y = -1.90921;
		dy = -0.00060;
		z = -0.54157;
		dz = -0.00144;
		rx = -26.78138;
		drx = -0.06667;
		ry = 0.42027;
		dry = 0.75744;
		rz = -10.93206;
		drz = 0.05133;
		s = 0.36891;
		ds = -0.07201;
	}
	else
		throw std::runtime_error("src_ref_frame not found!");
}

std::string HelmertFactory::proj_str() const
{
	char helmert_str[512]{};
	sprintf(helmert_str,
			"proj=helmert convention=position_vector t_epoch=%.3f"
			" x=%.8f dx=%.8f y=%.8f dy=%.8f z=%.8f dz=%.8f"
			" rx=%.8f drx=%.8f ry=%.8f dry=%.8f rz=%.8f drz=%.8f"
			" s=%.8f ds=%.8f",
			itrf_epoch,
			x, dx,
			y, dy,
			z, dz,
			rx*1e-3, drx*1e-3,  // mas -> as,
			ry*1e-3, dry*1e-3,  // mas -> as,
			rz*1e-3, drz*1e-3,  // mas -> as,
			s*1e-3, ds*1e-3     // ppb -> ppm
	);
	return {helmert_str};
}
}