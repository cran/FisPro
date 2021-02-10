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
#include <rule_wrapper.h>
#include <base/fis.h>
#include <boost/format.hpp>
#include <boost/icl/closed_interval.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm_ext/for_each.hpp>

using namespace Rcpp;
using namespace std;
using namespace util;
using namespace boost;
using namespace boost::icl;
using namespace boost::adaptors;
using namespace boost::algorithm;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void check_premise(FISIN *input, int premise) {
	closed_interval<int> premise_interval(0, input->GetNbMf());
	if(!contains(premise_interval, premise))
		stop(str(format("the premise value must be in range %1% for input '%2%'") % premise_interval % input->Name));
}

void check_premises(FISIN **inputs, int input_size, IntegerVector premises) {
	if(input_size != LENGTH(premises))
		stop("the rule's premise length not matches the number of inputs");
	auto fisin_range = make_iterator_range(inputs, inputs + input_size);
	for_each(fisin_range, premises, check_premise);
}

static void check_conclusion(FISOUT *fisout, double conclusion) {
	if(OUT_FUZZY* out_fuzzy = dynamic_cast<OUT_FUZZY *>(fisout)) {
		closed_interval<int> conclusion_interval(1, out_fuzzy->GetNbMf());
		if(!contains(conclusion_interval, conclusion))
			stop(str(format("the conclusion value must be in range %1% for output '%2%'") % conclusion_interval % out_fuzzy->Name));
	} else if(OUT_CRISP* out_crisp = dynamic_cast<OUT_CRISP *>(fisout)) {
		closed_interval<int> range_interval(out_crisp->min(), out_crisp->max());
		if(!contains(range_interval, conclusion))
			warning(str(format("the conclusion value is outside range %1% for output '%2%'") % range_interval % out_crisp->Name));
	} else
		stop(str(format("unsupported output type '%1%'") % typeid(*fisout).name()));
}

void check_conclusions(FISOUT **outputs, int output_size, NumericVector conclusions) {
	if(output_size != LENGTH(conclusions))
		stop("the rule's conclusion length not matches the number of outputs");
	auto fisout_range = make_iterator_range(outputs, outputs + output_size);
	for_each(fisout_range, conclusions, check_conclusion);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rule_wrapper::rule_wrapper() {}

rule_wrapper::rule_wrapper(RULE *rule) : rule(rule, ptr_deleter(false)) {}

rule_wrapper::rule_wrapper(IntegerVector premises, NumericVector conclusions) : premises(premises), conclusions(conclusions) {}

void rule_wrapper::set_premises(IntegerVector premises) {
	if(rule) {
		check_premises(rule->GetInputs(), rule->GetNbProp(), premises);
		rule->SetAProps(premises.begin());
	} else
		this->premises = premises;
}

IntegerVector rule_wrapper::get_premises() const {
	if(rule) {
		IntegerVector premises(rule->GetNbProp());
		rule->GetProps(premises.begin());
		return premises;
	} else
		return premises;
}

void rule_wrapper::set_conclusions(NumericVector conclusions) {
	if(rule) {
		check_conclusions(rule->GetOutputs(), rule->GetNbConc(), conclusions);
		rule->SetConcs(conclusions.begin());
	} else
		this->conclusions = conclusions;
}

NumericVector rule_wrapper::get_conclusions() const {
	if(rule) {
		NumericVector conclusions(rule->GetNbConc());
		rule->GetConcs(conclusions.begin());
		return conclusions;
	} else
		return conclusions;
}

string rule_wrapper::to_string() const {
	auto premise_range = get_premises() | transformed([](int premise) { return std::to_string(premise); });
	auto conclusion_range = get_conclusions() | transformed([](int conclusion) { return std::to_string(conclusion); });
	return str(format("rule(premises = [%1%], conclusions = [%2%])") % join(premise_range, ", ") % join(conclusion_range, ", "));
}
