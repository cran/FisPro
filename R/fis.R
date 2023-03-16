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

#' @title Class "Fis"
#' @name Fis
#' @docType class
#' @description Class to manage a Fis "Fuzzy Inference System"
#'
#' @field name [character] vector, The name of the Fis
#' @field conjunction [character] vector, The conjunction operator of rules in the Fis\cr
#' Allowed values are: "min" (the default), "prod" or "luka"\cr
#'
#' @section Constructors:
#' \describe{
#' \item{`Fis()`}{
#' The default constructor to build an empty Fis\cr
#' The Fis is initialized with "min" conjunction and empty name\cr
#' The design must be completed using the available functions to add inputs, outputs and rules before it can be used for inference
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{return:}{[Fis] object}
#' }}
#'
#' \item{`Fis(fis_file)`}{
#' The constructor to build a Fis from a configuration file\cr
#' The configuration file can be designed using the [FisPro](https://www.fispro.org) open source software
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{argument: `fis_file`}{[character] vector, The filename of the Fis configuration file}
#' \item{return:}{[Fis] object}
#' }}}
#'
#' @section Methods:
#' \describe{
#' \item{`input_size()`}{
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{return:}{[integer] value, The number of inputs in the Fis}
#' }}
#'
#' \item{`add_input(input)`}{
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{argument: `input`}{[FisIn] object, The input to add in the Fis}
#' }}
#'
#' \item{`get_input(input_index)`}{
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{argument: `input_index`}{[integer] value, The index (1-based index) of the input in the Fis}
#' \item{return:}{[FisIn] object}
#' }}
#'
#' \item{`get_inputs()`}{
#' Get all inputs in the Fis
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{return:}{[list] of [FisIn] objects}
#' }}
#'
#' \item{`output_size()`}{
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{return:}{[integer] value, The number of outputs in the Fis}
#' }}
#'
#' \item{`add_output(output)`}{
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{argument: `output`}{[FisOut] object, The output to add in the Fis}
#' }}
#'
#' \item{`get_output(output_index)`}{
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{argument: `output_index`}{[integer] value, The index (1-based index) of the output in the Fis}
#' \item{return:}{[FisOut] object}
#' }}
#'
#' \item{`get_outputs()`}{
#' Get all outputs in the Fis
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{return:}{[list] of [FisOut] objects}
#' }}
#'
#' \item{`rule_size()`}{
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{return:}{[integer] value, The number of rules in the Fis}
#' }}
#'
#' \item{`add_rule(rule)`}{
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{argument: `rule`}{[Rule] object, The rule to add in the Fis}
#' }}
#'
#' \item{`get_rule(rule_index)`}{
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{argument: `rule_index`}{[integer] value, The index (1-based index) of the rule in the Fis}
#' \item{return:}{[Rule] object}
#' }}
#'
#' \item{`get_rules()`}{
#' Get all rules in the Fis
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{return:}{[list] of [Rule] objects}
#' }}
#'
#' \item{`infer(data)`}{
#' Infers all outputs
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{argument: `data`}{[numeric] vector, [matrix] or [data.frame], The input data or dataset to infer (the vector length or the number of columns must be equal to the number of inputs)}
#' \item{return:}{[numeric] vector or [matrix] (in case of 2D input data)}
#' }}
#'
#' \item{`infer_output(data, output_index)`}{
#' Infers a single output
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{argument: `data`}{[numeric] vector, [matrix] or [data.frame], The input data or dataset to infer (the vector length or the number of columns must be equal to the number of inputs)}
#' \item{argument: `output_index`}{[integer] value, The index (1-based index) of the output to infer}
#' \item{return:}{[numeric] value or vector (in case of 2D input data)}
#' }}}
#'
#' @seealso {
#'   [NewFis]
#'
#'   [Fuzzy Logic Elementary Glossary](https://www.fispro.org/documentation/en/inline-help/node39.html)
#' }
#'
#' @examples
#' # build a Fis from a configuration file
#' fis_file <- system.file("extdata", "test.fis", package = "FisPro")
#' fis <- NewFis(fis_file)
#'
#' # infers all outputs
#' inferred <- fis$infer(c(0.25, 0.75))
#'
#' # infers first output
#' inferred_output1 <- fis$infer_output(c(0.25, 0.75), 1)
#'
#' # infers second output
#' inferred_output2 <- fis$infer_output(c(0.25, 0.75), 2)
#'
#' # infers test_data dataset
#' test_file <- system.file("extdata", "test_data.csv", package = "FisPro")
#' dataset <- read.csv(test_file)
#' inferred_dataset <- fis$infer(dataset)
#'
#' ########################################################################
#'
#' # or build a Fis from scratch
#' fis <- NewFis()
#' fis$name <- "foo"
#'
#' # build the first input
#' fisin1 <- NewFisIn(0, 1)
#' fisin1$name <- "input1"
#' fisin1$add_mf(NewMfTrapezoidalInf(0, 1))
#' fisin1$add_mf(NewMfTrapezoidalSup(0, 1))
#' fis$add_input(fisin1)
#'
#' # build the second input
#' fisin2 <- NewFisIn(0, 1)
#' fisin2$name <- "input2"
#' fisin2$add_mf(NewMfTrapezoidalInf(0, 0.5))
#' fisin2$add_mf(NewMfTriangular(0, 0.5, 1))
#' fisin2$add_mf(NewMfTrapezoidalSup(0.5, 1))
#' fis$add_input(fisin2)
#'
#' # build an output
#' fisout <- NewFisOutCrisp(0, 1)
#' fisout$name <- "output"
#' fis$add_output(fisout)
#'
#' # add rules to the Fis
#' fis$add_rule(NewRule(c(1, 2), 0))
#' fis$add_rule(NewRule(c(2, 0), 1))
#' @export Fis
NULL

#' @title Create object of class "Fis"
#' @name NewFis
#' @docType methods
#' @description Function to create object of class [Fis]
#'
#' @param ... arguments of [Fis] constructor
#' @return [Fis] object
#'
#' @export
NewFis <- function(...) {
  return(new(Fis, ...))
}

#' @description Overload of [all.equal] method
#' @noRd
#' @export
all.equal.Rcpp_Fis <- function(target, current, ...) {
  return(target$equals(current))
}
