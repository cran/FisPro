context("FisOutFuzzy")

test_that("FisOutFuzzy default constructor", {
  fisout <- NewFisOutFuzzy()
  expect_equal(fisout$range(), c("min" = 0, "max" = 1))
})

test_that("FisOutFuzzy default range constructor", {
  fisout <- NewFisOutFuzzy(1, 2)
  expect_equal(fisout$range(), c("min" = 1, "max" = 2))
})

test_that("FisOutFuzzy regular constructor", {
  FisOut <- NewFisOutFuzzy(3, 1, 2)
  expect_equal(FisOut$mf_size(), 3)
  expect_equal(FisOut$range(), c("min" = 1, "max" = 2))
  expect_true(FisOut$is_standardized())
})

test_that("FisOutFuzzy regular constructor error", {
  expect_error(NewFisOutFuzzy(3, 0, 0))
  expect_error(NewFisOutFuzzy(3, 1, 0))
  expect_no_error(NewFisOutFuzzy(3, 0, 1))
})

test_that("FisOutFuzzy irregular constructor", {
  fisOut <- NewFisOutFuzzy(c(0, 1, 2), 0, 2)
  expect_equal(fisOut$mf_size(), 3)
  expect_equal(fisOut$range(), c("min" = 0, "max" = 2))
  expect_true(fisOut$is_standardized())
})

test_that("FisOutFuzzy irregular constructor error", {
  expect_error(NewFisOutFuzzy(c(0, 1, 2), 0, 0))
  expect_error(NewFisOutFuzzy(c(0, 1, 2), 1, 0))
  expect_error(NewFisOutFuzzy(c(0, 1, 2), 0, 1))
  expect_error(NewFisOutFuzzy(c(0, 1, 2), 1, 2))
  expect_no_error(NewFisOutFuzzy(c(0, 1, 2), 0, 2))
})

test_that("FisOutFuzzy name", {
  fisout <- NewFisOutFuzzy()
  expect_equal(fisout$name, "")
  fisout$name <- "foo"
  expect_equal(fisout$name, "foo")
})

test_that("FisOutFuzzy defuzzification", {
  fisout <- NewFisOutFuzzy()
  expect_equal(fisout$defuzzification, "sugeno")
  fisout$defuzzification <- "area"
  expect_equal(fisout$defuzzification, "area")
  fisout$defuzzification <- "sugeno"
  expect_equal(fisout$defuzzification, "sugeno")
  fisout$defuzzification <- "MeanMax"
  expect_equal(fisout$defuzzification, "MeanMax")
  expect_error(fisout$defuzzification <- "foo")
})

test_that("FisOutFuzzy disjunction", {
  fisout <- NewFisOutFuzzy()
  expect_equal(fisout$disjunction, "max")
  fisout$disjunction <- "sum"
  expect_equal(fisout$disjunction, "sum")
  fisout$disjunction <- "max"
  expect_equal(fisout$disjunction, "max")
  expect_error(fisout$disjunction <- "foo")
})

test_that("FisOutFuzzy equality", {
  fisout1 <- NewFisOutFuzzy(2, 0, 1)
  fisout2 <- NewFisOutFuzzy(2, 0, 1)
  fisout3 <- NewFisOutFuzzy(3, 0, 1)
  expect_equal(fisout1, fisout2)
  expect_not_equal(fisout1, fisout3)
  fisout1$add_mf(NewMfTriangular(0, 1, 2))
  expect_not_equal(fisout1, fisout2)
})
