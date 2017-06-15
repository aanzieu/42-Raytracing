echo "========Lancement du RTv1========="
make fclean && make re
echo "========Making Done========"

echo "===================TESTING=========================="
./rtv1 demo/rtplan.xml
./rtv1 demo/rtsphere.xml
./rtv1 demo/rtcone.xml
./rtv1 demo/rtcylinder.xml
./rtv1 demo/rtscene.xml
./rtv1 demo/rtspots.xml
echo "\n=================TESTING DONE====================="
make fclean
