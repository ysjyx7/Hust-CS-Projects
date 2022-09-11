/******************************************************************************
 ** Logisim goes FPGA automatic generated Verilog code                       **
 **                                                                          **
 ** Component : ROM_ROM                                                      **
 **                                                                          **
 ******************************************************************************/

`timescale 1ns/1ps
module ROM_ROM( Address,
                Data);

   /***************************************************************************
    ** Here the inputs are defined                                           **
    ***************************************************************************/
   input[9:0]  Address;

   /***************************************************************************
    ** Here the outputs are defined                                          **
    ***************************************************************************/
   output[31:0] Data;
   reg[31:0] Data;

   always @ (Address)
   begin
      case(Address)
        0 : Data = 32'h00100493;
1 : Data = 32'h0100006f;
2 : Data = 32'h00100493;
3 : Data = 32'h00200913;
4 : Data = 32'h00300993;
5 : Data = 32'h0100006f;
6 : Data = 32'h00100493;
7 : Data = 32'h00200913;
8 : Data = 32'h00300993;
9 : Data = 32'h0100006f;
10 : Data = 32'h00100493;
11 : Data = 32'h00200913;
12 : Data = 32'h00300993;
13 : Data = 32'h0100006f;
14 : Data = 32'h00100493;
15 : Data = 32'h00200913;
16 : Data = 32'h00300993;
17 : Data = 32'h29c000ef;
18 : Data = 32'h00100413;
19 : Data = 32'h00100493;
20 : Data = 32'h01f49493;
21 : Data = 32'h00900533;
22 : Data = 32'h02200893;
23 : Data = 32'h00000073;
24 : Data = 32'h0024d493;
25 : Data = 32'h00048463;
26 : Data = 32'hfedff06f;
27 : Data = 32'h00900533;
28 : Data = 32'h02200893;
29 : Data = 32'h00000073;
30 : Data = 32'h00100493;
31 : Data = 32'h00249493;
32 : Data = 32'h00900533;
33 : Data = 32'h02200893;
34 : Data = 32'h00000073;
35 : Data = 32'h00048463;
36 : Data = 32'hfedff06f;
37 : Data = 32'h00100493;
38 : Data = 32'h01f49493;
39 : Data = 32'h00900533;
40 : Data = 32'h02200893;
41 : Data = 32'h00000073;
42 : Data = 32'h4034d493;
43 : Data = 32'h00900533;
44 : Data = 32'h02200893;
45 : Data = 32'h00000073;
46 : Data = 32'h4044d493;
47 : Data = 32'h00900533;
48 : Data = 32'h02200893;
49 : Data = 32'h00000073;
50 : Data = 32'h4044d493;
51 : Data = 32'h00900533;
52 : Data = 32'h02200893;
53 : Data = 32'h00000073;
54 : Data = 32'h4044d493;
55 : Data = 32'h00900533;
56 : Data = 32'h02200893;
57 : Data = 32'h00000073;
58 : Data = 32'h4044d493;
59 : Data = 32'h00900533;
60 : Data = 32'h02200893;
61 : Data = 32'h00000073;
62 : Data = 32'h4044d493;
63 : Data = 32'h00900533;
64 : Data = 32'h02200893;
65 : Data = 32'h00000073;
66 : Data = 32'h4044d493;
67 : Data = 32'h00900533;
68 : Data = 32'h02200893;
69 : Data = 32'h00000073;
70 : Data = 32'h4044d493;
71 : Data = 32'h00900533;
72 : Data = 32'h02200893;
73 : Data = 32'h00000073;
74 : Data = 32'h00100413;
75 : Data = 32'h01f41993;
76 : Data = 32'h41f9d993;
77 : Data = 32'h00000433;
78 : Data = 32'h00c00913;
79 : Data = 32'h00300b13;
80 : Data = 32'h00140413;
81 : Data = 32'h00f47413;
82 : Data = 32'h00800293;
83 : Data = 32'h00100313;
84 : Data = 32'h00499993;
85 : Data = 32'h0089e9b3;
86 : Data = 32'h01300533;
87 : Data = 32'h02200893;
88 : Data = 32'h00000073;
89 : Data = 32'h406282b3;
90 : Data = 32'hfe0294e3;
91 : Data = 32'h00140413;
92 : Data = 32'h00f00f93;
93 : Data = 32'h01f47433;
94 : Data = 32'h01c41413;
95 : Data = 32'h00800293;
96 : Data = 32'h00100313;
97 : Data = 32'h0049d993;
98 : Data = 32'h0089e9b3;
99 : Data = 32'h01300533;
100 : Data = 32'h02200893;
101 : Data = 32'h00000073;
102 : Data = 32'h406282b3;
103 : Data = 32'hfe0294e3;
104 : Data = 32'h01c45413;
105 : Data = 32'h406b0b33;
106 : Data = 32'h000b0463;
107 : Data = 32'hf95ff06f;
108 : Data = 32'h000002b3;
109 : Data = 32'hfff2c293;
110 : Data = 32'h00829293;
111 : Data = 32'h0ff2e293;
112 : Data = 32'h00500533;
113 : Data = 32'h02200893;
114 : Data = 32'h00000073;
115 : Data = 32'hfff00413;
116 : Data = 32'h00000493;
117 : Data = 32'h0084a023;
118 : Data = 32'h00140413;
119 : Data = 32'h00448493;
120 : Data = 32'h0084a023;
121 : Data = 32'h00140413;
122 : Data = 32'h00448493;
123 : Data = 32'h0084a023;
124 : Data = 32'h00140413;
125 : Data = 32'h00448493;
126 : Data = 32'h0084a023;
127 : Data = 32'h00140413;
128 : Data = 32'h00448493;
129 : Data = 32'h0084a023;
130 : Data = 32'h00140413;
131 : Data = 32'h00448493;
132 : Data = 32'h0084a023;
133 : Data = 32'h00140413;
134 : Data = 32'h00448493;
135 : Data = 32'h0084a023;
136 : Data = 32'h00140413;
137 : Data = 32'h00448493;
138 : Data = 32'h0084a023;
139 : Data = 32'h00140413;
140 : Data = 32'h00448493;
141 : Data = 32'h0084a023;
142 : Data = 32'h00140413;
143 : Data = 32'h00448493;
144 : Data = 32'h0084a023;
145 : Data = 32'h00140413;
146 : Data = 32'h00448493;
147 : Data = 32'h0084a023;
148 : Data = 32'h00140413;
149 : Data = 32'h00448493;
150 : Data = 32'h0084a023;
151 : Data = 32'h00140413;
152 : Data = 32'h00448493;
153 : Data = 32'h0084a023;
154 : Data = 32'h00140413;
155 : Data = 32'h00448493;
156 : Data = 32'h0084a023;
157 : Data = 32'h00140413;
158 : Data = 32'h00448493;
159 : Data = 32'h0084a023;
160 : Data = 32'h00140413;
161 : Data = 32'h00448493;
162 : Data = 32'h0084a023;
163 : Data = 32'h00140413;
164 : Data = 32'h00448493;
165 : Data = 32'h00140413;
166 : Data = 32'h00000433;
167 : Data = 32'h03c00493;
168 : Data = 32'h00042983;
169 : Data = 32'h0004aa03;
170 : Data = 32'h0149a2b3;
171 : Data = 32'h00028663;
172 : Data = 32'h0134a023;
173 : Data = 32'h01442023;
174 : Data = 32'hffc48493;
175 : Data = 32'hfe9412e3;
176 : Data = 32'h00800533;
177 : Data = 32'h02200893;
178 : Data = 32'h00000073;
179 : Data = 32'h00440413;
180 : Data = 32'h03c00493;
181 : Data = 32'hfc9416e3;
182 : Data = 32'h00a00893;
183 : Data = 32'h00000073;
184 : Data = 32'h00000413;
185 : Data = 32'h00140413;
186 : Data = 32'h00800533;
187 : Data = 32'h02200893;
188 : Data = 32'h00000073;
189 : Data = 32'h00240413;
190 : Data = 32'h00800533;
191 : Data = 32'h02200893;
192 : Data = 32'h00000073;
193 : Data = 32'h00340413;
194 : Data = 32'h00800533;
195 : Data = 32'h02200893;
196 : Data = 32'h00000073;
197 : Data = 32'h00440413;
198 : Data = 32'h00800533;
199 : Data = 32'h02200893;
200 : Data = 32'h00000073;
201 : Data = 32'h00540413;
202 : Data = 32'h00800533;
203 : Data = 32'h02200893;
204 : Data = 32'h00000073;
205 : Data = 32'h00640413;
206 : Data = 32'h00800533;
207 : Data = 32'h02200893;
208 : Data = 32'h00000073;
209 : Data = 32'h00740413;
210 : Data = 32'h00800533;
211 : Data = 32'h02200893;
212 : Data = 32'h00000073;
213 : Data = 32'h00840413;
214 : Data = 32'h00800533;
215 : Data = 32'h02200893;
216 : Data = 32'h02200893;
217 : Data = 32'h00000073;
218 : Data = 32'h00008067;

         default : Data = 0;
      endcase
   end

endmodule
