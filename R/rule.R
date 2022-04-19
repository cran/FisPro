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

#' @title Class "Rule"
#' @name Rule
#' @docType class
#' @description Class to manage a [Fis] rule
#'
#' @field premises [integer] vector, The premises of the rule\cr
#' A premise is the 1-based index of MF in the [FisIn]\cr
#' 0 means the input is not taken into account for this rule, i.e. the rule is incomplete\cr
#' The vector length must be equal to the number of inputs in the [Fis]
#' @field conclusions [numeric] vector, The conclusions of the rule\cr
#' A conclusion is a [numeric] value for crisp output [FisOutCrisp], or the 1-based index of MF in the fuzzy output [FisOutFuzzy]\cr
#' The vector length must be equal to the number of outputs in the [Fis]
#'
#' @section Constructors:
#' \describe{
#' \item{`Rule()`}{
#' The default constructor to build an empty rule\cr
#' The rule is initialized with empty premises and conclusions
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{return:}{[Rule] object}
#' }}
#'
#' \item{`Rule(premises, conclusions)`}{
#' The constructor to build a rule
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{argument: `premises`}{[integer] vector, The premises of the rule (the vector length must be equal to the number of inputs in the [Fis])}
#' \item{argument: `conclusions`}{[numeric] vector, The conclusions of the rule (the vector length must be equal to the number of outputs in the [Fis])}
#' \item{return:}{[Rule] object}
#' }}}
#'
#' @examples
#' rule1 <- NewRule()
#' rule1$premises <- c(1, 2, 0)
#' rule1$conclusions <- c(1, 2)
#'
#' rule2 <- NewRule(c(2, 1, 1), c(2, 1))
#' @seealso {
#'   [NewRule]
#'
#'   [Fuzzy Logic Elementary Glossary](https://www.fispro.org/documentation/en/inline-help/node39.html)
#' }
#'
#' @export Rule
NULL

#' @title Create object of class "Rule"
#' @name NewRule
#' @docType methods
#' @description Function to create object of class [Rule]
#'
#' @param ... arguments of [Rule] constructor
#' @return [Rule] object
#'
#' @export
NewRule <- function(...) {
  return(new(Rule, ...))
}
