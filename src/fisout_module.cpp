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
#include <fisout_wrapper.h>

using namespace Rcpp;

RCPP_EXPOSED_AS(mf_wrapper)

RCPP_EXPOSED_AS(fisout_wrapper)

RCPP_MODULE(fisout_module) {

	class_<fisout_wrapper>("FisOut")
	.default_constructor()
	.property("name", &fisout_wrapper::get_name, &fisout_wrapper::set_name)
	.method("range", &fisout_wrapper::get_range)
	.method("equals", &fisout_wrapper::equals)
	.method("to_string", &fisout_wrapper::to_string);

	class_<fisout_crisp_wrapper>("FisOutCrisp")
	.derives<fisout_wrapper>("FisOut")
	.default_constructor()
	.constructor<double, double>()
	.property("defuzzification", &fisout_crisp_wrapper::get_defuzzification, &fisout_crisp_wrapper::set_defuzzification)
	.property("disjunction", &fisout_crisp_wrapper::get_disjunction, &fisout_crisp_wrapper::set_disjunction);

	class_<fisout_fuzzy_wrapper>("FisOutFuzzy")
	.derives<fisout_wrapper>("FisOut")
	.default_constructor()
	.constructor<double, double>()
	.constructor<int, double, double>("regular constructor", is_regular_constructor)
	.constructor<NumericVector, double, double>("irregular constructor", is_irregular_constructor)
	.property("defuzzification", &fisout_fuzzy_wrapper::get_defuzzification, &fisout_fuzzy_wrapper::set_defuzzification)
	.property("disjunction", &fisout_fuzzy_wrapper::get_disjunction, &fisout_fuzzy_wrapper::set_disjunction)
	.method("mf_size", &fisout_fuzzy_wrapper::get_mf_size)
	.method("is_standardized", &fisout_fuzzy_wrapper::is_standardized)
	.method("add_mf", &fisout_fuzzy_wrapper::add_mf)
	.method("get_mf", &fisout_fuzzy_wrapper::get_mf)
	.method("get_mfs", &fisout_fuzzy_wrapper::get_mfs);
}
