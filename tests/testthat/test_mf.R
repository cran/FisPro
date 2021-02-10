context("Mf")

test_that("Mf instantiation error", {
  expect_error(new(Mf))
})

test_mf_label <- function(mf) {
  expect_equal(mf$label, "")
  mf$label <- "foo"
  expect_equal(mf$label, "foo")
}

test_that("Mf label", {
  test_mf_label(NewMfTriangular(0, 1, 2))
  test_mf_label(NewMfTrapezoidalInf(0, 1))
  test_mf_label(NewMfTrapezoidalSup(0, 1))
  test_mf_label(NewMfTrapezoidal(0, 1, 2, 3))
})
