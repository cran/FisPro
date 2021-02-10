
expect_rule <- function(rule, expected_premises, expected_conclusions) {
  actual <- quasi_label(rlang::enquo(rule))
  expect_equal(rule$premises, expected_premises, label = actual$lab)
  expect_equal(rule$conclusions, expected_conclusions, label = actual$lab)
}
