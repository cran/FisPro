## ---- include = FALSE---------------------------------------------------------
knitr::opts_chunk$set(
  collapse = TRUE,
  comment = "#>"
)

## ---- setup-------------------------------------------------------------------
library(FisPro)

## -----------------------------------------------------------------------------
fis_file <- system.file("extdata", "test.fis", package = "FisPro")
fis <- NewFis(fis_file)

## -----------------------------------------------------------------------------
fis <- NewFis()
fis$name <- "foo"

## -----------------------------------------------------------------------------
fisin1 <- NewFisIn(2, 0, 1)
fisin1$name <- "input1"
fis$add_input(fisin1)

## -----------------------------------------------------------------------------
fisin2 <- NewFisIn(0, 1)
fisin2$name <- "input2"

mf1 <- NewMfTrapezoidalInf(0, 0.5)
mf1$label <- "Low"
fisin2$add_mf(mf1)

mf2 <- NewMfTriangular(0, 0.5, 1)
mf2$label <- "Average"
fisin2$add_mf(mf2)

mf3 <- NewMfTrapezoidalSup(0.5, 1)
mf3$label <- "High"
fisin2$add_mf(mf3)

fis$add_input(fisin2)

## -----------------------------------------------------------------------------
fisout1 <- NewFisOutCrisp(0, 1)
fisout1$name <- "output1"
fis$add_output(fisout1)

## -----------------------------------------------------------------------------
fisout2 <- NewFisOutFuzzy(2, 0, 1)
fisout2$name <- "output2"
fis$add_output(fisout2)

## -----------------------------------------------------------------------------
fis$add_rule(NewRule(c(1, 2), c(0, 1)))
fis$add_rule(NewRule(c(2, 0), c(1, 2)))

## -----------------------------------------------------------------------------
fis$save("foo.fis")

## ---- include=FALSE-----------------------------------------------------------
file.remove("foo.fis")

## -----------------------------------------------------------------------------
inferred <- fis$infer(c(0.25, 0.75))

## -----------------------------------------------------------------------------
inferred_output1 <- fis$infer_output(c(0.25, 0.75), 1)

## -----------------------------------------------------------------------------
inferred_output2 <- fis$infer_output(c(0.25, 0.75), 2)

## -----------------------------------------------------------------------------
test_file <- system.file("extdata", "test_data.csv", package = "FisPro")
dataset <- read.csv(test_file)
inferred_dataset <- fis$infer(dataset)

