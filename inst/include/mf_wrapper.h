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
#ifndef H5A29DFC6_9253_452E_BA5C_9EA830848F1C
#define H5A29DFC6_9253_452E_BA5C_9EA830848F1C

#include <Rcpp.h>
#include <base/fis.h>
#include <memory>
#include <util/ptr_deleter.h>

class mf_wrapper {

private:
	std::unique_ptr<MF, util::ptr_deleter> mf;

	mf_wrapper(const mf_wrapper &) = delete;
	mf_wrapper(mf_wrapper &&) = delete;
	mf_wrapper& operator=(const mf_wrapper &) = delete;
	mf_wrapper& operator=(mf_wrapper &&) = delete;

protected:
	mf_wrapper(MF* mf, bool owner = true);

public:
	mf_wrapper();

	MF *clone() const;

	void set_name(const char *name);
	const char *get_name() const;

	double get_degree(double value) const;

	bool equals(const mf_wrapper &other) const;

	std::string to_string() const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class mf_triangular_wrapper : public mf_wrapper {

	friend class fuzzy_wrapper;

	mf_triangular_wrapper(MFTRI *mf_triangular, bool owner = true);

public:
	mf_triangular_wrapper();
	mf_triangular_wrapper(double lower_support, double kernel, double upper_support);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class mf_trapezoidal_inf_wrapper : public mf_wrapper {

	friend class fuzzy_wrapper;

	mf_trapezoidal_inf_wrapper(MFTRAPINF *mf_trapezoidal_inf, bool owner = true);

public:
	mf_trapezoidal_inf_wrapper();
	mf_trapezoidal_inf_wrapper(double upper_kernel, double upper_support);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class mf_trapezoidal_sup_wrapper : public mf_wrapper {

	friend class fuzzy_wrapper;

	mf_trapezoidal_sup_wrapper(MFTRAPSUP *mf_trapezoidal_sup, bool owner = true);

public:
	mf_trapezoidal_sup_wrapper();
	mf_trapezoidal_sup_wrapper(double lower_support, double lower_kernel);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class mf_trapezoidal_wrapper : public mf_wrapper {

	friend class fuzzy_wrapper;

	mf_trapezoidal_wrapper(MFTRAP *mf_trapezoidal, bool owner = true);

public:
	mf_trapezoidal_wrapper();
	mf_trapezoidal_wrapper(double lower_support, double lower_kernel, double upper_kernel, double upper_support);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream &os, const MF *mf);

std::ostream& operator<<(std::ostream &os, const MFTRI *mf_triangular);

std::ostream& operator<<(std::ostream &os, const MFTRAPINF *mf_trapezoidal_inf);

std::ostream& operator<<(std::ostream &os, const MFTRAPSUP *mf_trapezoidal_sup);

std::ostream& operator<<(std::ostream &os, const MFTRAP *mf_trapezoidal);

#endif // H5A29DFC6_9253_452E_BA5C_9EA830848F1C
