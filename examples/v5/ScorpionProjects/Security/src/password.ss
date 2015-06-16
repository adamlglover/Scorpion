/*
* password.ss
* (Possible) Library module
*
* This program protects your 
* Scorpion source code from unwanted 
* users
*/

&&working_dir: 'C:\Users\Braxton\Desktop\examples\v5\ScorpionProjects\Security\src\' ; set the general working dir

loadi SEAL_RETURN 0

import 'firewall.ss'

.seal:  ;seal the program 
  print 'This program is password protected/n'
  r_mv ip SEAL_RETURN
  print 'Type a password: '
  call passwd_request
  call verify_passwd
  call take_measures
  ret

 call seal

halt 
 
  
