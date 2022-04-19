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
#ifndef H3D6C24A8_6D1F_4E78_A3B9_8E0D45EACA51
#define H3D6C24A8_6D1F_4E78_A3B9_8E0D45EACA51

#include <Rcpp.h>
#include <base/fis.h>
#include <memory>
#include <util/ptr_deleter.h>

void check_premises(FISIN **inputs, int input_size, Rcpp::IntegerVector premises);
void check_conclusions(FISOUT **outputs, int output_size, Rcpp::NumericVector conclusions);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class rule_wrapper {

	friend class fis_wrapper;

	std::unique_ptr<RULE, util::ptr_deleter> rule;
	Rcpp::IntegerVector premises;
	Rcpp::NumericVector conclusions;

	rule_wrapper(RULE *rule);
	rule_wrapper(const rule_wrapper &) = delete;
	rule_wrapper(rule_wrapper &&) = delete;
	rule_wrapper& operator=(const rule_wrapper &) = delete;
	rule_wrapper& operator=(rule_wrapper &&) = delete;

public:
	rule_wrapper();
	rule_wrapper(Rcpp::IntegerVector premises, Rcpp::NumericVector conclusions);

	void set_premises(Rcpp::IntegerVector premises);
	Rcpp::IntegerVector get_premises() const;

	void set_conclusions(Rcpp::NumericVector conclusions);
	Rcpp::NumericVector get_conclusions() const;

	std::string to_string() const;
};

#endif // H3D6C24A8_6D1F_4E78_A3B9_8E0D45EACA51
