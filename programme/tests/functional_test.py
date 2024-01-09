import random
import hashlib
import os
import lorem

filesSize = 10_000_000

def getHash(file_path):
    file = open(file_path, "rb")
    hash = hashlib.sha256(file.read()).hexdigest()
    file.close()
    return hash

def generateFile(file_path, function):
    file = open(file_path, "wb")
    function(file)
    file.close()
    return getHash(file_path)

def compress(file_path):
    originalHash = getHash(file_path)
    os.system(f"./programme/bin/huffman c {file_path}")
    os.remove(file_path)
    return os.path.getsize(f"{file_path}.huff")

def decompress(file_path):
    os.system(f"./programme/bin/huffman d {file_path}.huff")
    return (getHash(file_path), os.path.getsize(file_path))

def printResult(file_path, originalHash, compressedSize, decompressedHash, decompressedSize):
    print(f"{file_path} :")
    if (originalHash != decompressedHash):
        print(f"\t Error : Hashes are different : {originalHash} != {decompressedHash}")
        return
    if (decompressedSize == 0):
        print(f"\t Error : Decompressed file is empty")
        return
    else:
        print(f"\toriginal hash : {originalHash}")
        print(f"\tcompressed size : {compressedSize} bytes")
        print(f"\tdecompressed hash : {decompressedHash}")
        print(f"\tdecompressed size : {decompressedSize} bytes")
        print(f"\tcompression ratio : {round(compressedSize / decompressedSize * 100, 2)}%")
    print("--------------------------------------------------")

# - Fichier vide
originalHash = generateFile("empty", lambda file: None)
compressedSize = compress("empty")
decompressedHash, decompressedSize = decompress("empty")
printResult("empty", originalHash, compressedSize, decompressedHash, decompressedSize)

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
    for i in range(filesSize):
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