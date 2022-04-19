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
#include <memory>
#include <fis_wrapper.h>

using namespace Rcpp;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool is_numeric_vector_infer(SEXP* args, int nargs) {
	return (nargs == 1) && Rf_isNumeric(args[0]) && !Rf_isMatrix(args[0]);
}

bool is_numeric_matrix_infer(SEXP* args, int nargs) {
	return (nargs == 1) && Rf_isNumeric(args[0]) && Rf_isMatrix(args[0]);
}

bool is_data_frame_infer(SEXP* args, int nargs) {
	return (nargs == 1) && Rf_inherits(args[0], "data.frame");
}

bool is_numeric_vector_infer_output(SEXP* args, int nargs) {
	return (nargs == 2) && Rf_isNumeric(args[0]) && !Rf_isMatrix(args[0]) && Rf_isNumeric(args[1]);
}

bool is_numeric_matrix_infer_output(SEXP* args, int nargs) {
	return (nargs == 2) && Rf_isNumeric(args[0]) && Rf_isMatrix(args[0]) && Rf_isNumeric(args[1]);
}

bool is_data_frame_infer_output(SEXP* args, int nargs) {
	return (nargs == 2) && Rf_inherits(args[0], "data.frame") && Rf_isNumeric(args[1]);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RCPP_EXPOSED_AS(fisin_wrapper)

RCPP_EXPOSED_AS(fisout_wrapper)

RCPP_EXPOSED_AS(rule_wrapper)

RCPP_EXPOSED_AS(fis_wrapper)

RCPP_MODULE(fis_module) {

	class_<fis_wrapper>("Fis")
	.default_constructor()
	.constructor<const char *>()
	.property("name", &fis_wrapper::get_name, &fis_wrapper::set_name)
	.property("conjunction", &fis_wrapper::get_conjunction, &fis_wrapper::set_conjunction)
	.method("input_size", &fis_wrapper::get_input_size)
	.method("add_input", &fis_wrapper::add_input)
	.method("get_input", &fis_wrapper::get_input)
	.method("get_inputs", &fis_wrapper::get_inputs)
	.method("output_size", &fis_wrapper::get_output_size)
	.method("add_output", &fis_wrapper::add_output)
	.method("get_output", &fis_wrapper::get_output)
	.method("get_outputs", &fis_wrapper::get_outputs)
	.method("rule_size", &fis_wrapper::get_rule_size)
	.method("add_rule", &fis_wrapper::add_rule)
	.method("get_rule", &fis_wrapper::get_rule)
	.method("get_rules", &fis_wrapper::get_rules)
	.method("infer", static_cast<NumericVector (fis_wrapper::*)(NumericVector) const>(&fis_wrapper::infer), "NumericVector infer", is_numeric_vector_infer)
	.method("infer", static_cast<SEXP (fis_wrapper::*)(NumericMatrix) const>(&fis_wrapper::infer), "NumericMatrix infer", is_numeric_matrix_infer)
	.method("infer", static_cast<SEXP (fis_wrapper::*)(DataFrame) const>(&fis_wrapper::infer), "DataFrame infer", is_data_frame_infer)
	.method("infer_output", static_cast<double (fis_wrapper::*)(NumericVector, int) const>(&fis_wrapper::infer_output), "NumericVector infer output", is_numeric_vector_infer_output)
	.method("infer_output", static_cast<NumericVector (fis_wrapper::*)(NumericMatrix, int) const>(&fis_wrapper::infer_output), "NumericMatrix infer output", is_numeric_matrix_infer_output)
	.method("infer_output", static_cast<NumericVector (fis_wrapper::*)(DataFrame, int) const>(&fis_wrapper::infer_output), "DataFrame infer output", is_data_frame_infer_output)
	.method("equals", &fis_wrapper::equals)
	.method("save", &fis_wrapper::save)
	.method("to_string", &fis_wrapper::to_string);
}
