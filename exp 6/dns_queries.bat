@echo off
REM ==============================================================
REM Experiment No. 6: DNS Packet Analysis Helper Script
REM Performs forward lookup, reverse lookup, and MX record queries
REM ==============================================================

echo [Step 1] Forward DNS Lookup: Resolving domain name to IP address...
echo Command: nslookup www.google.com
nslookup www.google.com
echo.

echo [Step 2] Reverse DNS Lookup: Resolving IP address back to domain...
echo Command: nslookup 142.251.155.119
nslookup 142.251.155.119
echo.

echo [Step 3] Querying Mail Exchange (MX) DNS Records...
echo Command: nslookup -query=mx google.com
nslookup -query=mx google.com
echo.

echo [Step 4] Querying Nameserver (NS) Records...
echo Command: nslookup -query=ns google.com
nslookup -query=ns google.com
echo.

echo All DNS queries executed. Check Wireshark packet capture with filter: dns
pause

