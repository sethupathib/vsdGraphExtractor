
***Netlist description***
M1 3 a vdd vdd pmos W=1.53u L=0.18u
M2 2 b vdd vdd pmos W=1.53u L=0.18u
M3 4 d 2 2 pmos W=1.53u L=0.18u
M4 4 c 3 3 pmos W=1.53u L=0.18u
M5 out e 4 4 pmos W=1.53u L=0.18u
M6 out f 4 4 pmos W=1.53u L=0.18u

M7 out a 6 6 nmos W=1.53u L=0.18u
M8 out c 6 6 nmos W=1.53u L=0.18u
M9 out e 7 7 nmos W=1.53u L=0.18u
M10 6 b 0 0 nmos W=1.53u L=0.18u
M11 6 d 0 0 nmos W=1.53u L=0.18u
M12 7 f 0 0 nmos W=1.53u L=0.18u

cload out 0 10f

Vdd vdd 0 2.5
V1 a 0 0 pulse 0 2.5 0.1n 10p 10p 1n 2n
V2 b 0 0 pulse 0 2.5 0.2n 10p 10p 1n 2n
V3 c 0 0 pulse 0 2.5 0.3n 10p 10p 1n 2n
V4 d 0 0 pulse 0 2.5 0.4n 10p 10p 1n 2n
V5 e 0 0 pulse 0 2.5 0.5n 10p 10p 1n 2n
V6 f 0 0 pulse 0 2.5 0.6n 10p 10p 1n 2n

***Simulation commands***
.op
.tran 10p 4n

*** .include model file ***
.LIB "my_model_file.tech" CMOS_MODELS
.end
