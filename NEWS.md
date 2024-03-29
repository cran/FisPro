# FisPro 1.1.4

* Fix S3 generic/method consistency warnings

# FisPro 1.1.3

* Fix M1mac deprecated-declarations warnings

# FisPro 1.1.2

* Fix CRAN check compiled code issues

# FisPro 1.1.1

* Fix compilation warnings

# FisPro 1.1

### Deprecated
* Classes `fis`, `mf`, `mf_trapezoidal`, `mf_trapezoidal_inf`, `mf_trapezoidal_sup` and `mf_triangular` are now deprecated and will be removed in a future version, use `Fis`, `Mf`, `MfTrapezoidal`, `MfTrapezoidalInf`, `MfTrapezoidalSup`, `MfTriangular` classes instead

### Major changes
* The `output_index` parameter of the `Fis` `infer_output` function is now 1-based indexed (the deprecated `fis` was 0-based indexed in FisPro 1.0)
* New Classes to manage `Fis`: `FisIn`, `FisOutCrisp`, `FisOutFuzzy` and `Rule`

### Documentation
* Add vignette "User Guide"

# FisPro 1.0

* Initial release
