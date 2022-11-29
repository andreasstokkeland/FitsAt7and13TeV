
#cleanup
rm *.so
rm *.d
rm *.pcm

# make plots 7 TeV
START="$(date +%s)"

nice aliroot -b <<EOF

.L Sum7TeV.C+


Summer("11.root", "12.root", "13.root", "14.root", "15.root", "16.root", "17.root", "18.root", "19.root", "20.root")


Summer("21.root", "22.root", "23.root", "24.root", "25.root", "26.root", "27.root", "28.root", "29.root", "30.root")


Summer("31.root", "32.root", "33.root", "34.root", "35.root", "36.root", "37.root", "38.root", "39.root", "40.root")



.q

EOF



#cleanup
rm *.so
rm *.d
rm *.pcm

# make plots 13 TeV

nice aliroot -b <<EOF

.L Sum13TeV.C+


Summer("HEPData-ins1784041-v1-Table_1.rootHist1D_y1.root", "HEPData-ins1784041-v1-Table_1.rootHist1D_y2.root", "HEPData-ins1784041-v1-Table_1.rootHist1D_y3.root", "HEPData-ins1784041-v1-Table_1.rootHist1D_y4.root", "HEPData-ins1784041-v1-Table_1.rootHist1D_y5.root", "HEPData-ins1784041-v1-Table_1.rootHist1D_y6.root", "HEPData-ins1784041-v1-Table_1.rootHist1D_y7.root", "HEPData-ins1784041-v1-Table_1.rootHist1D_y8.root", "HEPData-ins1784041-v1-Table_1.rootHist1D_y9.root", "HEPData-ins1784041-v1-Table_2.rootHist1D_y1.root")


Summer("HEPData-ins1784041-v1-Table_3.rootHist1D_y1.root", "HEPData-ins1784041-v1-Table_3.rootHist1D_y2.root", "HEPData-ins1784041-v1-Table_3.rootHist1D_y3.root", "HEPData-ins1784041-v1-Table_3.rootHist1D_y4.root", "HEPData-ins1784041-v1-Table_3.rootHist1D_y5.root", "HEPData-ins1784041-v1-Table_3.rootHist1D_y6.root", "HEPData-ins1784041-v1-Table_3.rootHist1D_y7.root", "HEPData-ins1784041-v1-Table_3.rootHist1D_y8.root", "HEPData-ins1784041-v1-Table_3.rootHist1D_y9.root", "HEPData-ins1784041-v1-Table_4.rootHist1D_y1.root")


Summer("HEPData-ins1784041-v1-Table_5.rootHist1D_y1.root", "HEPData-ins1784041-v1-Table_5.rootHist1D_y2.root", "HEPData-ins1784041-v1-Table_5.rootHist1D_y3.root", "HEPData-ins1784041-v1-Table_5.rootHist1D_y4.root", "HEPData-ins1784041-v1-Table_5.rootHist1D_y5.root", "HEPData-ins1784041-v1-Table_5.rootHist1D_y6.root", "HEPData-ins1784041-v1-Table_5.rootHist1D_y7.root", "HEPData-ins1784041-v1-Table_5.rootHist1D_y8.root", "HEPData-ins1784041-v1-Table_5.rootHist1D_y9.root", "HEPData-ins1784041-v1-Table_6.rootHist1D_y1.root")



.q

EOF

#cleanup
rm *.so
rm *.d
rm *.pcm


DURATION=$[ $(date +%s) - ${START} ]
echo "The time of the code ${DURATION} s"

