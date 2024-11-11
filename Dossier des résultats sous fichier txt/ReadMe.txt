Pour visualiser les agrégats sous Gnuplot
1)	Télécharger un fichier txt que vous souhaitez visualiser
2)	Ouvir Gnuplot 
3)	Aller dans le répértoire où le téléchargement est réalisé sur Gnuplot par: File -> Change Directory
4)	Taper la commande: << plot "File Name.txt"  using 1:2:0 pt 7 palette >> pour les agrégats en 2D
5)	Taper la commande: << splot "File Name.txt" using 1:2:3:0 pt 7 palette >> pour les agrégats en 3D
