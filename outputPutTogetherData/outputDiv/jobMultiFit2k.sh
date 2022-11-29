

#cleanup
rm *.so
rm *.d
rm *.pcm

# make plots 7 TeV
START="$(date +%s)"

nice root -b <<EOF


.L MultiFit2k7TeV.C+
combinedFit(1)
combinedFit(2)
combinedFit(3)

AddingHistos()


.q

EOF

#cleanup
rm *.so
rm *.d
rm *.pcm

# make plots 13 TeV
nice root -b <<EOF


.L MultiFit2k13TeV.C+
combinedFit(1)
combinedFit(3)
combinedFit(5)

AddingHistos()


.q

EOF

#cleanup
rm *.so
rm *.d
rm *.pcm


DURATION=$[ $(date +%s) - ${START} ]
echo "The time of the code ${DURATION} s"

