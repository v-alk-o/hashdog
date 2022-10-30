# Détails d'implémentation

1. La T3C est stockée en mémoire sous la forme d'un arbre binaire ayant un hash comme valeur clé d'un noeud. Dans un fichier texte, chaque ligne est de la forme **\<hash\>:\<clair\>**. Cela permet d'identifier facilement le hash du mot en clair en séparant la ligne en 2 parties, à la première occurence du caractère **:** (le hash étant stocké sous la forme d'une chaine de caractères représentant ses octets en base hexadécimale et ne contenant donc pas ce caractère, à la différence d'un mot de passe éventuellement).

2. La lecture depuis un flux (l'entrée standard ou un fichier dans notre cas) est effectuée par la fonction `read_string_and_check_size`. Celle-ci utilise la fonction `fgets` pour se prémunir des vulnérabilités de type buffer overflow. Elle s'assure également que tout le buffer a été consommé par la lecture (ie. que la taille de la chaine de caractères utilisée pour le stockage de la lecture est supérieure ou égale à celle du buffer. Cette vérification est faite en recherchant le caractère de fin de ligne `'\n'` dans la chaine de caractère après l'appel à `fgets`. Si celui-ci est présent, cela signifie que tout le buffer a été consommé. Sinon, ce n'est pas le cas et on videra le buffer avec la fonction `flush_input_buffer`.
Cela permet in fine de ne pas traiter une ligne trop longue d'un dictionnaire ou d'un mot en clair entré par le flux d'entrée standard comme plusieurs lignes pour la génération de hash et de prévenir l'utilisateur de ce problème.  

3. La génération de hash se fait par la fonction `get_hash` qui utilise la fonction `EVP_Q_digest` de la libraire openssl. Celle-ci permet de générer un hash selon un algorithme passé en paramètre sous forme de chaine de caractères. Le programme gère ainsi autant d'algorithmes que la fonction `EVP_Q_digest`, avec par exemple md5, sha1, sha512, etc.

4. La taille maximale d'un mot en clair a été fixée arbitrairement à 1OO caractères. Celle d'un hash à 2*`EVP_MAX_MD_SIZE`. `EVP_MAX_MD_SIZE` est une macro définie dans le module `<openssl/evp.h>` qui indique la taille maximale en octet d'un hash. On la multiplie ici par 2, car on réprésente un hash sous forme hexadécimale (un octet étant représenté par 2 caractères hexadécimaux).

5. Pour quitter le programme alors qu'il attend une saisie de l'utilisateur par le flux d'entrée standard, il faut saisir **"quit please"**. Cette formule magique a été choisie car la wordlist **rockyou.txt** contenait déjà les mots de passe **"q"**, **"quit"** et **"exit"** et que les fonctions `generate` et `lookup` ont été conçus de manière à s'abstraire de l'origine du flux utilisé pour la lecture (et aussi car le respect c'est important).