# 2425_ESE_TP_Actionneur_et_automatique_applique

# TP1
Lors de ce TP nous devons générer une PWM sur le pont U et V pour pouvoir controler le hacheur lié au moteur. 
Nous prenons une PWM de fréquence 02kHz et nous définissons un temps mort de 100ns pour éviter tout court circuit.
# TP2
## Mesure du courant

1) Le courant que nous devons mesurer est le courant consommé par le moteur ainsi que le courant fournit par l'alimentation. 
Pour cela nous allons utiliser le composant GO10-SME présent sur la carte électronique.

2) Le capteur renvoie une tension de 50mV pour 1A mesuré.

3) La pins correspondant à la mesure du courant pour la phase U est la pin 27 (PA0) du connecteur J103.
   La pin correspondant à la musre du courant consommé par la phase V est la pin 23 (PB1) du connecteur J104.
   La pin correspondant à la mesure du courant fournit par l'alimentation est la pin 29 (PA1) du connecteur J103.


## Mesure de vitesse
 Le conposant qui sert à mesurer la vitesse est le MAX3097E. 
