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
#ifndef H66D015AF_B966_45E7_B1FC_247F23BDF48A
#define H66D015AF_B966_45E7_B1FC_247F23BDF48A

#include <Rcpp.h>
#include <base/fis.h>
#include <memory>
#include <fuzzy_wrapper.h>
#include <mf_wrapper.h>
#include <util/ptr_deleter.h>

class fisin_wrapper {

	friend class fis_wrapper;

	std::unique_ptr<FISIN, util::ptr_deleter> fisin;
	fuzzy_wrapper fuzzy;

	fisin_wrapper(FISIN *fisin, bool owner = true);
	fisin_wrapper(const fisin_wrapper &) = delete;
	fisin_wrapper(fisin_wrapper &&) = delete;
	fisin_wrapper& operator=(const fisin_wrapper &) = delete;
	fisin_wrapper& operator=(fisin_wrapper &&) = delete;

public:
	fisin_wrapper();
	fisin_wrapper(double minimum, double maximum);
	fisin_wrapper(int number_of_mfs, double minimum, double maximum);
	fisin_wrapper(Rcpp::NumericVector breakpoints, double minimum, double maximum);

	FISIN *clone() const;

	operator const FISIN &() const;

	Rcpp::NumericVector get_range() const;

	void set_name(const char *name);
	const char *get_name() const;

	int get_mf_size() const;
	void add_mf(const mf_wrapper &mf);
	SEXP get_mf(int mf_index) const;
	Rcpp::List get_mfs() const;

	bool is_standardized() const;

	bool equals(const fisin_wrapper &other) const;

	std::string to_string() const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream &os, const FISIN *fisin);

#endif // H66D015AF_B966_45E7_B1FC_247F23BDF48A
