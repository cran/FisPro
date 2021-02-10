context("Deprecated mf_trapezoidal")

test_that("Deprecated mf trapezoidal degrees", {
  expect_warning(mf <- new(mf_trapezoidal, 0, 1, 2, 3), "deprecated")

  expect_equal(mf$degree(0), 0)
  expect_equal(mf$degree(0.5), 0.5)
  expect_equal(mf$degree(1), 1)
  expect_equal(mf$degree(2), 1)
  expect_equal(mf$degree(2.5), 0.5)
  expect_equal(mf$degree(3), 0)
})
