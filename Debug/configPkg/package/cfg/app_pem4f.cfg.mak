# invoke SourceDir generated makefile for app.pem4f
app.pem4f: .libraries,app.pem4f
.libraries,app.pem4f: package/cfg/app_pem4f.xdl
	$(MAKE) -f C:\Users\paul\Dropbox\Grocery/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\paul\Dropbox\Grocery/src/makefile.libs clean

