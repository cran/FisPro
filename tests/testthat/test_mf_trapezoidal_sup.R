context("MfTrapezoidalSup")

test_that("MfTrapezoidalSup constructor error", {
  expect_error(NewMfTrapezoidalSup())
  expect_error(NewMfTrapezoidalSup(1, 0))
  expect_error(NewMfTrapezoidalSup(0, 0))
})

test_that("MfTrapezoidalSup degrees", {
  mf <- NewMfTrapezoidalSup(0, 1)
  expect_equal(mf$degree(0), 0)
  expect_equal(mf$degree(0.5), 0.5)
  expect_equal(mf$degree(1), 1)
})

test_that("MfTrapezoidalSup equality", {
  mf1 <- NewMfTrapezoidalSup(0, 1)
  mf2 <- NewMfTrapezoidalSup(0, 1)
  mf3 <- NewMfTrapezoidalSup(0, 2)
  expect_equal(mf1, mf2)
  expect_not_equal(mf1, mf3)
})

test_that("MfTrapezoidalSup to_string", {
  mf <- NewMfTrapezoidalSup(0, 1)
  mf$label <- "foo"
  expect_equal(mf$to_string(), "mf_trapezoidal_sup(\"foo\", 0, 1)")
})
