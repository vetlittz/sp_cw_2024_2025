Program Prog ;
Start Var Int_4 Aaaa , Bbbb , Cccc ;
  Scan (Aaaa)
  Bbbb << 1
  For  Cccc << 0 To 32767 Do
    If ( Aaaa Ne 0 ) ; Else GoTo Bbbb ;
     Bbbb << Bbbb * Aaaa
     Aaaa << Aaaa ++ 1
  ;
  Exit :
  Print ( Bbbb )
Finish
