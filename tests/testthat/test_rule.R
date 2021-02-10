context("Rule")

test_that("Rule empty constructor", {
  rule <- NewRule()
  expect_equal(rule$premises, numeric())
  expect_equal(rule$conclusions, numeric())
})

test_that("Rule constructor", {
  rule <- NewRule(c(0, 1, 2), c(3, 4))
  expect_equal(rule$premises, c(0, 1, 2))
  expect_equal(rule$conclusions, c(3, 4))
})

test_that("Rule properties", {
  rule <- NewRule()
  rule$premises <- c(0, 1, 2)
  rule$conclusions <- c(3, 4)
  expect_equal(rule$premises, c(0, 1, 2))
  expect_equal(rule$conclusions, c(3, 4))
})
