context("Deprecated mf_triangular")

test_that("Deprecated mf triangular degrees", {
  expect_warning(mf <- new(mf_triangular, 0, 1, 2), "deprecated")

  expect_equal(mf$degree(0), 0)
  expect_equal(mf$degree(0.5), 0.5)
  expect_equal(mf$degree(1), 1)
  expect_equal(mf$degree(1.5), 0.5)
  expect_equal(mf$degree(2), 0)
})
