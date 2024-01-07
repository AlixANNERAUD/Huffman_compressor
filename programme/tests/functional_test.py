

file = open("test", "wb")

for i in range(0, 10_000_000):
    file.write(bytes([i % (0x50)]))

file.close()

