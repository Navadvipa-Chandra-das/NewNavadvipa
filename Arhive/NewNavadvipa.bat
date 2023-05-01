C:\PostgreSQL\14\bin\pg_dump.exe -d NewNavadvipa -U "Navadvipa Chandra das" -W PASWORD -b -c --column-inserts --inserts --disable-triggers --if-exists --no-unlogged-table-data -S "Navadvipa Chandra das" -f C:\C\NewNavadvipa\SQL\NewNavadvipa.sql
set now=%TIME:~0,-3%
set now=%now::=.%
set now=%now: =0%
set now=_%DATE:~-4%.%DATE:~3,2%.%DATE:~0,2%_%now%
"C:\PRG\7-Zip\7z.exe" -t7z -scsUTF-8 a NewNavadvipa%now%.7z -ir@NewNavadvipa.inc -xr@NewNavadvipa.exc
copy NewNavadvipa%now%.7z ..\TOOLS\NewNavadvipa.7z
