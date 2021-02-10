context("MfTrapezoidalInf")

test_that("MfTrapezoidalInf constructor error", {
  expect_error(NewMfTrapezoidalInf())
  expect_error(NewMfTrapezoidalInf(1, 0))
  expect_error(NewMfTrapezoidalInf(0, 0))
})

test_that("MfTrapezoidalInf degrees", {
  mf <- NewMfTrapezoidalInf(0, 1)
  expect_equal(mf$degree(0), 1)
  expect_equal(mf$degree(0.5), 0.5)
  expect_equal(mf$degree(1), 0)
})

test_that("MfTrapezoidalInf equality", {
  mf1 <- NewMfTrapezoidalInf(0, 1)
  mf2 <- NewMfTrapezoidalInf(0, 1)
  mf3 <- NewMfTrapezoidalInf(0, 2)
  expect_equal(mf1, mf2)
  expect_not_equal(mf1, mf3)
})

test_that("MfTrapezoidalInf to_string", {
  mf <- NewMfTrapezoidalInf(0, 1)
  mf$label <- "foo"
  expect_equal(mf$to_string(), "mf_trapezoidal_inf(\"foo\", 0, 1)")
})
