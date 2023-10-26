import cv2
from google.colab import files
from google.colab.patches import cv2_imshow

uploaded = files.upload()
file_names = list(uploaded.keys())

if len(file_names) != 2:
    print("Por favor, carregue exatamente duas imagens para realizar operações AND e OR.")
else:
    image1 = cv2.imread(file_names[0])
    image2 = cv2.imread(file_names[1])

    cv2_imshow(image1)
    cv2_imshow(image2)

    if image1.shape == image2.shape:
        altura, largura, canais = image1.shape

        result_and = image1.copy()
        result_or = image1.copy()

        for i in range(altura):
            for j in range(largura):
                pixel1 = image1[i, j]
                pixel2 = image2[i, j]

                # Realizar a operação AND
                pixel_and = [min(pixel1[0], pixel2[0]), min(pixel1[1], pixel2[1]), min(pixel1[2], pixel2[2])]
                result_and[i, j] = pixel_and

                # Realizar a operação OR
                pixel_or = [max(pixel1[0], pixel2[0]), max(pixel1[1], pixel2[1]), max(pixel1[2], pixel2[2])]
                result_or[i, j] = pixel_or

        cv2_imshow(result_and)
        cv2_imshow(result_or)

        cv2.imwrite('Resultado_AND.jpg', result_and)
        cv2.imwrite('Resultado_OR.jpg', result_or)
    else:
        print("As duas imagens devem ter o mesmo tamanho para realizar operações AND e OR.")
