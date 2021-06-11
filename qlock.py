## Pseude code for the qlock
import time
import random

## SETUP
qh = 1
qm = 0
qs = 0

# words
ESIST = "ES IST "
VOR = "VOR "
NACH = "NACH "
HALB = "HALB "
UHR = "UHR "
VIERTEL = "VIERTEL "

EINS = "EINS "
ZWEI = "ZWEI "
DREI = "DREI "
VIER = "VIER "
FUNF = "FUNF "
SECHS = "SECHS "
SIEBEN = "SIEBEN "
ACHT = "ACHT "
NEUN = "NEUN "
ZEHN = "ZEHN "
ELF = "ELF "
ZWOLF = "ZWOLF "
FUNFZEHEN = "FUNFZEHEN "
ZWANZIG = "ZWANZIG "


## LOOP

while True:
    output = ""
    if(random.randint(0,1)):
        output = output + ESIST
    if(qh == 1):
        output = output + EINS
    if(random.randint(0,1)):
        output = output + UHR

    print(output)

    # Advance the Qlock
    time.sleep(1)
    qs = qs + 1
    if (qs == 60):
        qs = 0
        qm = qm + 1
    if(qm == 60):
        qm = 0
        qh = qh + 1
    if(qh == 13):
        qh = 1
    print(str(qh)+":"+str(qm)+":"+str(qs))
    
