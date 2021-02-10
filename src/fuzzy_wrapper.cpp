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
#include <fuzzy_wrapper.h>
#include <boost/format.hpp>
#include <boost/icl/closed_interval.hpp>
#include <boost/range/counting_range.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/for_each.hpp>

using namespace Rcpp;
using namespace Rcpp::internal;
using namespace boost;
using namespace boost::icl;
using namespace boost::adaptors;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool is_regular_constructor(SEXP* args, int nargs) {
	return (nargs == 3) && Rf_isNumeric(args[0]) && (LENGTH(args[0]) == 1) && Rf_isNumeric(args[1]) && Rf_isNumeric(args[2]);
}

bool is_irregular_constructor(SEXP* args, int nargs) {
	return (nargs == 3) && Rf_isNumeric(args[0]) && (LENGTH(args[0]) > 1) && Rf_isNumeric(args[1]) && Rf_isNumeric(args[2]);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

fuzzy_wrapper::fuzzy_wrapper(FISIN *fisin) : fisin(fisin) {}

int fuzzy_wrapper::get_mf_size() const {
	return fisin->GetNbMf();
}

bool fuzzy_wrapper::is_ordered() const {
	double inf, sup;
	for(int i = 0; i < fisin->GetNbMf(); i++)
		if(i && (fisin->GetMF(i)->Kernel(inf, sup) < fisin->GetMF(i - 1)->Kernel(inf, sup)))
			return false;
	return true;
}

bool fuzzy_wrapper::is_standardized() const {
	if(is_ordered()) {
		int *sorted = nullptr;
		return fisin->IsSfp(sorted);
	} else
		return false;
}

void fuzzy_wrapper::add_mf(const mf_wrapper &mf) {
	fisin->AddMF(mf.clone());
}

SEXP fuzzy_wrapper::get_mf(int mf_index) const {
	closed_interval<int> mf_index_interval(1, fisin->GetNbMf());
	if(!contains(mf_index_interval, mf_index))
		stop(str(format("mf_index must be in range %1%") % mf_index_interval));
	MF *mf = fisin->GetMF(mf_index - 1);
	if(MFTRI *mftri = dynamic_cast<MFTRI *>(mf))
		return make_new_object(new mf_triangular_wrapper(mftri, false));
	else if(MFTRAPINF *mftrapinf = dynamic_cast<MFTRAPINF *>(mf))
		return make_new_object(new mf_trapezoidal_inf_wrapper(mftrapinf, false));
	else if(MFTRAPSUP *mftrapsup = dynamic_cast<MFTRAPSUP *>(mf))
		return make_new_object(new mf_trapezoidal_sup_wrapper(mftrapsup, false));
	else if(MFTRAP *mftrap = dynamic_cast<MFTRAP *>(mf))
		return make_new_object(new mf_trapezoidal_wrapper(mftrap, false));
	else
		stop(str(format("unsupported mf type '%1%'") % typeid(*mf).name()));
}

List fuzzy_wrapper::get_mfs() const {
	auto mf_range = counting_range(0, fisin->GetNbMf());
	auto rcpp_mf_range = mf_range | transformed([this](int mf_index) { return this->get_mf(mf_index + 1); });
	return List(boost::begin(rcpp_mf_range), boost::end(rcpp_mf_range));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fuzzy_to_stream(ostream &os, const FISIN *fisin) {
	FISIN *nc_fisin = const_cast<FISIN *>(fisin);
	auto mf_range = counting_range(0, nc_fisin->GetNbMf());
	for_each(mf_range, [&os, nc_fisin](int mf_index) {
		os << str(format("mf%1% = ") % (mf_index + 1));
		os << nc_fisin->GetMF(mf_index) << endl;
	});
}
