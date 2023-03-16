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

#' @title Class "FisOut"
#' @name FisOut
#' @docType class
#' @description The base class of [Fis] output (cannot be instantiate)\cr
#' Use derived classes [FisOutCrisp] or [FisOutFuzzy]
#'
#' @field name [character] vector, The name of the output
#'
#' @section Methods:
#' \describe{
#' \item{`range()`}{
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{return:}{[numeric] vector, The range of the output (min max values)}
#' }}}
#'
#' @export FisOut
NULL

###############################################################################

#' @title Class "FisOutCrisp"
#' @name FisOutCrisp
#' @docType class
#' @description Class to manage a [Fis] crisp output
#'
#' @section Inherits:
#' [FisOutCrisp] class inherits all fields and methods of [FisOut] class
#'
#' @field defuzzification [character] vector, The defuzzification operator of the crisp output\cr
#' Allowed values are: "sugeno" (the default) or "MaxCrisp"\cr
#' @field disjunction [character] vector, The disjunction operator of the crisp output\cr
#' Allowed values are: "max" (the default) or "sum"\cr
#'
#' @section Constructors:
#' \describe{
#' \item{`FisOutCrisp()`}{
#' The default constructor to build a crisp output with the default range \[0, 1\]
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{return:}{[FisOutCrisp] object}
#' }}
#'
#' \item{`FisOutCrisp(minimum, maximum)`}{
#' The constructor to build a crisp output
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{argument: `minimum`}{[numeric] value, The minimum range value of the output}
#' \item{argument: `maximum`}{[numeric] value, The maximum range value of the output}
#' \item{return:}{[FisOutCrisp] object}
#' }}}
#'
#' @seealso {
#'   [NewFisOutCrisp]
#'
#'   [Fuzzy Logic Elementary Glossary](https://www.fispro.org/documentation/en/inline-help/node39.html)
#' }
#'
#' @examples
#' output <- NewFisOutCrisp(0, 1)
#' output$name <- "foo"
#' output$defuzzification <- "sugeno"
#' output$disjunction <- "max"
#' @export FisOutCrisp
NULL

#' @title Create object of class "FisOutCrisp"
#' @name NewFisOutCrisp
#' @docType methods
#' @description Function to create object of class [FisOutCrisp]
#'
#' @param ... arguments of [FisOutCrisp] constructor
#' @return [FisOutCrisp] object
#'
#' @export
NewFisOutCrisp <- function(...) {
  return(new(FisOutCrisp, ...))
}

#' @description Overload of [all.equal] method
#' @noRd
#' @export
all.equal.Rcpp_FisOutCrisp <- function(target, current, ...) {
  return(target$equals(current))
}

###############################################################################

#' @title Class "FisOutFuzzy"
#' @name FisOutFuzzy
#' @docType class
#' @description Class to manage a [Fis] fuzzy output
#'
#' @section Inherits:
#' [FisOutFuzzy] class inherits all fields and methods of [FisOut] class
#'
#' @field defuzzification [character] vector, The defuzzification operator of the fuzzy output\cr
#' Allowed values are: "sugeno" (the default) "MeanMax", or "area"\cr
#' @field disjunction [character] vector, The disjunction operator of the fuzzy output\cr
#' Allowed values are: "max" (the default) or "sum"\cr
#'
#' @section Constructors:
#' \describe{
#' \item{`FisOutFuzzy()`}{
#' The default constructor to build a fuzzy output with the default range \[0, 1\]
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{return:}{[FisOutFuzzy] object}
#' }}
#'
#' \item{`FisOutFuzzy(minimum, maximum)`}{
#' The constructor to build a fuzzy output
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{argument: `minimum`}{[numeric] value, The minimum range value of the output}
#' \item{argument: `maximum`}{[numeric] value, The maximum range value of the output}
#' \item{return:}{[FisOutFuzzy] object}
#' }}
#'
#' \item{`FisOutFuzzy(number_of_mfs, minimum, maximum)`}{
#' The constructor to build a fuzzy with a regular standardized fuzzy partition
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{argument: `number_of_mfs`}{[integer] value, The number of Mfs in the fuzzy partition}
#' \item{argument: `minimum`}{[numeric] value, The minimum range value of the output}
#' \item{argument: `maximum`}{[numeric] value, The maximum range value of the output}
#' \item{return:}{[FisOutFuzzy] object}
#' }}
#'
#' \item{`FisOutFuzzy(breakpoints, minimum, maximum)`}{
#' The constructor to build a fuzzy with an irregular standardized fuzzy partition
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{argument: `breakpoints`}{[numeric] vector, The breakpoint values (sorted in ascending order) of the Mfs in the fuzzy partition}
#' \item{argument: `minimum`}{[numeric] value, The minimum range value of the output}
#' \item{argument: `maximum`}{[numeric] value, The maximum range value of the output}
#' \item{return:}{[FisOutFuzzy] object}
#' }}}
#'
#' @section Methods:
#' \describe{
#' \item{`mf_size()`}{
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{return:}{[integer] value, The number of Mfs in the output partition}
#' }}
#'
#' \item{`add_mf(mf)`}{
#' Add an Mf in the output partition
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{argument: `mf`}{[Mf] object, The Mf to add}
#' }}
#'
#' \item{`get_mf(mf_index)`}{
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{argument: `mf_index`}{[integer] value, The index (1-based index) of the mf to return}
#' \item{return:}{[Mf] object}
#' }}
#'
#' \item{`get_mfs()`}{
#' Get all mfs in the output
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{return:}{[list] of [Mf] objects}
#' }}
#'
#' \item{`is_standardized()`}{
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{return:}{[logical] value, `TRUE` if the output is a standardized fuzzy partition, `FALSE` otherwise}
#' }}}
#'
#' @seealso {
#'   [NewFisOutFuzzy]
#'
#'   [Fuzzy Logic Elementary Glossary](https://www.fispro.org/documentation/en/inline-help/node39.html)
#' }
#'
#' @examples
#' output <- NewFisOutFuzzy(0, 2)
#' output$name <- "foo"
#' output$defuzzification <- "sugeno"
#' output$disjunction <- "max"
#' output$add_mf(NewMfTrapezoidalInf(0, 1))
#' output$add_mf(NewMfTriangular(0, 1, 2))
#' output$add_mf(NewMfTrapezoidalSup(1, 2))
#' @export FisOutFuzzy
NULL

#' @title Create object of class "FisOutFuzzy"
#' @name NewFisOutFuzzy
#' @docType methods
#' @description Function to create object of class [FisOutFuzzy]
#'
#' @param ... arguments of [FisOutFuzzy] constructor
#' @return [FisOutFuzzy] object
#'
#' @export
NewFisOutFuzzy <- function(...) {
  return(new(FisOutFuzzy, ...))
}

#' @description Overload of [all.equal] method
#' @noRd
#' @export
all.equal.Rcpp_FisOutFuzzy <- function(target, current, ...) {
  return(target$equals(current))
}
