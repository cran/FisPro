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
#include <fisout_wrapper.h>
#include <fuzzy_range.h>
#include <boost/format.hpp>

using namespace Rcpp;
using namespace std;
using namespace util;
using namespace boost;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

fisout_wrapper::fisout_wrapper(FISOUT *fisout, bool owner) : fisout(fisout, ptr_deleter(owner)) {}

fisout_wrapper::fisout_wrapper() : fisout(nullptr) {
	stop("do not instantiate 'FisOut' class");
}

FISOUT *fisout_wrapper::clone() const {
	return fisout->Clone();
}

NumericVector fisout_wrapper::get_range() const {
	return NumericVector::create(Named("min") = fisout->min(), Named("max") = fisout->max());
}

void fisout_wrapper::set_name(const char *name) {
	fisout->SetName(name);
}

const char *fisout_wrapper::get_name() const {
	return fisout->Name;
}

bool fisout_wrapper::equals(const fisout_wrapper &other) const {
	return !(*fisout != *other.fisout);
}

string fisout_wrapper::to_string() const {
	ostringstream os;
	os << fisout.get();
	return os.str();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static OUT_CRISP *make_fisout_crisp(double minimum, double maximum) {
	check_range(minimum, maximum);
	OUT_CRISP *fisout_crisp = new OUT_CRISP();
	fisout_crisp->SetRange(minimum, maximum);
	return fisout_crisp;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

fisout_crisp_wrapper::fisout_crisp_wrapper(OUT_CRISP *fisout_crisp, bool owner) : fisout_wrapper(fisout_crisp, owner) {}

fisout_crisp_wrapper::fisout_crisp_wrapper() : fisout_crisp_wrapper(new OUT_CRISP()) {}

fisout_crisp_wrapper::fisout_crisp_wrapper(double minimum, double maximum) : fisout_crisp_wrapper(make_fisout_crisp(minimum, maximum)) {}

void fisout_crisp_wrapper::set_defuzzification(const char *defuzzification) {
	if((strcmp(defuzzification, OUT_CRISP::SugenoDefuz()) != 0) && (strcmp(defuzzification, OUT_CRISP::MaxCrispDefuz()) != 0))
		stop(str(format("unknown defuzzification '%1%'") % defuzzification));
	fisout->SetOpDefuz(defuzzification);
}

const char *fisout_crisp_wrapper::get_defuzzification() const {
	return fisout->Defuzzify();
}

void fisout_crisp_wrapper::set_disjunction(const char *disjunction) {
	if((strcmp(disjunction, OUT_CRISP::DisjMax()) != 0) && (strcmp(disjunction, OUT_CRISP::DisjSum()) != 0))
		stop(str(format("unknown disjunction '%1%'") % disjunction));
	fisout->SetOpDisj(disjunction);
}

const char *fisout_crisp_wrapper::get_disjunction() const {
	return fisout->GetDisj();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static OUT_FUZZY *make_fisout_fuzzy(int number_of_mfs, double minimum, double maximum, const char *defuzzification, const char *disjunction, bool classif) {
	check_range(minimum, maximum);
	return new OUT_FUZZY(number_of_mfs, minimum, maximum, defuzzification, disjunction, classif);
}

static OUT_FUZZY *make_fisout_fuzzy(int number_of_mfs, double minimum, double maximum) {
	return make_fisout_fuzzy(number_of_mfs, minimum, maximum, OUT_FUZZY::SugenoDefuz(), OUT_FUZZY::DisjMax(), false);
}

static OUT_FUZZY *make_fisout_fuzzy(double minimum, double maximum) {
	return make_fisout_fuzzy(0, minimum, maximum);
}

static OUT_FUZZY *make_fisout_fuzzy() {
	return make_fisout_fuzzy(0, 1);
}

static OUT_FUZZY *make_fisout_fuzzy(NumericVector breakpoints, double minimum, double maximum, const char *defuzzification, const char *disjunction, bool classif, bool sort) {
	check_range(breakpoints, minimum, maximum);
	return new OUT_FUZZY(breakpoints.begin(), breakpoints.size(), minimum, maximum, sort, defuzzification, disjunction, classif);
}

static OUT_FUZZY *make_fisout_fuzzy(NumericVector breakpoints, double minimum, double maximum) {
	return make_fisout_fuzzy(breakpoints, minimum, maximum, OUT_FUZZY::SugenoDefuz(), OUT_FUZZY::DisjMax(), false, true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

fisout_fuzzy_wrapper::fisout_fuzzy_wrapper(OUT_FUZZY *fisout_fuzzy, bool owner) : fisout_wrapper(fisout_fuzzy, owner), fuzzy(fisout_fuzzy) {}

fisout_fuzzy_wrapper::fisout_fuzzy_wrapper() : fisout_fuzzy_wrapper(make_fisout_fuzzy()) {}

fisout_fuzzy_wrapper::fisout_fuzzy_wrapper(double minimum, double maximum) : fisout_fuzzy_wrapper(make_fisout_fuzzy(minimum, maximum)) {}

fisout_fuzzy_wrapper::fisout_fuzzy_wrapper(int number_of_mfs, double minimum, double maximum) : fisout_fuzzy_wrapper(make_fisout_fuzzy(number_of_mfs, minimum, maximum)) {}

fisout_fuzzy_wrapper::fisout_fuzzy_wrapper(NumericVector breakpoints, double minimum, double maximum) : fisout_fuzzy_wrapper(make_fisout_fuzzy(breakpoints, minimum, maximum)) {}

void fisout_fuzzy_wrapper::set_defuzzification(const char *defuzzification) {
	if((strcmp(defuzzification, OUT_FUZZY::SugenoDefuz()) != 0) && (strcmp(defuzzification, OUT_FUZZY::AreaDefuz()) != 0) && (strcmp(defuzzification, OUT_FUZZY::MeanMaxDefuz()) != 0))
		stop(str(format("unknown defuzzification '%1%'") % defuzzification));
	fisout->SetOpDefuz(defuzzification);
}

const char *fisout_fuzzy_wrapper::get_defuzzification() const {
	return fisout->Defuzzify();
}

void fisout_fuzzy_wrapper::set_disjunction(const char *disjunction) {
	if((strcmp(disjunction, OUT_FUZZY::DisjMax()) != 0) && (strcmp(disjunction, OUT_FUZZY::DisjSum()) != 0))
		stop(str(format("unknown disjunction '%1%'") % disjunction));
	fisout->SetOpDisj(disjunction);
}

const char *fisout_fuzzy_wrapper::get_disjunction() const {
	return fisout->GetDisj();
}

int fisout_fuzzy_wrapper::get_mf_size() const {
	return fuzzy.get_mf_size();
}

bool fisout_fuzzy_wrapper::is_standardized() const {
	return fuzzy.is_standardized();
}

void fisout_fuzzy_wrapper::add_mf(const mf_wrapper &mf) {
	fuzzy.add_mf(mf);
}

SEXP fisout_fuzzy_wrapper::get_mf(int mf_index) const {
	return fuzzy.get_mf(mf_index);
}

List fisout_fuzzy_wrapper::get_mfs() const {
	return fuzzy.get_mfs();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ostream& operator<<(ostream &os, const FISOUT *fisout) {
	if(const OUT_CRISP *fisout_crisp = dynamic_cast<const OUT_CRISP *>(fisout))
		return os << fisout_crisp;
	else if(const OUT_FUZZY *fisout_fuzzy = dynamic_cast<const OUT_FUZZY *>(fisout))
		return os << fisout_fuzzy;
	else
		stop(str(format("unsupported output type '%1%'") % typeid(*fisout).name()));
}

static void output_to_stream(ostream &os, const FISOUT *fisout) {
	FISOUT *nc_fisout = const_cast<FISOUT *>(fisout);
	os << str(format("name = \"%1%\"") % fisout->Name) << endl;
	os << str(format("nature = \"%1%\"") % fisout->GetOutputType()) << endl;
	os << str(format("range = [%1%, %2%]") % nc_fisout->min() % nc_fisout->max()) << endl;
	os << str(format("defuzzification = %1%") % nc_fisout->Defuzzify()) << endl;
	os << str(format("disjunction = %1%") % nc_fisout->GetDisj()) << endl;
}

ostream& operator<<(ostream &os, const OUT_CRISP *fisout_crisp) {
	output_to_stream(os, fisout_crisp);
	return os;
}

ostream& operator<<(ostream &os, const OUT_FUZZY *fisout_fuzzy) {
	output_to_stream(os, fisout_fuzzy);
	fuzzy_to_stream(os, fisout_fuzzy);
	return os;
}
