context("MfTriangular")

test_that("MfTriangular constructor error", {
  expect_error(NewMfTriangular())
  expect_error(NewMfTriangular(2, 1, 2))
  expect_error(NewMfTriangular(0, 1, 0))
  expect_error(NewMfTriangular(1, 1, 1))
  expect_no_error(NewMfTriangular(0, 0, 1))
  expect_no_error(NewMfTriangular(0, 1, 1))
})

test_that("MfTriangular degrees", {
  mf <- NewMfTriangular(0, 1, 2)
  expect_equal(mf$degree(0), 0)
  expect_equal(mf$degree(0.5), 0.5)
  expect_equal(mf$degree(1), 1)
  expect_equal(mf$degree(1.5), 0.5)
  expect_equal(mf$degree(2), 0)
})

test_that("MfTriangular equality", {
  mf1 <- NewMfTriangular(0, 1, 2)
  mf2 <- NewMfTriangular(0, 1, 2)
  mf3 <- NewMfTriangular(0, 1, 3)
  expect_equal(mf1, mf2)
  expect_not_equal(mf1, mf3)
})

test_that("MfTriangular to_string", {
  mf <- NewMfTriangular(0, 1, 2)
  mf$label <- "foo"
  expected <- "mf_triangular(\"foo\", 0, 1, 2)"
  expect_equal(mf$to_string(), expected)
  output <- capture.output(show(mf))
  expect_equal(output, expected)
})
