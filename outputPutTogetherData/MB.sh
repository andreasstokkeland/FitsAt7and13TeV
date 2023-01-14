#!/bin/bash

#cleanup
rm *.so
rm *.d
rm *.pcm

# make plots
START="$(date +%s)"

nice aliroot -b <<EOF

.L MB.C+


HEPData()






.q

EOF

#cleanup
rm *.so
rm *.d
rm *.pcm


DURATION=$[ $(date +%s) - ${START} ]
echo "The time of the code ${DURATION} s"

