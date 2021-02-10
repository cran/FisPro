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
#ifndef H39FBBF25_4257_4DF1_BEC6_9289D2CCC239
#define H39FBBF25_4257_4DF1_BEC6_9289D2CCC239

#include <Rcpp.h>
#include <base/fis.h>
#include <memory>
#include <fisin_wrapper.h>
#include <fisout_wrapper.h>
#include <rule_wrapper.h>

class fis_wrapper {

private:
	std::unique_ptr<FIS> fis;

	fis_wrapper(FIS *fis);
	fis_wrapper(const fis_wrapper &) = delete;
	fis_wrapper(fis_wrapper &&) = delete;
	fis_wrapper& operator=(const fis_wrapper &) = delete;
	fis_wrapper& operator=(fis_wrapper &&) = delete;

	void check_rule(const rule_wrapper &rule) const;
	void check_infer_values(Rcpp::NumericVector values) const;

public:
	fis_wrapper();
	fis_wrapper(const char *fis_file);

	void set_name(const char *name);
	const char *get_name() const;

	void set_conjunction(const char *conjunction);
	const char *get_conjunction() const;

	int get_input_size() const;
	void add_input(const fisin_wrapper &input);
	SEXP get_input(int input_index) const;
	Rcpp::List get_inputs() const;

	int get_output_size() const;
	void add_output(const fisout_wrapper &output);
	SEXP get_output(int output_index) const;
	Rcpp::List get_outputs() const;

	int get_rule_size() const;
	void add_rule(const rule_wrapper &rule);
	SEXP get_rule(int rule_index) const;
	Rcpp::List get_rules() const;

	Rcpp::NumericVector infer(Rcpp::NumericVector data) const;
	SEXP infer(Rcpp::NumericMatrix data) const;
	SEXP infer(Rcpp::DataFrame data) const;
	double infer_output(Rcpp::NumericVector data, int output_index) const;
	Rcpp::NumericVector infer_output(Rcpp::NumericMatrix data, int output_index) const;
	Rcpp::NumericVector infer_output(Rcpp::DataFrame data, int output_index) const;

	bool equals(const fis_wrapper &other) const;

	void save(const char *fis_file) const;

	std::string to_string() const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream &os, const FIS *fis);

#endif // H39FBBF25_4257_4DF1_BEC6_9289D2CCC239
