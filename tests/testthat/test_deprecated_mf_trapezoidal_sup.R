context("Deprecated mf_trapezoidal_sup")

test_that("Deprecated mf trapezoidal sup degrees", {
  expect_warning(mf <- new(mf_trapezoidal_sup, 0, 1), "deprecated")

  expect_equal(mf$degree(0), 0)
  expect_equal(mf$degree(0.5), 0.5)
  expect_equal(mf$degree(1), 1)
})
