import matplotlib.pyplot as plt
import csv

fichier = open("/home/rachine/Documents/ENPC cours/ProjetSocGen/Cours/test.csv","rU")
cr = csv.reader(fichier)

abcisse = []
ordonnee = []
for row in cr:
    if len(abcisse)<1:
    	for value in row:
          abcisse = abcisse + [1+len(abcisse)]
          ordonnee = ordonnee + [value]

print(ordonnee)

plt.plot(abcisse,ordonnee)
plt.ylabel('Evolution du cours')
plt.show()
