bzr push sftp://nccastaff.bournemouth.ac.uk/web/httpd/ncca/htdocs/jmacey/Code/GraphicsLib
bzr log --limit 1 &>version.txt
cp version.txt ~/Web/jmacey/GraphicsLib
bzr log >fullhistory.txt
cp fullhistory.txt ~/Web/jmacey/GraphicsLib
scp fullhistory.txt version.txt jmacey@nccastaff.bmth.ac.uk:/web/httpd/ncca/htdocs/jmacey/GraphicsLib
bzr push --no-strict lp:ncca
