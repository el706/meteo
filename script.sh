
fich_data="fich2"
methode="--abr"


###### génération du fichier altitude ##################

rm temp1 temp2 temp3 temp4 temp5 final_altitude

./main.c "$methode" "$fich_data"  temp1

cut -d';' -f1,14 temp1 > temp2
##on repasse les numéro de station en nombre entiers , et on supprime les doublons 
paste -d ';' <(cut -d'.' -f1 temp2) <(cut -d';' -f2 temp2) |uniq > temp3
##on passe l'altitude en première colonnne du fichier
paste -d ';' <(cut -d';' -f2 temp3) <(cut -d';' -f1 temp3) > temp4
## on trie par altitude decroissante
./main "$methode"  temp4 temp5 '>'
##on repasse les numéros de station en premiere colone du fichier
paste -d ' ' <(cut -d';' -f2 temp5) <(cut -d';' -f1 temp5) |uniq > final_altitude 
 
###### resultat dans "final_altitude" ###########################



###### génération du fichier humidité ##################
rm temp1 temp2 temp3 temp4 temp5 final_humidite

./main "$methode" "$fich_data"  temp1
##on séléctionne les colonnes station , et humidite 
cut -d';' -f1,6 temp1 > temp2
##on repasse les numéro de station en nombre entiers , et on supprime les doublons 
paste -d ';' <(cut -d'.' -f1 temp2) <(cut -d';' -f2 temp2) |uniq > temp3
##on passe l'humidite en première colonnne du fichier
paste -d ';' <(cut -d';' -f2 temp3) <(cut -d';' -f1 temp3) > temp4
## on trie par humidite decroissante

./main "$methode"  temp4 temp5 '>'
##on repasse les numéros de station en premiere colone du fichier
paste -d ' ' <(cut -d';' -f2 temp5) <(cut -d';' -f1 temp5) |uniq > final_humidite
###### resultat dans "final_humidite" ###########################



########   génération tri par date+heure
rm temp1 temp2 temp3 tri_date_station
##on passe les dates en premiere colone
paste -d ';' <(cut -d';' -f2 "$fich_data") <(cut -d';' -f1 "$fich_data") <(cut -d';' -f3-16 "$fich_data")> temp1
##on ajoute en début de fichier les dates converties en chiffres #
paste -d';' <(paste -d '' <(cut -c1-4 temp1) <(cut -c6-7 temp1) <(cut -c9-10 temp1) <(cut -c12-13 temp1) <(cut -c15-16 temp1) <(cut -c18-19 temp1)) <(cat temp1) > temp2
##on tri par dates+heures croissantes
./main "$methode" temp2 temp3
##on supprime la colonne avec les dates converties en chiffres
cut -d';' -f2-17 temp3 > tri_date
############################### résultat dans tri_date ###############################
########   génération tri par date+heure+idstation
rm temp1 temp2 temp3 tri_date_station
##on passe les dates en premiere colone
paste -d ';' <(cut -d';' -f2 "$fich_data") <(cut -d';' -f1 "$fich_data") <(cut -d';' -f3-16 "$fich_data")> temp1
##on converti les dates+heures en chiffres #
paste -d';' <(paste -d '' <(cut -c1-4 temp1) <(cut -c6-7 temp1) <(cut -c9-10 temp1) <(cut -c12-13 temp1) <(cut -c15-16 temp1) <(cut -c18-19 temp1) <(cut -d';' -f2 temp1 ) ) <(cat temp1) > temp2
##on tri par dates+heures croissantes
./main "$methode" temp2 temp3
##on supprime la colonne avec les dates+id_station convertis en chiffres
cut -d';' -f2-17 temp3 > tri_date_station
######################## résultat dans tri_date_station #########################
