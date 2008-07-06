This setup assumes Visual C++ 2008 Express Edition, which is a free download.  

To open the project, click on Perspectives.sln 

I migrated this stuff from a tutorial where everything was named "test", so you
still see that name in a couple places. 

It assumes that xulrunner sdk 1.9 is in ..\xulrunner-sdk\ 

It produces Debug\Perspectives.dll, which you should copy to the appropriate 
directory in the perspectives@cmu.edu folder.

Note: the extension currently doesn't valididate notary signatures, and thus is 
completely insecure.  woohoo!


C:\PROGRA~1\MOZILL~1>copy c:\xulrunner-1.9\xpcom-test\Debug\Perspectives.dll "C:
\Documents and Settings\Dan\Application Data\Mozilla\Firefox\Profiles\default.x7
a\extensions\perspectives@cmu.edu\platform\WINNT_x86-msvc\components"
Overwrite C:\Documents and Settings\Dan\Application Data\Mozilla\Firefox\Profile
s\default.x7a\extensions\perspectives@cmu.edu\platform\WINNT_x86-msvc\components
\Perspectives.dll? (Yes/No/All): Yes
        1 file(s) copied.

C:\PROGRA~1\MOZILL~1>firefox.exe -console