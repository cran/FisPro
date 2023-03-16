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

#' @title Class "Mf"
#' @docType class
#' @name Mf
#' @description The base class of all "membership function" classes (cannot be instantiate)\cr
#' Use derived classes [MfTriangular], [MfTrapezoidal], [MfTrapezoidalInf] or [MfTrapezoidalSup]
#'
#' @field label [character] vector, The label of the membership function
#'
#' @section Methods:
#' \describe{
#' \item{`degree(value)`}{
#' Get the membership degree
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{argument: `value`}{[numeric] value to compute the membership degree}
#' \item{return:}{[numeric] value}
#' }}}
#'
#' @seealso {
#'   [Fuzzy Logic Elementary Glossary](https://www.fispro.org/documentation/en/inline-help/node39.html)
#' }
#'
#' @export Mf
NULL

###############################################################################

#' @title Class "MfTriangular"
#' @name MfTriangular
#' @docType class
#' @description Class to manage a triangular membership function
#'
#' @section Inherits:
#' `MfTriangular` class inherits all fields and methods of [Mf] class
#'
#' @section Constructors:
#' \describe{
#' \item{`MfTriangular(lower_support, kernel, upper_support)`}{
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{argument: `lower_support`}{[numeric] lower value of support}
#' \item{argument: `kernel`}{[numeric] value of kernel}
#' \item{argument: `upper_support`}{[numeric] upper value of support}
#' \item{return:}{[MfTriangular] object}
#' }}}
#'
#' @seealso [NewMfTriangular]
#'
#' @examples
#' mf <- NewMfTriangular(0, 1, 2)
#' mf$degree(0.5)
#' @export MfTriangular
NULL

#' @title Create object of class "MfTriangular"
#' @name NewMfTriangular
#' @docType methods
#' @description Function to create object of class [MfTriangular]
#'
#' @param ... arguments of [MfTriangular] constructor
#' @return [MfTriangular] object
#'
#' @export
NewMfTriangular <- function(...) {
  return(new(MfTriangular, ...))
}

#' @description Overload of [all.equal] method
#' @noRd
#' @export
all.equal.Rcpp_MfTriangular <- function(target, current, ...) {
  return(target$equals(current))
}

#' @description Overload of [toString] method
#' @noRd
#' @export
toString.Rcpp_MfTriangular <- function(x, ...) {
  return(x$to_string())
}

###############################################################################

#' @title Class "MfTrapezoidalInf"
#' @name MfTrapezoidalInf
#' @docType class
#' @description Class to manage a trapezoidal inf membership function
#'
#' @section Inherits:
#' MfTrapezoidalInf class inherits all fields and methods of [Mf] class
#'
#' @section Constructors:
#' \describe{
#' \item{`MfTrapezoidalInf(upper_kernel, upper_support)`}{
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{argument: `upper_kernel`}{[numeric] upper value of kernel}
#' \item{argument: `upper_support`}{[numeric] upper value of support}
#' \item{return:}{[MfTrapezoidalInf] object}
#' }}}
#'
#' @seealso [NewMfTrapezoidalInf]
#'
#' @examples
#' mf <- NewMfTrapezoidalInf(0, 1)
#' mf$degree(0.5)
#' @export MfTrapezoidalInf
NULL

#' @title Create object of class "MfTrapezoidalInf"
#' @name NewMfTrapezoidalInf
#' @docType methods
#' @description Function to create object of class [MfTrapezoidalInf]
#'
#' @param ... arguments of [MfTrapezoidalInf] constructor
#' @return [MfTrapezoidalInf] object
#'
#' @export
NewMfTrapezoidalInf <- function(...) {
  return(new(MfTrapezoidalInf, ...))
}

#' @description Overload of [all.equal] method
#' @noRd
#' @export
all.equal.Rcpp_MfTrapezoidalInf <- function(target, current, ...) {
  return(target$equals(current))
}

#' @description Overload of [toString] method
#' @noRd
#' @export
toString.Rcpp_MfTrapezoidalInf <- function(x, ...) {
  return(x$to_string())
}

###############################################################################

#' @title Class "MfTrapezoidalSup"
#' @name MfTrapezoidalSup
#' @docType class
#' @description Class to manage a trapezoidal sup membership function
#'
#' @section Inherits:
#' MfTrapezoidalSup class inherits all fields and methods of [Mf] class
#'
#' @section Constructors:
#' \describe{
#' \item{`MfTrapezoidalSup(lower_support, lower_kernel)`}{
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{argument: `lower_support`}{[numeric] lower value of support}
#' \item{argument: `lower_kernel`}{[numeric] lower value of kernel}
#' \item{return:}{[MfTrapezoidalSup] object}
#' }}}
#'
#' @seealso [NewMfTrapezoidalSup]
#'
#' @examples
#' mf <- NewMfTrapezoidalSup(0, 1)
#' mf$degree(0.5)
#' @export MfTrapezoidalSup
NULL

#' @title Create object of class "MfTrapezoidalSup"
#' @name NewMfTrapezoidalSup
#' @docType methods
#' @description Function to create object of class [MfTrapezoidalSup]
#'
#' @param ... arguments of [MfTrapezoidalSup] constructor
#' @return [MfTrapezoidalSup] object
#'
#' @export
NewMfTrapezoidalSup <- function(...) {
  return(new(MfTrapezoidalSup, ...))
}

#' @description Overload of [all.equal] method
#' @noRd
#' @export
all.equal.Rcpp_MfTrapezoidalSup <- function(target, current, ...) {
  return(target$equals(current))
}

#' @description Overload of [toString] method
#' @noRd
#' @export
toString.Rcpp_MfTrapezoidalSup <- function(x, ...) {
  return(x$to_string())
}

###############################################################################

#' @title Class "MfTrapezoidal"
#' @name MfTrapezoidal
#' @docType class
#' @description Class to manage a trapezoidal membership function
#'
#' @section Inherits:
#' MfTrapezoidal class inherits all fields and methods of [Mf] class
#'
#' @section Constructors:
#' \describe{
#' \item{`MfTrapezoidal(lower_support, lower_kernel, upper_kernel, upper_support)`}{
#' \if{latex}{\out{\hfill}}
#' \describe{
#' \item{argument: `lower_support`}{[numeric] lower value of support}
#' \item{argument: `lower_kernel`}{[numeric] lower value of kernel}
#' \item{argument: `upper_kernel`}{[numeric] upper value of kernel}
#' \item{argument: `upper_support`}{[numeric] upper value of support}
#' \item{return:}{[MfTrapezoidal] object}
#' }}}
#'
#' @seealso [NewMfTrapezoidal]
#'
#' @examples
#' mf <- NewMfTrapezoidal(0, 1, 2, 3)
#' mf$degree(0.5)
#' @export MfTrapezoidal
NULL

#' @title Create object of class "MfTrapezoidal"
#' @name NewMfTrapezoidal
#' @docType methods
#' @description Function to create object of class [MfTrapezoidal]
#'
#' @param ... arguments of [MfTrapezoidal] constructor
#' @return [MfTrapezoidal] object
#'
#' @export
NewMfTrapezoidal <- function(...) {
  return(new(MfTrapezoidal, ...))
}

#' @description Overload of [all.equal] method
#' @noRd
#' @export
all.equal.Rcpp_MfTrapezoidal <- function(target, current, ...) {
  return(target$equals(current))
}

#' @description Overload of [toString] method
#' @noRd
#' @export
toString.Rcpp_MfTrapezoidal <- function(x, ...) {
  return(x$to_string())
}
