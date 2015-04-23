
string msg 'This is a string message'
adr ref msg
inc ref
rloop parse loop_b msg
   rload char ref
   printf '<c,char>'
   inc ref
endl parse loop_b

print '/n'

loadi data 29430
printf 'formatted data  %d(<d,data>) %f(<f,data>) %x(<x,data>) %u(<u,data>)' 
printf ' %g(<g,data>) %e(<e,data>) %do(<do,data>)  %lg(<le,data>) %le(<le,data>)/n' 

halt

