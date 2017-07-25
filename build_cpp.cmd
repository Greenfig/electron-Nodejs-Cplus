@ECHO OFF
@IF EXIST "binding.gyp" (
    ECHO here
) ELSE (
    @COPY NUL binding.gyp
)
