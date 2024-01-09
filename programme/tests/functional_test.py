import random

filesSize = 10_000_000

# - Fichier vide
emptyFile = open("empty", "wb")
emptyFile.close()

# - Fichier avec un unique caractère
file = open("unique", "wb")
for i in range(filesSize):
    file.write(bytes([1]))
file.close()

# - Fichier aléatoire
randomFile = open("random", "wb")
for i in range(filesSize):
    randomFile.write(random.randbytes(1))
randomFile.close()

# - Fichier équilibré
balancedFile = open("balanced", "wb")
for i in range(filesSize):
    balancedFile.write(bytes([i % (0xFF + 1)]))
balancedFile.close()

# - Fichier déséquilibré
unbalancedFile = open("test", "wb")
for i in range(filesSize / 256):
    for j in range(i % (0xFF + 1) + 1):
        unbalancedFile.write(bytes([i % (0xFF + 1)]))
unbalancedFile.close()

