#!/bin/bash

#cleanup
rm *.so
rm *.d
rm *.pcm

# make plots 7 TeV
START="$(date +%s)"

nice aliroot -b <<EOF

.L Div7TeV.C+


//Tab 1
Diver( "11.root", "Tot11.root.root") //1
Diver( "12.root", "Tot11.root.root") //2
Diver( "13.root", "Tot11.root.root") //3
Diver( "14.root", "Tot11.root.root") //4
Diver( "15.root", "Tot11.root.root") //5
Diver( "16.root", "Tot11.root.root") //6
Diver( "17.root", "Tot11.root.root") //7
Diver( "18.root", "Tot11.root.root") //8
Diver( "19.root", "Tot11.root.root") //9
Diver( "20.root", "Tot11.root.root") //10



//Tab 2
Diver( "21.root", "Tot21.root.root") //1
Diver( "22.root", "Tot21.root.root") //2
Diver( "23.root", "Tot21.root.root") //3
Diver( "24.root", "Tot21.root.root") //4
Diver( "25.root", "Tot21.root.root") //5
Diver( "26.root", "Tot21.root.root") //6
Diver( "27.root", "Tot21.root.root") //7
Diver( "28.root", "Tot21.root.root") //8
Diver( "29.root", "Tot21.root.root") //9
Diver( "30.root", "Tot21.root.root") //10



//Tab 3
Diver( "31.root", "Tot31.root.root") //1
Diver( "32.root", "Tot31.root.root") //2
Diver( "33.root", "Tot31.root.root") //3
Diver( "34.root", "Tot31.root.root") //4
Diver( "35.root", "Tot31.root.root") //5
Diver( "36.root", "Tot31.root.root") //6
Diver( "37.root", "Tot31.root.root") //7
Diver( "38.root", "Tot31.root.root") //8
Diver( "39.root", "Tot31.root.root") //9
Diver( "40.root", "Tot31.root.root") //10




.q

EOF


#cleanup
rm *.so
rm *.d
rm *.pcm


# make plots 13 TeV

nice aliroot -b <<EOF

.L Div13TeV.C+


//Tab 1
Diver( "HEPData-ins1784041-v1-Table_1.rootHist1D_y1.root", "TotHEPData-ins1784041-v1-Table_1.rootHist1D_y1.root.root") //1
Diver( "HEPData-ins1784041-v1-Table_1.rootHist1D_y2.root", "TotHEPData-ins1784041-v1-Table_1.rootHist1D_y1.root.root") //2
Diver( "HEPData-ins1784041-v1-Table_1.rootHist1D_y3.root", "TotHEPData-ins1784041-v1-Table_1.rootHist1D_y1.root.root") //3
Diver( "HEPData-ins1784041-v1-Table_1.rootHist1D_y4.root", "TotHEPData-ins1784041-v1-Table_1.rootHist1D_y1.root.root") //4
Diver( "HEPData-ins1784041-v1-Table_1.rootHist1D_y5.root", "TotHEPData-ins1784041-v1-Table_1.rootHist1D_y1.root.root") //5
Diver( "HEPData-ins1784041-v1-Table_1.rootHist1D_y6.root", "TotHEPData-ins1784041-v1-Table_1.rootHist1D_y1.root.root") //6
Diver( "HEPData-ins1784041-v1-Table_1.rootHist1D_y7.root", "TotHEPData-ins1784041-v1-Table_1.rootHist1D_y1.root.root") //7
Diver( "HEPData-ins1784041-v1-Table_1.rootHist1D_y8.root", "TotHEPData-ins1784041-v1-Table_1.rootHist1D_y1.root.root") //8
Diver( "HEPData-ins1784041-v1-Table_1.rootHist1D_y9.root", "TotHEPData-ins1784041-v1-Table_1.rootHist1D_y1.root.root") //9
Diver( "HEPData-ins1784041-v1-Table_2.rootHist1D_y1.root", "TotHEPData-ins1784041-v1-Table_1.rootHist1D_y1.root.root") //10



//Tab 2
Diver( "HEPData-ins1784041-v1-Table_3.rootHist1D_y1.root", "TotHEPData-ins1784041-v1-Table_3.rootHist1D_y1.root.root") //1
Diver( "HEPData-ins1784041-v1-Table_3.rootHist1D_y2.root", "TotHEPData-ins1784041-v1-Table_3.rootHist1D_y1.root.root") //2
Diver( "HEPData-ins1784041-v1-Table_3.rootHist1D_y3.root", "TotHEPData-ins1784041-v1-Table_3.rootHist1D_y1.root.root") //3
Diver( "HEPData-ins1784041-v1-Table_3.rootHist1D_y4.root", "TotHEPData-ins1784041-v1-Table_3.rootHist1D_y1.root.root") //4
Diver( "HEPData-ins1784041-v1-Table_3.rootHist1D_y5.root", "TotHEPData-ins1784041-v1-Table_3.rootHist1D_y1.root.root") //5
Diver( "HEPData-ins1784041-v1-Table_3.rootHist1D_y6.root", "TotHEPData-ins1784041-v1-Table_3.rootHist1D_y1.root.root") //6
Diver( "HEPData-ins1784041-v1-Table_3.rootHist1D_y7.root", "TotHEPData-ins1784041-v1-Table_3.rootHist1D_y1.root.root") //7
Diver( "HEPData-ins1784041-v1-Table_3.rootHist1D_y8.root", "TotHEPData-ins1784041-v1-Table_3.rootHist1D_y1.root.root") //8
Diver( "HEPData-ins1784041-v1-Table_3.rootHist1D_y9.root", "TotHEPData-ins1784041-v1-Table_3.rootHist1D_y1.root.root") //9
Diver( "HEPData-ins1784041-v1-Table_4.rootHist1D_y1.root", "TotHEPData-ins1784041-v1-Table_3.rootHist1D_y1.root.root") //10



//Tab 3
Diver( "HEPData-ins1784041-v1-Table_5.rootHist1D_y1.root", "TotHEPData-ins1784041-v1-Table_5.rootHist1D_y1.root.root") //1
Diver( "HEPData-ins1784041-v1-Table_5.rootHist1D_y2.root", "TotHEPData-ins1784041-v1-Table_5.rootHist1D_y1.root.root") //2
Diver( "HEPData-ins1784041-v1-Table_5.rootHist1D_y3.root", "TotHEPData-ins1784041-v1-Table_5.rootHist1D_y1.root.root") //3
Diver( "HEPData-ins1784041-v1-Table_5.rootHist1D_y4.root", "TotHEPData-ins1784041-v1-Table_5.rootHist1D_y1.root.root") //4
Diver( "HEPData-ins1784041-v1-Table_5.rootHist1D_y5.root", "TotHEPData-ins1784041-v1-Table_5.rootHist1D_y1.root.root") //5
Diver( "HEPData-ins1784041-v1-Table_5.rootHist1D_y6.root", "TotHEPData-ins1784041-v1-Table_5.rootHist1D_y1.root.root") //6
Diver( "HEPData-ins1784041-v1-Table_5.rootHist1D_y7.root", "TotHEPData-ins1784041-v1-Table_5.rootHist1D_y1.root.root") //7
Diver( "HEPData-ins1784041-v1-Table_5.rootHist1D_y8.root", "TotHEPData-ins1784041-v1-Table_5.rootHist1D_y1.root.root") //8
Diver( "HEPData-ins1784041-v1-Table_5.rootHist1D_y9.root", "TotHEPData-ins1784041-v1-Table_5.rootHist1D_y1.root.root") //9
Diver( "HEPData-ins1784041-v1-Table_6.rootHist1D_y1.root", "TotHEPData-ins1784041-v1-Table_5.rootHist1D_y1.root.root") //10



.q

EOF

#cleanup
rm *.so
rm *.d
rm *.pcm


DURATION=$[ $(date +%s) - ${START} ]
echo "The time of the code ${DURATION} s"

