@echo off
REM ==============================================================
REM Experiment No. 7: Traffic Generator for Wireshark Packet Analysis
REM Generates DNS traffic (UDP port 53) and HTTP traffic (TCP port 80)
REM ==============================================================

echo [Step 1] Generating DNS Traffic...
echo Resolving www.google.com using nslookup
nslookup www.google.com
echo.

echo [Step 2] Generating Plain HTTP Traffic (Port 80)...
echo Requesting http://example.com using curl
curl -I http://example.com
echo.

echo Requesting http://neverssl.com using curl
curl -I http://neverssl.com
echo.

echo Packets sent! You can now analyze:
echo 1. Filter: 'dns' for UDP port 53 query/response.
echo 2. Filter: 'http' for TCP port 80 GET request and 200 OK response.
pause

