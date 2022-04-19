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
 * "https://cecill.info".
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
#include <Rcpp.h>
#include <string>
#include "fis.h"

using namespace Rcpp;

class deprecated_fis_wrapper {

private:
    FIS *fis;

	void check_infer_values(NumericVector values) const {
		if(values.size() != fis->GetNbIn())
			stop("values must be equal to input size");
	}

	void warn_deprecated() const {
		Function deprecated(".Deprecated");
		deprecated("Fis", "FisPro", Named("old", "fis"));
	}

public:
	deprecated_fis_wrapper() : fis(NULL) {
		warn_deprecated();
	    stop("fis default constructor not allowed");
	}

	deprecated_fis_wrapper(const char *fis_file) : fis(new FIS(fis_file)) {
		warn_deprecated();
	}

	~deprecated_fis_wrapper() {
		delete fis;
		fis = NULL;
	}

	const char *get_name() const {
		return fis->Name;
	}

	void set_name(const char *name) {
		fis->SetName(name);
	}

	int get_input_size() const {
		return fis->GetNbIn();
	}

	int get_output_size() const {
		return fis->GetNbOut();
	}

	NumericVector infer(NumericVector values) const {
		check_infer_values(values);
		fis->Infer(values.begin());
		return NumericVector(fis->OutValue, fis->OutValue + fis->GetNbOut());
	}

	double infer_output(NumericVector values, int output_number) const {
		Function deprecated(".Deprecated");
		deprecated("Fis$infer_output", "FisPro", Named("old", "fis$infer_output"));
		warning("WARNING !!! the output_index is now 1-based indexed in 'Fis$infer_output', was 0-based indexed in deprecated 'fis$infer_output'");
		check_infer_values(values);
		if((output_number < 0) || (output_number >= fis->GetNbOut()))
			stop("output_number must be in range [0, output size)");
		fis->Infer(values.begin(), output_number);
		return fis->OutValue[output_number];
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class deprecated_mf_wrapper {

private:
	MF* mf;

	void warn_deprecated() const {
		Function deprecated(".Deprecated");
		deprecated("Mf", "FisPro", Named("old", "mf"));
	}

protected:
	deprecated_mf_wrapper(MF* mf) : mf(mf) {}

public:
	deprecated_mf_wrapper() : mf(NULL) {
		warn_deprecated();
		stop("mf class is not instantiable, use derived classes");
	}

	virtual ~deprecated_mf_wrapper() {
		delete mf;
		mf = NULL;
	}

	const char *get_name() const {
		return mf->Name;
	}

	void set_name(const char *name) {
		mf->SetName(name);
	}

	double get_degree(double value) const {
		return mf->GetDeg(value);
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class deprecated_mf_triangular_wrapper : public deprecated_mf_wrapper {

private:
	MFTRI *mf_triangular;

	void warn_deprecated() const {
		Function deprecated(".Deprecated");
		deprecated("MfTriangular", "FisPro", Named("old", "mf_triangular"));
	}

public:
	deprecated_mf_triangular_wrapper() : deprecated_mf_triangular_wrapper(NULL) {
		warn_deprecated();
	    stop("mf_triangular default constructor not allowed");
	}
	deprecated_mf_triangular_wrapper(double lower_support, double kernel, double upper_support) : deprecated_mf_triangular_wrapper(new MFTRI(lower_support, kernel, upper_support)) {
		warn_deprecated();
	}

	deprecated_mf_triangular_wrapper(MFTRI *mf_triangular) : deprecated_mf_wrapper(mf_triangular), mf_triangular(mf_triangular) {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class deprecated_mf_trapezoidal_inf_wrapper : public deprecated_mf_wrapper {

private:
	MFTRAPINF *mf_trapezoidal_inf;

	void warn_deprecated() const {
		Function deprecated(".Deprecated");
		deprecated("MfTrapezoidalInf", "FisPro", Named("old", "mf_trapezoidal_inf"));
	}

public:
	deprecated_mf_trapezoidal_inf_wrapper() : deprecated_mf_trapezoidal_inf_wrapper(NULL) {
		warn_deprecated();
	    stop("mf_trapezoidal_inf default constructor not allowed");
	}
	deprecated_mf_trapezoidal_inf_wrapper(double upper_kernel, double upper_support) : deprecated_mf_trapezoidal_inf_wrapper(new MFTRAPINF(upper_kernel, upper_kernel, upper_support)) {
		warn_deprecated();
	}

	deprecated_mf_trapezoidal_inf_wrapper(MFTRAPINF *mf_trapezoidal_inf) : deprecated_mf_wrapper(mf_trapezoidal_inf), mf_trapezoidal_inf(mf_trapezoidal_inf) {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class deprecated_mf_trapezoidal_sup_wrapper : public deprecated_mf_wrapper {

private:
	MFTRAPSUP *mf_trapezoidal_sup;

	static const std::string deprecated_message;

	void warn_deprecated() const {
		Function deprecated(".Deprecated");
		deprecated("MfTrapezoidalSup", "FisPro", Named("old", "mf_trapezoidal_sup"));
	}

public:
	deprecated_mf_trapezoidal_sup_wrapper() : deprecated_mf_trapezoidal_sup_wrapper(NULL) {
		warn_deprecated();
	    stop("mf_trapezoidal_sup default constructor not allowed");
	}

	deprecated_mf_trapezoidal_sup_wrapper(double lower_support, double lower_kernel) : deprecated_mf_trapezoidal_sup_wrapper(new MFTRAPSUP(lower_support, lower_kernel, lower_kernel)) {
		warn_deprecated();
	}

	deprecated_mf_trapezoidal_sup_wrapper(MFTRAPSUP *mf_trapezoidal_sup) : deprecated_mf_wrapper(mf_trapezoidal_sup), mf_trapezoidal_sup(mf_trapezoidal_sup) {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class deprecated_mf_trapezoidal_wrapper : public deprecated_mf_wrapper {

private:
	MFTRAP *mf_trapezoidal;

	static const std::string deprecated_message;

	void warn_deprecated() const {
		Function deprecated(".Deprecated");
		deprecated("MfTrapezoidal", "FisPro", Named("old", "mf_trapezoidal"));
	}

public:
	deprecated_mf_trapezoidal_wrapper() : deprecated_mf_trapezoidal_wrapper(NULL) {
		warn_deprecated();
	    stop("mf_trapezoidal default constructor not allowed");
	}

	deprecated_mf_trapezoidal_wrapper(double lower_support, double lower_kernel, double upper_kernel, double upper_support) : deprecated_mf_trapezoidal_wrapper(new MFTRAP(lower_support, lower_kernel, upper_kernel, upper_support)) {
		warn_deprecated();
	}

	deprecated_mf_trapezoidal_wrapper(MFTRAP *mf_trapezoidal) : deprecated_mf_wrapper(mf_trapezoidal), mf_trapezoidal(mf_trapezoidal) {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RCPP_MODULE(deprecated_module) {

	class_<deprecated_fis_wrapper>("fis")
	.default_constructor()
	.constructor<const char *>()
	.property("name", &deprecated_fis_wrapper::get_name, &deprecated_fis_wrapper::set_name)
	.property("input_size", &deprecated_fis_wrapper::get_input_size)
	.property("output_size", &deprecated_fis_wrapper::get_output_size)
	.method("infer", &deprecated_fis_wrapper::infer)
	.method("infer_output", &deprecated_fis_wrapper::infer_output);

	class_<deprecated_mf_wrapper>("mf")
	.default_constructor()
	.property("name", &deprecated_mf_wrapper::get_name, &deprecated_mf_wrapper::set_name)
	.method("degree", &deprecated_mf_wrapper::get_degree);

	class_<deprecated_mf_triangular_wrapper>("mf_triangular")
	.derives<deprecated_mf_wrapper>("mf")
	.default_constructor()
	.constructor<double, double, double>();

	class_<deprecated_mf_trapezoidal_inf_wrapper>("mf_trapezoidal_inf")
	.derives<deprecated_mf_wrapper>("mf")
	.default_constructor()
	.constructor<double, double>();

	class_<deprecated_mf_trapezoidal_sup_wrapper>("mf_trapezoidal_sup")
	.derives<deprecated_mf_wrapper>("mf")
	.default_constructor()
	.constructor<double, double>();

	class_<deprecated_mf_trapezoidal_wrapper>("mf_trapezoidal")
	.derives<deprecated_mf_wrapper>("mf")
	.default_constructor()
	.constructor<double, double, double, double>();
}
