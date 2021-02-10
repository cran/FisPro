context("MfTrapezoidal")

test_that("MfTrapezoidal constructor error", {
  expect_error(NewMfTrapezoidal())
  expect_error(NewMfTrapezoidal(1, 0, 2, 3))
  expect_error(NewMfTrapezoidal(0, 2, 1, 3))
  expect_error(NewMfTrapezoidal(0, 1, 3, 2))
  expect_error(NewMfTrapezoidal(0, 1, 1, 1))
  expect_no_error(NewMfTrapezoidal(1, 1, 2, 2))
})

test_that("MfTrapezoidal degrees", {
  mf <- NewMfTrapezoidal(0, 1, 2, 3)
  expect_equal(mf$degree(0), 0)
  expect_equal(mf$degree(0.5), 0.5)
  expect_equal(mf$degree(1), 1)
  expect_equal(mf$degree(2), 1)
  expect_equal(mf$degree(2.5), 0.5)
  expect_equal(mf$degree(3), 0)
})

test_that("MfTrapezoidal equality", {
  mf1 <- NewMfTrapezoidal(0, 1, 2, 3)
  mf2 <- NewMfTrapezoidal(0, 1, 2, 3)
  mf3 <- NewMfTrapezoidal(0, 1, 2, 4)
  expect_equal(mf1, mf2)
  expect_not_equal(mf1, mf3)
})

test_that("MfTrapezoidal to_string", {
  mf <- NewMfTrapezoidal(0, 1, 2, 3)
  mf$label <- "foo"
  expect_equal(mf$to_string(), "mf_trapezoidal(\"foo\", 0, 1, 2, 3)")
})
