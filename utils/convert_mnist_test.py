import numpy as np
import struct
import gzip

def load_images(filename):
    with gzip.open(filename, 'rb') as f:
        magic, num, rows, cols = struct.unpack(">IIII", f.read(16))
        data = np.frombuffer(f.read(), dtype=np.uint8).reshape(num, rows * cols)
        return data / 255.0

def load_labels(filename):
    with gzip.open(filename, 'rb') as f:
        magic, num = struct.unpack(">II", f.read(8))
        return np.frombuffer(f.read(), dtype=np.uint8)

# Cargar test
images = load_images("../data/raw/t10k-images-idx3-ubyte.gz")
labels = load_labels("../data/raw/t10k-labels-idx1-ubyte.gz")

# Guardar
with open("../data/processed/fashion_test.txt", "w") as f:
    for img, label in zip(images, labels):
        f.write(f"{label} " + " ".join(map(str, img)) + "\n")
