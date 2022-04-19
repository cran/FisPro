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
#include <fis_wrapper.h>
#include <boost/format.hpp>
#include <boost/assign.hpp>
#include <boost/icl/closed_interval.hpp>
#include <boost/range/counting_range.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/algorithm/string/join.hpp>

using namespace Rcpp;
using namespace Rcpp::internal;
using namespace std;
using namespace boost;
using namespace boost::icl;
using namespace boost::assign;
using namespace boost::adaptors;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static FIS *make_fis(const char *fis_file) {
	try {
		return new FIS(fis_file);
	} catch(std::exception &e) {
		stop(str(format("cannot load Fis file '%1%'") % fis_file));
	}
}

struct row_getter {

	typedef NumericVector result_type;

	NumericMatrix data;

	row_getter(NumericMatrix data) : data(data) {}

	NumericVector operator()(int row_index) const {
		return data.row(row_index);
	}
};

struct inferred_back_inserter {

	vector<double> &inferred_values;

	inferred_back_inserter(vector<double> &inferred_values) : inferred_values(inferred_values) {}

	void operator()(const NumericVector &inferred) const {
		push_back(inferred_values).range(inferred);
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

fis_wrapper::fis_wrapper(FIS *fis) : fis(fis) {}

fis_wrapper::fis_wrapper() : fis_wrapper(new FIS()) {}

fis_wrapper::fis_wrapper(const char *fis_file) : fis_wrapper(make_fis(fis_file)) {}

void fis_wrapper::set_name(const char *name) {
	fis->SetName(name);
}

const char *fis_wrapper::get_name() const {
	return fis->Name;
}

void fis_wrapper::set_conjunction(const char *conjunction) {
	if((strcmp(conjunction, RULE::PremiseMin()) != 0) && (strcmp(conjunction, RULE::PremiseProd()) != 0) && (strcmp(conjunction, RULE::PremiseLuka()) != 0))
		stop(str(format("unknown conjunction '%1%'") % conjunction));
	fis->SetConjunction(conjunction);
}

const char *fis_wrapper::get_conjunction() const {
	return fis->TypeConj();
}

int fis_wrapper::get_input_size() const {
	return fis->GetNbIn();
}

void fis_wrapper::add_input(const fisin_wrapper &input) {
	fis->AddInput(input.clone());
}

SEXP fis_wrapper::get_input(int input_index) const {
	closed_interval<int> input_index_interval(1, fis->GetNbIn());
	if(!contains(input_index_interval, input_index))
		stop(str(format("input_index must be in range %1%") % input_index_interval));
	FISIN *fisin = fis->In[input_index - 1];
	return make_new_object(new fisin_wrapper(fisin, false));
}

List fis_wrapper::get_inputs() const {
	auto fisin_range = counting_range(0, fis->GetNbIn());
	auto rcpp_fisin_range = fisin_range | transformed([this](int input_index) { return this->get_input(input_index + 1); });
	return List(boost::begin(rcpp_fisin_range), boost::end(rcpp_fisin_range));
}

int fis_wrapper::get_output_size() const {
	return fis->GetNbOut();
}

void fis_wrapper::add_output(const fisout_wrapper &output) {
	fis->AddOutput(output.clone());
}

SEXP fis_wrapper::get_output(int output_index) const {
	closed_interval<int> output_index_interval(1, fis->GetNbOut());
	if(!contains(output_index_interval, output_index))
		stop(str(format("output_index must be in range %1%") % output_index_interval));
	FISOUT *fisout = fis->Out[output_index - 1];
	if(OUT_CRISP *out_crisp = dynamic_cast<OUT_CRISP *>(fisout))
		return make_new_object(new fisout_crisp_wrapper(out_crisp, false));
	else if(OUT_FUZZY *out_fuzzy = dynamic_cast<OUT_FUZZY *>(fisout))
		return make_new_object(new fisout_fuzzy_wrapper(out_fuzzy, false));
	else
		stop(str(format("unsupported output type '%1%'") % typeid(*fisout).name()));
}

List fis_wrapper::get_outputs() const {
	auto fisout_range = counting_range(0, fis->GetNbOut());
	auto rcpp_fisout_range = fisout_range | transformed([this](int output_index) { return this->get_output(output_index + 1); });
	return List(boost::begin(rcpp_fisout_range), boost::end(rcpp_fisout_range));
}

int fis_wrapper::get_rule_size() const {
	return fis->GetNbRule();
}

void fis_wrapper::check_rule(const rule_wrapper &rule) const {
	check_premises(fis->In, fis->GetNbIn(), rule.get_premises());
	check_conclusions(fis->Out, fis->GetNbOut(), rule.get_conclusions());
}

void fis_wrapper::add_rule(const rule_wrapper &rule) {
	check_rule(rule);
	RULE *new_rule = new RULE();
	new_rule->SetPremise(fis->GetNbIn(), fis->In, fis->TypeConj());
	new_rule->SetConclusion(fis->GetNbOut(), fis->Out);
	IntegerVector premises = rule.get_premises();
	new_rule->SetAProps(premises.begin());
	NumericVector conclusions = rule.get_conclusions();
	new_rule->SetConcs(conclusions.begin());
	fis->AddRule(new_rule);
}

SEXP fis_wrapper::get_rule(int rule_index) const {
	closed_interval<int> rule_index_interval(1, fis->GetNbRule());
	if(!contains(rule_index_interval, rule_index))
		stop(str(format("rule_index must be in range %1%") % rule_index_interval));
	RULE *rule = fis->Rule[rule_index - 1];
	return make_new_object(new rule_wrapper(rule));
}

List fis_wrapper::get_rules() const {
	auto rule_range = counting_range(0, fis->GetNbRule());
	auto rcpp_rule_range = rule_range | transformed([this](int rule_index) { return this->get_rule(rule_index + 1); });
	return List(boost::begin(rcpp_rule_range), boost::end(rcpp_rule_range));
}

void fis_wrapper::check_infer_values(NumericVector data) const {
	if(fis->GetNbRule() == 0)
		stop("no rule to infer");
	if(data.size() != fis->GetNbIn())
		stop("data length must be equal to input size");
}

NumericVector fis_wrapper::infer(NumericVector data) const {
	check_infer_values(data);
	fis->Infer(data.begin());
	return NumericVector(fis->OutValue, fis->OutValue + fis->GetNbOut());
}

SEXP fis_wrapper::infer(NumericMatrix data) const {
	auto row_range = counting_range(0, data.nrow()) | transformed(row_getter(data));
	auto infer_range = row_range | transformed([this](NumericVector data) { return this->infer(data); });
	vector<double> inferred_values;
	for_each(infer_range, inferred_back_inserter(inferred_values));
	if(fis->GetNbOut() == 1)
		return NumericVector(boost::begin(inferred_values), boost::end(inferred_values));
	else {
		NumericMatrix inferred = transpose(NumericMatrix(fis->GetNbOut(), data.nrow(), inferred_values.begin()));
		auto name_range = counting_range(0, fis->GetNbOut()) | transformed([this](int output_index) { return fis->Out[output_index]->Name; });
		CharacterVector names(boost::begin(name_range), boost::end(name_range));
		colnames(inferred) = names;
		return inferred;
	}
}

SEXP fis_wrapper::infer(DataFrame data) const {
	Function as_matrix("as.matrix");
	return infer(as<NumericMatrix>(as_matrix(data)));
}

double fis_wrapper::infer_output(NumericVector data, int output_index) const {
	check_infer_values(data);
	closed_interval<int> output_number_interval(1, fis->GetNbOut());
	if(!contains(output_number_interval, output_index))
		stop(str(format("output_number must be in range %1%") % output_number_interval));
	fis->Infer(data.begin(), output_index - 1);
	return fis->OutValue[output_index - 1];
}

NumericVector fis_wrapper::infer_output(NumericMatrix data, int output_index) const {
	auto row_range = counting_range(0, data.nrow()) | transformed(row_getter(data));
	auto infer_range = row_range | transformed([this, output_index](NumericVector data) { return this->infer_output(data, output_index); });
	return NumericVector(boost::begin(infer_range), boost::end(infer_range));
}

NumericVector fis_wrapper::infer_output(DataFrame data, int output_index) const {
	Function as_matrix("as.matrix");
	return infer_output(as<NumericMatrix>(as_matrix(data)), output_index);
}

bool fis_wrapper::equals(const fis_wrapper &other) const {
	return !(*fis != *other.fis);
}

void fis_wrapper::save(const char *fis_file) const {
	if(FILE *file = fopen(fis_file, "wt")) {
		fis->PrintCfg(file);
		fclose(file);
	} else
		stop(str(format("cannot save the Fis to file '%1%'") % fis_file));
}

string fis_wrapper::to_string() const {
	ostringstream os;
	os << fis.get();
	return os.str();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ostream& operator<<(ostream &os, const FIS *fis) {
	FIS *nc_fis = const_cast<FIS *>(fis);
	os << str(format("name = \"%1%\"") % fis->Name) << endl;
	os << str(format("nb inputs = %1%") % nc_fis->GetNbIn()) << endl;
	os << str(format("nb outputs = %1%") % nc_fis->GetNbOut()) << endl;
	os << str(format("nb rules = %1%") % nc_fis->GetNbRule()) << endl;
	os << str(format("conjunction = \"%1%\"") % fis->TypeConj()) << endl;
	auto fisin_range = counting_range(0, nc_fis->GetNbIn());
	for_each(fisin_range, [&os, fis](int fisin_index) {
		os << endl << str(format("[input %1%]") % (fisin_index + 1)) << endl;
		os << fis->In[fisin_index];
	});
	auto fisout_range = counting_range(0, nc_fis->GetNbOut());
	for_each(fisout_range, [&os, fis](int fisout_index) {
		os << endl << str(format("[output %1%]") % (fisout_index + 1)) << endl;
		os << fis->Out[fisout_index];
	});
	if(nc_fis->GetNbRule() != 0) {
		os << endl << "[Rules]" << endl;
		auto rule_range = make_iterator_range(fis->Rule, fis->Rule + nc_fis->GetNbRule());
		for_each(rule_range, [&os](RULE *rule) {
			vector<int> premises(rule->GetNbProp());
			auto premise_range = premises | transformed([](int premise) { return std::to_string(premise); });
			rule->GetProps(&premises[0]);
			vector<double> conclusions(rule->GetNbConc());
			rule->GetConcs(&conclusions[0]);
			auto conclusion_range = conclusions | transformed([](double conclusion) { return str(format("%1%") % conclusion); });
			os << str(format("%1%, %2%") % join(premise_range, ", ") % join(conclusion_range, ", ")) << endl;
		});
	}
	return os;
}
