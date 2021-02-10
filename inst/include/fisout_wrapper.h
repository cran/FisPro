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
#ifndef H4BC68904_C3F9_4093_936E_ADE2FECD4C5A
#define H4BC68904_C3F9_4093_936E_ADE2FECD4C5A

#include <Rcpp.h>
#include <base/fis.h>
#include <memory>
#include <fuzzy_wrapper.h>
#include <mf_wrapper.h>
#include <util/ptr_deleter.h>

class fisout_wrapper {

private:
	fisout_wrapper(const fisout_wrapper &) = delete;
	fisout_wrapper(fisout_wrapper &&) = delete;
	fisout_wrapper& operator=(const fisout_wrapper &) = delete;
	fisout_wrapper& operator=(fisout_wrapper &&) = delete;

protected:
	std::unique_ptr<FISOUT, util::ptr_deleter> fisout;

	fisout_wrapper(FISOUT *fisout, bool owner = true);

public:
	fisout_wrapper();

	FISOUT *clone() const;

	Rcpp::NumericVector get_range() const;

	void set_name(const char *name);
	const char *get_name() const;

	bool equals(const fisout_wrapper &other) const;

	std::string to_string() const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class fisout_crisp_wrapper : public fisout_wrapper {

	friend class fis_wrapper;

	fisout_crisp_wrapper(OUT_CRISP *fisout_crisp, bool owner = true);

public:
	fisout_crisp_wrapper();
	fisout_crisp_wrapper(double minimum, double maximum);

	void set_defuzzification(const char *defuzzification);
	const char *get_defuzzification() const;

	void set_disjunction(const char *disjunction);
	const char *get_disjunction() const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class fisout_fuzzy_wrapper : public fisout_wrapper {

	friend class fis_wrapper;

	fuzzy_wrapper fuzzy;

	fisout_fuzzy_wrapper(OUT_FUZZY *fisout_fuzzy, bool owner = true);

public:
	fisout_fuzzy_wrapper();
	fisout_fuzzy_wrapper(double minimum, double maximum);
	fisout_fuzzy_wrapper(int number_of_mfs, double minimum, double maximum);
	fisout_fuzzy_wrapper(Rcpp::NumericVector breakpoints, double minimum, double maximum);

	void set_defuzzification(const char *defuzzification);
	const char *get_defuzzification() const;

	void set_disjunction(const char *disjunction);
	const char *get_disjunction() const;

	int get_mf_size() const;
	bool is_standardized() const;

	void add_mf(const mf_wrapper &mf);
	SEXP get_mf(int mf_index) const;
	Rcpp::List get_mfs() const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream &os, const FISOUT *fisout);

std::ostream& operator<<(std::ostream &os, const OUT_CRISP *fisout_crisp);

std::ostream& operator<<(std::ostream &os, const OUT_FUZZY *fisout_fuzzy);

#endif // H4BC68904_C3F9_4093_936E_ADE2FECD4C5A
