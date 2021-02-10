context("Fuzzy")

test_fuzzy_add_mf <- function(fuzzy) {
  fuzzy$add_mf(NewMfTriangular(0, 1, 2))
  expect_equal(fuzzy$mf_size(), 1)
  fuzzy$add_mf(NewMfTrapezoidalInf(0, 1))
  expect_equal(fuzzy$mf_size(), 2)
  fuzzy$add_mf(NewMfTrapezoidalSup(0, 1))
  expect_equal(fuzzy$mf_size(), 3)
  fuzzy$add_mf(NewMfTrapezoidal(0, 1, 2, 3))
  expect_equal(fuzzy$mf_size(), 4)
}

test_that("Fuzzy add mf", {
  test_fuzzy_add_mf(NewFisIn(0, 0, 3))
  test_fuzzy_add_mf(NewFisOutFuzzy(0, 0, 3))
})

test_fuzzy_get_mf <- function(fuzzy) {
  mf1 <- NewMfTriangular(0, 1, 2)
  mf2 <- NewMfTrapezoidalInf(0, 1)
  mf3 <- NewMfTrapezoidalSup(0, 1)
  mf4 <- NewMfTrapezoidal(0, 1, 2, 3)
  fuzzy$add_mf(mf1)
  fuzzy$add_mf(mf2)
  fuzzy$add_mf(mf3)
  fuzzy$add_mf(mf4)
  expect_equal(fuzzy$get_mf(1), mf1)
  expect_equal(fuzzy$get_mf(2), mf2)
  expect_equal(fuzzy$get_mf(3), mf3)
  expect_equal(fuzzy$get_mf(4), mf4)
  expect_error(fuzzy$get_mf(5))
  mfs <- fuzzy$get_mfs()
  expect_equal(length(mfs), 4)
  expect_equal(mfs[[1]], mf1)
  expect_equal(mfs[[2]], mf2)
  expect_equal(mfs[[3]], mf3)
  expect_equal(mfs[[4]], mf4)
  expect_equal(fuzzy$get_mf(1)$label, "")
  mf1 <- fuzzy$get_mf(1)
  mf1$label <- "foo"
  expect_equal(fuzzy$get_mf(1)$label, "foo")
}

test_that("FisIn get mf", {
  test_fuzzy_get_mf(NewFisIn(0, 0, 3))
  test_fuzzy_get_mf(NewFisOutFuzzy(0, 0, 3))
})

test_fuzzy_standardized_partition <- function(fuzzy) {
  fuzzy$add_mf(NewMfTrapezoidalInf(0, 1))
  fuzzy$add_mf(NewMfTrapezoidal(0, 1, 2, 3))
  fuzzy$add_mf(NewMfTriangular(2, 3, 4))
  fuzzy$add_mf(NewMfTrapezoidalSup(3, 4))
  expect_true(fuzzy$is_standardized())
}

test_that("Fuzzy standardized fuzzy partition", {
  test_fuzzy_standardized_partition(NewFisIn(0, 0, 4))
  test_fuzzy_standardized_partition(NewFisOutFuzzy(0, 0, 4))
})

test_fuzzy_not_standardized_partition <- function(fuzzy) {
  fuzzy$add_mf(NewMfTrapezoidalInf(0, 1))
  fuzzy$add_mf(NewMfTrapezoidalSup(1, 2))
  expect_false(fuzzy$is_standardized())
}

test_that("FisIn not standardized fuzzy partition", {
  test_fuzzy_not_standardized_partition(NewFisIn(0, 0, 2))
  test_fuzzy_not_standardized_partition(NewFisOutFuzzy(0, 0, 2))
})

test_fuzzy_unordered_partition <- function(fuzzy) {
  fuzzy$add_mf(NewMfTrapezoidalInf(0, 1))
  fuzzy$add_mf(NewMfTrapezoidalSup(1, 2))
  fuzzy$add_mf(NewMfTriangular(0, 1, 2))
  expect_false(fuzzy$is_standardized())
}

test_that("FisIn unordered fuzzy partition", {
  test_fuzzy_unordered_partition(NewFisIn(0, 0, 2))
  test_fuzzy_unordered_partition(NewFisOutFuzzy(0, 0, 2))
})
