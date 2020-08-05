**Reference Spice File
***Pre Layout On- Off Current***
M1 3 2 1 1 pfet W=28u L=1u
M2 2 2 1 1 pfet W=28u L=1u
M3 5 2 1 1 pfet W=28u L=1u
M4 6 4 3 1 pfet W=28u L=1u
M5 4 4 2 1 pfet W=28u L=1u
M6 vref 4 5 1 pfet W=28u L=1u
M7 6 6 7 0 nfet W=14u L=1u
M8 4 6 8 0 nfet W=14u L=1u
M_pd 6 en_bar 0  0 nfet W=8U L=1U
M_pass 4 en 4x 0 nfet W=2U L=2U
Minv_p en_bar en 1 1 pfet W=3U L=1U
Minv_n en_bar en 0 0 nfet W=2U L=1U

M9 a 2 1 1 pfet W=12U L=1u
M10 6 a 4x 1 pfet W=12U L=0.8U
M11 a a b 0 nfet W=1U L=3u
M12 b b c 0 nfet W=1U L=3u
M13 c c 0 0 nfet W=1U L=3U
D1 7 0 PNPDIODE
R1 8 9 9K
D2 9 0 PNPDIODE 8
R2 vref 10 76K
D3 10 0 PNPDIODE 8


.model PNPDIODE D is=1e-18 n=1
Vdd 1 0 dc 3.3V
Vd_en en 0 pulse(0 3.3V 0 0 0 1s 2s)
bv en_bar 0 V=V(1)-V(en)
Rl vref 0 100MEG
.tran 0.1s 2s
.include osu018.lib

.control
run
plot V(en)
plot -I(Vdd)
.endc
.end
