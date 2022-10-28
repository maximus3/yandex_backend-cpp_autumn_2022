for c in `seq 1 1000`; do echo $RANDOM; done | tr -s '\n' ', ' > body1000.txt

