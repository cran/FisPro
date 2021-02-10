context("FisOutCrisp")

test_that("FisOutCrisp default constructor", {
  fisout <- NewFisOutCrisp()
  expect_equal(fisout$range(), c("min" = 0, "max" = 1))
})

test_that("FisOutCrisp default range constructor", {
  fisout <- NewFisOutCrisp(1, 2)
  expect_equal(fisout$range(), c("min" = 1, "max" = 2))
})

test_that("FisOutCrisp name", {
  fisout <- NewFisOutCrisp()
  expect_equal(fisout$name, "")
  fisout$name <- "foo"
  expect_equal(fisout$name, "foo")
})

test_that("FisOutCrisp defuzzification", {
  fisout <- NewFisOutCrisp()
  expect_equal(fisout$defuzzification, "sugeno")
  fisout$defuzzification <- "MaxCrisp"
  expect_equal(fisout$defuzzification, "MaxCrisp")
  fisout$defuzzification <- "sugeno"
  expect_equal(fisout$defuzzification, "sugeno")
  expect_error(fisout$defuzzification <- "foo")
})

test_that("FisOutCrisp disjunction", {
  fisout <- NewFisOutCrisp()
  expect_equal(fisout$disjunction, "max")
  fisout$disjunction <- "sum"
  expect_equal(fisout$disjunction, "sum")
  fisout$disjunction <- "max"
  expect_equal(fisout$disjunction, "max")
  expect_error(fisout$disjunction <- "foo")
})

test_that("FisOutCrisp equality", {
  fisout1 <- NewFisOutCrisp(0, 1)
  fisout2 <- NewFisOutCrisp(0, 1)
  fisout3 <- NewFisOutCrisp(0, 2)
  expect_equal(fisout1, fisout2)
  expect_not_equal(fisout1, fisout3)
})
