/**
 * FisPro R package
 *
 * Copyright (C) 2020 INRAE
 *
 * Authors:
 * 	Jean-luc Lablée - INRAE
 * 	Serge Guillaume - INRAE
 *
 * License: CeCILL v2.1
 * 	https://cecill.info/licences/Licence_CeCILL_V2.1-en.html
 * 	https://cecill.info/licences/Licence_CeCILL_V2.1-fr.html
 *
 * This software is governed by the CeCILL license under French law and
 * abiding by the rules of distribution of free software.  You can  use,
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 *
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or
 * data to be ensured and,  more generally, to use and operate it in the
 * same conditions as regards security.
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 */
#include <mf_wrapper.h>
#include <boost/format.hpp>

using namespace std;
using namespace Rcpp;
using namespace util;
using namespace boost;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

mf_wrapper::mf_wrapper(MF* mf, bool owner) : mf(mf, ptr_deleter(owner)) {}

mf_wrapper::mf_wrapper() : mf(nullptr) {
	stop("do not instantiate 'Mf' class");
}

const char *mf_wrapper::get_name() const {
	return mf->Name;
}

void mf_wrapper::set_name(const char *name) {
	mf->SetName(name);
}

double mf_wrapper::get_degree(double value) const {
	return mf->GetDeg(value);
}

MF *mf_wrapper::clone() const {
	return mf->Clone();
}

bool mf_wrapper::equals(const mf_wrapper &other) const {
	return !(*mf != *other.mf);
}

string mf_wrapper::to_string() const {
	ostringstream os;
	os << mf.get();
	return os.str();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static MFTRI *make_mf_triangular(double lower_support, double kernel, double upper_support) {
	if(lower_support > kernel)
		stop("lower_support must be <= kernel");
	if(upper_support < kernel)
		stop("kernel must be <= upper_support");
	if(!(upper_support > lower_support))
		stop("lower_support must be < upper_support");
	return new MFTRI(lower_support, kernel, upper_support);
}

mf_triangular_wrapper::mf_triangular_wrapper() : mf_triangular_wrapper(NULL) {
	stop("MfTriangular default constructor not allowed");
}

mf_triangular_wrapper::mf_triangular_wrapper(double lower_support, double kernel, double upper_support) : mf_triangular_wrapper(make_mf_triangular(lower_support, kernel, upper_support)) {}

mf_triangular_wrapper::mf_triangular_wrapper(MFTRI *mf_triangular, bool owner) : mf_wrapper(mf_triangular, owner) {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static MFTRAPINF *make_mf_trapezoidal_inf(double upper_kernel, double upper_support) {
	if(!(upper_support > upper_kernel))
		stop("upper_kernel must be < upper_support");
	return new MFTRAPINF(upper_kernel, upper_kernel, upper_support);
}

mf_trapezoidal_inf_wrapper::mf_trapezoidal_inf_wrapper() : mf_trapezoidal_inf_wrapper(NULL) {
	stop("MfTrapezoidalInf default constructor not allowed");
}

mf_trapezoidal_inf_wrapper::mf_trapezoidal_inf_wrapper(double upper_kernel, double upper_support) : mf_trapezoidal_inf_wrapper(make_mf_trapezoidal_inf(upper_kernel, upper_support)) {}

mf_trapezoidal_inf_wrapper::mf_trapezoidal_inf_wrapper(MFTRAPINF *mf_trapezoidal_inf, bool owner) : mf_wrapper(mf_trapezoidal_inf, owner) {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static MFTRAPSUP *make_mf_trapezoidal_sup(double lower_support, double lower_kernel) {
	if(!(lower_kernel > lower_support))
	    stop("lower_support must be < lower_kernel");
	return new MFTRAPSUP(lower_support, lower_kernel, lower_kernel);
}

mf_trapezoidal_sup_wrapper::mf_trapezoidal_sup_wrapper() : mf_trapezoidal_sup_wrapper(NULL) {
	stop("MfTrapezoidalSup default constructor not allowed");
}

mf_trapezoidal_sup_wrapper::mf_trapezoidal_sup_wrapper(double lower_support, double lower_kernel) : mf_trapezoidal_sup_wrapper(make_mf_trapezoidal_sup(lower_support, lower_kernel)) {}

mf_trapezoidal_sup_wrapper::mf_trapezoidal_sup_wrapper(MFTRAPSUP *mf_trapezoidal_sup, bool owner) : mf_wrapper(mf_trapezoidal_sup, owner) {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static MFTRAP *make_mf_trapezoidal(double lower_support, double lower_kernel, double upper_kernel, double upper_support) {
	if(lower_support > lower_kernel)
	    stop("lower_support must be <= lower_kernel");
	if(lower_kernel > upper_kernel)
	    stop("lower_kernel must be <= upper_kernel");
	if(upper_kernel > upper_support)
	    stop("upper_kernel must be <= upper_support");
	if(!(upper_support > lower_kernel))
	    stop("lower_kernel must be < upper_support");
	return new MFTRAP(lower_support, lower_kernel, upper_kernel, upper_support);
}

mf_trapezoidal_wrapper::mf_trapezoidal_wrapper() : mf_trapezoidal_wrapper(NULL) {
	stop("MfTrapezoidal default constructor not allowed");
}

mf_trapezoidal_wrapper::mf_trapezoidal_wrapper(double lower_support, double lower_kernel, double upper_kernel, double upper_support) : mf_trapezoidal_wrapper(make_mf_trapezoidal(lower_support, lower_kernel, upper_kernel, upper_support)) {}

mf_trapezoidal_wrapper::mf_trapezoidal_wrapper(MFTRAP *mf_trapezoidal, bool owner) : mf_wrapper(mf_trapezoidal, owner) {}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ostream& operator<<(ostream &os, const MF *mf) {
	if(const MFTRI *mf_triangular = dynamic_cast<const MFTRI *>(mf))
		return os << mf_triangular;
	else if(const MFTRAPINF *mf_trapezoidal_inf = dynamic_cast<const MFTRAPINF *>(mf))
		return os << mf_trapezoidal_inf;
	else if(const MFTRAPSUP *mf_trapezoidal_sup = dynamic_cast<const MFTRAPSUP *>(mf))
		return os << mf_trapezoidal_sup;
	else if(const MFTRAP *mf_trapezoidal = dynamic_cast<const MFTRAP *>(mf))
		return os << mf_trapezoidal;
	else
		return os << str(format("unsupported mf \"%1%\"") % typeid(*mf).name());
}

ostream& operator<<(ostream &os, const MFTRI *mf_triangular) {
	double params[3];
	mf_triangular->GetParams(params);
	return os << str(format("mf_triangular(\"%1%\", %2%, %3%, %4%)") % mf_triangular->Name % params[0] % params[1] % params[2]);
}

ostream& operator<<(ostream &os, const MFTRAPINF *mf_trapezoidal_inf) {
	double params[3];
	mf_trapezoidal_inf->GetParams(params);
	return os << str(format("mf_trapezoidal_inf(\"%1%\", %2%, %3%)") % mf_trapezoidal_inf->Name % params[1] % params[2]);
}

ostream& operator<<(ostream &os, const MFTRAPSUP *mf_trapezoidal_sup) {
	double params[3];
	mf_trapezoidal_sup->GetParams(params);
	return os << str(format("mf_trapezoidal_sup(\"%1%\", %2%, %3%)") % mf_trapezoidal_sup->Name % params[0] % params[1]);
}

ostream& operator<<(ostream &os, const MFTRAP *mf_trapezoidal) {
	double params[4];
	mf_trapezoidal->GetParams(params);
	return os << str(format("mf_trapezoidal(\"%1%\", %2%, %3%, %4%, %5%)") % mf_trapezoidal->Name % params[0] % params[1] % params[2] % params[3]);
}
