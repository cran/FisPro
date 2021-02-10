context("FisIn")

test_that("FisIn default constructor", {
  fisin <- NewFisIn()
  expect_equal(fisin$mf_size(), 0)
  expect_equal(fisin$range(), c("min" = 0, "max" = 1))
  expect_false(fisin$is_standardized())
})

test_that("FisIn default range constructor", {
  fisin <- NewFisIn(1, 2)
  expect_equal(fisin$mf_size(), 0)
  expect_equal(fisin$range(), c("min" = 1, "max" = 2))
  expect_false(fisin$is_standardized())
})

test_that("FisIn regular constructor", {
  fisin <- NewFisIn(3, 1, 2)
  expect_equal(fisin$mf_size(), 3)
  expect_equal(fisin$range(), c("min" = 1, "max" = 2))
  expect_true(fisin$is_standardized())
})

test_that("FisIn regular constructor error", {
  expect_error(NewFisIn(3, 0, 0))
  expect_error(NewFisIn(3, 1, 0))
  expect_no_error(NewFisIn(3, 0, 1))
})

test_that("FisIn irregular constructor", {
  fisin <- NewFisIn(c(0, 1, 2), 0, 2)
  expect_equal(fisin$mf_size(), 3)
  expect_equal(fisin$range(), c("min" = 0, "max" = 2))
  expect_true(fisin$is_standardized())
})

test_that("FisIn irregular constructor error", {
  expect_error(NewFisIn(c(0, 1, 2), 0, 0))
  expect_error(NewFisIn(c(0, 1, 2), 1, 0))
  expect_error(NewFisIn(c(0, 1, 2), 0, 1))
  expect_error(NewFisIn(c(0, 1, 2), 1, 2))
  expect_no_error(NewFisIn(c(0, 1, 2), 0, 2))
})

test_that("FisIn name", {
  fisin <- NewFisIn()
  expect_equal(fisin$name, "")
  fisin$name <- "foo"
  expect_equal(fisin$name, "foo")
})

test_that("FisIn equality", {
  fisin1 <- NewFisIn(2, 0, 1)
  fisin2 <- NewFisIn(2, 0, 1)
  fisin3 <- NewFisIn(3, 0, 1)
  expect_equal(fisin1, fisin2)
  expect_not_equal(fisin1, fisin3)
  fisin1$add_mf(NewMfTriangular(0, 0.5, 1))
  expect_not_equal(fisin1, fisin2)
})
