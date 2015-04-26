import <util/Exception>

; Scorpion VM Runtime Exception Module

; ****Variables****
; RUNTIME_EMESSAGE : The message to create the exception

; Throw a runtime exception in its most basic form
.RuntimeException: ; RuntimeException(string execption_message);
   r_mv ip RuntimeException_b
   
   string RUNTIME_EXCEPTION 'RuntimeException'
   cp EXCEPTION_MSG RUNTIME_EXCEPTION
   adr EXCEPTION_ADDR RUNTIME_EXCEPTION
   cp EXCEPTION_MESSAGE RUNTIME_EMESSAGE
   adr EXCEPTION_MSG_ADDR RUNTIME_EMESSAGE
   loadi EXCEPTION_EXIT 1
   
   call Exception              ; Exception(String execption, String excpn_message, int exit_code);
   cp Exception Exception_b
   ret
   