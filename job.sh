#cleanup
rm *.so
rm *.d
rm *.pcm

# make plots 7 TeV
START="$(date +%s)"

nice aliroot -b <<EOF

.L PutTogetherData7TeV.C+



//pion

Sphere("Table 11", 11) //1
Sphere("Table 12", 12) //2
Sphere("Table 13", 13) //3
Sphere("Table 14", 14) //4
Sphere("Table 15", 15) //5
Sphere("Table 16", 16) //6
Sphere("Table 17", 17) //7
Sphere("Table 18", 18) //8
Sphere("Table 19", 19) //9
Sphere("Table 20", 20) //10



//kaon

Sphere("Table 21", 21) //1
Sphere("Table 22", 22) //2
Sphere("Table 23", 23) //3
Sphere("Table 24", 24) //4
Sphere("Table 25", 25) //5
Sphere("Table 26", 26) //6
Sphere("Table 27", 27) //7
Sphere("Table 28", 28) //8
Sphere("Table 29", 29) //9
Sphere("Table 30", 30) //10


//proton

Sphere("Table 31", 31) //1
Sphere("Table 32", 32) //2
Sphere("Table 33", 33) //3
Sphere("Table 34", 34) //4
Sphere("Table 35", 35) //5
Sphere("Table 36", 36) //6
Sphere("Table 37", 37) //7
Sphere("Table 38", 38) //8
Sphere("Table 39", 39) //9
Sphere("Table 40", 40) //10









.q

EOF


#cleanup
rm *.so
rm *.d
rm *.pcm

# make plots 13 TeV
nice aliroot -b <<EOF

.L PutTogetherData13TeV.C+




//Table 1
Sphere("HEPData-ins1784041-v1-Table_1.root", "Table 1", "Hist1D_y1", "Hist1D_y1_e1", "Hist1D_y1_e2", "Hist1D_y1_e3") //1
Sphere("HEPData-ins1784041-v1-Table_1.root", "Table 1", "Hist1D_y2", "Hist1D_y2_e1", "Hist1D_y2_e2", "Hist1D_y2_e3") //2
Sphere("HEPData-ins1784041-v1-Table_1.root", "Table 1", "Hist1D_y3", "Hist1D_y3_e1", "Hist1D_y3_e2", "Hist1D_y3_e3") //3
Sphere("HEPData-ins1784041-v1-Table_1.root", "Table 1", "Hist1D_y4", "Hist1D_y4_e1", "Hist1D_y4_e2", "Hist1D_y4_e3") //4
Sphere("HEPData-ins1784041-v1-Table_1.root", "Table 1", "Hist1D_y5", "Hist1D_y5_e1", "Hist1D_y5_e2", "Hist1D_y5_e3") //5
Sphere("HEPData-ins1784041-v1-Table_1.root", "Table 1", "Hist1D_y6", "Hist1D_y6_e1", "Hist1D_y6_e2", "Hist1D_y6_e3") //6
Sphere("HEPData-ins1784041-v1-Table_1.root", "Table 1", "Hist1D_y7", "Hist1D_y7_e1", "Hist1D_y7_e2", "Hist1D_y7_e3") //7
Sphere("HEPData-ins1784041-v1-Table_1.root", "Table 1", "Hist1D_y8", "Hist1D_y8_e1", "Hist1D_y8_e2", "Hist1D_y8_e3") //8
Sphere("HEPData-ins1784041-v1-Table_1.root", "Table 1", "Hist1D_y9", "Hist1D_y9_e1", "Hist1D_y9_e2", "Hist1D_y9_e3") //9
//Table 2
Sphere("HEPData-ins1784041-v1-Table_2.root", "Table 2", "Hist1D_y1", "Hist1D_y1_e1", "Hist1D_y1_e2", "Hist1D_y1_e3") //10




//Table 3
Sphere("HEPData-ins1784041-v1-Table_3.root", "Table 3", "Hist1D_y1", "Hist1D_y1_e1", "Hist1D_y1_e2", "Hist1D_y1_e3") //1
Sphere("HEPData-ins1784041-v1-Table_3.root", "Table 3", "Hist1D_y2", "Hist1D_y2_e1", "Hist1D_y2_e2", "Hist1D_y2_e3") //2
Sphere("HEPData-ins1784041-v1-Table_3.root", "Table 3", "Hist1D_y3", "Hist1D_y3_e1", "Hist1D_y3_e2", "Hist1D_y3_e3") //3
Sphere("HEPData-ins1784041-v1-Table_3.root", "Table 3", "Hist1D_y4", "Hist1D_y4_e1", "Hist1D_y4_e2", "Hist1D_y4_e3") //4
Sphere("HEPData-ins1784041-v1-Table_3.root", "Table 3", "Hist1D_y5", "Hist1D_y5_e1", "Hist1D_y5_e2", "Hist1D_y5_e3") //5
Sphere("HEPData-ins1784041-v1-Table_3.root", "Table 3", "Hist1D_y6", "Hist1D_y6_e1", "Hist1D_y6_e2", "Hist1D_y6_e3") //6
Sphere("HEPData-ins1784041-v1-Table_3.root", "Table 3", "Hist1D_y7", "Hist1D_y7_e1", "Hist1D_y7_e2", "Hist1D_y7_e3") //7
Sphere("HEPData-ins1784041-v1-Table_3.root", "Table 3", "Hist1D_y8", "Hist1D_y8_e1", "Hist1D_y8_e2", "Hist1D_y8_e3") //8
Sphere("HEPData-ins1784041-v1-Table_3.root", "Table 3", "Hist1D_y9", "Hist1D_y9_e1", "Hist1D_y9_e2", "Hist1D_y9_e3") //9
//Table 4
Sphere("HEPData-ins1784041-v1-Table_4.root", "Table 4", "Hist1D_y1", "Hist1D_y1_e1", "Hist1D_y1_e2", "Hist1D_y1_e3") //10



//Table 5
Sphere("HEPData-ins1784041-v1-Table_5.root", "Table 5", "Hist1D_y1", "Hist1D_y1_e1", "Hist1D_y1_e2", "Hist1D_y1_e3") //1
Sphere("HEPData-ins1784041-v1-Table_5.root", "Table 5", "Hist1D_y2", "Hist1D_y2_e1", "Hist1D_y2_e2", "Hist1D_y2_e3") //2
Sphere("HEPData-ins1784041-v1-Table_5.root", "Table 5", "Hist1D_y3", "Hist1D_y3_e1", "Hist1D_y3_e2", "Hist1D_y3_e3") //3
Sphere("HEPData-ins1784041-v1-Table_5.root", "Table 5", "Hist1D_y4", "Hist1D_y4_e1", "Hist1D_y4_e2", "Hist1D_y4_e3") //4
Sphere("HEPData-ins1784041-v1-Table_5.root", "Table 5", "Hist1D_y5", "Hist1D_y5_e1", "Hist1D_y5_e2", "Hist1D_y5_e3") //5
Sphere("HEPData-ins1784041-v1-Table_5.root", "Table 5", "Hist1D_y6", "Hist1D_y6_e1", "Hist1D_y6_e2", "Hist1D_y6_e3") //6
Sphere("HEPData-ins1784041-v1-Table_5.root", "Table 5", "Hist1D_y7", "Hist1D_y7_e1", "Hist1D_y7_e2", "Hist1D_y7_e3") //7
Sphere("HEPData-ins1784041-v1-Table_5.root", "Table 5", "Hist1D_y8", "Hist1D_y8_e1", "Hist1D_y8_e2", "Hist1D_y8_e3") //8
Sphere("HEPData-ins1784041-v1-Table_5.root", "Table 5", "Hist1D_y9", "Hist1D_y9_e1", "Hist1D_y9_e2", "Hist1D_y9_e3") //9
//Table 6
Sphere("HEPData-ins1784041-v1-Table_6.root", "Table 6", "Hist1D_y1", "Hist1D_y1_e1", "Hist1D_y1_e2", "Hist1D_y1_e3") //10




.q

EOF

#cleanup
rm *.so
rm *.d
rm *.pcm


DURATION=$[ $(date +%s) - ${START} ]
echo "The time of the code ${DURATION} s"

