@echo off

SET ORIG_PATH=%PATH%

REM Ensure that we can run CMAKE
SET PATH=%PATH%;C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin

cmake -DDESIRED_TAG=0.12.16-release -P cmake/update_version.cmake

SET PATH=%ORIG_PATH%