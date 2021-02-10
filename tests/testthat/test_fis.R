context("Fis")

# expected inferred values of test fis test_1_output test_2_outputs with test_data dataset
expected_output1 <- c(0.375, 0.412, 0.542, 0.450, 0.525, 0.625, 0.525, 0.637, 0.708)
expected_output2 <- c(0.295, 0.178, 0.435, 0.404, 0.287, 0.404, 0.500, 0.381, 0.362)
expected_inferred <- matrix(c(expected_output1, expected_output2), length(expected_output1), 2)
colnames(expected_inferred) <- c("output1", "output2")

test_that("Fis default constructor", {
  fis <- NewFis()
  expect_equal(fis$input_size(), 0)
  expect_equal(fis$output_size(), 0)
  expect_equal(fis$rule_size(), 0)
})

test_that("Fis file constructor", {
  fis_file <- system.file("extdata", "test.fis", package = "FisPro")
  fis <- NewFis(fis_file)
  expect_equal(fis$input_size(), 2)
  expect_equal(fis$output_size(), 2)
  expect_equal(fis$rule_size(), 2)
})

test_that("Fis file constructor error", {
  expect_error(NewFis("foo"), "cannot load Fis file 'foo'")
})

test_that("Fis conjunction", {
  fis <- NewFis()
  expect_equal(fis$conjunction, "min")
  fis$conjunction <- "prod"
  expect_equal(fis$conjunction, "prod")
  fis$conjunction <- "min"
  expect_equal(fis$conjunction, "min")
  fis$conjunction <- "luka"
  expect_equal(fis$conjunction, "luka")
  expect_error(fis$conjunction <- "foo", "unknown conjunction")
})

test_that("Fis add input", {
  fis <- NewFis()
  fis$add_input(NewFisIn())
  fis$add_input(NewFisIn())
  expect_equal(fis$input_size(), 2)
})

test_that("Fis get input", {
  fis <- NewFis()
  input1 <- NewFisIn(2, 0, 1)
  input2 <- NewFisIn(3, 0, 1)
  fis$add_input(input1)
  fis$add_input(input2)
  expect_equal(fis$get_input(1), input1)
  expect_equal(fis$get_input(2), input2)
  expect_error(fis$get_input(3), "input_index must be in range \\[1,2\\]")
  inputs <- fis$get_inputs()
  expect_equal(length(inputs), 2)
  expect_equal(inputs[[1]], input1)
  expect_equal(inputs[[2]], input2)
  expect_equal(fis$get_input(1)$name, "")
  input1 <- fis$get_input(1)
  input1$name <- "foo"
  expect_equal(fis$get_input(1)$name, "foo")
})

test_that("Fis add output", {
  fis <- NewFis()
  fis$add_output(NewFisOutCrisp())
  fis$add_output(NewFisOutFuzzy())
  expect_equal(fis$output_size(), 2)
})

test_that("Fis get output", {
  fis <- NewFis()
  output1 <- NewFisOutCrisp()
  output2 <- NewFisOutFuzzy(3, 0, 1)
  fis$add_output(output1)
  fis$add_output(output2)
  expect_equal(fis$get_output(1), output1)
  expect_equal(fis$get_output(2), output2)
  expect_error(fis$get_output(3), "output_index must be in range \\[1,2\\]")
  outputs <- fis$get_outputs()
  expect_equal(length(outputs), 2)
  expect_equal(outputs[[1]], output1)
  expect_equal(outputs[[2]], output2)
  expect_equal(fis$get_output(1)$name, "")
  output1 <- fis$get_output(1)
  output1$name <- "foo"
  expect_equal(fis$get_output(1)$name, "foo")
})

test_that("Fis add rule", {
  fis <- NewFis()
  fis$add_input(NewFisIn(2, 0, 1))
  fis$add_input(NewFisIn(2, 0, 1))
  fis$add_output(NewFisOutCrisp())
  fis$add_rule(NewRule(c(0, 1), 0))
  fis$add_rule(NewRule(c(1, 0), 1))
  expect_equal(fis$rule_size(), 2)
})

test_that("Fis add rule error", {
  fis <- NewFis()
  fis$add_input(NewFisIn(2, 0, 1))
  fis$add_input(NewFisIn(3, 0, 1))
  fis$add_output(NewFisOutCrisp())
  fis$add_output(NewFisOutFuzzy(2, 0, 1))
  expect_error(fis$add_rule(NewRule(c(0, 1, 2), c(0, 1))), "premise length not matches") # premise length error
  expect_error(fis$add_rule(NewRule(c(2, 4), c(0, 1))), "premise value must be in range \\[0,3\\]") # premise value range error
  expect_error(fis$add_rule(NewRule(c(3, 2), c(0, 1))), "premise value must be in range \\[0,2\\]") # premise value range error
  expect_error(fis$add_rule(NewRule(c(0, 1), c(0, 1, 2))), "conclusion length not matches") # conclusion length error
  expect_error(fis$add_rule(NewRule(c(2, 2), c(0, 0))), "conclusion value must be in range \\[1,2\\]") # conclusion fuzzy value range error
  expect_error(fis$add_rule(NewRule(c(2, 2), c(0, 3))), "conclusion value must be in range \\[1,2\\]") # conclusion fuzzy value range error
  expect_warning(fis$add_rule(NewRule(c(2, 2), c(2, 1))), "conclusion value is outside range \\[0,1\\]") # conclusion crisp value range warning
})

test_that("Fis get rule", {
  fis <- NewFis()
  fis$add_input(NewFisIn(2, 0, 1))
  fis$add_input(NewFisIn(2, 0, 1))
  fis$add_output(NewFisOutCrisp())
  fis$add_output(NewFisOutFuzzy(2, 0, 1))
  rule1 <- NewRule(c(0, 1), c(0, 1))
  rule2 <- NewRule(c(1, 0), c(1, 2))
  rule3 <- NewRule(c(1, 1), c(0, 2))
  fis$add_rule(rule1)
  fis$add_rule(rule2)
  fis$add_rule(rule3)
  expect_equal(fis$rule_size(), 3)
  expect_rule(fis$get_rule(1), c(0, 1), c(0, 1))
  expect_rule(fis$get_rule(2), c(1, 0), c(1, 2))
  expect_rule(fis$get_rule(3), c(1, 1), c(0, 2))
  rules <- fis$get_rules()
  expect_equal(length(rules), 3)
  expect_equal(rules[[1]], rule1)
  expect_equal(rules[[2]], rule2)
  expect_equal(rules[[3]], rule3)
  rule <- fis$get_rule(1)
  rule$premises <- c(1, 0)
  rule$conclusions <- c(1, 2)
  expect_rule(rule, c(1, 0), c(1, 2))
  expect_rule(fis$get_rule(1), c(1, 0), c(1, 2))
  expect_equal(rule1$to_string(), "rule(premises = [0, 1], conclusions = [0, 1])")
  expect_equal(rule$to_string(), "rule(premises = [1, 0], conclusions = [1, 2])")
})

test_that("Fis save", {
  fis <- NewFis()
  fis$add_input(NewFisIn(2, 0, 1))
  fis$add_input(NewFisIn(2, 0, 1))
  fis$add_output(NewFisOutCrisp())
  fis$add_output(NewFisOutFuzzy(2, 0, 1))
  fis$add_rule(NewRule(c(0, 1), c(0, 1)))
  fis$add_rule(NewRule(c(1, 0), c(1, 2)))
  fis$add_rule(NewRule(c(1, 1), c(0, 2)))
  fis$save("foo.fis")
  expect_fis <- NewFis("foo.fis")
  expect_equal(fis, expect_fis)
  file.remove("foo.fis")
})

test_that("Fis get rule error", {
  fis <- NewFis()
  fis$add_input(NewFisIn(2, 0, 1))
  fis$add_input(NewFisIn(3, 0, 1))
  fis$add_output(NewFisOutCrisp())
  fis$add_output(NewFisOutFuzzy(2, 0, 1))
  fis$add_rule(NewRule(c(0, 1), c(0, 1)))
  fis$add_rule(NewRule(c(1, 0), c(1, 2)))
  fis$add_rule(NewRule(c(1, 1), c(0, 2)))
  expect_equal(fis$rule_size(), 3)
  expect_error(fis$get_rule(0), "rule_index must be in range \\[1,3\\]")
  expect_error(fis$get_rule(4), "rule_index must be in range \\[1,3\\]")
  rule <- fis$get_rule(1)
  expect_error(rule$premises <- c(0, 1, 2), "the rule's premise length not matches the number of inputs") # premise length error
  expect_error(rule$premises <- c(2, 4), "the premise value must be in range \\[0,3\\]") # premise value range error
  expect_error(rule$premises <- c(3, 2), "the premise value must be in range \\[0,2\\]") # premise value range error
  expect_error(rule$conclusions <- c(0, 1, 2), "conclusion length not matches") # conclusion length error
  expect_error(rule$conclusions <- c(0, 0), "conclusion value must be in range \\[1,2\\]") # conclusion fuzzy value range error
  expect_error(rule$conclusions <- c(0, 3), "conclusion value must be in range \\[1,2\\]") # conclusion fuzzy value range error
  expect_warning(rule$conclusions <- c(2, 1), "conclusion value is outside range") # conclusion crisp value range warning
})

test_that("Fis infer error", {
  fis <- NewFis()
  fis$add_input(NewFisIn(2, 0, 1))
  fis$add_input(NewFisIn(2, 0, 1))
  fis$add_output(NewFisOutCrisp(0, 1))
  fis$add_output(NewFisOutFuzzy(2, 0, 1))
  expect_error(fis$infer(c(0.5, 0.5)), "no rule to infer") # no rule error
  fis$add_rule(NewRule(c(1, 2), c(0, 1)))
  fis$add_rule(NewRule(c(2, 0), c(1, 2)))
  expect_error(fis$infer(c(0.5, 0.5, 0.5)), "data length must be equal to input size") # length error
  expect_error(fis$infer_output(c(0.5, 0.5, 0.5), 1), "data length must be equal to input size") # length error
  expect_error(fis$infer_output(c(0.5, 0.5), 3), "output_number must be in range \\[1,2\\]") # output number error
  expect_no_error(fis$infer_output(c(0.5, 0.5), 1))
})

test_that("Fis infer", {
  fis_file <- system.file("extdata", "test.fis", package = "FisPro")
  fis <- NewFis(fis_file)

  expect_equal(fis$input_size(), 2)
  expect_equal(fis$output_size(), 2)

  expect_equal(fis$infer(c(0.5, 0.5)), c(0.5, 0.5))
  expect_equal(fis$infer(c(0.25, 0.75)), c(0.333, 0.361), tolerance = 1e-3)

  expect_equal(fis$infer_output(c(0.5, 0.5), 1), 0.5)
  expect_equal(fis$infer_output(c(0.25, 0.75), 1), 0.333, tolerance = 1e-3)
  expect_equal(fis$infer_output(c(0.5, 0.5), 2), 0.5)
  expect_equal(fis$infer_output(c(0.25, 0.75), 2), 0.361, tolerance = 1e-3)
})

test_that("Fis infer matrix", {
  data <- as.matrix(read.csv("test_data.csv"))

  fis <- NewFis("test_1_output.fis")
  inferred <- fis$infer(data)
  expect_is(inferred, "numeric")
  expect_equal(inferred, expected_output1, tolerance = 1e-3)
  inferred_output1 <- fis$infer_output(data, 1)
  expect_equal(inferred_output1, expected_output1, tolerance = 1e-3)

  fis <- NewFis("test_2_outputs.fis")
  inferred <- fis$infer(data)
  expect_is(inferred, "matrix")
  expect_equal(inferred, expected_inferred, tolerance = 1e-3)
  expect_equal(colnames(inferred), c("output1", "output2"))
  inferred_output1 <- fis$infer_output(data, 1)
  inferred_output2 <- fis$infer_output(data, 2)
  expect_equal(inferred_output1, expected_output1, tolerance = 1e-3)
  expect_equal(inferred_output2, expected_output2, tolerance = 1e-3)
})

test_that("Fis infer data.frame", {
  data <- read.csv("test_data.csv")

  fis <- NewFis("test_1_output.fis")
  inferred <- fis$infer(data)
  expect_is(inferred, "numeric")
  expect_equal(inferred, expected_output1, tolerance = 1e-3)
  inferred_output1 <- fis$infer_output(data, 1)
  expect_equal(inferred_output1, expected_output1, tolerance = 1e-3)

  fis <- NewFis("test_2_outputs.fis")
  inferred <- fis$infer(data)
  expect_is(inferred, "matrix")
  expect_equal(inferred, expected_inferred, tolerance = 1e-3)
  expect_equal(colnames(inferred), c("output1", "output2"))
  inferred_output1 <- fis$infer_output(data, 1)
  inferred_output2 <- fis$infer_output(data, 2)
  expect_equal(inferred_output1, expected_output1, tolerance = 1e-3)
  expect_equal(inferred_output2, expected_output2, tolerance = 1e-3)
})

test_that("Fis equality", {
  fis_file <- system.file("extdata", "test.fis", package = "FisPro")
  fis1 <- NewFis()
  fis2 <- NewFis()
  fis3 <- NewFis(fis_file)
  expect_equal(fis1, fis2)
  expect_not_equal(fis1, fis3)
  fis1$add_input(NewFisIn())
  expect_not_equal(fis1, fis2)
})
