################################################################################
#
# FisPro R package
#
# Copyright (C) 2019 INRAE
#
# Authors:
# 	Jean-luc Lablée - INRAE
# 	Serge Guillaume - INRAE
#
# License: CeCILL v2.1
# 	https://cecill.info/licences/Licence_CeCILL_V2.1-en.html
# 	https://cecill.info/licences/Licence_CeCILL_V2.1-fr.html
#
# This software is governed by the CeCILL license under French law and
# abiding by the rules of distribution of free software.  You can  use,
# modify and/ or redistribute the software under the terms of the CeCILL
# license as circulated by CEA, CNRS and INRIA at the following URL
# "http://www.cecill.info".
#
# As a counterpart to the access to the source code and  rights to copy,
# modify and redistribute granted by the license, users are provided only
# with a limited warranty  and the software's author,  the holder of the
# economic rights,  and the successive licensors  have only  limited liability.
#
# In this respect, the user's attention is drawn to the risks associated
# with loading,  using,  modifying and/or developing or reproducing the
# software by the user in light of its specific status of free software,
# that may mean  that it is complicated to manipulate,  and  that  also
# therefore means  that it is reserved for developers  and  experienced
# professionals having in-depth computer knowledge. Users are therefore
# encouraged to load and test the software's suitability as regards their
# requirements in conditions enabling the security of their systems and/or
# data to be ensured and,  more generally, to use and operate it in the
# same conditions as regards security.
#
# The fact that you are presently reading this means that you have had
# knowledge of the CeCILL license and that you accept its terms.
#
################################################################################

#' @title Deprecated classes in package \pkg{FisPro}.
#' @name FisPro-deprecated
#' @description The classes listed below are deprecated and will be removed in future version.
#' Alternative classes with similar functionality are also mentioned.\cr
#' Help pages for deprecated functions are available at `help("<class>-deprecated")`.
#'
#' @section Deprecated classes:
#' For [fis], use [Fis] instead\cr
#' For [mf], use [Mf] instead\cr
#' For [mf_triangular], use [MfTriangular] instead\cr
#' For [mf_trapezoidal_inf], use [MfTrapezoidalInf] instead\cr
#' For [mf_trapezoidal_sup], use [MfTrapezoidalSup] instead\cr
#' For [mf_trapezoidal], use [MfTrapezoidal] instead\cr
#'
#' @seealso [fis-deprecated]\cr
#' [mf-deprecated]\cr
#' [mf_triangular-deprecated]\cr
#' [mf_trapezoidal_inf-deprecated]\cr
#' [mf_trapezoidal_sup-deprecated]\cr
#' [mf_trapezoidal-deprecated]
#' @keywords internal
NULL

###############################################################################

#' @title Deprecated class "fis"
#' @name fis-deprecated
#' @description The `fis` class is deprecated and will be removed in future version, use [Fis] instead
#'
#' @section Methods:
#' \describe{
#' \item{`infer_output(data, output_index)`}{
#' WARNING !!! the `output_index` is now 1-based indexed in [Fis], was 0-based indexed in [fis-deprecated]}
#' }
#'
#' @seealso [FisPro-deprecated]
#' @keywords internal
NULL

#' @name fis
#' @rdname fis-deprecated
#'
#' @export fis
NULL

###############################################################################

#' @title Deprecated class "mf"
#' @name mf-deprecated
#' @description The `mf` class is deprecated and will be removed in future version, use [Mf] instead
#'
#' @seealso [FisPro-deprecated]
#' @keywords internal
NULL

#' @name mf
#' @rdname mf-deprecated
#'
#' @export mf
NULL

###############################################################################

#' @title Deprecated class "mf_triangular"
#' @name mf_triangular-deprecated
#' @description The `mf_triangular` class is deprecated and will be removed in future version, use [MfTriangular] instead
#'
#' @seealso [FisPro-deprecated]
#' @keywords internal
NULL

#' @name mf_triangular
#' @rdname mf_triangular-deprecated
#'
#' @export mf_triangular
NULL

###############################################################################

#' @title Deprecated class "mf_trapezoidal_inf"
#' @name mf_trapezoidal_inf-deprecated
#' @description The `mf_trapezoidal_inf` class is deprecated and will be removed in future version, use [MfTrapezoidalInf] instead
#'
#' @seealso [FisPro-deprecated]
#' @keywords internal
NULL

#' @name mf_trapezoidal_inf
#' @rdname mf_trapezoidal_inf-deprecated
#'
#' @export mf_trapezoidal_inf
NULL

###############################################################################

#' @title Deprecated class "mf_trapezoidal_sup"
#' @name mf_trapezoidal_sup-deprecated
#' @description The `mf_trapezoidal_sup` class is deprecated and will be removed in future version, use [MfTrapezoidalSup] instead
#'
#' @seealso [FisPro-deprecated]
#' @keywords internal
NULL

#' @name mf_trapezoidal_sup
#' @rdname mf_trapezoidal_sup-deprecated
#'
#' @export mf_trapezoidal_sup
NULL

###############################################################################

#' @title Deprecated class "mf_trapezoidal"
#' @name mf_trapezoidal-deprecated
#' @description The `mf_trapezoidal` class is deprecated and will be removed in future version, use [MfTrapezoidal] instead
#'
#' @seealso [FisPro-deprecated]
#' @keywords internal
NULL

#' @name mf_trapezoidal
#' @rdname mf_trapezoidal-deprecated
#'
#' @export mf_trapezoidal
NULL
