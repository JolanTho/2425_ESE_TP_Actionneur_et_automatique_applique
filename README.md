# 2425_ESE_TP_Actionneur_et_automatique_applique

# TP1
Lors de ce TP nous devons générer une PWM en complémentaire décalé sur le pont U et V pour pouvoir controler le hacheur lié au moteur. 
Nous prenons une PWM de fréquence 20kHz et nous définissons un temps mort de 100ns pour éviter tout court circuit.

Après avoir générer la PWM nous utiisons un shell en liaison UART pour pouvoir changer la vitesse du moteur. Nous avons créer la fonction "Speed XXX" qui permet de récupérer la valuer de "XXX" et ainsi changer le rapport cyclique de la PWM.
Après quelques testes en faisant bien attention à limitér le courant fournit par l'alimentation, nous avons observé lors du changement de consigne que le moteur changeait de vitesse très rapidement ce qui peut engendrer des courants très important dans le moteur et la carte et ainsi cramer la carte de commande. 
Nous avons donc décidé d'envoyer la consigne du moteur via une rampe. C'est à dire que lorsqu'une nouvelle commande et envoyée, nous faisons en sorte que le moteur chnage de vitesse progressivement.
# TP2

Dans cette partie nous devons commander en boucle ouverte le moteur et établir une mesure du courant et de la vitesse pour pouvoir dans un deuxième temps effectuer un asservissement du moteur.

Pour la commande en boucle ouverte nous avons crées deux nouvelles fonction dans le shell qui est la fonction "start" et la fonction "stop".
- La fonction "start" permet de fixer le rapport cyclique à 50%, ce qui correspond à une vitesse nulle et également à activer la génération de la PWM.
- La focntion "stop" permet de désactiver la génération de PWM et ainsi couper le moteur.
## Mesure du courant

1) Le courant que nous devons mesurer est le courant consommé par le moteur ainsi que le courant fournit par l'alimentation. 
Pour cela nous allons utiliser le composant GO10-SME présent sur la carte électronique.

2) Le capteur renvoie une tension de 50mV pour 1A mesuré.

3) La pins correspondant à la mesure du courant pour la phase U est la pin 27 (PA0) du connecteur J103.
   La pin correspondant à la musre du courant consommé par la phase V est la pin 23 (PB1) du connecteur J104.
   La pin correspondant à la mesure du courant fournit par l'alimentation est la pin 29 (PC2) du connecteur J103.


## Mesure de vitesse
 Le conposant qui sert à mesurer la vitesse est le MAX3097E. 
 L'information sur la vitesse est récupéré via la sonde tachimétrique du moteur, puis transmis à la carte via un bus CAN. Le signal passe ensuite dans le composant MAX3097E pour ensuite être envoyé dans le microprocesseur sur les pins PA6 (encodeur A), PA4 (encoder B) et PC8 (encodeur Z). 
