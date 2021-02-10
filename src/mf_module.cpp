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
#include <Rcpp.h>
#include <mf_wrapper.h>

using namespace Rcpp;

RCPP_EXPOSED_AS(mf_wrapper)

RCPP_MODULE(mf_module) {

	class_<mf_wrapper>("Mf")
	.default_constructor()
	.property("label", &mf_wrapper::get_name, &mf_wrapper::set_name)
	.method("degree", &mf_wrapper::get_degree)
	.method("equals", &mf_wrapper::equals)
	.method("to_string", &mf_wrapper::to_string);

	class_<mf_triangular_wrapper>("MfTriangular")
	.derives<mf_wrapper>("Mf")
	.default_constructor()
	.constructor<double, double, double>();

	class_<mf_trapezoidal_inf_wrapper>("MfTrapezoidalInf")
	.derives<mf_wrapper>("Mf")
	.default_constructor()
	.constructor<double, double>();

	class_<mf_trapezoidal_sup_wrapper>("MfTrapezoidalSup")
	.derives<mf_wrapper>("Mf")
	.default_constructor()
	.constructor<double, double>();

	class_<mf_trapezoidal_wrapper>("MfTrapezoidal")
	.derives<mf_wrapper>("Mf")
	.default_constructor()
	.constructor<double, double, double, double>();
}
