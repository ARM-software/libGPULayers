:: SPDX-License-Identifier: MIT
:: -----------------------------------------------------------------------------
:: Copyright (c) 2025 Arm Limited
::
:: Permission is hereby granted, free of charge, to any person obtaining a copy
:: of this software and associated documentation files (the 'Software'), to
:: deal in the Software without restriction, including without limitation the
:: rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
:: sell copies of the Software, and to permit persons to whom the Software is
:: furnished to do so, subject to the following conditions:
::
:: The above copyright notice and this permission notice shall be included in
:: all copies or substantial portions of the Software.
::
:: THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
:: IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
:: FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
:: AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
:: LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
:: OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
:: SOFTWARE.
:: -----------------------------------------------------------------------------
@echo off
setlocal

set total_errors = 0
set total_runs = 0

echo = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
echo Running tests without devices
echo = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
echo:

py -3 -m lglpy.ui.test
set /a total_runs+=1
set /a total_errors=total_errors+%ERRORLEVEL%

echo = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
echo Running tests with devices
echo = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
echo:

py -3 -m lglpy.android.test
set /a total_runs+=1
set /a total_errors=total_errors+%ERRORLEVEL%

echo = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
echo Test run summary statistics
echo = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
echo:
echo   - Total suites run = %total_runs%
echo   - Total suites in error = %total_errors%
