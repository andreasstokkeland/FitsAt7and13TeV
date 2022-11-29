

#cleanup
rm *.so
rm *.d
rm *.pcm

# make plots 7 TeV
START="$(date +%s)"

nice aliroot -b <<EOF

.L AddingHistoTalkerWithFit7TeV.C+


AddingHistoTalker()

AddingHistos()



.q

EOF


#cleanup
rm *.so
rm *.d
rm *.pcm

# make plots 13 TeV
nice aliroot -b <<EOF

.L AddingHistoTalkerWithFit13TeV.C+


AddingHistoTalker()

AddingHistos()


.q

EOF

#cleanup
rm *.so
rm *.d
rm *.pcm


DURATION=$[ $(date +%s) - ${START} ]
echo "The time of the code ${DURATION} s"

