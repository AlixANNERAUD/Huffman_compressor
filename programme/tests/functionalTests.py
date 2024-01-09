import random
import hashlib
import os
import lorem

filesSize = 10_000_000

# - Fonction qui retourne le hash d'un fichier
def getHash(file_path):
    file = open(file_path, "rb")
    hash = hashlib.sha256(file.read()).hexdigest()
    file.close()
    return hash

# - Fonction qui génère un fichier avec une fonction donnée
def generateFile(file_path, function):
    if (os.path.exists(file_path)):
        os.remove(file_path)
    file = open(file_path, "wb")
    function(file)
    file.close()
    return getHash(file_path)

# - Fonction qui compresse un fichier et retourne sa taille
def compress(file_path):
    originalHash = getHash(file_path)
    os.system(f"./programme/bin/huffman c {file_path}")
    return os.path.getsize(f"{file_path}.huff")

# - Fonction qui décompresse un fichier et retourne son hash et sa taille
def decompress(file_path):
    os.system(f"./programme/bin/huffman d {file_path}.huff")
    return (getHash(file_path), os.path.getsize(file_path))

# - Fonction qui affiche le résultat d'un test
def printResult(file_path, originalHash, compressedSize, decompressedHash, decompressedSize):
    print(f"{file_path} :")
    if (originalHash != decompressedHash):
        print(f"\t Error : Hashes are different : {originalHash} != {decompressedHash}")
    if (decompressedSize == 0):
        print(f"\t Decompressed file is empty")
    else:
        print(f"\tsize : {decompressedSize} -> {compressedSize} bytes ({round(compressedSize / decompressedSize * 100, 2)}%)")
    print("--------------------------------------------------")

# - Fichier vide
originalHash = generateFile("empty", lambda file: None)
compressedSize = compress("empty")
decompressedHash, decompressedSize = decompress("empty")
printResult("empty", originalHash, compressedSize, decompressedHash, decompressedSize)

# - File avec un seul caractère
originalHash = generateFile("single", lambda file: file.write(bytes([0])))
compressedSize = compress("single")
decompressedHash, decompressedSize = decompress("single")
printResult("single", originalHash, compressedSize, decompressedHash, decompressedSize)

# - Fichier avec un unique caractère
def generateUniqueFile(file):
    for i in range(filesSize):
        file.write(bytes([1]))

originalHash = generateFile("unique", generateUniqueFile)
compressedSize = compress("unique")
decompressedHash, decompressedSize = decompress("unique")
printResult("unique", originalHash, compressedSize, decompressedHash, decompressedSize)

# - Lorem ipsum
def generateLoremFile(file):
    for i in range(round(filesSize / 10)):
        file.write(bytes(lorem.get_word().encode("utf-8")))

originalHash = generateFile("lorem", generateLoremFile)
compressedSize = compress("lorem")
decompressedHash, decompressedSize = decompress("lorem")
printResult("lorem", originalHash, compressedSize, decompressedHash, decompressedSize)

# - Fichier aléatoire
def generateRandomFile(file):
    for i in range(filesSize):
        file.write(bytes([random.randint(0, 255)]))

originalHash = generateFile("random", generateRandomFile)
compressedSize = compress("random")
decompressedHash, decompressedSize = decompress("random")
printResult("random", originalHash, compressedSize, decompressedHash, decompressedSize)

# - Fichier équilibré
def generateBalancedFile(file):
    for i in range(filesSize):
        file.write(bytes([i % (0xFF + 1)]))

originalHash = generateFile("balanced", generateBalancedFile)
compressedSize = compress("balanced")
decompressedHash, decompressedSize = decompress("balanced")
printResult("balanced", originalHash, compressedSize, decompressedHash, decompressedSize)

# - Fichier déséquilibré
def generateUnbalancedFile(file):
    for i in range(round(filesSize / 256)):
        for j in range(i % (0xFF + 1) + 1):
            file.write(bytes([i % (0xFF + 1)]))

originalHash = generateFile("unbalanced", generateUnbalancedFile)
compressedSize = compress("unbalanced")
decompressedHash, decompressedSize = decompress("unbalanced")
printResult("unbalanced", originalHash, compressedSize, decompressedHash, decompressedSize)