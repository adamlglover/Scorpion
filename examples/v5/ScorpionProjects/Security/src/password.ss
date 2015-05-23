/*
* password.ss
* (Possible) Library module
*
* This program protects your 
* Scorpion source code from unwanted 
* users
*/

&&working_dir: 'C:\Users\Braxton\Desktop\examples\v5\ScorpionProjects\Security\src\' ; set the general working dir

import 'firewall.ss'

.seal:  ;seal the program 
  call passwd_request
  ;call verify_passwd
  ;call take_measures
  ret

call seal

halt
