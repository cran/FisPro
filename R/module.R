################################################################################
#
# FisPro R package
#
# Copyright (C) 2020 INRAE
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
# "https://cecill.info".
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

loadModule("mf_module", TRUE)
loadModule("fisin_module", TRUE)
loadModule("fisout_module", TRUE)
loadModule("rule_module", TRUE)
loadModule("fis_module", TRUE)
loadModule("deprecated_module", TRUE)

evalqOnLoad({

  #' @description Fis overload of [show] method
  #' @noRd
  setMethod("show", "Rcpp_Fis", function(object) {
    cat(object$to_string())
  })

  #' @description FisIn overload of [show] method
  #' @noRd
  setMethod("show", "Rcpp_FisIn", function(object) {
    cat(object$to_string())
  })

  #' @description FisOutCrisp overload of [show] method
  #' @noRd
  setMethod("show", "Rcpp_FisOutCrisp", function(object) {
    cat(object$to_string())
  })

  #' @description FisOutFuzzy overload of [show] method
  #' @noRd
  setMethod("show", "Rcpp_FisOutFuzzy", function(object) {
    cat(object$to_string())
  })

  #' @description MfTriangular overload of [show] method
  #' @noRd
  setMethod("show", "Rcpp_MfTriangular", function(object) {
    cat(object$to_string())
  })

  #' @description MfTrapezoidalInf overload of [show] method
  #' @noRd
  setMethod("show", "Rcpp_MfTrapezoidalInf", function(object) {
    cat(object$to_string())
  })

  #' @description MfTrapezoidalSup overload of [show] method
  #' @noRd
  setMethod("show", "Rcpp_MfTrapezoidalSup", function(object) {
    cat(object$to_string())
  })

  #' @description MfTrapezoidal overload of [show] method
  #' @noRd
  setMethod("show", "Rcpp_MfTrapezoidal", function(object) {
    cat(object$to_string())
  })

  #' @description Rule overload of [show] method
  #' @noRd
  setMethod("show", "Rcpp_Rule", function(object) {
    cat(object$to_string())
  })
})
