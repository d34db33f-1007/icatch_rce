# icatch_rce
iCatch or LILIN DVRs RCE PoC


besides already publicy known hardcoded credentials admin:123456, root:icath99, report：8Jg0SR8K50 \
and remote commands execution through NTP, FTP and etc. settings changing \n 
for this devices, this PoC invokes buffer overflow and unauthenticated remote code executionю

just change dvr ip, compile and run

shodan dork: http.html_hash:"1640961097"

snapshots location: <host>:<port>/cgi-bin/net_jpeg.cgi?ch=1
brute with https://github.com/ztgrace/changeme \
or https://gitlab.com/Reinmar/IPSca
