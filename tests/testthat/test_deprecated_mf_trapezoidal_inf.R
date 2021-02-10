context("Deprecated mf_trapezoidal_inf")

test_that("Deprecated mf trapezoidal inf degrees", {
  expect_warning(mf <- new(mf_trapezoidal_inf, 0, 1), "deprecated")

  expect_equal(mf$degree(0), 1)
  expect_equal(mf$degree(0.5), 0.5)
  expect_equal(mf$degree(1), 0)
})
