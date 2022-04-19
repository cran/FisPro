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

#' @title Class "Fisin"
#' @name FisIn
#' @docType class
#' @description Class to manage a [Fis] input
#'
#' @field name [character] vector, The name of the input
#'
#' @section Constructors:
#' \describe{
#' \item{`FisIn()`}{
#' The default constructor to build an empty input with the default range \[0, 1\]
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{return:}{[FisIn] object}}
#' }
#'
#' \item{`FisIn(minimum, maximum)`}{
#' The constructor to build an empty input
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{argument: `minimum`}{[numeric] value, The minimum range value of the input}
#' \item{argument: `maximum`}{[numeric] value, The maximum range value of the input}
#' \item{return:}{[FisIn] object}
#' }}
#'
#' \item{`FisIn(number_of_mfs, minimum, maximum)`}{
#' The constructor to build an input with a regular standardized fuzzy partition
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{argument: `number_of_mfs`}{[integer] value, The number of Mfs in the fuzzy partition}
#' \item{argument: `minimum`}{[numeric] value, The minimum range value of the input}
#' \item{argument: `maximum`}{[numeric] value, The maximum range value of the input}
#' \item{return:}{[FisIn] object}
#' }}
#'
#' \item{`FisIn(breakpoints, minimum, maximum)`}{
#' The constructor to build an input with an irregular standardized fuzzy partition
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{argument: `breakpoints`}{[numeric] vector, The breakpoint values (sorted in ascending order) of the Mfs in the fuzzy partition}
#' \item{argument: `minimum`}{[numeric] value, The minimum range value of the input}
#' \item{argument: `maximum`}{[numeric] value, The maximum range value of the input}
#' \item{return:}{[FisIn] object}
#' }}}
#'
#' @section Methods:
#' \describe{
#' \item{`range()`}{
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{return:}{[numeric] vector, The range of the input (min max values)}
#' }}
#'
#' \item{`mf_size()`}{
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{return:}{[integer] value, The number of Mfs in the input partition}
#' }}
#'
#' \item{`add_mf(mf)`}{
#' Add an Mf in the input partition
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
#' Get all mfs in the input
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{return:}{[list] of [Mf] objects}
#' }}
#'
#' \item{`is_standardized()`}{
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{return:}{[logical] value, `TRUE` if the input is a standardized fuzzy partition, `FALSE` otherwise}
#' }}}
#'
#' @seealso {
#'   [NewFisIn]
#'
#'   [Fuzzy Logic Elementary Glossary](https://www.fispro.org/documentation/en/inline-help/node39.html)
#' }
#'
#' @examples
#' input <- NewFisIn(0, 2)
#' input$name <- "foo"
#' input$add_mf(NewMfTrapezoidalInf(0, 1))
#' input$add_mf(NewMfTriangular(0, 1, 2))
#' input$add_mf(NewMfTrapezoidalSup(1, 2))
#' @export FisIn
NULL

#' @title Create object of class "FisIn"
#' @name NewFisIn
#' @docType methods
#' @description Function to create object of class [FisIn]
#'
#' @param ... arguments of [FisIn] constructor
#' @return [FisIn] object
#'
#' @export
NewFisIn <- function(...) {
  return(new(FisIn, ...))
}

#' @description Overload of [all.equal] method
#' @noRd
#' @export
all.equal.Rcpp_FisIn <- function(x, y) {
  return(x$equals(y))
}
