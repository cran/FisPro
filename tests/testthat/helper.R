
expect_no_error <- function(expr) {
  err <- FALSE
  message <- NULL
  tryCatch(force(expr), error = function(e) {
    err <<- TRUE
    message <<- e
  })
  expect(!err, paste("Expected no error, but had error:", message))
  invisible(NULL)
}

expect_not_equal <- function(object, other, ..., tolerance = NULL) {
  object_label <- quasi_label(rlang::enquo(object))
  other_label <- quasi_label(rlang::enquo(other))
  if (!is.null(tolerance)) {
    comp <- compare(object, other, ..., tolerance = tolerance)
  } else {
    comp <- compare(object, other, ...)
  }
  expect(!comp$equal, sprintf("%s should be not equal to %s", object_label$lab, other_label$lab), NULL)
  invisible(NULL)
}
