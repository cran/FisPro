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
#include <fisin_wrapper.h>
#include <fuzzy_range.h>
#include <boost/format.hpp>

using namespace Rcpp;
using namespace std;
using namespace util;
using namespace boost;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static FISIN *make_fisin(double minimum, double maximum) {
	check_range(minimum, maximum);
	return new FISIN(0, minimum, maximum);
}

static FISIN *make_fisin(int number_of_mfs, double minimum, double maximum) {
	check_range(minimum, maximum);
	return new FISIN(number_of_mfs, minimum, maximum);
}

static FISIN *make_fisin(NumericVector breakpoints, double minimum, double maximum) {
	check_range(breakpoints, minimum, maximum);
	return new FISIN(breakpoints.begin(), breakpoints.size(), minimum, maximum);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

fisin_wrapper::fisin_wrapper(FISIN *fisin, bool owner) : fisin(fisin, ptr_deleter(owner)), fuzzy(fisin) {}

fisin_wrapper::fisin_wrapper() : fisin_wrapper(new FISIN()) {}

fisin_wrapper::fisin_wrapper(double minimum, double maximum) : fisin_wrapper(make_fisin(minimum, maximum)) {}

fisin_wrapper::fisin_wrapper(int number_of_mfs, double minimum, double maximum) : fisin_wrapper(make_fisin(number_of_mfs, minimum, maximum)) {}

fisin_wrapper::fisin_wrapper(NumericVector breakpoints, double minimum, double maximum) : fisin_wrapper(make_fisin(breakpoints, minimum, maximum)) {}

FISIN *fisin_wrapper::clone() const {
	return new FISIN(*fisin);
}

NumericVector fisin_wrapper::get_range() const {
	return NumericVector::create(Named("min") = fisin->min(), Named("max") = fisin->max());
}

void fisin_wrapper::set_name(const char *name) {
	fisin->SetName(name);
}

const char *fisin_wrapper::get_name() const {
	return fisin->Name;
}

fisin_wrapper::operator const FISIN &() const {
	return *fisin;
}

int fisin_wrapper::get_mf_size() const {
	return fuzzy.get_mf_size();
}

void fisin_wrapper::add_mf(const mf_wrapper &mf) {
	fuzzy.add_mf(mf);
}

SEXP fisin_wrapper::get_mf(int mf_index) const {
	return fuzzy.get_mf(mf_index);
}

List fisin_wrapper::get_mfs() const {
	return fuzzy.get_mfs();
}

bool fisin_wrapper::is_standardized() const {
	return fuzzy.is_standardized();
}

bool fisin_wrapper::equals(const fisin_wrapper &other) const {
	return !(*fisin != *other.fisin);
}

string fisin_wrapper::to_string() const {
	ostringstream os;
	os << fisin.get();
	return os.str();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ostream& operator<<(ostream &os, const FISIN *fisin) {
	FISIN *nc_fisin = const_cast<FISIN *>(fisin);
	os << str(format("name = \"%1%\"") % fisin->Name) << endl;
	os << str(format("range = [%1%, %2%]") % nc_fisin->min() % nc_fisin->max()) << endl;
	fuzzy_to_stream(os, fisin);
	return os;
}
