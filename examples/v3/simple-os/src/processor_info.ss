; Processor info used for BIOS

loadi magic_number 0x39
loadi boot_value 0
;****************
loadi cores 1
loadi task_limit 65336
loadi processor_ID 45327

loadbl run false

~test:
     mov i1 int
     rmov sdx n
     mov i1 bool
     same run n magic_number
     do run
        loadi boot_value 1
        rm n
        ret 1
     end
     ret
