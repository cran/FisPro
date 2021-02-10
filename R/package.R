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

#' @title FisPro package
#' @name FisPro
#' @aliases FisPro-package
#' @docType package
#' @description This package is a basic implementation of the main functions to use a "Fuzzy Inference System" that can be used for reasoning purposes, especially for simulating a physical or biological system. It is derived from the [FisPro](https://www.fispro.org) open source software. Fuzzy inference systems are briefly described in the [Fuzzy Logic Elementary Glossary](https://www.fispro.org/documentation/en/inline-help/node39.html). They are based on fuzzy rules, which have a good capability for managing progressive phenomenons. Fuzzy logic, since the pioneer work by Zadeh, has proven to be a powerful interface between symbolic and numerical spaces. One of the reasons for this success is the ability of fuzzy systems to incorporate human expert knowledge with its nuances, as well as to express the behaviour of the system in an interpretable way for humans. Another reason is the possibility of designing data-driven FIS to make the most of available data.\cr
#' To design a fuzzy system that can be handled by this package the user can use the [FisPro](https://www.fispro.org) software. If needed, the package can be extended to other functions. \cr
#' All the mentioned publications are available from the [FisPro](https://www.fispro.org) web site.\cr
#' Enjoy \pkg{FisPro}!
#' @author FisPro Team \email{contact@fispro.org}
#' @useDynLib FisPro
#' @import Rcpp
#' @importFrom Rdpack reprompt
#' @importFrom methods new
#' @importFrom methods setMethod
#'
#' @references {
#'   \insertRef{Guillaume2011}{FisPro}
#'
#'   \insertRef{ExpertSystems12}{FisPro}
#' }
#'
#' @seealso {
#'   \url{https://www.fispro.org}
#' }
#'
NULL
