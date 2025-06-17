import numpy as np
import gzip
import os
import struct

def load_images(path):
    with gzip.open(path, 'rb') as f:
        _, num_images, rows, cols = struct.unpack(">IIII", f.read(16))
        buf = f.read(rows * cols * num_images)
        data = np.frombuffer(buf, dtype=np.uint8).astype(np.float32) / 255.0
        return data.reshape(num_images, rows * cols)

def load_labels(path):
    with gzip.open(path, 'rb') as f:
        f.read(8)  # skip magic and number of labels
        buf = f.read()
        return np.frombuffer(buf, dtype=np.uint8)

def save_txt(images, labels, out_path):
    with open(out_path, 'w') as f:
        for img, lbl in zip(images, labels):
            f.write(f"{lbl} " + " ".join(map(str, img)) + "\n")

if __name__ == "__main__":
    images = load_images("data/raw/train-images-idx3-ubyte.gz")
    labels = load_labels("data/raw/train-labels-idx1-ubyte.gz")
    save_txt(images, labels, "data/processed/fashion_train.txt")
    print("Fashion-MNIST convertido a TXT correctamente.")
