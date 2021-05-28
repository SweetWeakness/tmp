from pdf2image import convert_from_path
import tifffile
import numpy as np
import os


var_noises = 0.002


def add_noises(image):
    out = np.copy(image)
    amount = int(image.size[0] * image.size[1] * var_noises)
    y = np.random.randint(0, image.size[0], amount)
    x = np.random.randint(0, image.size[1], amount)
    coords = np.array([x, y]).T
    for coord in coords:
        out[coord[0], coord[1]] = [0, 0, 0]
    return out


# конвертируем pdf в jpeg
name = input("Введите имя файла:\n")
if os.path.exists(("./%s.pdf" % name)):
    images = convert_from_path(("./%s.pdf" % name), fmt="jpeg", dpi=300)
else:
    exit("Ошибка, файл с таким именем отсутствует.")

# удаляем результаты прерыдущей работы
if os.path.exists(("%s_result.tiff" % name)):
    os.remove(("%s_result.tiff" % name))

# добавляем шумы
noised_images = []
for image in images:
    noised_images.append(add_noises(image))

# сохраняем в TIFF
with tifffile.TiffWriter(("%s_result.tiff" % name)) as tiff:
    for image in noised_images:
        tiff.save(image,  compress=6)

print("done")
